#include<iostream> 

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include<assert.h>
#include <cmath>
#include <chrono>
#include <thread>
// #include "./utils/Pixel.cpp"


#include "./BMPController.cpp"
#include "./JuanController.cpp"

using namespace std;
int main(int argc, char* argv[]) {
    // PARA CORRER
    //./A [NOMBRE_ARCHIVO_LECTURA] [NOMBRE_ARCHIVO_ESCRITURA] [ID] [DATE]
    //./A ../img/raw/boat.bmp ../img/encoded/compressedImg.juan 10101 2024-04-07T23:09:15Z

    BMPController prueba = BMPController();
    vector<vector<Pixel>> pict = prueba.leerArchivoBMP(argv[1]);
    int rows = pict.size(), cols = pict[0].size();

    JuanController writer = JuanController();
    writer.write(pict, argv[2], argv[3], argv[4]);
    
    return 0;
}