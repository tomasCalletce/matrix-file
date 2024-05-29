#include <string>
#include <fstream>
#include <vector>
#include <cstring> 
#include <tuple>

using namespace std;

class JuanController {
public:
    void write(const std::vector<std::vector<Pixel>>& pict, const char* fileName, const char* id, const char* date) {
        std::ofstream outFile(fileName, std::ios::binary);
        if (!outFile) {
            throw std::runtime_error("Failed to open file for writing");
        }

        uint16_t rows = static_cast<uint16_t>(pict.size());
        outFile.write(reinterpret_cast<const char*>(&rows), sizeof(rows));

        uint16_t cols = pict.empty() ? 0 : static_cast<uint16_t>(pict[0].size());
        outFile.write(reinterpret_cast<const char*>(&cols), sizeof(cols));

        outFile.write(id, 8);

        outFile.write(date, 20);

        for (const auto& row : pict) {
            for (const auto& pixel : row) {
                outFile.write(reinterpret_cast<const char*>(&pixel.blue), sizeof(pixel.blue));
                outFile.write(reinterpret_cast<const char*>(&pixel.green), sizeof(pixel.green));
                outFile.write(reinterpret_cast<const char*>(&pixel.red), sizeof(pixel.red));
            }
        }

        outFile.close();
    }
    
    tuple<vector<vector<Pixel>>, char*, char*> read(const char* pathname) {
        std::ifstream inFile(pathname, std::ios::binary);
        if (!inFile) {
            throw std::runtime_error("Failed to open file for reading");
        }

        uint16_t rows;
        inFile.read(reinterpret_cast<char*>(&rows), sizeof(rows));

        uint16_t cols;
        inFile.read(reinterpret_cast<char*>(&cols), sizeof(cols));

        char* id = new char[9]; 
        inFile.read(id, 8);
        id[8] = '\0'; 

        char* date = new char[21]; 
        inFile.read(date, 20);
        date[20] = '\0'; 

        vector<vector<Pixel>> matrix(rows, vector<Pixel>(cols));
        for (auto& row : matrix) {
            for (auto& pixel : row) {
                inFile.read(reinterpret_cast<char*>(&pixel.blue), sizeof(pixel.blue));
                inFile.read(reinterpret_cast<char*>(&pixel.green), sizeof(pixel.green));
                inFile.read(reinterpret_cast<char*>(&pixel.red), sizeof(pixel.red));
            }
        }

        inFile.close();

        return make_tuple(matrix, id, date);
    }
};