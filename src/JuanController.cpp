#include <string>
#include <fstream>
#include <vector>
#include <cstring> 
#include <tuple>
#define el '\n'
#define d(x) cerr<<#x<<" "<<x<<el
#define sz(a) (int) a.size()
using namespace std;


 struct Token {
    int distance;
    int length;
    char nextChar;
};


class JuanController {
public:
    string compFileName;
    const int windowSize = 4096; // Tamaño de la ventana deslizante
    const int lookaheadBuffer = 15; // Tamaño del buffer de búsqueda adelantada
    void  compress(string outputFileName, string input);
    Token readToken(ifstream& inputFile) {
        Token token;
        inputFile.read(reinterpret_cast<char*>(&token), sizeof(Token));
        return token;
    }


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

        string image = "";
        for (const auto& row : pict) {
            for (auto pixel : row) {
               image += pixel.toString();
               assert(pixel == Pixel::stringToPix(pixel.toString()));
            }
        }
        compress(outFile, image);
        outFile.close();
    }

    string decompress(vector<Token> tokens){
        string s = "";
        for(Token token : tokens){
            if(token.distance){
                s += s.substr(sz(s) - token.distance, token.length);
            }
            s += token.nextChar;
        }
        return s;
    }

    vector<Token> search(int &start, string input){
        int end = min(start + lookaheadBuffer, sz(input) );
        vector<Token> tokens;

        while (start < end) {
            int bestMatchDistance = 0;
            int bestMatchLength = 0;
            char bestMatchChar = input[start + bestMatchLength];

            for (int i = max(0, start - windowSize); i < start; ++i) {
                int j = start;
                int length = 0;
                while (j < end - 1 && i + length < start && input[i + length] == input[j]) {
                    ++j;
                    ++length;
                }

                if (length > bestMatchLength) {
                    bestMatchDistance = start - i;
                    bestMatchLength = length;
                    bestMatchChar = input[j];
                }
            }

            tokens.push_back({bestMatchDistance, bestMatchLength, bestMatchChar});
            start += (bestMatchLength + 1);
        }
        
        return tokens;
    }

    void  compress(ofstream &outFile, string input){
        int currentIndex = 0;
        // d(input);
        vector<Token> szs;
        while(currentIndex < sz(input)){
            vector<Token> tokens = search(currentIndex, input);
             for(Token token : tokens){
                szs.push_back(token);
                outFile.write(reinterpret_cast<const char*>(&token), sizeof(Token));
            }
        }
        
    }

    tuple<string, char*, char*, uint16_t, uint16_t> read(const char* pathname) {
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
        
        vector<Token> tokens;
        while (inFile.peek() != EOF) {
            Token token = readToken(inFile);
            tokens.push_back(token);
        }
        inFile.close();

        
        return make_tuple(decompress(tokens), id, date, rows, cols);
    }
};