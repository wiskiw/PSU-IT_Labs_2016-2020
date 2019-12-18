//
// Created by WiskiW on 29.04.2017.
//

#ifndef OAP_DATABASE_H
#define OAP_DATABASE_H


#include <fstream>
#include <git_rep/git_rep_io.h>
#include <list/GitRepStackList.h>

std::ofstream newDB();

void removeDB(char name[]);

void saveGitRepList(GitRep *gitRepList, int gitRepNumb);

GitRep *loadGitRepList(GitRep *gitRepList, int *gitRepNumb) ;


// STACK LIST FUNCTIONS

void saveList(StackList *list);

#endif //OAP_DATABASE_H
