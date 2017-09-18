//
// Created by WiskiW on 01.05.2017.
//

#ifndef TS1_STACKLIST_H
#define TS1_STACKLIST_H

#include <git_rep/git_rep_io.h>


struct StackListItem {
    GitRep data;
    StackListItem *next;
};

struct StackList {
    StackListItem *head;
};

int sizeOf(StackList *list);

int addItem(StackList *stackList, GitRep data, int index);

int removeItem(StackList *stackList, int index);

int getItem(StackList *stackList, StackListItem **item, int index);

int readItem(StackList *stackList, StackListItem **item, int index);

int findInList(StackList *stackList, GitRep key, GitRepField field, bool fullComp);

int listToArray(StackList *list, GitRep **array, int *size);

int arrayToList(StackList *list, GitRep *array, int size);

StackList *newList();

void freeList(StackList *stackList);

int printList(StackList *stackList);

void cleanList(StackList *stackList);

int listToArray(StackList *list, int *size);

bool isEmpty(StackList *stackList);

#endif //TS1_STACKLIST_H
