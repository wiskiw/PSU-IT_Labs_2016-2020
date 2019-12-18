//
// Created by WiskiW on 09.05.2017.
//

#include <malloc.h>
#include "QueueList.h"
#include "console_io_lib/console_io_lib.cpp"

QueueList *newList() {
    QueueList *queueList = (QueueList *) malloc(0);
    if (queueList == NULL) {
        return NULL;
    }
    queueList->first = (QueueListItem *) malloc(sizeof(QueueListItem));
    queueList->first->next = NULL;
    queueList->last = queueList->first;
    return queueList;
}

void freeList(QueueList *queueList) {
    QueueListItem *item;
    while (getItem(queueList, &item) == CODE_SUCCESS) {
        free(item);
    }
    queueList->last = NULL;
    free(queueList->first);
}

int addItem(QueueList *queueList, Data data) {
    QueueListItem *newItem = (QueueListItem *) malloc(sizeof(QueueListItem));
    if (newItem == NULL) {
        return CODE_NO_MEMORY;
    }
    newItem->data = data;
    queueList->last->next = newItem;
    newItem->next = NULL;
    queueList->last = newItem;
    return CODE_SUCCESS;
}

int getItem(QueueList *queueList, QueueListItem **item) {
    *item = queueList->first->next;
    if (*item == NULL) {
        return CODE_EMPTY_LIST;
    }
    queueList->first->next = (*item)->next;
    return CODE_SUCCESS;
}

int removeItem(QueueList *queueList) {
    QueueListItem *item;
    int code = getItem(queueList, &item);
    if (code == CODE_SUCCESS) {
        free(item);
    }
    return code;
}

void printList(QueueList *queueList) {
    QueueListItem *item = queueList->first->next;
    if (item == NULL) {
        printf(Cyan, "List is empty!\n");
        return;
    }
    printf(LightGray, "\t List: \n");
    while (item != NULL) {
        printf(LightGray, " data: '");
        printf("%g", item->data);
        if (queueList->first->next == item && queueList->last == item) {
            printf(LightGray, "' <- first & last\n");
        } else if (queueList->first->next == item) {
            printf(LightGray, "' <- first\n");
        } else if (queueList->last == item) {
            printf(LightGray, "' <- last\n");
        } else {
            printf(LightGray, "'\n");
        }
        item = item->next;
    }
}
