/*
КНИГА:
•	код ISBN (строка 15 символов)
•	фамилия и инициалы автора (строка 15 символов);
•	название книги (строка 20 символов);
•	год издания (целое четырехзначное число);
•	количество страниц (целое четырехзначное число).
 */

#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>

/*
// Для теста сортировок копируем текст ниже и вставляем сразу после запуска.
3
ISBN_CODE_1
Author A
Book Name1
1964
503
ISBN_CODE_3
Author F
Book Name8
2001
5
ISBN_CODE_2
Author B
Book Name12
2020
181
1

 */

struct Book {
    char code[16];
    char author[16];
    char name[21];
    unsigned int year;
    unsigned int pages;
};


int scanBook(Book *book) {
    // функция сканирования книги
    // возвращает 1 - если ошибка
    // 0- если все успешно

    printf("ISBN code [max15]: ");
    getchar();
    gets(book->code);

    printf("author [max15]: ");
    gets(book->author);

    printf("name [max20]: ");
    gets(book->name);


    printf("year [0-9999]: ");
    if (scanf("%d", &book->year) != 1 || book->year < 0 || book->year > 9999) {
        // ошибка в дате
        return 1;
    }

    printf("pages [0-...]: ");
    if (scanf("%d", &book->pages) != 1 || book->pages < 0) {
        // ошибка в кол-ве страниц
        return 1;
    }


    return 0;
}

void scanList(int size, Book *array) {
    for (int i = 0; i < size; i++) {
        Book book;
        system("cls"); // чистка консоли
        printf("===book #%d\n", i + 1);
        if (scanBook(&book) == 1) {
            // если ошибка при вводе книги
            printf("Incorrect book!\n");
            printf("Try again\n");
            i--;
        } else {
            // если ввод успешен, сохраняем книгу в массив
            array[i] = book;
        }
    }
    system("cls");
}

void printList(int size, Book *array) {
    // функция вывода массива книг
    printf("==== Book List [%d] ===\n", size);
    for (int i = 0; i < size; i++) {
        Book book = array[i];
        printf(" ---- Book #%d\n", i + 1);
        printf("   ISBN code: '%s'\n", book.code);
        printf("   author: '%s'\n", book.author);
        printf("   name: '%s'\n", book.name);
        printf("   year: %d\n", book.year);
        printf("   pages: %d\n", book.pages);
    }
}


/*
  Все функция сравнения ( compare... ) возвращают
    > 1 если элементы стоят по убыванию(по алфавиту)
    > 1 если элементы стоят по возрастанию
    = 0 элементы равны

    P.S Функция strcmp() сравнивает дву строки
 */

int compareCode(Book *bookA, Book *bookB) {
    return strcmp(bookA->code, bookB->code);
}

int compareAuthor(Book *bookA, Book *bookB) {
    return strcmp(bookA->author, bookB->author);
}

int compareName(Book *bookA, Book *bookB) {
    return strcmp(bookA->name, bookB->name);
}

int compareYear(Book *bookA, Book *bookB) {
    return bookA->year - bookB->year;
}

int comparePages(Book *bookA, Book *bookB) {
    return bookA->pages - bookB->pages;
}


// Функция меняет местами две книги
void swap(Book *bookA, Book *bookB) {
    Book temp = *bookA;
    *bookA = *bookB;
    *bookB = temp;
}

// Сортировка пузырем (По Убыванию)
void forwardBobbleSort(int size, Book *array, int (*compare)(Book *, Book *)) {
    // *compare - указатель на функцию сравнения
    for (int i = size - 1; i >= 0; i--) {
        for (int j = size - 1; j > i; j--) {
            Book *bookA = &array[j - 1];
            Book *bookB = &array[j];
            if (compare(bookA, bookB) >=
                0) { // compare(bookA, bookB) вызывает одну из функций сравнения(завит от того, что выбрал пользователь)
                swap(bookA, bookB);
            }
        }
    }
}

// Сортировка пузырем (По Возрастания)
void backwardBobbleSort(int size, Book *array, int (*compare)(Book *, Book *)) {
    // *compare - указатель на функцию сравнения
    for (int i = 0; i < size; i++) {
        for (int j = size - 1; j > i; j--) {
            Book *bookA = &array[j - 1];
            Book *bookB = &array[j];
            if (compare(bookA, bookB) <=
                0) {// compare(bookA, bookB) вызывает одну из функций сравнения(завит от того, что выбрал пользователь)
                swap(bookA, bookB);
            }
        }
    }
}


int main() {
    int size = 0;
    printf("The list size: ");
    scanf("%d", &size);
    Book booksArray[size]; // создаем массив для хранения книг
    scanList(size, booksArray); // считываем книги

    int field = 1;
    int
    (*compare)(Book *, Book *); // *compare - указатель на функцию сравнения. Его будем передовать в функцию сортировки
    int dir = 0;

    printf("\n ");
    while (1) {
        int tsN = -1;
        printf("\t[1] - print list;\n");
        printf("\t[2] - sort list;\n");
        printf("\t[0] - exit \t\n: ");

        scanf("%d", &tsN);
        getchar();
        switch (tsN) {
            case 0:
                system("cls");
                return 0;
            case 1:
                system("cls");
                printList(size, booksArray); // отображение списка книг
                break;
            case 2:
                system("cls");
                printf("Sort field\n");
                printf("\tcode   : 1\n");
                printf("\tauthor : 2\n");
                printf("\tname   : 3\n");
                printf("\tyear   : 4\n");
                printf("\tpages  : 5\n");
                printf(":");
                scanf("%d", &field); // выбор поля сортировки
                // присваеваем указателю на функцию сравнения - нужную функцию сранения
                switch (field) {
                    case 1:
                        compare = compareCode;
                        break;
                    case 2:
                        compare = compareAuthor;
                        break;
                    case 3:
                        compare = compareName;
                        break;
                    case 4:
                        compare = compareYear;
                        break;
                    default:
                        compare = comparePages;
                        break;
                }

                printf("Sort direction\n");
                printf("\ta->Z: 1\n");
                printf("\tZ->a: 2\n");
                printf(":");
                scanf("%d", &dir); // выбор направления сортировки
                // запускаем нужню сортировку и передаем туда указатель на функцию сравнения
                switch (dir) {
                    case 1:
                        forwardBobbleSort(size, booksArray, compare);
                        break;
                    case 2:
                        backwardBobbleSort(size, booksArray, compare);
                        break;
                    default:
                        printf("Unknown direction!\n");
                }
                break;
            default:
                system("cls");
                printf("\tUnknown command, try again");
        }
        printf("\n");
    }
}


