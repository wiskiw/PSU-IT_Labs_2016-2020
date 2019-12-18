#include <stdio.h>
#include <malloc.h>
#include <string.h>

// Стандартные установки сортировки:
int sortSpeed = 0; // 0 - slow, 1 - fast
int sortDirection = 0; // 0 - inc(forward), 1 - dec(backward)
int sortField = 1; // 1 - 4

int bookListSize = 0;

struct Book {
    char author[16];
    char name[21];
    unsigned int year;
    unsigned int size;
};

// Формат ввода: код ISBN: Фамилия И. О. «Название», год, кол-во страниц
// ISBN: Author R "Book Name" 2015 228

int readAuthor(struct Book *book, char line[]) {
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

int readName(struct Book *book, char line[]) {
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

int readYear(struct Book *book, char line[]) {
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

int readSize(struct Book *book, char line[]) {
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
void swap(struct Book *bookA, struct Book *bookB) {
    struct Book bookTemp = *bookA;
    *bookA = *bookB;
    *bookB = bookTemp;
}

int compareBooks(struct Book *bookA, struct Book *bookB, int field) {
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

// Сортировка пузырем (По возрастания)
void forwardBobbleSort(struct Book *bookList) {
    // Внешний цикл алгоритма совершает
    // ровно size итераций
    for (int i = 0; i < bookListSize; i++) {
        // Массив просматривается с конца до
        // позиции i и "легкие элементы всплывают"
        for (int j = bookListSize - 1; j > i; j--) {
            struct Book *bookA = &bookList[j - 1];
            struct Book *bookB = &bookList[j];
            if (compareBooks(bookA, bookB, sortField) > 0) {
                swap(bookA, bookB);
            }
        }
    }
}

// Сортировка пузырем (По убыванию)
void backwardBobbleSort(struct Book *bookList) {
    // Внешний цикл алгоритма совершает
    // ровно size итераций
    for (int i = bookListSize - 1; i >= 0; i--) {
        // Массив просматривается с конца до
        // позиции i и "легкие элементы всплывают"
        //
        for (int j = bookListSize - 1; j > i; j--) {
            struct Book *bookA = &bookList[j - 1];
            struct Book *bookB = &bookList[j];
            if (compareBooks(bookA, bookB, sortField) < 0) {
                swap(bookA, bookB);
            }
        }
    }
}

// Метод быстрой сортировки Хоара (с рекурсивным вызовом) (По убыванию)
void backwardHoare(struct Book *bookList, int first, int last) {
    int i = first, j = last;
    struct Book *x = &bookList[(first + last) / 2];
    do {
        while (compareBooks(&bookList[i], x, sortField) > 0) i++;
        while (compareBooks(&bookList[j], x, sortField) < 0) j--;

        if (i <= j) {
            if (compareBooks(&bookList[i], &bookList[j], sortField) < 0) {
                swap(&bookList[i], &bookList[j]);
            }
            i++;
            j--;
        }
    } while (i <= j);
    if (i < last) backwardHoare(bookList, i, last);
    if (first < j) backwardHoare(bookList, first, j);
}

// Сортировка Хоара (По возрастания)
void forwardHoare(struct Book *bookList, int first, int last) {
    backwardHoare(bookList, first, last);
    // инвертируем сипсок книг
    struct Book tempBook;
    for (int i = 0; i < bookListSize / 2; i++) {
        tempBook = bookList[i];
        bookList[i] = bookList[bookListSize - i - 1];
        bookList[bookListSize - i - 1] = tempBook;
    }
}

void printList(struct Book *bookList) {
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
            scanf("%s");
            getchar();
        };
    }

    char buffer[256];
    struct Book *bookList = NULL;
    struct Book newBook;

    for (int i = 0; i < bookListSize; i++) {
        bookList = realloc(bookList, sizeof(struct Book) * (i + 1));
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
        if (sortSpeed == 0) { // выбор направления сортировки
            // Медленная сортировка
            if (sortDirection == 0) {
                forwardBobbleSort(bookList);
            } else {
                backwardBobbleSort(bookList);
            }
        } else {
            // быстрая
            if (sortDirection == 0) { // выбор направления сортировки
                forwardHoare(bookList, 0, bookListSize - 1);
            } else {
                backwardHoare(bookList, 0, bookListSize - 1);
            }
        }
        printList(bookList);


    }

    system("pause");
    return 0;
}