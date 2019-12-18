#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <console_io_lib/console_io_lib.cpp>
#include <git_rep/git_rep_io.cpp>
#include <database/database.cpp>
#include <menu/menu.cpp>
#include <list/GitRepStackList.cpp>


GitRep *gitRepList = NULL;
StackList *list;
int gitRepNumb = 0;

void addGitRep() {
    GitRep gitRep;
    scanGitRep(&gitRep);
    gitRepList = (GitRep *) realloc(gitRepList, sizeof(GitRep) * ++gitRepNumb);
    gitRepList[gitRepNumb - 1] = gitRep;
}

void clear() {
    if (gitRepList != NULL && gitRepNumb > 0) {
        free(gitRepList);
        gitRepNumb = 0;
        printf("Memory free up!\n");
    } else {
        printf("Memory is already empty!\n");
    }
}

int main() {

    setWindowSize(DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT);
    list = newList();

    if (list == NULL) {
        printf(LightRed, "No memory!\n");
        system("pause");
        return 0;
    }
    while (true) {
        switch (mainMenu()) {
            case 0:
                system("cls");
                return 0;
            case 1:
                system("cls");
                addGitRep();
                break;
            case 2:
                system("cls");
                if (gitRepNumb > 0) {
                    printGitRep(gitRepList[0]);
                } else {
                    printf("The list is empty.\n");
                }
                break;
            case 3:
                system("cls");
                printGitRepList(gitRepList, gitRepNumb);
                break;
            case 4:
                system("cls");
                saveGitRepList(gitRepList, gitRepNumb);
                break;
            case 5:
                system("cls");
                gitRepList = loadGitRepList(gitRepList, &gitRepNumb);
                //printf("list: %s\n", gitRepList);
                break;
            case 6:
                system("cls");
                clear();
                break;
            case 7:
                system("cls");
                removeDB((char *) DEFAULT_DB_FILENAME);
                break;

            default:
                system("cls");
                printf(LightRed, "\tUnknown command, try again");
        }
        printf("\n");
        getchar();
    }
}