//
// Created by WiskiW on 29.04.2017.
//

#include <cstring>
#include <cstdlib>
#include <console_io_lib/console_io_lib.h>
#include <git_rep/git_rep_io.h>
#include <fstream>
#include <list/GitRepStackList.h>
#include <conio.h>
#include "database.h"
#include "../../preferences.h"
#include "../../codes.h"

const char DEFAULT_DB_FILENAME[] = "database.txt";


void removeDB(char *name) {
    if (remove(name) == 0) {
        printf("Database file successfully removed!\n");
    } else {
        printf("Cannot remove the database file!\n");
    }
}

std::ofstream newDB(char *name) {
    std::ofstream dbFile(name);
    return dbFile;
}

std::ifstream openDB(char *name) {
    std::ifstream dbFile(name); // открыли файл для чтения
    return dbFile;
}

char *getFilename() {
    char *filename = (char *) calloc(256, sizeof(char));
    printf(MSG_COLOR, "Database filename (default: %s): ", DEFAULT_DB_FILENAME);
    Color pColor = getConsoleTextColor();
    setConsoleTextColor(INPUT_COLOR);
    gets(filename);
    setConsoleTextColor(pColor);
    if (filename[0] == '\0') {
        free(filename);
        return (char *) DEFAULT_DB_FILENAME;
    } else {
        return filename;
    }
}

void saveGitRepList(GitRep *gitRepList, int gitRepNumb) {
    if (gitRepNumb == 0) {
        printf("The list is empty. Nothing to save.\n");
        return;
    }

    std::ofstream dbFile = newDB(getFilename());
    if (!dbFile.is_open()) {
        return;
    }

    for (int i = 0; i < gitRepNumb; i++) {
        GitRep gitRep = gitRepList[i];
        saveToFile(dbFile, gitRep);
    }
    dbFile << "# end_of_file\n"; // для коректной работы цикла по чтению файла добовляем непустую строку к концу
    dbFile.close();
}

int saveList(StackList *list) {
    std::ofstream dbFile = newDB(getFilename());
    if (!dbFile.is_open()) {
        return CODE_CANNOT_CREATE_FILE;
    }
    StackListItem *stackListItem;
    StackList *tempList = newList();
    while (!isEmpty(list)) {
        getItem(list, &stackListItem, 0);
        addItem(tempList, stackListItem->data, 0);
    }

    while (!isEmpty(tempList)) {
        getItem(tempList, &stackListItem, 0);
        addItem(list, stackListItem->data, 0);
        saveToFile(dbFile, stackListItem->data);
    }
    freeList(tempList);
    dbFile << "# end_of_file\n"; // для коректной работы цикла по чтению файла добовляем непустую строку к концу
    dbFile.close();
    return 0;
}

int loadList(StackList *list) {
    std::ifstream dbFile = openDB(getFilename());
    if (!dbFile.is_open()) {
        return CODE_CANNOT_OPEN_FILE;
    }

    cleanList(list);
    int repLine = 0;
    int size = 0;
    char buff[256] = "";
    GitRep gitRep;
    while (dbFile.getline(buff, 255)) {
        if (dbFile.eof() && (buff[0] == '\n' || buff[0] == '\0')) {
            // если у нас не конец файла и не пустая строка - пропускаем
            continue;
        }
        repLine++;
        switch (repLine) {
            case 1:
                strncpy(gitRep.name, buff, NAME_LEN - 1);
                break;
            case 2:
                strncpy(gitRep.pl, buff, PL_LEN - 1);
                break;
            case 3:
                strncpy(gitRep.author, buff, AUTHOR_LEN - 1);
                break;
            case 4:
                gitRep.rate = (float) atof(buff);
                break;
            case 5:
                gitRep.commitNumb = atoi(buff);
                break;
            case 6:
                gitRep.errorNumb = atoi(buff);
                break;
            case 7:
                gitRep.fixErrorNumb = atoi(buff);
                break;
            case 8:
                gitRep.branchNumb = atoi(buff);
                break;
            case 9:
                gitRep.createDate.day = atoi(buff);
                break;
            case 10:
                gitRep.createDate.month = atoi(buff);
                break;
            case 11:
                gitRep.createDate.year = atoi(buff);
                break;
            case 12:
                gitRep.editDate.day = atoi(buff);
                break;
            case 13:
                gitRep.editDate.month = atoi(buff);
                break;
            case 14:
                gitRep.editDate.year = atoi(buff);
                break;
            default:
                size++;
                addItem(list, gitRep, 0);
                repLine = 0;
        }
    }
    dbFile.close();
    return 0;
}

GitRep *loadGitRepList(GitRep *gitRepList, int *gitRepNumb) {
    std::ifstream dbFile = openDB(getFilename());
    if (!dbFile.is_open()) {
        return 0;
    }

    int repLine = 0;
    int size = 0;
    char buff[256] = "";
    GitRep gitRep;
    while (dbFile.getline(buff, 255)) {
        if (dbFile.eof() && (buff[0] == '\n' || buff[0] == '\0')) {
            // если у нас не конец файла и не пустая строка - пропускаем
            continue;
        }
        repLine++;
        switch (repLine) {
            case 1:
                strncpy(gitRep.name, buff, NAME_LEN - 1);
                break;
            case 2:
                strncpy(gitRep.pl, buff, PL_LEN - 1);
                break;
            case 3:
                strncpy(gitRep.author, buff, AUTHOR_LEN - 1);
                break;
            case 4:
                gitRep.rate = (float) atof(buff);
                break;
            case 5:
                gitRep.commitNumb = atoi(buff);
                break;
            case 6:
                gitRep.errorNumb = atoi(buff);
                break;
            case 7:
                gitRep.fixErrorNumb = atoi(buff);
                break;
            case 8:
                gitRep.branchNumb = atoi(buff);
                break;
            case 9:
                gitRep.createDate.day = atoi(buff);
                break;
            case 10:
                gitRep.createDate.month = atoi(buff);
                break;
            case 11:
                gitRep.createDate.year = atoi(buff);
                break;
            case 12:
                gitRep.editDate.day = atoi(buff);
                break;
            case 13:
                gitRep.editDate.month = atoi(buff);
                break;
            case 14:
                gitRep.editDate.year = atoi(buff);
                break;
            default:
                printf(Green, "name %s\n", gitRep.name);
                size++;
                gitRepList = (GitRep *) realloc(gitRepList, sizeof(GitRep) * size);
                gitRepList[size - 1] = gitRep;
                repLine = 0;
        }
    }
    printf(Red, "size %d\n", size);
    *gitRepNumb = size;
    return gitRepList;
}