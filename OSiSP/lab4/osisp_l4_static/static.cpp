#include <stdio.h>
#include <strings.h>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <cstdlib> 

using namespace std;

std::string getFileString(std::string fileName) {
    std::string fileStr;
    std::ifstream fin(fileName);
    while (!fin.eof()) {
        fileStr += fin.get();
    }
    fin.close();
    return fileStr;
}

std::string getLetters(std::string str) {
    int i = 0;
    int j = 0;
    std::string list;
    std::string letter;
    while (i < str.length()) {
        if (str[i] != str[i - 1]) {
            letter += str[i];
        }
        i++;
    }
    std::string c;
    while (j < letter.length()) {
        long num = std::count(str.begin(), str.end(), letter[j]);
        c += "Number of letter: " + std::to_string(num) + ".\tLetter - '" + letter[j] + "'\n";
        j++;
    }
    return c;
}

extern int hello(std::string nameFile){
	string str = getFileString(nameFile);
	std::sort(str.begin(), str.end());
	std::cout << getLetters(str) << std::endl;
	return 0;
}


