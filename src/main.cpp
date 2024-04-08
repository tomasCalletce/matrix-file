
#include<bits/stdc++.h>
#include <string>
#include <chrono>
#include <thread>


#include "./BMPController.cpp"
#include "./JuanController.cpp"

using namespace std;
int main(int argc, char* argv[]) {
    
    /***
     * ENCODE
     * ./A [TIPO] [NOMBRE_ARCHIVO_LECTURA] [NOMBRE_ARCHIVO_ESCRITURA] [ID] [DATE]
     * ./A encode ../img/raw/boat.bmp ../img/encoded/compressedImg.juan 10101 2024-04-07T23:09:15Z 
     * 
     * 
     * DECODE
     * ./A [TIPO] [NOMBRE_ARCHIVO_COMPRIMIDO] [NOMBRE_ARCHIVO_RAW]
     * ./A decode ../img/encoded/compressedImg.juan ../img/raw/boat2.bmp
    */
    BMPController bmpController = BMPController();
    JuanController juanController = JuanController();
    if(argv[1][0] == 'e'){
        vector<vector<Pixel>> pict = bmpController.leerArchivoBMP(argv[2]);
        int rows = pict.size(), cols = pict[0].size();
        juanController.write(pict, argv[3], argv[4], argv[5]);
    }else{
        auto [matrix, id, date] = juanController.read(argv[2]);
        bmpController.guardarMatrizEnBMP(argv[3],matrix);
    }
    return 0;
}