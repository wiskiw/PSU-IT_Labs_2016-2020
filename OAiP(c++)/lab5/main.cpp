#include <iostream>
#include <cstdlib>
#include <cstdio>

using namespace std;

int main() {

/*
    // Task 1
    int n = 0;
    cin >> n;
    int array[n];

    for (int i = 0; i < n; ++i) {
        int k = 1 + i*2;
        array[i] = k;
    }

    cout << "array[" << n << "] = { ";
    for (int j = 0; j < n; ++j) {
        cout << array[j] << " ";
    }
    cout << "}" << endl;
*/

/*
    // Task 2
    int n = 0;
    cout << "n=";
    cin >> n;
    cout << "array: " ;
    double array[n];
    for (int i = 0; i < n; ++i) {
        cin >> array[i];
    }

    double max = 0;
    int position = -1;
    for (int j = 0; j < n; ++j) {
        if (array[j]>max){
            max = array[j];
            position = j;
        }
    }
    cout << "max: " << max << endl;
    cout << "position: " << position << endl;
*/

/*
    // Task 3
    int n = 0;
    int x = 0;
    cout << "n=";
    cin >> n;

    cout << "x=";
    cin >> x;
    cout << "array: ";
    int array[n];
    for (int i = 0; i < n; ++i) {
        cin >> array[i];
    }


    for (int j = 0; j < n; ++j) {
        if (array[j] == x) {
            n--;
            for (int i = j; i < n; ++i) {
                array[i] = array[i + 1];
            }
            j--;
        }
    }
    cout << "array[" << n << "] = { ";
    for (int j = 0; j < n; ++j) {
        cout << array[j] << " ";
    }

    cout << "}" << endl;
*/



/*
    // Task 4
    int m = 0;
    int n = 0;
    int k = 0;
    cout << "m=";
    cin >> m;

    cout << "n=";
    cin >> n;

    cout << "k=";
    cin >> k;

    cout << "Matrix: " << endl;
    int matrix[m][n];
    for (int i = 0; i < m; ++i) {
        cout << "Line " << i + 1 << ": ";
        for (int j = 0; j < n; ++j) {
            cin >> matrix[i][j];
        }
    }

    for (int l = 0; l < n; ++l) {
        cout << matrix[k-1][l] << " ";
    }
*/



/*
    // Task 5
    int m = 0;
    int n = 0;
    cout << "m=";
    cin >> m;

    cout << "n=";
    cin >> n;

    cout << "Matrix: " << endl;
    int matrix[m][n];
    for (int i = 0; i < m; ++i) {
        cout << "Line " << i + 1 << ": ";
        for (int j = 0; j < n; ++j) {
            cin >> matrix[i][j];
        }
    }

    bool sym = true;
    if (m != n) {
        sym = false;
    }
    for (int i = 0; i < m && sym; ++i) {
        for (int j = 0; j < n; ++j) {
            if (matrix[i][j] != matrix[j][i]) {
                sym = false;
            }
        }

    }
    if (sym){
        cout << "symmetric"<< endl;
    } else {
        cout << "asymmetrical"<< endl;
    }
*/



    system("pause");
    return 0;
}