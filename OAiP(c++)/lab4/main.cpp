#include <iostream>
#include <cstdlib>

using namespace std;

int main() {


/*
    // Task 1
    int x;
    cin >> x;
    int sum = 0;
    for (int i = 0; i <= 5; ++i) {
        sum = sum + x + 7 * i;
    }
    cout << "result=" << sum << endl;
*/


/*
    // Task 2
    int dayNumb = 0;
    cin >> dayNumb;
    while (dayNumb < 250){
        dayNumb = dayNumb + 15;
    }
    cout << "=" << dayNumb << endl;
*/

/*
    // Task 3
    int n = 14;
    cin >> n;
    int f1 = 1;
    int f2 = 2;
    for (int j = 0; j < n; ++j) {
        int toOut = f1 + f2;
        f1 = f2;
        f2 = toOut;
        cout << toOut << "   ";
    }
    cout << endl;
*/

/*
    // Task 4
    int n = 12354;
    cin >> n;
    int count = 0;
    int sum = 0;
    while (n != 0){
        count++;
        sum = sum + n % 10;
        n = n / 10;
    }
    cout << "count: " << count << endl;
    cout << "sum: " << sum << endl;
*/

/*
    // Task 5
    int n = 0;
    cin >> n;
    int max = n;
    while (n != 0) {
        cin >> n;
        max = max < n ? n : max;
    }
    cout << "max: " << max << endl;
*/
    system("pause");
    return 0;
}