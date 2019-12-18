#include <iostream>
#include "StackList.h"


/*
 лаба 1
 вариант 8
 задание 2 (стек)
 */

int action(StackList *pList);


// Фунцкия обработки возврат-кода функций
void processResult(int code) {
    switch (code) {
        case CODE_SUCCESS:
            printf("Success!\n");
            break;
        case CODE_LIST_TO_SHORT:
            printf("Position not found! [%d]\n", CODE_LIST_TO_SHORT);
            break;
        case CODE_OUT_OF_BORDER:
            printf("Position not found! [%d]\n", CODE_OUT_OF_BORDER);
            break;
        default:
            break;
    }
}

int main() {
    // Member 10
    StackList *stackList;
    while (true) {
        int tsN = -1;
        int iValA = 0;
        printf("\t[1] - create list;\n");
        printf("\t[2] - add item;\n");
        printf("\t[3] - remove item;\n");
        printf("\t[4] - show the list;\n");
        printf("\t[5] - clear list;\n");
        printf("\t[6] - task 8;\n");
        printf("\t[0] - exit \t\n: ");
        scanf("%d", &tsN);

        switch (tsN) {
            case 0: // выход
                //system("cls");
                clearList(stackList);
                return 0;
            case 1: // создать список
                stackList = newList();
                break;
            case 2: // добавить элемент
                //system("cls");
                printf("Data(int): ");
                Data data;
                scanf("%d", &data);
                printf("Index: ");
                scanf("%d", &iValA);
                processResult(addItem(stackList, data, iValA));
                break;
            case 3: // удалить элемент
                //system("cls");
                printf("Index: ");
                scanf("%d", &iValA);
                processResult(removeItem(stackList, iValA));
                break;
            case 4: // вывести список
                //system("cls");
                printList(stackList);
                break;
            case 5: // очистить список
                //system("cls");
                processResult(clearList(stackList));
                break;
            case 6: // задание варианта
                /*
                 8  Дан стек целых чисел. Удалить все локальные минимумы,
                    при этом первый и последний элемент не обрабатывать.
                 */
                //system("cls");
                //processResult(swap(stackList));
                processResult(action(stackList));
                break;
            default:
                //system("cls");
                printf("\tUnknown command, try again");
        }
        printf("\n");
        getchar();
    }
}

int action(StackList *stackList) {
    StackListItem *leftItem, *currentItem, *rightItem;
    int pos = 0; // начальный индекс первой тройки
    while (true) {

        std::cout << "pos:" <<  pos << "\n";
        // достаем тройку элементов из списка


        if (getItem(stackList, &leftItem, pos) != CODE_SUCCESS) {
            // если не удалось достать "левый" элемент из тройки
            return CODE_OUT_OF_BORDER; // недостаточно элементов в списке
        }
        std::cout << "l:" <<  leftItem->data << "\n";
        if (getItem(stackList, &currentItem, pos) != CODE_SUCCESS) {
            // если не удалось достать "центральный" элемент из тройки
            addItem(stackList, leftItem->data, pos); // возвращаем "левый" в список
            return CODE_OUT_OF_BORDER; // недостаточно элементов в списке
        }
        std::cout << "c:" <<  currentItem->data << "\n";
        if (getItem(stackList, &rightItem, pos) != CODE_SUCCESS) { // "правый"
            // если не удалось достать "правый" элемент из строки, возвращаем 2 первых обратно в список
            addItem(stackList, currentItem->data, pos);
            addItem(stackList, leftItem->data, pos);
            break;
        }
        std::cout << "r:" <<  rightItem->data << "\n";

        if(currentItem->data <= leftItem->data && currentItem->data <= rightItem->data){
            //если "центральный" элемент наименьший в тройке

            // возвращаем в список только боковые элементы
            addItem(stackList, rightItem->data, pos);
            addItem(stackList, leftItem->data, pos);
        } else {
            // иначе, возвращаем элементы обратно в список
            addItem(stackList, rightItem->data, pos);
            addItem(stackList, currentItem->data, pos);
            addItem(stackList, leftItem->data, pos);

            pos++; // сдвигаемся на олин элемент вправо по списку, для получения следующей тройки
        }
        printList(stackList);
    }
    return CODE_SUCCESS;
}
