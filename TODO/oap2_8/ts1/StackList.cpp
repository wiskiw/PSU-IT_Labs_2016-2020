//
// Created by WiskiW on 01.05.2017.
//

#include <malloc.h>
#include "StackList.h"
#include "console_io_lib/console_io_lib.cpp"

StackList *newList() {
    StackList *stackList = (StackList *) malloc(0);
    stackList->head = NULL;
    return stackList;
}

bool isEmpty(StackList *stackList) {
    return stackList->head == NULL;
}

// Основной метод StackList: добавление элемента
int addItem(StackList *stackList, Data data) {
    StackListItem *item = (StackListItem *) malloc(sizeof(StackListItem));
    if (!item) {
        return CODE_NO_MEMORY;
    }

    memset(item->data, '\0', 15);
    strcpy(item->data, data);// сохранение данных

    item->next = stackList->head;
    stackList->head = item;

    return CODE_SUCCESS;
}

// Основной метод StackList: извлечение элемента
int getItem(StackList *stackList, StackListItem **item) {
    if (stackList->head == NULL) {
        return CODE_EMPTY_LIST;
    }
    //StackListItem *out;
    *item = stackList->head;
    stackList->head = stackList->head->next;
    return CODE_SUCCESS;

}

// Основной метод StackList: чтение верхнего элемента
int readItem(StackList *stackList, StackListItem **item) {
    int res = getItem(stackList, item);
    if (res == CODE_SUCCESS) {
        addItem(stackList, (*item)->data);
    }
    return res;

}

void printList(StackList *stackList) {
    StackList *tempList = newList();
    StackListItem *item = NULL;

    if (isEmpty(stackList)) {
        printf(Cyan, "List is empty!\n");
        return;
    }

    printf(LightGray, "\t Stack List: \n");
    while (!isEmpty(stackList)) {
        getItem(stackList, &item);
        printf(LightGray, " data: '");
        printf("%s", item->data);
        printf(LightGray, "'\n");

        addItem(tempList, item->data);
        free(item);
    }
    while (!isEmpty(tempList)) {
        getItem(tempList, &item);
        addItem(stackList, item->data);
        free(item);
    }
}
