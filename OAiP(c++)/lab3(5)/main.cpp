#include <iostream>
#include <cstdlib>
#include <cmath>

using namespace std;


void print(int a, int b) {
    if (a == 1) {
        switch (b) {
            case 0:
                cout << "  десять";
                break;
            case 1:
                cout << "  одинадцать";
                break;
            case 2:
                cout << "  двенадцать";
                break;
            case 3:
                cout << "  тринадцать";
                break;
            case 4:
                cout << "  четырнадцать";
                break;
            case 5:
                cout << "  пятнадцать";
                break;
            case 6:
                cout << "  шестнадцать";
                break;
            case 7:
                cout << "  семьнадцать";
                break;
            case 8:
                cout << "  восемьнадцать";
                break;
            case 9:
                cout << "  девятнадцать";
                break;
            default:;
        }
    } else {
        switch (a) {
            case 2:
                cout << "  двадцать";
                break;
            case 3:
                cout << "  тридцать";
                break;
            case 4:
                cout << "  сорок";
                break;
            case 5:
                cout << "  пятьдесят";
                break;
            case 6:
                cout << "  шестьдесят";
                break;
            case 7:
                cout << "  семьдесят";
                break;
            case 8:
                cout << "  восемьдесят";
                break;
            case 9:
                cout << "  девяносто";
                break;
            default:;
        }

        switch (b) {
            case 1:
                cout << "  одна";
                break;
            case 2:
                cout << "  две";
                break;
            case 3:
                cout << "  три";
                break;
            case 4:
                cout << "  четыре";
                break;
            case 5:
                cout << "  пять";
                break;
            case 6:
                cout << "  шесть";
                break;
            case 7:
                cout << "  семь";
                break;
            case 8:
                cout << "  восемь";
                break;
            case 9:
                cout << "  девять";
                break;
            default:;
        }
    }
}

int main() {
    // Task 5
    system("chcp 65001");
    system("CLS");

    double numb = 0;
    cin >> numb;

    // a1 a2 . b1 b2
    int a1, a2, b1, b2;
    a1 = ((int(numb)) / 10) % 10;
    a2 = (int(numb)) % 10;
    b1 = (int(round(numb * 10))) % 10;
    b2 = (int(round(numb * 100))) % 10;
    //cout << a1 << "_" << a2 << ".." << b1 << "_" << b2 << endl;


    cout << endl;
    print(a1, a2);
    if (a2 == 1) {
        cout << "  целая";
    } else {
        cout << "  целых";
    }
    cout << ",";

    if (b2 == 0) {
        if (b1 == 0) {
            cout << "  ноль  десятых";
        } else if (b1 == 1) {
            cout << "  одна  десятая";
        } else {
            print(0, b1);
            cout << "  десятых";
        }
    } else {
        print(b1, b2);
        if (b2 == 1) {
            cout << "  сотая";
        } else {
            cout << "  сотых";
        }
    }
    cout << endl;


    cout << endl;
    system("pause");
    return 0;
}