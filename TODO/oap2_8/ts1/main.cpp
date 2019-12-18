#include <iostream>
#include <cstdlib>
#include "StackList.h"

int main() {
    // Member 8

    StackList *stackList = newList();

    addItem(stackList, "Data 1");
    addItem(stackList, "Data 2");
    addItem(stackList, "Data 3");
    addItem(stackList, "Data 4");
    printList(stackList);


    system("pause");
    return 0;
}