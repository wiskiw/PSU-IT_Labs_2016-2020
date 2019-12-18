//
// Created by WiskiW on 09.05.2017.
//

#ifndef QUEUELIST_QUEUELIST_H
#define QUEUELIST_QUEUELIST_H

const int CODE_SUCCESS = 0;
const int CODE_NO_MEMORY = 1;
const int CODE_OUT_OF_BORDER = 2;
const int CODE_EMPTY_LIST = 3;
const int CODE_ERROR = 999;

typedef float Data;

struct QueueListItem {
    Data data;
    QueueListItem *next;
};

struct QueueList {
    QueueListItem *first;
    QueueListItem *last;
};


int addItem(QueueList *queueList, Data data);

int removeItem(QueueList *queueList);

int getItem(QueueList *queueList, QueueListItem **item);

QueueList *newList();

void freeList(QueueList *queueList);

void printList(QueueList *queueList);


#endif //QUEUELIST_QUEUELIST_H
