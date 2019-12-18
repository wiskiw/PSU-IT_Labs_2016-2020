#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <cmath>

using namespace std;

int main() {
    // Number 4
    // Task 1
    char charC;
    scanf("%c", &charC);
    float floatC = float(charC);
    printf("%d", &floatC);
    cout << "\n\n";


    // Task 2
    int a = 0;
    int b = 0;
    printf("%s", "A=");
    scanf("%d", &a);
    printf("%s", "B=");
    scanf("%d", &b);
    printf("%s", "(a%b)|b = ");
    int res = ((a % b) | b);
    printf("%x", res);
    cout << "\n\n";


    // Task 3
    a = 10;
    b = 20;
    int c = 15;
    cout << (a < b ? a : b) * (a < c ? a : c);
    cout << "\n\n";


    // Task 4
    char charToCheck = 0;
    scanf("%c", &charToCheck);
    int charCode = int(charToCheck);
    if (charCode >= -128 && charCode <= 1){
        cout << 1 << endl;
    } else {
        cout << charCode << endl;
        cout << 0 << endl;
    }


    // Task 5
    int x5, y5;
    cin >> x5 >> y5;

    float a5, b5;
    a5 = (x5++ + y5 + x5 * y5) * 2;
    b5 = (pow(x5, 2) + pow(y5, 3)) * 3;
    cout << a5 / b5<< endl;


    system("pause");
    return 0;
}