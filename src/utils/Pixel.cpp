
#include <vector>

using namespace std;

struct Pixel {
    unsigned char blue;
    unsigned char green;
    unsigned char red;

    Pixel(){}
    Pixel(unsigned char blue,
    unsigned char green,
    unsigned char red):blue(blue), green(green), red(red){}
    Pixel operator^(vector<int> a){
        return Pixel{((int)blue ^ a[0]), ((int)green ^ a[1]), ((int)red ^ a[2])};
    }
    
    // Pixel operator^(vector<int> a){
    //     return {((int)blue - a[0] + 256) % 256, ((int)green - a[1] + 256)%256, ((int)red - a[2] + 256)%256};
    // }
    string getString(){
        
    }
};