#include <iostream>
#include <cstdlib>
#include <afxres.h>
#include <math.h>

using namespace std;

int main() {

    // Task 1
    /*
    float a, b, c;
    cin >> a >> b >> c;
    cout << (a > c ? a : c) / (b > c ? b : c) << endl;
    */


    // Task 2
    /*
    int a, b;
    cin >> a >> b;
    cout << "a % b = 0 ?     ";
    if (a % b == 0) {
        cout << "true" << endl;
    } else {
        cout << "false" << endl;
    }
    */


    // Task 3
    /*
    int numb;
    cin >> numb;
    cout << endl;
    switch (numb){
        case 0:
            cout << "Zero";
            break;
        case 1:
            cout << "One";
            break;
        case 2:
            cout << "Two";
            break;
        case 3:
            cout << "Three";
            break;
        case 4:
            cout << "Four";
            break;
        case 5:
            cout << "Five";
            break;
        case 6:
            cout << "Six";
            break;
        case 7:
            cout << "Seven";
            break;
        case 8:
            cout << "Eight";
            break;
        case 9:
            cout << "Nine";
            break;
        default:
            cout << "Uncorrected numb.";
    }
    cout << endl;
    */


    // Task 4
    const double exp = 2.718281;
    int a, b;
    cin >> a >> b;
    cout << endl;
    int tc = a * b;
    if (0.5 < tc && tc < 10) {
        cout << pow(exp, (abs(a) - abs(b))) << endl;
    } else if (0.1 < tc && tc < 0.5) {
        cout << sqrt(abs(a - b)) << endl;
    } else {
        cout << 2 * pow(b, 2) << endl;
    }

    system("pause");
    return 0;
}