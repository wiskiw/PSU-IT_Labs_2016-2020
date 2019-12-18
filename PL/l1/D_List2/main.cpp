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

struct DListItem {
    float data;
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

// Функция очистки списка
int clearList(DList *dList) {
    goStart(dList);
    while (hasNext(dList)) {
        removeItem(dList, 0);
    }
    return CODE_SUCCESS;
}

// Функция удаления списка
void removeList(DList *dList) {
    clearList(dList);
    dList->current = NULL;
    free(dList->start);
    free(dList->end);
}

// Функция добавления элемента
int addItem(DList *dList, int pos, float iData) {
    // вставка после позиции
    DListItem *item = (DListItem *) malloc(sizeof(DListItem));
    if (!item) {
        return CODE_NO_MEMORY;
    }

    item->data = iData;// сохранение данных

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
        printf(LightGray, " data: ");
        printf("%g", dList->current->data);
        printf(LightGray, "\n");
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

    int tempData = itemA->data;

    itemA->data = itemB->data;

    itemB->data = tempData;
    return CODE_SUCCESS;
}

// Функция удаления элементов из заданного диапазона
int removeItems(DList *dList, float aItem, float bItem) {
    if (aItem > bItem) {
        float temp = aItem;
        aItem = bItem;
        bItem = temp;
    }
    goStart(dList);
    goNext(dList);
    //printf(" %g - %g\n", aItem, bItem);
    for (int pos = 0; true; pos++) {
        float val = dList->current->data;
        if (val <= bItem && val >= aItem) {
            DListItem *temp = dList->current;
            dList->current->preview->next = temp->next;
            dList->current->next->preview = temp->preview;
            temp = NULL;
            free(temp);
        }
        if (!hasNext(dList)) {
            break;
        }
        goNext(dList);
    }
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
    DList *dList = (DList *) malloc(0);
    initList(dList);

    printf("\n ");
    while (true) {
        int tsN = -1;
        setConsoleTextColor(Yellow);
        printf("\t[1] - add item;\n");
        printf("\t[2] - show list;\n");
        printf("\t[3] - remove item;\n");
        printf("\t[4] - clear list;\n");
        printf("\t[5] - task 24;\n");
        printf("\t[0] - exit \t\n: ");
        setConsoleTextColor(White);

        scanf("%d", &tsN);
        getchar();
        int pos1 = 0;
        int pos2 = 0;
        float buffer = 0;
        switch (tsN) {
            case 0:
                system("cls");
                removeList(dList);
                return 0;
            case 1:
                system("cls");
                printf(LightGray, "Float: ");
                scanf("%g", &buffer);
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
                processResult(clearList(dList));
                break;
            case 5:
                system("cls");
                printf(LightGray, "A: ");
                scanf("%d", &pos1);
                printf(LightGray, "B: ");
                scanf("%d", &pos2);
                processResult(removeItems(dList, pos1, pos2));
                break;
            default:
                system("cls");
                printf("\tUnknown command, try again");
        }
        printf("\n");
    }
}

