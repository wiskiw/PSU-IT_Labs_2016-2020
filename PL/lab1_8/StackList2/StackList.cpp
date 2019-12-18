//
// Created by WiskiW on 01.05.2017.
//

#include <malloc.h>
#include <memory.h>
#include <cstring>
#include <cstdio>
#include "StackList.h"


// Основной метод StackList: создание списка
StackList *newList() {
    StackList *stackList = (StackList *) malloc(0);
    stackList->head = nullptr;
    return stackList;
}

// Основной метод StackList: удаление списка
int clearList(StackList *stackList) {
    StackListItem *item;
    while (getItem(stackList, &item, 0) == CODE_SUCCESS) {
        free(item);
    }
    return CODE_SUCCESS;
}

bool isEmpty(StackList *stackList) {
    return stackList->head == nullptr;
}

// Основной метод StackList: добавление элемента
int addItem(StackList *stackList, Data data) {
    StackListItem *item = (StackListItem *) malloc(sizeof(StackListItem));
    if (!item) {
        return CODE_NO_MEMORY;
    }

    item->data = data;
    //memset(item->data, '\0', 15);
    //strcpy(item->data, data);// сохранение данных

    item->next = stackList->head;
    stackList->head = item;

    return CODE_SUCCESS;
}

int addItem(StackList *stackList, Data data, int index) {
    if (index < 0) {
        return CODE_OUT_OF_BORDER;
    }
    if (index == 0) {
        return addItem(stackList, data);
    }

    StackList *tempList = newList();
    StackListItem *tempItem;
    for (int i = 0; i < index; i++) {
        if (getItem(stackList, &tempItem, 0) != CODE_SUCCESS) {
            clearList(tempList);
            return CODE_OUT_OF_BORDER;
        }
        addItem(tempList, tempItem->data);
    }

    addItem(stackList, data);

    for (int j = 0; j < index; j++) {
        getItem(tempList, &tempItem, 0);
        addItem(stackList, tempItem->data);
    }
    clearList(tempList);
    return CODE_SUCCESS;
}

// Основной метод StackList: извлечение элемента
int getItem(StackList *stackList, StackListItem **item) {
    if (stackList->head == nullptr) {
        return CODE_EMPTY_LIST;
    }
    //StackListItem *out;
    *item = stackList->head;
    stackList->head = stackList->head->next;
    return CODE_SUCCESS;
}

// извлечение элемента по индексу от головы
int getItem(StackList *stackList, StackListItem **item, int index) {
    if (index < 0) {
        return CODE_OUT_OF_BORDER;
    }
    if (index == 0) {
        return getItem(stackList, item);
    }

    StackList *tempList = newList();
    StackListItem *tempItem;
    index++;
    for (int i = 0; i < index; i++) {
        if (getItem(stackList, &tempItem) != CODE_SUCCESS) {
            while (!isEmpty(tempList)) {
                getItem(tempList, &tempItem);
                addItem(stackList, tempItem->data);
            }
            return CODE_OUT_OF_BORDER;
        }
        addItem(tempList, tempItem->data);
    }
    getItem(tempList, item);
    for (int j = 0; j < index - 1; j++) {
        getItem(tempList, &tempItem);
        addItem(stackList, tempItem->data);
    }
    clearList(tempList);
    return CODE_SUCCESS;
}

int removeItem(StackList *stackList, int index) {
    StackListItem *item;
    int code = getItem(stackList, &item, index);
    if (code == CODE_SUCCESS) {
        free(item);
    }
    return code;
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
    StackListItem *item = nullptr;

    if (isEmpty(stackList)) {
        printf("List is empty!\n");
        return;
    }

    printf("\t Stack List: \n");
    while (!isEmpty(stackList)) {
        getItem(stackList, &item);
        printf(" data: '");
        printf("%d", item->data);
        printf("'\n");

        addItem(tempList, item->data);
        free(item);
    }
    while (!isEmpty(tempList)) {
        getItem(tempList, &item);
        addItem(stackList, item->data);
        free(item);
    }
}
