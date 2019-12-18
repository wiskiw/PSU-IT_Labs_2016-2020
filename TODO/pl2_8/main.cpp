#include <stdio.h>
#include <malloc.h>
#include <string.h>

// Стандартные установки сортировки:
int sortSpeed = 0; // 0 - slow, 1 - fast
int sortDirection = 0; // 0 - inc(Z9-a0), 1 - dec(a0-Z9)
int sortField = 4; // 1 - 4

int bookListSize = 0;

struct Book {
    char author[16];
    char name[21];
    unsigned int year;
    unsigned int size;
};

// Формат ввода: код ISBN: Фамилия И. О. «Название», год, кол-во страниц
// ISBN: Author R "Book Name" 2015 228
/*

 ISBN: Author A "Book Name A" 2000 101
 ISBN: Author C "Book Name F" 2016 315
 ISBN: Author B "Book Name C" 2010 205
 */

int readAuthor(Book *book, char line[]) {
    char *c = strchr(line, ':'); // +1 для учета ':'
    if (c == NULL) {
        return 1;
    }
    int statPos = strlen(line) - strlen(c + 2); // +2 не учитываем ':' и следующий пробел

    c = strchr(line, '"');
    if (c == NULL) {
        return 1;
    }
    int endPos = strlen(line) - strlen(c) - 1;

    char mAuthor[16] = "";
    strncpy(mAuthor, line + statPos, endPos - statPos);
    if (mAuthor[0] == '\0') {
        return 1;
    }
    strcpy(book->author, mAuthor); // сохраняем в структуру

    //printf("mAuthor: '%s'\n", mAuthor);
    return 0;
}

int readName(Book *book, char line[]) {
    char *c = strchr(line, '"');
    if (c == NULL) {
        return 1;
    }
    int statPos = strlen(line) - strlen(c + 1);

    c = strchr(line + statPos, '"');
    if (c == NULL) {
        return 1;
    }
    int endPos = strlen(line) - strlen(c);

    char mName[21] = "";
    strncpy(mName, line + statPos, endPos - statPos);
    if (mName[0] == '\0') {
        return 1;
    }
    strcpy(book->name, mName); // сохраняем в структуру

    //printf("mName: '%s'\n", mName);
    return 0;
}

int readYear(Book *book, char line[]) {
    char *c = strrchr(line, '"');
    if (c == NULL) {
        return 1;
    }
    int statPos = strlen(line) - strlen(c + 2);

    c = strchr(line + statPos, ' ');
    if (c == NULL) {
        return 1;
    }
    int endPos = strlen(line) - strlen(c);

    char mYear[5] = "";
    strncpy(mYear, line + statPos, endPos - statPos);
    if (mYear[0] == '\0') {
        return 1;
    }

    int intYear = atoi(mYear);
    if (intYear <= 0) {
        return 1;
    }
    book->year = (unsigned int) intYear; // сохраняем в структуру

    //printf("intYear: '%d'\n", intYear);
    return 0;
}

int readSize(Book *book, char line[]) {
    for (int i = strlen(line) - 1; i >= 0; i--) { // Убираем пробелвы в конце строки
        char c = line[i];
        if (c == ' ') {
            line[i] = '\0';
        } else {
            break;
        }
    }

    char *c = strrchr(line, ' ');
    if (c == NULL) {
        return 1;
    }
    int statPos = strlen(line) - strlen(c + 1);

    int intSize = atoi(line + statPos);
    if (intSize <= 0) {
        return 1;
    }
    book->size = (unsigned int) intSize; // сохраняем в структуру

    //printf("intSize: '%d'\n", intSize);
    return 0;
}

// менямет местами значения указателей bookA и bookB
void swap(Book *bookA, Book *bookB) {
    struct Book bookTemp = *bookA;
    *bookA = *bookB;
    *bookB = bookTemp;
}

int compareBooks(Book *bookA, Book *bookB, int field) {
    // return: >0 : если нужно менять
    int res;
    switch (field) {
        /*
         strcmp(a,b)
            >0 : a>b
            <0 : a<b
            =0 : a=b
         */
        case 1:
            res = strcmp(bookA->author, bookB->author);
            if (res == 0) { // если элементы совпадают по текущему полю
                if (field + 1 <= 4) {
                    // сравниваем по следующему
                    return compareBooks(bookA, bookB, field + 1);
                }
            }
            return res;
        case 2:
            res = strcmp(bookA->name, bookB->name);
            if (res == 0) { // если элементы совпадают по текущему полю
                if (field + 1 <= 4) {
                    // сравниваем по следующему
                    return compareBooks(bookA, bookB, field + 1);
                }
            }
            return res;
        case 3:
            if (bookA->year == bookB->year) {
                if (field + 1 <= 4) {
                    // сравниваем по следующему
                    return compareBooks(bookA, bookB, field + 1);
                }
            }
            return bookA->year - bookB->year;
        case 4:
            //printf("dif=%d\n", bookA->size - bookB->size);
            return bookA->size - bookB->size;
        default:
            return 0;
    }
}

void printList(Book *bookList) {
    printf("\nList size %d \n", bookListSize);
    for (int i = 0; i < bookListSize; i++) {
        struct Book book = bookList[i];
        printf("==== Book #%d :\n", i + 1);
        printf("\tauthor: %s\n", book.author);
        printf("\tname: %s\n", book.name);
        printf("\tyear: %d\n", book.year);
        printf("\tsize: %d\n", book.size);
    }
    printf("\n");
}

void minimaxSort(Book *bookList) {
    // a0-Z9
    int s = bookListSize;
    while (s > 0) {
        int maxpos = 0;
        for (int i = 0; i < s; i++) {
            if (compareBooks(&bookList[i], &bookList[maxpos], sortField) * (sortDirection == 0 ? -1 : 1) > 0) {
                maxpos = i;
            }
        }
        if (maxpos != s - 1) {
            swap(&bookList[maxpos], &bookList[s - 1]);
        }
        s--;
    }
}

void shellSort(Book *bookList) {
    // a0 - Z9
    int steps[] = {9, 6, 3, 1};
    int stepsNumb = sizeof(steps) / sizeof(int);
    for (int i = 0; i < stepsNumb; i++) {
        int first = 0;
        while (first < bookListSize) {
            int pos = first;
            int max = first;
            while (pos < bookListSize) {
                if (compareBooks(&bookList[pos], &bookList[max], sortField) * (sortDirection == 0 ? 1 : -1) > 0) {
                    max = pos;
                }
                pos = pos + steps[i];
            }
            if (max > first) {
                swap(&bookList[max], &bookList[first]);
            }
            first = first + steps[i];
        }
    }
}

void getSortSpeed() {
    printf("\nEnter the sort speed\n");
    printf("\tslow: 0\n");
    printf("\tfast: 1\n: ");
    while (scanf("%d", &sortSpeed) != 1) {
        printf("Incorrect value, try again: ");
    }
}

void getSortDirection() {
    printf("\nEnter the sort direction\n");
    printf("\tint(Z9-a0): 0\n");
    printf("\tdec(a0-Z9): 1\n: ");
    while (scanf("%d", &sortDirection) != 1) {
        printf("Incorrect value, try again: ");
    }
}

void getSortField() {
    printf("\nEnter the sort field\n");
    printf("\tauthor: 1\n");
    printf("\tname:   2\n");
    printf("\tyear:   3\n");
    printf("\tsize:   4\n: ");
    while (scanf("%d", &sortField) != 1) {
        printf("Incorrect value, try again: ");
    }
}

int main(int argc, char **argv) {
    if (argc == 4) {
        // проверяем по первому символу параментра
        sortSpeed = argv[1][0] == 's' ? 0 : 1;
        sortDirection = argv[2][0] == 'i' ? 0 : 1;

        sortField = atoi(argv[3]);
    }

    printf("------------------------\n");
    printf(" Sort settings:\n");
    printf("   speed:     %s\n", sortSpeed == 0 ? "SLOW" : "FAST");
    printf("   direction: %s\n", sortDirection == 0 ? "INC" : "DEC");
    printf("   field:     %d\n", sortField);
    printf("------------------------\n\n");


    while (1) {
        printf("Enter the numb of books: ");
        if (scanf("%d", &bookListSize)) {
            getchar();
            break;
        } else {
            system("cls");
            printf("Incorrect book numb! Try again. \n");
            //scanf("%s");
            getchar();
        };
    }

    char buffer[256];
    Book *bookList = NULL;
    struct Book newBook;

    for (int i = 0; i < bookListSize; i++) {
        bookList = (Book *) realloc(bookList, sizeof(Book) * (i + 1));
        printf("\nEnter a book #%d: ", i + 1);
        gets(buffer);

        int callback = 0;
        callback += readAuthor(&newBook, buffer);
        callback += readName(&newBook, buffer);
        callback += readYear(&newBook, buffer);
        callback += readSize(&newBook, buffer);
        if (callback > 0) {
            printf("Incorrect book format! Try again. \n");
            i--;
        } else {
            bookList[i] = newBook;
        }
    }


    if (bookListSize <= 0) {
        printf("List is empty!\n");
    } else {
/*
        getSortSpeed();
        getSortDirection();
        getSortField();
*/

        if (sortSpeed == 0) { // выбор направления сортировки
            // Медленная сортировка
            minimaxSort(bookList);
        } else {
            // быстрая
            shellSort(bookList);
            /*
            if (sortDirection == 0) { // выбор направления сортировки
                //forwardHoare(bookList, 0, bookListSize - 1);
                decMinimax(bookList);
            } else {
                incMinimax(bookList);
                //backwardHoare(bookList, 0, bookListSize - 1);
            }
             */
        }
        printList(bookList);


    }

    system("pause");
    return 0;
}