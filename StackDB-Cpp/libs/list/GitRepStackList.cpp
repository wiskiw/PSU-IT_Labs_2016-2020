//
// Created by WiskiW on 01.05.2017.
//

#include <malloc.h>
#include <cstring>
#include <console_io_lib/console_io_lib.h>
#include <git_rep/git_rep_io.h>
#include "GitRepStackList.h"
#include "../../preferences.h"
#include "../../codes.h"


// Основной метод StackList: создание списка
StackList *newList() {
    StackList *stackList = (StackList *) malloc(0);
    stackList->head = NULL;
    return stackList;
}

// Основной метод StackList: удаление списка
void freeList(StackList *stackList) {
    StackListItem *item;
    while (getItem(stackList, &item, 0) == 0) {
        free(item);
    }
}

void cleanList(StackList *stackList) {
    while (!isEmpty(stackList)) {
        removeItem(stackList, 0);
    }
}

bool isEmpty(StackList *stackList) {
    if (stackList == NULL) {
        return true;
    }
    //printf("isEmpty test\n");
    if (stackList->head == NULL) {
        return true;
    }

    return false;
    //return stackList == NULL || stackList->head == NULL;
}

// Основной метод StackList: добавление элемента
int addItem(StackList *stackList, GitRep data) {
    StackListItem *item = (StackListItem *) malloc(sizeof(StackListItem));
    if (!item) {
        return CODE_NO_MEMORY;
    }
    item->data = data;

    item->next = stackList->head;
    stackList->head = item;

    return 0;
}

int addItem(StackList *stackList, GitRep data, int index) {
    if (index == 0) {
        return addItem(stackList, data);
    }
    if (index < 0) {
        return CODE_OUT_OF_BORDER;
    }
    int res = 0;
    StackList *tempList = newList();
    StackListItem *tempItem;
    int size = 0;
    for (; size < index; size++) {
        if (getItem(stackList, &tempItem, 0) != 0) {
            // если выход за пределы списка
            res = CODE_ADDED_TO_END;
            break;
        }
        addItem(tempList, tempItem->data);
    }
    addItem(stackList, data);
    for (int j = 0; j < size; j++) {
        getItem(tempList, &tempItem, 0);
        addItem(stackList, tempItem->data);
    }
    freeList(tempList);
    return res;
}

// Основной метод StackList: извлечение элемента
int getItem(StackList *stackList, StackListItem **item) {
    if (stackList->head == NULL) {
        return CODE_EMPTY_LIST;
    }
    //StackListItem *out;
    *item = stackList->head;
    stackList->head = (*item)->next;
    (*item)->next = NULL;
    return 0;
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
    int res = 0;
    int size = 0;
    for (; size < index; size++) {
        if (getItem(stackList, &tempItem) != 0) {
            res = CODE_OUT_OF_BORDER;
            break;
        }
        addItem(tempList, tempItem->data);
    }
    getItem(tempList, item);
    for (int j = 0; j < size - 1; j++) {
        getItem(tempList, &tempItem);
        addItem(stackList, tempItem->data);
    }
    freeList(tempList);
    return res;
}

int removeItem(StackList *stackList, int index) {
    StackListItem *item;
    int code = getItem(stackList, &item, index);
    if (code == 0) {
        //free(item);
    }
    return code;
}

// Основной метод StackList: чтение верхнего элемента
int readItem(StackList *stackList, StackListItem **item) {
    int res = getItem(stackList, item);
    if (res == 0) {
        addItem(stackList, (*item)->data);
    }
    return res;

}

int readItem(StackList *stackList, StackListItem **item, int index) {
    if (index < 0) {
        return CODE_OUT_OF_BORDER;
    }
    if (index == 0) {
        return readItem(stackList, item);
    }

    StackList *tempList = newList();
    index++;
    int res = 0;
    int size = 0;
    for (; size < index; size++) {
        if (getItem(stackList, item) != 0) {
            res = CODE_OUT_OF_BORDER;
            break;
        }
        addItem(tempList, (*item)->data);
    }
    StackListItem *tempItem;
    for (int j = 0; j < size; j++) {
        getItem(tempList, &tempItem);
        addItem(stackList, tempItem->data);
    }
    freeList(tempList);
    return res;
}

int printList(StackList *stackList) {
    StackList *tempList = newList();
    StackListItem *item = NULL;

    if (isEmpty(stackList)) {
        return CODE_EMPTY_LIST;
    }

    printTableHeader();

    int i = 0;
    while (!isEmpty(stackList)) {
        getItem(stackList, &item);
        printItemRow(i, item->data);
        i++;
        addItem(tempList, item->data);
        free(item);
    }
    while (!isEmpty(tempList)) {
        getItem(tempList, &item);
        addItem(stackList, item->data);
        free(item);
    }
    freeList(tempList);
    return 0;
}

int findInList(StackList *stackList, GitRep key, GitRepField field, bool fullComp) {
    if (isEmpty(stackList)) {
        return CODE_EMPTY_LIST;
    }

    StackList *tempList = newList();
    StackListItem *tempItem;
    int res = CODE_ITEMS_NOT_FOUND;
    int resultItemsCount = 0;
    for (int i = 0; !isEmpty(stackList); i++) {
        getItem(stackList, &tempItem);
        addItem(tempList, tempItem->data);
        if (compareGitReps(&(tempItem->data), &key, field, fullComp) == 0) {
            resultItemsCount++;
            if (resultItemsCount == 1) {
                printf("\n");
                printTableHeader();
            }
            printItemRow(i, tempItem->data);
            res = CODE_SUCCESS;
        }
    }
    COORD pPos = getCursorPosition();
    if (resultItemsCount > 0) {
        setCursorTo(0, 0);
        printf(OK_COLOR, "Find %d GitReps.\n", resultItemsCount);
    }
    setCursorTo(pPos.X, pPos.Y);

    while (!isEmpty(tempList)) {
        getItem(tempList, &tempItem);
        addItem(stackList, tempItem->data);
    }
    freeList(tempList);
    return res;
}

int sizeOf(StackList *list) {
    int size = 0;
    StackList *tempList = newList();
    StackListItem *tempItem = NULL;
    while (!isEmpty(list)) {
        getItem(list, &tempItem);
        addItem(tempList, tempItem->data);
        size++;
    }
    while (!isEmpty(tempList)) {
        getItem(tempList, &tempItem);
        addItem(list, tempItem->data);
    }
    freeList(tempList);
    return size;
}


int listToArray(StackList *list, GitRep **array, int *size) {
    int n = 0;
    *array = NULL;
    StackList *tempList = newList();
    StackListItem *tempItem = NULL;
    while (!isEmpty(list)) {
        getItem(list, &tempItem);
        addItem(tempList, tempItem->data);
        n++;
        *array = (GitRep *) realloc(*array, n * sizeof(GitRep));
        (*array)[n - 1] = tempItem->data;
    }
    *size = n;


    while (!isEmpty(tempList)) {
        getItem(tempList, &tempItem);
        addItem(list, tempItem->data);
    }
    freeList(tempList);
    return CODE_SUCCESS;
}

int arrayToList(StackList *list, GitRep *array, int size) {
    int res = 0;
    for (int i = size - 1; i >= 0; i--) {
        res = addItem(list, array[i]);
        if (res != 0) {
            break;
        }
    }
    return res;
}



