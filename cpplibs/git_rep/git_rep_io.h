//
// Created by WiskiW on 29.04.2017.
//

#ifndef LIB_GIT_REP_IO_H
#define LIB_GIT_REP_IO_H


#include "date.h"

struct GitRep {
    char name[36];
    char pl[36];
    char author[36];
    float rate;
    Date createDate;
    Date editDate;
    int commitNumb;
    int errorNumb;
    int fixErrorNumb;
    int branchNumb;
};

void scanGitRep(GitRep *gitRep);

#endif //LIB_GIT_REP_IO_H
