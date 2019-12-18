//
// Created by WiskiW on 09.05.2017.
//

#ifndef DECLISK_DECLIST_H
#define DECLISK_DECLIST_H

const int CODE_SUCCESS = 0;
const int CODE_NO_MEMORY = 1;
const int CODE_OUT_OF_BORDER = 2;
const int CODE_EMPTY_LIST = 3;
const int CODE_ERROR = 999;


typedef float Data;

struct DecListItem {
    Data data;
    DecListItem *preview;
    DecListItem *next;
};

struct DecList {
    DecListItem *head;
    DecListItem *tail;
};

enum Position {
    Head = 0, Tail
};

int addItem(DecList *decList, Data data, Position pos);

int removeItem(DecList *decList, Position pos);

int getItem(DecList *decList, DecListItem **item, Position pos);

DecList *newList();

void freeList(DecList *decList);

void printList(DecList *decList);


#endif //DECLISK_DECLIST_H
