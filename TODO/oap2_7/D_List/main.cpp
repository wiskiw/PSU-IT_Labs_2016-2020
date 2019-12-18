#include <iostream>
#include <malloc.h>
#include <cstring>
#include <cstdio>
#include "console_io_lib/console_io_lib.cpp"

const int CODE_SUCCESS = 0;
const int CODE_NO_MEMORY = 1;
const int CODE_LIST_TO_SHORT = 2;
const int CODE_NO_NEXT_ELEMENTS = 3;
const int CODE_NO_PREVIEW_ELEMENTS = 4;

typedef char Data[15];

struct DListItem {
    Data data;
    DListItem *preview;
    DListItem *next;
};

struct DList { // Doubly linked list
    DListItem *start;
    DListItem *current;
    DListItem *end;
};

// ====== Дополнительные функции работы со списком
bool hasPreview(DList *dList) {
    return dList->current->preview != dList->start;
}

bool hasNext(DList *dList) {
    return dList->current->next != dList->end;
}

int goPreview(DList *dList) {
    if (hasPreview(dList)) {
        dList->current = dList->current->preview;
        return CODE_SUCCESS;
    } else {
        return CODE_NO_PREVIEW_ELEMENTS;
    }
}

void goStart(DList *dList) {
    dList->current = dList->start;
}

int goNext(DList *dList) {
    if (hasNext(dList)) {
        dList->current = dList->current->next;
        return CODE_SUCCESS;
    } else {
        return CODE_NO_NEXT_ELEMENTS;
    }
}

int sizeOf(DList *dList) {
    goStart(dList);
    int size = 0;
    while (hasNext(dList)) {
        goNext(dList);
        size++;
    }
    return size;
}
// ======== ========== ========= ==========



// Функция создания нового списка
int initList(DList *dList) {
    dList->start = (DListItem *) malloc(sizeof(DListItem));
    if (!dList->start) {
        return CODE_NO_MEMORY;
    }

    dList->end = (DListItem *) malloc(sizeof(DListItem));
    if (!dList->end) {
        free(dList->start);
        dList->start = NULL;
        return CODE_NO_MEMORY;
    }

    //dList->start->data = -1;
    //dList->end->data = 1;
    dList->start->preview = NULL;
    dList->end->next = NULL;

    dList->start->next = dList->end;
    dList->end->preview = dList->start;

    dList->current = dList->start;
    return CODE_SUCCESS;
}

// Функция удаления элемента списка
int removeItem(DList *dList, int pos) {
    goStart(dList);
    for (int i = 0; i < pos + 1; i++) {
        if (hasNext(dList)) {
            goNext(dList);
        } else {
            return CODE_LIST_TO_SHORT;
        }
    }
    DListItem *temp = dList->current;
    dList->current->preview->next = temp->next;
    dList->current->next->preview = temp->preview;
    temp = NULL;
    free(temp);
    return CODE_SUCCESS;
}

// Функция удаления списка
void removeList(DList *dList) {
    goStart(dList);
    while (hasNext(dList)) {
        removeItem(dList, 0);
    }
    dList->current = NULL;
    free(dList->start);
    free(dList->end);
}

// Функция добавления элемента
int addItem(DList *dList, int pos, Data data) {
    // вставка после позиции
    DListItem *item = (DListItem *) malloc(sizeof(DListItem));
    if (!item) {
        return CODE_NO_MEMORY;
    }

    memset(item->data, '\0', 15);
    strcpy(item->data, data);// сохранение данных

    goStart(dList);
    for (int i = 0; i < pos; i++) {
        if (hasNext(dList)) {
            goNext(dList);
        } else {
            return CODE_LIST_TO_SHORT;
        }
    }

    item->next = dList->current->next; // устанавливаем ссылку для нового к слудующему элементу
    item->preview = dList->current; // устанавливаем ссылку для нового к предыдущему элементу

    if (hasNext(dList))
        item->next->preview = item; // новый элемент перед следующем от текущего

    item->preview->next = item; // новый элемент после текущего

    return CODE_SUCCESS;
}

// Функция печати всех элементов списка
void printDList(DList *dList) {
    int size = sizeOf(dList);
    if (size == 0) {
        printf(Cyan, "List is empty!\n");
        return;
    }
    printf(LightGray, " ==== Size: %d ===\n", size);
    goStart(dList);
    while (hasNext(dList)) {
        goNext(dList);
        printf(LightGray, " data: '");
        printf("%s", dList->current->data);
        printf(LightGray, "'\n");
    }

    /*
     // для принта с start & end элементами
    while (dList->current->next != NULL) {
        printf("red: %d\n", dList->current->data);
        dList->current = dList->current->next;
    }
    printf("red: %d\n", dList->current->data);
     */
}

// Функция перестановки элементов
int swap(DList *dList, int posA, int posB) {
    DListItem *itemA, *itemB;

    goStart(dList);
    for (int i = 0; i < posA + 1; i++) {
        if (hasNext(dList)) {
            goNext(dList);
        } else {
            return CODE_LIST_TO_SHORT;
        }
    }
    itemA = dList->current;

    goStart(dList);
    for (int i = 0; i < posB + 1; i++) {
        if (hasNext(dList)) {
            goNext(dList);
        } else {
            return CODE_LIST_TO_SHORT;
        }
    }
    itemB = dList->current;

    Data tempData = "";
    strcpy(tempData, itemA->data);

    memset(itemA->data, '\0', 15);
    strcpy(itemA->data, itemB->data);

    memset(itemB->data, '\0', 15);
    strcpy(itemB->data, tempData);
    return CODE_SUCCESS;
}

// Фунцкия обработки возврат-кода функций
void processResult(int code) {
    switch (code) {
        case CODE_SUCCESS:
            printf(LightGreen, "Success!\n");
            break;
        case CODE_LIST_TO_SHORT:
            printf(LightRed, "Position not found!\n");
            break;
        default:
            break;
    }
}

int main() {
    // Member 13
    DList *dList = (DList *) malloc(0);
    initList(dList);

    printf("\n ");
    while (true) {
        int tsN = -1;
        setConsoleTextColor(Yellow);
        printf("\t[1] - add record;\n");
        printf("\t[2] - show records list;\n");
        printf("\t[3] - remove record;\n");
        printf("\t[4] - swap items;\n");
        printf("\t[0] - exit \t\n: ");
        setConsoleTextColor(White);

        scanf("%d", &tsN);
        getchar();
        int pos1 = 0;
        int pos2 = 0;
        char buffer[15] = "";
        switch (tsN) {
            case 0:
                system("cls");
                removeList(dList);
                return 0;
            case 1:
                system("cls");
                printf(LightGray, "Char[14]: ");
                gets(buffer);
                printf(LightGray, "Position: ");
                scanf("%d", &pos1);
                processResult(addItem(dList, pos1, buffer));
                break;
            case 2:
                system("cls");
                printDList(dList);
                break;
            case 3:
                system("cls");
                printf(LightGray, "Position: ");
                scanf("%d", &pos1);
                processResult(removeItem(dList, pos1));
                break;
            case 4:
                system("cls");
                printf(LightGray, "First item position: ");
                scanf("%d", &pos1);
                printf(LightGray, "Second item position: ");
                scanf("%d", &pos2);
                swap(dList, pos1, pos2);
                break;
            default:
                system("cls");
                printf("\tUnknown command, try again");
        }
        printf("\n");
    }
}