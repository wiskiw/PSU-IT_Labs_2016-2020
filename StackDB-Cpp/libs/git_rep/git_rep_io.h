//
// Created by WiskiW on 29.04.2017.
//

#ifndef LIB_GIT_REP_IO_H
#define LIB_GIT_REP_IO_H


#include <git_rep/date/date.h>

const int NAME_LEN = 36;
const int PL_LEN = 36;
const int AUTHOR_LEN = 36;
const int MAX_COMMIT_NUMB = 999;
const int MAX_ERROR_NUMB = 999;
const int MAX_FIX_ERROR_NUMB = 999;
const int MAX_BRANCH_NUMB = 99;
const float MAX_RATE = 5;

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

enum Gravity {
    Left, Right, Center
};

enum GitRepField {
    Name, Pl, Author, Rate, CommitNumb, ErrorNumb, FixErrorNumb, BranchNumb, CreateDate, EditDate
};

enum SortDirection {
    Inc, Dec
};

void scanGitRep(GitRep *gitRep);

void printGitRep(GitRep gitRep);

int printGitRepArrayList(GitRep *gitRepList, int gitRepNumb);

void printItemRow(int index, GitRep rep);

void printTableHeader();

int compareGitReps(GitRep *a, GitRep *b, GitRepField field, bool fullComp);

void saveToFile(std::ofstream &dbFile, GitRep gitRep);

void readDate(Date *date, const char *msg, const Date *defaultValue, Date *minDate, bool allowEmpty);

void readString(char *buffer, const char *msg, const char *defaultValue, int minLength, int maxLength, bool allowEmpty);

void readUnsignedInt(int *intValue, const char *msg, int defaultValue, int minValue, int maxValue);

void readUnsignedFloat(float *floatValueBuffer, const char *msg, float defaultValue, float minValue, float maxValue);

void sortGitRepArrayList(GitRep **gitRepList, int gitRepNumb, SortDirection dir, GitRepField field);

#endif //LIB_GIT_REP_IO_H
