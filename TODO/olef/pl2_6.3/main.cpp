//Реализовать функцию поиска двух целочисленных значений наиболее близких к значению К,
//среди всех переданных в качестве параметров.
//Значение K передается в параметрах, функция должна вернуть два значения.
//При реализации функции использовать механизм передачи неопределенного числа параметров. 

#include <iostream>
#include <cmath>
#include <cstdio>
#include <cstdarg>
#include <complex>
#include <limits.h>

const char INCORRECT_INPUT[] = "Incorrect input!\n";

using namespace std;

void search(int *k1, int *k2, int k, int n, ...) {
    va_list args;
    *k1 = INT_MAX;
    *k2 = INT_MAX;

    int dif = 0, cur = 0;
    va_start (args, n);
    for (; n - 1 > 0; n = n - 2) {
        cur = va_arg(args, int);
        dif = (int) abs(k - cur);
        if (dif != 0 && dif < abs(k - *k1)) {
            *k1 = cur;
        }
        cur = va_arg(args, int);
        if (dif == 0) {
            // если первый элемент равен k, приравниаем его к следующему
            *k1 = cur;
        }
        dif = (int) abs(k - cur);
        if (dif == 0) {
            *k2 = *k1; // если второй элемент равен k
        } else if (dif < abs(k - *k2)) {
            *k2 = cur;
        }
    }

    if (n == 1) {
        if (*k1 == *k2 && *k1 == INT_MAX) {
            // если список размера 1
            // или состоит из элементов равных k
            // или состоит из элементов равных INT_MAX
            *k1 = va_arg(args, int);
            *k2 = *k1;
        } else {
            cur = va_arg(args, int);
            dif = (int) abs(k - cur);
            // поиск найденного элемента, который дальше от k
            // сравниваем этот элемент с последним оставшимся в списке
            if (abs(k - *k1) > abs(k - *k2)) {
                if (dif != 0 && dif < abs(k - *k1)) {
                    *k1 = cur;
                }
            } else {
                if (dif != 0 && dif < abs(k - *k2)) {
                    *k2 = cur;
                }
            }
        }
    }
    va_end(args);
}



int main() {
    int begin;
    do {
        int k;
        cout << "input k: ";
        if (1 != scanf("%d", &k)) {
            cout << INCORRECT_INPUT;
            break;
        }

        int n = 5; // длинна массива значений
        int a[n];
        bool enter_flag = true;
        cout << "input params: \n";
        for (int i = 0; i < n; i++) {
            if (1 != scanf("%d", &a[i])) {
                cout << INCORRECT_INPUT;
                enter_flag = false;
                break;
            }
        }
        if (!enter_flag) {
            break;
        }

        int k1 = 0;
        int k2 = 0;
        search(&k1, &k2, k, n, a[0], a[1], a[2], a[3], a[4], a[5]);

        cout << "first k: " << k1 << endl;
        cout << "second k: " << k2 << endl;
        cout << "\n1 - continue\n0 - exit\n";
        cin >> begin;
        if (begin != 0 && begin != 1) {
            cout << INCORRECT_INPUT;
            break;
        }
    } while (begin);
}

