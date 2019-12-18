//
// Created by WiskiW on 29.04.2017.
//

#ifndef LIB_GIT_REP_IO_H
#define LIB_GIT_REP_IO_H


#include <date/date.h>


const int NAME_LEN = 36;
const int PL_LEN = 36;
const int AUTHOR_LEN = 36;

struct GitRep {
    char name[NAME_LEN];
    char pl[PL_LEN];
    char author[AUTHOR_LEN];
    float rate;
    int commitNumb;
    int errorNumb;
    int fixErrorNumb;
    int branchNumb;
    Date createDate;
    Date editDate;
};

void scanGitRep(GitRep *gitRep);

void printGitRep(GitRep gitRep);

void printGitRepList(GitRep *gitRepList, int gitRepNumb);

void saveToFile(std::ofstream &dbFile, GitRep gitRep);

#endif //LIB_GIT_REP_IO_H
