//
// Created by WiskiW on 09.05.2017.
//

#include <malloc.h>
#include "DecList.h"
#include "console_io_lib/console_io_lib.cpp"


DecList *newList() {
    DecList *decList = (DecList *) malloc(0);
    if (decList == NULL){
        return NULL;
    }
    decList->head = (DecListItem *) malloc(sizeof(DecListItem));
    decList->tail = (DecListItem *) malloc(sizeof(DecListItem));

    decList->head->next = decList->tail;
    decList->head->preview = NULL;

    decList->tail->preview = decList->head;
    decList->tail->next = NULL;
    return decList;
}

void freeList(DecList *decList) {
    DecListItem *item;
    while (getItem(decList, &item, Head) == CODE_SUCCESS) {
        free(item);
    }
    free(decList->head);
    free(decList->tail);
}


int addItem(DecList *decList, Data data, Position pos) {
    DecListItem *newItem = (DecListItem *) malloc(sizeof(DecListItem));
    if (newItem == NULL) {
        return CODE_NO_MEMORY;
    }
    newItem->data = data;
    switch (pos) {
        case Head:
            newItem->next = decList->head->next;
            newItem->preview = decList->head;
            newItem->next->preview = newItem;
            decList->head->next = newItem;
            return CODE_SUCCESS;
        case Tail:
            newItem->next = decList->tail;
            newItem->preview = decList->tail->preview;
            newItem->preview->next = newItem;
            decList->tail->preview = newItem;
            return CODE_SUCCESS;
        default:
            return CODE_ERROR;
    }

}

int getItem(DecList *decList, DecListItem **item, Position pos) {
    switch (pos) {
        case Head:
            *item = decList->head->next;
            if (*item == decList->tail) {
                return CODE_EMPTY_LIST;
            }
            decList->head->next = (*item)->next;
            (*item)->next->preview = decList->head;
            break;
        case Tail:
            *item = decList->tail->preview;
            if (*item == decList->head) {
                return CODE_EMPTY_LIST;
            }
            decList->tail->preview = (*item)->preview;
            (*item)->preview->next = decList->tail;
            break;
        default:
            return CODE_ERROR;
    }
    return CODE_SUCCESS;
}

int removeItem(DecList *decList, Position pos) {
    DecListItem *item;
    int code = getItem(decList, &item, pos);
    if (code == CODE_SUCCESS) {
        free(item);
    }
    return code;
}


void printList(DecList *decList) {
    DecListItem *item = decList->head->next;
    if (item == decList->tail) {
        printf(Cyan, "List is empty!\n");
        return;
    }

    printf(LightGray, "\t Dec List: \n");
    while (item != decList->tail) {
        printf(LightGray, " data: '");
        printf("%g", item->data);
        printf(LightGray, "'\n");
        item = item->next;
    }
}