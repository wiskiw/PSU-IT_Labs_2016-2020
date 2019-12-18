//
// Created by WiskiW on 25.04.2017.
//

#include "console_io_lib.cpp"

const char MSG_INCORRECT_FORMAT[]= "Incorrect data format! Try again. \n";

struct Date {
    int day;
    int month;
    int year;
};

struct GitRep {
    char name[101];
    char pl[101];
    char author[101];
    float rate;
    Date createDate;
    Date editDate;
    int commitNumb;
    int errorNumb;
    int fixErrorNumb;
    int branchNumb;
};

int getInt(int c) {
    return c - '0';
}

void printWarning(char *msg){
    printf(Magenta, msg);
}

char *readLine(char msg) {
    printf(msg);
    char buffer[256];
    gets(buffer);
}


int readName(GitRep *gitRep) {
    gitRep->name = readLine("Name: ");
    return 0;
}

int readProgramingLanguage(GitRep *gitRep) {
    gitRep->pl = readLine("Programing Language: ");
    return 0;
}

int readAuthor(GitRep *gitRep) {
    gitRep->pl = readLine("Author: ");
    return 0;
}

int readRate(GitRep *gitRep) {
    char *rateStr = readLine("Rate: ");
    float rate = strtof(rateStr);
    gitRep->pl = rate;
    if (rate != 0) {
        return 0;
    } else {
        printWarning(MSG_INCORRECT_FORMAT);
        return readRate(gitRep);
    }
}

int parseDate(Date * date, char*line){
    int startIndex = 0;
    // поиск индекса первого символа с начала строки, который не пробел
    for (; dateStr[startIndex] == ' '; startIndex++);

    if (strspn(dateStr, "0123456789. \n") != strlen(dateStr)) {
        // если в строке есть что-то кроме этих символов
        return 1;
    }
    if (dateStr[2 + startIndex] != '.' || dateStr[5 + startIndex] != '.') {
        return 1;
    }
    date.day = getInt(dateStr[startIndex]) * 10 + getInt(dateStr[startIndex + 1]);
    date.month = getInt(dateStr[startIndex + 3]) * 10 + getInt(dateStr[startIndex + 4]);
    date.year = getInt(dateStr[startIndex + 6]) * 1000 + getInt(dateStr[startIndex + 7]) * 100 +
                getInt(dateStr[startIndex + 8]) * 10 + getInt(dateStr[startIndex + 9]);
    return 0;
}

int readCreateDate(GitRep *gitRep) {
    char *dateStr = readLine("Create Date: ");
    Date date;
    if (parseDate(&date, dateStr) == 0){
        gitRep->createDate = date;
    } else {
        printWarning(MSG_INCORRECT_FORMAT);
        return readCreateDate(gitRep);
    }
}

int readEditDate(GitRep *gitRep) {
    char *dateStr = readLine("Edit Date: ");
    Date date;
    if (parseDate(&date, dateStr) == 0){
        gitRep->editDate = date;
    } else {
        printWarning(MSG_INCORRECT_FORMAT);
        return readEditDate(gitRep);
    }
}

int readCommitNumb(GitRep *gitRep) {
    char *str = readLine("Commit Numb: ");
    int i = atof(str);
    gitRep->commitNumb = i;
    if (i != 0) {
        return 0;
    } else {
        printWarning(MSG_INCORRECT_FORMAT);
        return readCommitNumb(gitRep);
    }
}

int readErrorNumb(GitRep *gitRep) {
    char *str = readLine("Error Numb: ");
    int i = atof(str);
    gitRep->errorNumb = i;
    if (i != 0) {
        return 0;
    } else {
        printWarning(MSG_INCORRECT_FORMAT);
        return readErrorNumb(gitRep);
    }
}

int readFixErrorNumb(GitRep *gitRep) {
    char *str = readLine("Fix Error Numb: ");
    int i = atof(str);
    gitRep->fixErrorNumb = i;
    if (i != 0) {
        return 0;
    } else {
        printWarning(MSG_INCORRECT_FORMAT);
        return readFixErrorNumb(gitRep);
    }
}

int readBranchNumb(GitRep *gitRep) {
    char *str = readLine("Branch Numb: ");
    int i = atof(str);
    gitRep->fixErrorNumb = i;
    if (i != 0) {
        return 0;
    } else {
        printWarning(MSG_INCORRECT_FORMAT);
        return readBranchNumb(gitRep);
    }
}

GitRep scanGitRep() {
    GitRep gitRep;

    readName(&gitRep);
    readProgramingLanguage(&gitRep);
    readAuthor(&gitRep);
    readRate(&gitRep);
    parseDate(&gitRep);
    readCreateDate(&gitRep);
    readEditDate(&gitRep);
    readCommitNumb(&gitRep);
    readErrorNumb(&gitRep);
    readFixErrorNumb(&gitRep);
    readBranchNumb(&gitRep);
    return gitRep;
}
