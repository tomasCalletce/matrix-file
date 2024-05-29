#include <iostream>
#include <string>

#include<bits/stdc++.h>

#define el '\n'
#define d(x) cerr<<#x<<" "<<x<<el
#define sz(a) (int) a.size()
using namespace std;

 struct Token {
    int distance;
    int length;
    char nextChar;
};

struct LZ77{
    string compFileName;
    const int windowSize = 4096; // Tamaño de la ventana deslizante
    const int lookaheadBuffer = 15; // Tamaño del buffer de búsqueda adelantada
    LZ77(){}
    // LZ77(string compFileName): compFileName(compFileName){}


    Token readToken(ifstream& inputFile) {
        Token token;
        inputFile.read(reinterpret_cast<char*>(&token), sizeof(Token));
        return token;
    }

    vector<Token> readFile(string fileName) {
        ifstream inputFile(fileName, ios::binary);
        vector<Token> tokens;
        while (inputFile.peek() != EOF) {
            Token token = readToken(inputFile);
            tokens.push_back(token);
        }
        inputFile.close();
        return tokens;
    }

    void  compress(string outputFileName, string input){
         ofstream outputFile(outputFileName, ios::binary);
        int currentIndex = 0;
        // d(input);
        vector<Token> szs;
        while(currentIndex < sz(input)){
            vector<Token> tokens = search(currentIndex, input);
             for(Token token : tokens){
                szs.push_back(token);
                outputFile.write(reinterpret_cast<const char*>(&token), sizeof(Token));
            }
        }
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
};

