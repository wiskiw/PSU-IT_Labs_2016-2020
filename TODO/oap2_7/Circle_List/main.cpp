#include <iostream>
#include <malloc.h>
#include "console_io_lib/console_io_lib.cpp"

const int CODE_SUCCESS = 0;
const int CODE_NO_MEMORY = 1;
const int CODE_EMPTY_LIST = 2;
const int CODE_NEGATIVE_INDEX = 3;

typedef float Data;

struct CircleListItem {
    Data data;
    CircleListItem *next;
};

struct CircleList {
    CircleListItem *current;
    CircleListItem *start;
};

// ====== Дополнительные функции работы со списком
int goNext(CircleList *circleList) {
    if (circleList->start == NULL) {
        return CODE_EMPTY_LIST;
    }
    circleList->current = circleList->current->next;
    return CODE_SUCCESS;
}

void goStart(CircleList *circleList) {
    circleList->current = circleList->start;
}

int goEnd(CircleList *circleList) {
    if (circleList->start == NULL) {
        return CODE_EMPTY_LIST;
    }
    while (circleList->current->next != circleList->start)
        goNext(circleList);
    return CODE_SUCCESS;
}

int sizeOf(CircleList *circleList) {
    int size = 0;
    if (circleList->start != NULL) {
        size++;
        goStart(circleList);
        while (circleList->current->next != circleList->start) {
            size++;
            goNext(circleList);
        }
    }
    return size;
}

// Переход к pos элементу списка
void goToPos(CircleList *circleList, int pos) {
    goStart(circleList);
    for (int i = 0; i < pos; i++) {
        goNext(circleList);
    }
}
// ======== ========== ========= ==========


// Функция создания нового списка
CircleList *newList() {
    CircleList *circleList = (CircleList *) malloc(sizeof(CircleList));
    if (!circleList) {
        return NULL;
    }
    circleList->start = NULL;
    circleList->current = circleList->start;
    return circleList;
}

// Функция извлечения следующего элемента списка
int getItem(CircleList *circleList, CircleListItem **extItem) {
    // Функция извлекает следующий элемент после current
    if (circleList->start == NULL) {
        *extItem = NULL;
        return CODE_EMPTY_LIST;
    } else {
        *extItem = circleList->current->next;
        circleList->current->next = (*extItem)->next;
        if (*extItem == circleList->start) {
            // если достаем голову
            if ((*extItem)->next != circleList->start) {
                circleList->start = (*extItem)->next;
            } else {
                // Если достали последний элемент
                circleList->current = NULL;
                circleList->start = NULL;
            }
        }
        (*extItem)->next = NULL;
    }
    return CODE_SUCCESS;
}

// Функция удаления элемента списка по его индексу
int removeItem(CircleList *circleList, int pos) {
    if (pos < 0) {
        return CODE_NEGATIVE_INDEX;
    }
    if (pos == 0) {
        goEnd(circleList);
    } else {
        goToPos(circleList, pos - 1);
    }

    CircleListItem *temp;
    int code = getItem(circleList, &temp);
    if (code == CODE_SUCCESS) {
        free(temp);
    }
    return code;
}

// Функция добавления элемента
int addItem(CircleList *circleList, int pos, float fData) {
    CircleListItem *item = (CircleListItem *) malloc(sizeof(CircleListItem));
    if (!item) {
        return CODE_NO_MEMORY;
    }
    item->data = fData;

    if (circleList->current == NULL) {
        // если список пуст
        circleList->start = item;
        circleList->current = circleList->start;
        circleList->current->next = circleList->start;
    } else {
        if (pos == 0) {
            // Если добавляем элемент в начало
            goEnd(circleList); // перемащаемся в конец
            item->next = circleList->start; // устанавлицаем как следующий текущую "голову"
            circleList->current->next = item; // добавляем новый элемент в конец
            circleList->start = item; // сообщаем, что конец - новая голова
        } else {
            goToPos(circleList, pos - 1); // преход к позиции перед pos
            item->next = circleList->current->next; // устанавлицаем следующий для нового - слудующий от текущего
            circleList->current->next = item; // устанавлицаем как следующий от текущего наш новый элемент
        }
        circleList->current = item; // перемещаем указатель на добавленный элемент
    }
    return CODE_SUCCESS;
}

// Функция удаления списка
void removeList(CircleList *circleList) {
    while (removeItem(circleList, 0) == CODE_SUCCESS);
    free(circleList);
}

// Функция печати всех элементов списка
void printList(CircleList *circleList) {
    int size = sizeOf(circleList);
    if (size == 0) {
        printf(Cyan, "List is empty!\n");
        return;
    }
    printf(LightGray, " ==== Circle List Size: %d ===\n", size);
    goStart(circleList);
    for (int i = 0; i < size; i++) {
        printf(LightGray, " data: '");
        printf("%g", circleList->current->data);
        printf(LightGray, "'\n");
        goNext(circleList);
    }
}

// Функция перестановки элементов
int swap(CircleList *circleList, int posA, int posB) {
    CircleListItem *itemA, *itemB;

    goToPos(circleList, posA);
    itemA = circleList->current;

    goToPos(circleList, posB);
    itemB = circleList->current;

    Data tempData = itemA->data;
    itemA->data = itemB->data;
    itemB->data = tempData;
    return CODE_SUCCESS;
}


// Фунцкия обработки возврат-кода функций
void processResult(int code) {
    switch (code) {
        case CODE_SUCCESS:
            printf(LightGreen, "Success!\n");
            break;
        case CODE_NO_MEMORY:
            printf(LightRed, "No memory!\n");
            break;
        case CODE_EMPTY_LIST:
            printf(LightRed, "List is empty!\n");
            break;
        case CODE_NEGATIVE_INDEX:
            printf(LightRed, "Negative position!\n");
            break;
        default:
            break;
    }
}

int clearList(CircleList *circleList){
    while (removeItem(circleList, 0) == CODE_SUCCESS);
}

// Функция удаления элементов из заданного диапазона
int removeItems(CircleList *cList, float aItem, float bItem) {
    if (aItem > bItem) {
        float temp = aItem;
        aItem = bItem;
        bItem = temp;
    }
    int size = sizeOf(cList);
    //goStart(cList);
    //printf("size: %d\n", size);
    for (int i = 0; i < size; i++) {
        float val = cList->current->next->data;
        //printf("[i:%d] v: %g\n", i, val);
        if (val <= bItem && val >= aItem) {
            CircleListItem *temp;
            int code = getItem(cList, &temp);
            if (code == CODE_SUCCESS) {
                free(temp);
            }
            i--;
        }
        goNext(cList);
    }
    return CODE_SUCCESS;
}



int main() {
    // Member 13
    CircleList *circleList = newList();

    printf("\n ");
    while (true) {
        int tsN = -1;
        setConsoleTextColor(Yellow);
        printf("\t[1] - add record;\n");
        printf("\t[2] - show records list;\n");
        printf("\t[3] - remove record;\n");
        printf("\t[4] - swap items;\n");
        printf("\t[5] - task 24;\n");
        printf("\t[6] - clear list;\n");
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
                removeList(circleList);
                return 0;
            case 1:
                system("cls");
                printf(LightGray, "Float: ");
                scanf("%g", &buffer);
                printf(LightGray, "Position: ");
                scanf("%d", &pos1);
                processResult(addItem(circleList, pos1, buffer));
                break;
            case 2:
                system("cls");
                printList(circleList);
                break;
            case 3:
                system("cls");
                printf(LightGray, "Position: ");
                scanf("%d", &pos1);
                processResult(removeItem(circleList, pos1));
                break;
            case 4:
                system("cls");
                printf(LightGray, "First item position: ");
                scanf("%d", &pos1);
                printf(LightGray, "Second item position: ");
                scanf("%d", &pos2);
                swap(circleList, pos1, pos2);
                break;
            case 5:
                system("cls");
                printf(LightGray, "A: ");
                scanf("%d", &pos1);
                printf(LightGray, "B: ");
                scanf("%d", &pos2);
                processResult(removeItems(circleList, pos1, pos2));
                break;
            case 6:
                system("cls");
                processResult(clearList(circleList));
                break;
            default:
                system("cls");
                printf("\tUnknown command, try again");
        }
        printf("\n");
    }
}
