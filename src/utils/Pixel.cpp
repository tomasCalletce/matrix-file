#include <vector>
#include <string>
#define d(x) cerr<<#x<<" "<<x<<endl

using namespace std;
struct Pixel {
    unsigned char blue;
    unsigned char green;
    unsigned char red;

    Pixel() {}
    Pixel(unsigned char blue, unsigned char green, unsigned char red)
        : blue(blue), green(green), red(red) {}

    Pixel operator^(vector<int> a) {
        return Pixel{((int)blue ^ a[0]), ((int)green ^ a[1]), ((int)red ^ a[2])};
    }

    bool operator==(Pixel pix){
        return blue == pix.blue &&  green == pix.green && red == pix.red;
    }
    

    string toString() {
        string result;
        result += static_cast<char>(blue);
        result += static_cast<char>(green);
        result += static_cast<char>(red);

        return result;
    }

    static Pixel stringToPix(string pixel) {
        return Pixel(
            static_cast<unsigned char>(pixel[0]),
            static_cast<unsigned char>(pixel[1]),
            static_cast<unsigned char>(pixel[2])
        );
    }

    static vector<vector<Pixel>> toMatrix(string text, int rows, int cols){
        assert(text.size() % 3 == 0);
        vector<vector<Pixel>> matrix(rows, vector<Pixel> (cols));
        for(int i = 0, k = 0; i < rows; ++i){
            for(int j = 0; j < cols && k < text.size(); ++j, k+=3){
                matrix[i][j] = stringToPix(text.substr(k,3));
            }
        }
        return matrix;
    }
};
