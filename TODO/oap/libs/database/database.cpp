//
// Created by WiskiW on 29.04.2017.
//

#include <cstring>
#include <cstdlib>
#include <console_io_lib/console_io_lib.h>
#include <git_rep/git_rep_io.h>
#include <fstream>
#include <list/GitRepStackList.h>

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
    if (dbFile.is_open()) {
        //printf("Database file successfully created!\n");
    } else {
        printf(LightRed, "Cannot create the database file: %s\n", name);
    }
    return dbFile;
}

std::ifstream openDB(char *name) {
    std::ifstream dbFile(name); // открыли файл для чтения
    if (dbFile.is_open()) {
        //printf("Database file successfully opened!\n");
    } else {
        printf(LightRed, "Cannot open the database file: %s\n", name);
    }
    return dbFile;
}

char *getFilename() {
    char *filename = (char *) calloc(256, sizeof(char));
    printf("Database filename (default: %s): ", DEFAULT_DB_FILENAME);
    gets(filename);
    getchar();
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

void saveList(StackList *list) {
    int gitRepNumb = 0;
    GitRep *array;
    int code = listToArray(list, &array, &gitRepNumb);
    if (code != CODE_SUCCESS) {
        printf(LightRed, "Error: %d\n", code);
        return;
    }
    if (gitRepNumb == 0) {
        printf("The list is empty. Nothing to save.\n");
        return;
    }

    std::ofstream dbFile = newDB(getFilename());
    if (!dbFile.is_open()) {
        return;
    }

    for (int i = 0; i < gitRepNumb; i++) {
        GitRep gitRep = array[i];
        saveToFile(dbFile, gitRep);
    }
    dbFile << "# end_of_file\n"; // для коректной работы цикла по чтению файла добовляем непустую строку к концу
    dbFile.close();
}

void loadList(StackList *list) {
    std::ifstream dbFile = openDB(getFilename());
    if (!dbFile.is_open()) {
        return;
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
                size++;
                addItem(list, gitRep);
                repLine = 0;
        }
    }
    dbFile.close();
    if (size == 0) {
        printf(Yellow, "No git repositores found!\n");
    }
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