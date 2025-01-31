#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm> 

using namespace std;

int main() {
    ifstream keywordsFile("keywords.txt");
    if (!keywordsFile) {
        cerr << "Error: Unable to open keywords.txt" << endl;
        return 1;
    }

    vector<string> keywords;
    string line;
    while (getline(keywordsFile, line)) {
        keywords.push_back(line);
    }
    keywordsFile.close();

    FILE* fptr = fopen("samplecode.txt", "r");
    if (fptr == nullptr) {
        cerr << "Error: Unable to open source.txt" << endl;
        return 1;
    }

    char c;
    string word;
    while ((c = fgetc(fptr)) != EOF) {
        if (isspace(c)) { 
            if (find(keywords.begin(), keywords.end(), word) != keywords.end()) {
                cout << word << " is a keyword" << endl;
            }
            word = ""; 
        } else {
            word += c; 
        }
    }

    fclose(fptr);
    return 0;
}