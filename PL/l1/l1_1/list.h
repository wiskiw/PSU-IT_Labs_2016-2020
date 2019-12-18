//
// Created by WiskiW on 01.09.2017.
//

#ifndef L1_1_LIST_H
#define L1_1_LIST_H

struct ListItem {
    ListItem *next;
    int data;
    ListItem *prev;
};

struct List {
    ListItem *head;
    ListItem *tail;
};

#endif //L1_1_LIST_H
