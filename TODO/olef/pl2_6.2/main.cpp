//Реализовать функцию, осуществляющую поиск в целочисленном массиве серии максимальной длины. 
//В качестве параметров передается массив и его размер. 
//Функция должна вернуть длину серии и позицию, с которой она начинается в массиве. 
//Используя разработанную функцию осуществить поиск в N массивах, введенных пользователем. 
//Если серий максимальной длины несколько, то только последнюю из них.

#include <iostream>
#include <cstdio>
#include <cstdlib>

using namespace std;

const char INCORRECT_INPUT[] = "Incorrect input!\n";

void ser(int *array, int size, int *maxLength, int *maxPosition) {
    int compareItem = array[0];
    int sLength = 0;
    int startPosition = 0;
    for (int i = 0; i < size +1 ; i++) {
        if (compareItem == array[i]) {
            sLength++;
        } else {
            // если серия закончилась
            compareItem = array[i];
            if (*maxLength <= sLength) {
                *maxLength = sLength;
                *maxPosition = startPosition;
            }
            sLength = 0;
            startPosition = i;
            i--;
        }
    }
}

int main() {
    // Member 23
    int begin;
    do {
        int size;
        cout << "array size: ";
        if (1 != scanf("%d", &size)) {
            cout << INCORRECT_INPUT;
            break;
        }
        int array[size];
        bool enterFlag = true;
        cout << "array: \n";
        for (int i = 0; i < size; i++) {
            if (1 != scanf("%d", &array[i])) {
                cout << INCORRECT_INPUT;
                enterFlag = false;
                break;
            }
        }
        if (!enterFlag) {
            break;
        }

        int maxLength = 0;
        int maxPosition = 0;
        ser(array, size, &maxLength, &maxPosition);

        cout << "max s-length: " << maxLength << endl;
        cout << "s-pos: " << maxPosition << endl;
        cout << "\n1 - continue\n0 - exit\n";
        cin >> begin;
        if (begin == 0) {
            return 0;
        } else if (begin != 1) {
            cout << INCORRECT_INPUT;
            break;
        }
    } while (begin);
    system("pause");
}

