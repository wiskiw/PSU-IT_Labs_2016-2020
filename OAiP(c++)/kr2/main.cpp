#include <iostream>
#include <cstdlib>

using namespace std;

int main() {



    // Task 1
    /*
    int n, n1, n2;
    cout << "Range n1 < n < n2" << endl;
    cout << "Input n1, n2: ";
    cin >> n1;
    cin >> n2;
    cout << "n: ";
    cin >> n;

    int ll, lh;
    ll = n1 > n2 ? n2 : n1;
    lh = n1 > n2 ? n1 : n2;

    if (ll < n && n < lh) {
        cout << "true" << endl;
    } else {
        cout << "false" << endl;
    }
*/
    // Task 2
    /*
    setlocale(LC_ALL, "Russian");
    int numb;
    cin >> numb;
    cout << endl;
    switch (numb){
        case 0:
            cout << "Zero - Ноль";
            break;
        case 1:
            cout << "One - Один";
            break;
        case 2:
            cout << "Two - Два";
            break;
        case 3:
            cout << "Three - Три";
            break;
        case 4:
            cout << "Four - Четыре";
            break;
        case 5:
            cout << "Five - Пять";
            break;
        case 6:
            cout << "Six - Шесть";
            break;
        case 7:
            cout << "Seven - Семь";
            break;
        case 8:
            cout << "Eight - Восемь";
            break;
        case 9:
            cout << "Nine - Девять";
            break;
        default:
            cout << "Uncorrected numb.";
    }
    cout << endl;
*/


    // Task 3
    /*
    int result = 1;
    for (int i = 1; result <= 500; ++i) {
        result *= i;
    }
    cout << "Result = " << result << endl;
     */

    // Task 4
    /*
    int size;
    cout << "Input array size: " ;
    cin >> size;

    cout << "Input array: " ;
    float array[size];
    for (int i = 0; i < size; ++i) {
        cin >> array[i];
    }

    cout << "Back order: ";
    for (int j = size-1; j >= 0; j--) {
        cout << array[j] << " ";
    }
    cout << endl;
*/

    /*
    // Task 5
    int var;
    cout << "var: ";
    cin >> var;
    int *varPath = &var;
    cout << "path: " << varPath << endl;
    cout << "var(path): " << *varPath << endl;
*/

    system("pause");
    return 0;
}