//
// Created by WiskiW on 01.05.2017.
//

#ifndef TS1_STACKLIST_H
#define TS1_STACKLIST_H

const int CODE_SUCCESS = 0;
const int CODE_NO_MEMORY = 1;
const int CODE_LIST_TO_SHORT = 2;
const int CODE_NO_NEXT_ELEMENTS = 3;
const int CODE_EMPTY_LIST = 4;
const int CODE_OUT_OF_BORDER= 5;

typedef char Data[15];

struct StackListItem {
    Data data;
    StackListItem *next;
};

struct StackList {
    StackListItem *head;
};

int addItem(StackList *stackList, Data data, int index);

int addItem(StackList *stackList, Data data);

int removeItem(StackList *stackList, int index);

int getItem(StackList *stackList, StackListItem **item, int index);

int readItem(StackList *stackList, StackListItem **item);

StackList *newList();

void freeList(StackList *stackList);

void printList(StackList *stackList);

#endif //TS1_STACKLIST_H
