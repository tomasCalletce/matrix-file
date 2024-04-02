#include<iostream> 

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include<assert.h>
#include <cmath>
#include <chrono>
#include <thread>
#include "./FileReader.cpp"


int main(int argc, char* argv[]) {

    FileReader prueba = FileReader();
    vector<vector<Pixel>> pict = prueba.leerArchivoBMP(argv[1]);
    int rows = pict.size(), cols = pict[0].size();
    
    return 0;
}