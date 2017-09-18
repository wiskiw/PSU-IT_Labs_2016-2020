#include <iostream>
#include <list/GitRepStackList.cpp>
#include <database/database.cpp>
#include <menu/menu.cpp>
#include <git_rep/git_rep_io.cpp>
#include <console_io_lib/console_io_lib.cpp>
#include "preferences.h"
#include "codes.h"

const int WINDOW_WIDTH = 1034;
const int WINDOW_HEIGHT = 600;

bool dbChanged = false;
StackList *gitRepList = NULL;

void removeItem();

void registerDBChanges() {
    dbChanged = true;
}

void resetDBChanges() {
    dbChanged = false;
}

bool dbHasChanged() {
    return dbChanged;
}

int getInt(char *msg, int *res) {
    printf(MSG_COLOR, msg);
    Color pColor = getConsoleTextColor();
    setConsoleTextColor(INPUT_COLOR);
    while (scanf("%d", res) != 1) {
        system("cls");
        printf(WARNING_COLOR, "Incorrect numb, try again: ");
        getchar();
    }
    setConsoleTextColor(pColor);
    getchar();
    return *res;
}

void printList() {
    if (isEmpty(gitRepList)) {
        printf(WARNING_COLOR, "There are nothing to show: GitRep list is empty.\n");
    } else {
        printf("\n");
        printList(gitRepList);
    }
}

void moveItem() {
    if (isEmpty(gitRepList)) {
        printf(WARNING_COLOR, "There are nothing to move: GitRep list is empty.\n");
        return;
    }
    int posA = 0;
    int posB = 0;

    system("cls");
    printf("\n");
    printList(gitRepList);
    getInt((char *) "\nItem position (from): ", &posA);
    getInt((char *) "\nNew item position (to): ", &posB);

    StackListItem *listItem;
    switch (getItem(gitRepList, &listItem, posA)) {
        case CODE_SUCCESS:
            switch (addItem(gitRepList, listItem->data, posB)) {
                case CODE_OUT_OF_BORDER:
                    printf(EXCEPTION_COLOR, "Cannot add the item: incorrect index!\n");
                    break;
                case CODE_NO_MEMORY:
                    printf(EXCEPTION_COLOR, "Cannot add the item: not memory!\n");
                    break;
                default:
                    system("cls");
                    printf(OK_COLOR, "Moved!\n");
                    registerDBChanges();
                    printList(gitRepList);
            }
            break;
        case CODE_OUT_OF_BORDER:
            system("cls");
            printf(EXCEPTION_COLOR, "Cannot show the item: incorrect position!\n");
            printList(gitRepList);
            break;
        default:
            system("cls");
            printf(EXCEPTION_COLOR, "Error!\n");
            printList(gitRepList);
    }

}

void loadDatabase() {
    if (!isEmpty(gitRepList) && dbHasChanged()) {
        system("cls");
        printf(WARNING_COLOR, "GitRep list is not empty! You will lose all your data if continue\n");
        printList(gitRepList);
        switch (confirmMenu()) {
            case 1:
                system("cls");
                printf("\n");
                printList(gitRepList);
                break;
            default:
                printf("\n");
                printList(gitRepList);
                return;
        }
    }

    printf("\n");
    int res = loadList(gitRepList);
    system("cls");
    switch (res) {
        case CODE_CANNOT_OPEN_FILE:
            printf(EXCEPTION_COLOR, "Cannot open the database file!\n");
            break;
        default:
            if (isEmpty(gitRepList)) {
                printf(WARNING_COLOR, "No git repositores found!\n");
            } else {
                system("cls");
                printf(OK_COLOR, "The database has been successfully loaded!\n");
                printList(gitRepList);
            }
    }
}

void saveDatabase() {
    if (isEmpty(gitRepList)) {
        printf(WARNING_COLOR, "There are nothing to save! GitRep list is empty.\n");
        return;
    }
    system("cls");
    printf("\n");
    int res = saveList(gitRepList);
    system("cls");
    switch (res) {
        case CODE_CANNOT_CREATE_FILE:
            printf(EXCEPTION_COLOR, "Cannot create the database file!\n");
            break;
        default:
            resetDBChanges();
            printf(OK_COLOR, "The database has been successfully saved!\n");
    }
}

void sortList() {
    if (isEmpty(gitRepList)) {
        printf(WARNING_COLOR, "There are nothing to sort: GitRep list is empty.\n");
        return;
    }
    SortDirection dir;
    int intSortDir = printDirMenu();
    if (intSortDir > 0 && intSortDir < 3) {
        dir = (SortDirection) (intSortDir - 1);
    } else {
        return;
    }

    GitRepField field;
    int intSortField = printFieldMenu();
    if (intSortField > 0 && intSortField < 11) {
        field = (GitRepField) (intSortField - 1);
    } else {
        sortList();
    }

    system("cls");
    printf("\n");
    //printf(OK_COLOR, "List has been sorted!\n");

    int size = 0;
    GitRep *arrayList = NULL;
    listToArray(gitRepList, &arrayList, &size);
    sortGitRepArrayList(&arrayList, size, dir, field);
    cleanList(gitRepList);
    arrayToList(gitRepList, arrayList, size);
    printList(gitRepList);
    registerDBChanges();
}

void cleanList() {
    if (!isEmpty(gitRepList)) {
        system("cls");
        printf(WARNING_COLOR, "GitRep list is not empty! You will lose all your data if continue\n");
        printList(gitRepList);
        int res = confirmMenu();
        system("cls");
        switch (res) {
            case 1:
                break;
            default:
                printf("\n");
                printList(gitRepList);
                return;
        }
        cleanList(gitRepList);
    }
    printf(OK_COLOR, "List has been cleared!\n");
    registerDBChanges();
}

void addItem() {
    printf("\n");
    GitRep newRep;
    scanGitRep(&newRep);
    int pos = 0;
    getInt((char *) "\nAdd to position: ", &pos);
    system("cls");

    switch (addItem(gitRepList, newRep, pos)) {
        case CODE_ADDED_TO_END:
            printf(OK_COLOR, "Added to the end!\n");
            registerDBChanges();
            printList(gitRepList);
            break;
        case CODE_OUT_OF_BORDER:
            printf(EXCEPTION_COLOR, "Cannot add the item: incorrect index!\n");
            break;
        case CODE_NO_MEMORY:
            printf(EXCEPTION_COLOR, "Cannot add the item: not memory!\n");
            break;
        default:
            printf(OK_COLOR, "Added!\n");
            registerDBChanges();
            printList(gitRepList);
    }
}

void showItem() {
    if (isEmpty(gitRepList)) {
        printf(WARNING_COLOR, "There are nothing to show: GitRep list is empty.\n");
        return;
    }

    StackListItem *listItem;
    int pos = 0;
    system("cls");
    printf("\n");
    printList(gitRepList);;
    getInt((char *) "\nItem position: ", &pos);
    switch (readItem(gitRepList, &listItem, pos)) {
        case 0:
            printGitRep(listItem->data);
            break;
        case CODE_OUT_OF_BORDER:
            system("cls");
            printf(EXCEPTION_COLOR, "Cannot show the item: incorrect position!\n");
            printList(gitRepList);
            break;
        default:
            system("cls");
            printf(EXCEPTION_COLOR, "Error!\n");
            printList(gitRepList);
    }
}

void editItem() {
    if (isEmpty(gitRepList)) {
        printf(WARNING_COLOR, "There are nothing to show: GitRep list is empty.\n");
        return;
    }

    int pos = 0;
    system("cls");
    printf("\n");
    printList(gitRepList);
    getInt((char *) "\nItem position: ", &pos);
    StackListItem *listItem;
    GitRep rep;
    switch (getItem(gitRepList, &listItem, pos)) {
        case CODE_SUCCESS:
            printf("\n");
            rep = listItem->data;
            listItem->data;

            readString(rep.name, "Rep. name: ", rep.name, 3, 35, false);
            readString(rep.pl, "Programing language: ", rep.pl, 0, 35, false);
            readString(rep.author, "Rep. author: ", rep.author, 3, 35, false);
            readUnsignedFloat(&rep.rate, "Rep. rate: ", rep.rate, -1, MAX_RATE);
            readUnsignedInt(&rep.commitNumb, "Number of commits: ", rep.commitNumb, -1, MAX_COMMIT_NUMB);
            readUnsignedInt(&rep.errorNumb, "Number of errors: ", rep.errorNumb, -1, MAX_ERROR_NUMB);
            readUnsignedInt(&rep.fixErrorNumb, "Number of fixed errors: ", rep.fixErrorNumb, -1, MAX_FIX_ERROR_NUMB);
            readUnsignedInt(&rep.branchNumb, "Number of branches: ", rep.branchNumb, -1, MAX_BRANCH_NUMB);
            readDate(&rep.createDate, "Create date: ", &rep.createDate, NULL, false);
            readDate(&rep.editDate, "Edit date: ", &rep.editDate, &rep.createDate, false);

            addItem(gitRepList, rep, pos);
            system("cls");
            printf(OK_COLOR, "Item has been updated!\n");
            registerDBChanges();
            printList(gitRepList);
            break;
        case CODE_OUT_OF_BORDER:
            printf(EXCEPTION_COLOR, "Cannot edit the item: incorrect position!\n");
            break;
        default:
            printf(EXCEPTION_COLOR, "Error!\n");
    }
}

void removeItem() {
    if (isEmpty(gitRepList)) {
        printf(WARNING_COLOR, "There are nothing to remove! GitRep list is empty.\n");
        return;
    }

    int pos = 0;
    // TODO : getInt((char *) "\nPosition to remove: ", &pos);
    system("cls");
    switch (removeItem(gitRepList, pos)) {
        case CODE_OUT_OF_BORDER:
            printf(EXCEPTION_COLOR, "Item didn't removed: position is out of border!\n");
            break;
        case CODE_SUCCESS:
            printf(OK_COLOR, "Item has been removed!\n");
            registerDBChanges();
            if (!isEmpty(gitRepList)) {
                printList(gitRepList);
            }
            break;
        default:
            printf(EXCEPTION_COLOR, "Error!\n");
    }
}

void findItems(bool fullCmp) {
    if (isEmpty(gitRepList)) {
        printf(WARNING_COLOR, "GitRep list is empty.\n");
        return;
    }
    GitRep keyGitRep;
    GitRepField field;
    int intSortField = printFieldMenu();
    if (intSortField > 0 && intSortField < 11) {
        printf("\n");
        switch (intSortField) {
            case 1:
                readString(keyGitRep.name, "Rep. name: ", NULL, 0, 35, true);
                break;
            case 2:
                readString(keyGitRep.pl, "Programing language: ", NULL, 0, 35, true);
                break;
            case 3:
                readString(keyGitRep.author, "Rep. author: ", NULL, 0, 35, true);
                break;
            case 4:
                readUnsignedFloat(&keyGitRep.rate, "Rep. rate: ", -1, -1, MAX_RATE);
                break;
            case 5:
                readUnsignedInt(&keyGitRep.commitNumb, "Number of commits: ", -1, -1, MAX_COMMIT_NUMB);
                break;
            case 6:
                readUnsignedInt(&keyGitRep.errorNumb, "Number of errors: ", -1, -1, MAX_ERROR_NUMB);
                break;
            case 7:
                readUnsignedInt(&keyGitRep.fixErrorNumb, "Number of fixed errors: ", -1, -1, MAX_FIX_ERROR_NUMB);
                break;
            case 8:
                readUnsignedInt(&keyGitRep.branchNumb, "Number of branches: ", -1, -1, MAX_BRANCH_NUMB);
                break;
            case 9:
                readDate(&keyGitRep.createDate, "Create date: ", NULL, NULL, true);
                break;
            case 10:
                readDate(&keyGitRep.editDate, "Edit date: ", NULL, &keyGitRep.createDate, true);
                break;
        }
        field = (GitRepField) (intSortField - 1);
    } else {
        return;
    }

    system("cls");
    if (findInList(gitRepList, keyGitRep, field, fullCmp) == CODE_ITEMS_NOT_FOUND) {
        printf(WARNING_COLOR, "GitReps not found.\n");
    }
}

bool exit() {
    if (!isEmpty(gitRepList) && dbHasChanged()) {
        system("cls");
        printf(WARNING_COLOR, "GitRep list didn't saved! You will lose all your data if continue\n");
        printList(gitRepList);
        switch (confirmMenu()) {
            case 1:
                return true;
            default:
                system("cls");
                printf("\n");
                printList(gitRepList);
                return false;
        }
    }
    return true;
}

int main() {
    setWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    gitRepList = newList();
    while (true) {
        switch (printMainMenu()) {
            case 0:
                if (exit()) {
                    freeList(gitRepList);
                    return 0;
                }
                break;
            case 1:
                system("cls");
                if (!isEmpty(gitRepList)) {
                    printf("\n");
                    printList(gitRepList);
                }
                switch (printDatabaseMenu()) {
                    case 1:
                        loadDatabase();
                        break;
                    case 2:
                        saveDatabase();
                        break;
                }
                break;
            case 2:
                system("cls");
                printf("size %d\n", sizeOf(gitRepList));

                if (!isEmpty(gitRepList)) {
                    printf("\n");
                    printList(gitRepList);
                }
                switch (printItemMenu()) {
                    case 1:
                        addItem();
                        break;
                    case 2:
                        showItem();
                        break;
                    case 3:
                        editItem();
                        break;
                    case 4:
                        moveItem();
                        break;
                    case 5:
                        removeItem();
                        break;
                    case 6:
                        showItem();
                        break;
                }
                break;
            case 3:
                system("cls");
                if (isEmpty(gitRepList)) {
                    printf(WARNING_COLOR, "GitRep list is empty!\n");
                    break;
                }
                printf("\n");
                printList(gitRepList);
                switch (printListMenu()) {
                    case 1:
                        sortList();
                        break;
                    case 2:
                        // фильтр
                        findItems(false);
                        break;
                    case 3:
                        // поиск
                        findItems(true);
                        break;
                    case 4:
                        cleanList();
                        break;
                }
                break;
        }
    }
}