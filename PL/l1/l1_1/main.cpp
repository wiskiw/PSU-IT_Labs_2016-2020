#include <iostream>
#include <cstdlib>
#include <cstdio>
#include "list.h"

void newQueue();

void addItem();

void removeItem();

void printQueue();

void clearQueue();

using namespace std;

int printMenu() {
    printf("1. Create queue\n");
    printf("2. Add item\n");
    printf("3. Remove item\n");
    printf("4. Print queue\n");
    printf("5. Clear queue\n");
    printf("6. Exit\n");
    printf("> ");

    int res = 0;
    if (scanf("%d", &res) != 1 || (res < 1 || res > 6)) {
        system("cls");
        printf("Incorrect input! Try again:\n");
        printMenu();
    }
    return res;
}

int main() {
    while (true) {
        switch (printMenu()) {
            case 1:
                newQueue();
                break;
            case 2:
                addItem();
                break;
            case 3:
                removeItem();
                break;
            case 4:
                printQueue();
                break;
            case 5:
                clearQueue();
                break;
            default:
                return 0;
        }
    }
}

void clearQueue() {

}

void printQueue() {

    system("pause");
}

void removeItem() {

}

void addItem() {

}

void newQueue() {

}
