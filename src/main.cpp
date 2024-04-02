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
#include "./FileWriter.cpp"


int main(int argc, char* argv[]) {

    FileReader prueba = FileReader();
    vector<vector<Pixel>> pict = prueba.leerArchivoBMP(argv[1]);
    int rows = pict.size(), cols = pict[0].size();

    FileWriter writer = FileWriter();
    writer.write(pict, argv[2], argv[3], argv[4]);
    
    return 0;
}