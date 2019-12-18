#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>

using namespace std;


int main() {
    char fileName[50];
    printf("Filename(filename.txt): ");
    gets(fileName);
    ifstream fin(fileName);


    if (!fin.is_open()) { // если файл не открыт
        cout << "Cannot open the file!\n";
    } else {
        int sum = 0;
        char buff[500] = "not null";
        while (buff[0] != NULL) {
            fin.getline(buff, 500);
            for (int i = 0; i < strlen(buff); i++) {
                char c = buff[i];
                if (c == ' ') continue;
                sum += c - 48;
            }
        }
        cout << sum << endl;
    }
    system("pause");
    return 0;
}
