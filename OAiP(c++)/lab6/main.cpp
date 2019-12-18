

#include <cstdlib>
#include <iostream>
#include <time.h>

using namespace std;

int main() {
    /*

        &переменная - вернет адресс переменной
        *указатель - вернет значение переменной по указателю

     a) double
     b) char
     */

/*


    // Task 1
    double a;
    cin >> a;
    double *ptrA = &a;
    cout << "ptr: " << ptrA << endl;
    cout << "var: " << *ptrA << endl;





    /*
    // Task 2
    char x;
    cin >> x;
    char *p1 = &x;
    char *p2 = &x;
    char *p3 = &x;
    char *p4 = &x;
    cout << "n1: " << *(p1++) << endl;
    cout << "n2: " << (*p2)++ << endl;
    cout << "n3: " << ++(*p3) << endl;
    cout << "n4: " << *(++p4) << endl;
     */




/*
    // Task 3
    double *ptrA;
    char *ptrB;
    double x;
    cin >> x;
    ptrA = &x;

    // 1)
    cout << "var a: " << *ptrA << endl;
    cout << "var b: " << *ptrB << endl;
    cout << "ptr a: " << ptrA << endl;
    cout << "ptr  b: " << ptrA << endl;
    cout << "==============" << endl;

    //2)
    ptrB = (char *) ptrA;
    cout << "var a: " << *ptrA << endl;
    cout << "var b: " << *ptrB << endl;
    cout << "ptr a: " << ptrA << endl;
    cout << "ptr  b: " << ptrA << endl;
*/




    // Task 4
    srand(time(NULL));

    double array[10];
    double *ptr;
    ptr = array;
    for (int i = 0; i < 10; i++) {
        *(ptr++) = rand() % 101 - 50;
    }

    ptr = array;
    double min = 0;
    for (int j = 0; j < 10; j++) {
        double el = *(ptr++);
        cout << j+1 << ") " << el << endl;
        min = el < min ? el : min;
    }
    cout << "min: " << min << endl;





    system("pause");
    return 0;
}