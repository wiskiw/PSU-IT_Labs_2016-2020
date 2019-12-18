#include <stdio.h>
#include <strings.h>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <cstdlib> 

// 3) Вывод всех символов и их количество встречаемых в текстом файле;

using namespace std;

#define CHAR_LOG true
#define TIME_LOG true

string getFileContent(const string &filePath) {
    ifstream myReadFile;
    myReadFile.open(filePath);
    char output[1000];
    string resultContent;
    if (myReadFile.is_open()) {
        while (!myReadFile.eof()) {
            myReadFile >> output;
            resultContent.append(output);
        }
    } else {
        cout << "error\n";
    }
    myReadFile.close();
    return resultContent;
}

long getCharIncludesCount(const string dataString, char c) {
    return count(dataString.begin(), dataString.end(), c);
}


void syncSearch(string fileContent) {
    for (int i = 32; i < 127; ++i) {
        char c = (char) i;
        long count = getCharIncludesCount(fileContent, c);
        if (CHAR_LOG && count > 0) {
            printf("'%c' - %li\n", c, count);
        }
    }
}

extern "C" int hello() {
	string fileContent = getFileContent("file1.txt");
	syncSearch(fileContent);
	return 0;
}
