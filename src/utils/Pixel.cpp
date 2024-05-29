#include <vector>
#include <string>

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

    static std::string pictToString(const std::vector<std::vector<Pixel>>& pict) {
        std::string result;
        for (const auto& row : pict) {
            for (const auto& pixel : row) {
                result += static_cast<char>(pixel.blue);
                result += static_cast<char>(pixel.green);
                result += static_cast<char>(pixel.red);
            }
        }
        return result;
    }
};