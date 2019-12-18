#include <iostream>
#include <fstream>

const static std::string PATH = "file.txt";
using namespace std;


string readFileContentCpp(string fileName) {
    ifstream file;
    file.open(fileName);
    char lineBuffer[1000];
    string resultContent;
    if (file.is_open()) {
        while (!file.eof()) {
            file.getline(lineBuffer, sizeof(lineBuffer));
            resultContent.append(lineBuffer).append("\n");
        }
        return resultContent;
    } else {
        return "";
    }
}

string readFileContentC(string fileName) {
    FILE *file = fopen(fileName.c_str(), "r");
    char lineBuffer[1000];
    string resultContent;

    while (!feof(file)) {
        fgets(lineBuffer, sizeof(lineBuffer), file);
        //resultContent += lineBuffer;
        resultContent.append(lineBuffer);
    }
    fclose(file);
    return resultContent;
}

int main() {
    cout << "File: " << PATH << endl;
    cout << "=================================" << endl;
    cout << readFileContentC(PATH) << endl;
    return 0;

}
