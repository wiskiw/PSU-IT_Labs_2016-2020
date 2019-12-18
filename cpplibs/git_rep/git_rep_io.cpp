//
// Created by WiskiW on 29.04.2017.
//

#include <limits.h>
#include "git_rep_io.h"
#include "io_reader.h"


void scanGitRep(GitRep *gitRep) {
    readString(gitRep->name, "Rep. name: ", 3, 35, false);
    readString(gitRep->pl, "Programing language: ", 0, 35, false);
    readString(gitRep->author, "Rep. author: ", 3, 35, false);
    readUnsignedFloat(&gitRep->rate, "Rep. rate: ", -1, 5);
    readUnsignedInt(&gitRep->commitNumb, "Number of commits: ", -1, INT_MAX);
    readUnsignedInt(&gitRep->errorNumb, "Number of errors: ", -1, INT_MAX);
    readUnsignedInt(&gitRep->fixErrorNumb, "Number of fixed errors: ", -1, INT_MAX);
    readUnsignedInt(&gitRep->branchNumb, "Number of branches: ", -1, INT_MAX);
    readDate(&gitRep->createDate, "Create date: ", false);
    readDate(&gitRep->editDate, "Edit date: ", gitRep->createDate, false);
}