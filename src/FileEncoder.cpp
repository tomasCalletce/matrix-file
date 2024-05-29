
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include<assert.h>
#include <cmath>
#include <chrono>
#include <thread>


#define d(x) cerr<<#x<<" "<<x<<"\n"

using namespace std;
//255, 100, 255
const vector<int> delta = {15, 255, 15};

class FileEncoder {
public:
    vector<vector<Pixel>> encode(vector<vector<Pixel>> &matrix){
        for(auto &row : matrix){
            for(auto &pix : row){
                pix = pix ^ delta;
            }
        }
        return matrix;
    }
    vector<vector<Pixel>> decode(vector<vector<Pixel>> &matrix){
        for(auto &row : matrix){
            for(auto &pix : row){
                pix = pix ^ delta;
            }
        }
        return matrix;
    }
};