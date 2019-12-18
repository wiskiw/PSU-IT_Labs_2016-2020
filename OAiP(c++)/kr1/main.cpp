#include <iostream>
#include <cstdlib>
#include <cstdio>

using namespace std;


int main() {
    // Вариант 1
    // Яблонский Андрей
    // 16 ИТ-3


    // task 1
    cout << "=== Task 1 ====================" << endl;

    char name1[256];
    scanf("%s", name1);
    cout << "Hello " << name1;



    //tack 2
    cout << endl << endl << "=== Task 2 ====================" << endl;

    cout << " _____" << endl;
    cout << "{~._.~}" << endl;
    cout << " ( Y )" << endl;
    cout << "()~*~()" << endl;
    cout << "(_)-(_)";



    //tack 3
    cout << endl << endl << "=== Task 3 ====================" << endl;

    int input3 = 0;
    scanf("%d", &input3);
    if (input3 > 0 && input3 < 255) {
        printf("%c", input3);
    } else {
        cout << "0 < int < 255 !";
    }



    //task 4
    cout << endl << endl << "=== Task 4 ====================" << endl;

    int a4 = 0;
    int b4 = 0;
    scanf("%o%o", &a4, &b4);
    int c4 = a4/b4;
    c4 = c4^a4;
    printf("%d", c4);



    //tack 5
    cout << endl << endl << "=== Task 5 ====================" << endl;

    int a5 = 0;
    int b5 = 0;
    int c5 = 0;
    cin >> a5 >> b5 >> c5;
    cout << (a5>c5?a5:c5)/(b5>c5?b5:c5) << endl << endl;

    system("pause");
    return 0;
}