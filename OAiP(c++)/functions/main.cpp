#include <iostream>
#include <cstdlib>

using namespace std;

int textFunction(int);


int main() {

    cout << "Hello, World!" << std::endl;


    textFunction(0);
    system("pause");
    return 0;
}

int textFunction(int a = 2) {
    cout << "a=" << a << endl;
    return 0;
}
