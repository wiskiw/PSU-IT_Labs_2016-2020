#include <stdio.h>
#include <stdlib.h>
#include <mem.h>


int listSize = 0; // количество считаных структур
int lineIndex = 0; // номер строки файла/консоли , которую сейчас читаем (от 0 до много-много)
int docLineIndex; // номер строки при считывание каждой стркутуры (от 0 до 3)

struct Date {
    int day;
    int month;
    int year;
};

struct Document {
    int numb;
    struct Date date;
    double sum;
    char name[21]; // +1 для символа конца строки "\0"
};

int getInt(int c) {
    return c - '0';
}

// функция обработки строки в номер
int parseNumb(char *line) {
    if (strspn(line, "0123456789. \n\n") != strlen(line)) {
        // если в строке есть что-то кроме этих символов
        return 0;
    }
    return atoi(line);
}

// поиск индекса первого символа с начала строки, который не пробел в строке с датой
// возвращает -1, если дата не соответствует формату dd.mm.yyyy
int getDateStartIndex(char *temp) {
    if (strchr(temp, '.') != NULL) { // Если в строке есть хоть одна точка
        int startIndex = 0;
        // поиск индекса первого символа с начала строки, который не пробел
        for (; temp[startIndex] == ' '; startIndex++);
        if (temp[startIndex + 2] == '.' && temp[startIndex + 5] == '.') {
            if (strspn(temp, "0123456789. \n") != strlen(temp)) {
                // если в строке есть что-то кроме этих символов
                return -1;
            } else {
                return startIndex;
            }
        } else {
            return -1;
        };
    } else {
        return -1;
    }
}

// функция обработки строки в день даты
int parseDateDay(char *line) {
    char temp[strlen(line)]; // временная строка
    strcpy(temp, line);
    int startIndex = getDateStartIndex(temp);
    if (startIndex == -1) {
        // если дата не корректна
        return 0;
    }
    return getInt(temp[startIndex]) * 10 + getInt(temp[startIndex + 1]);
}

// функция обработки строки в месяц даты
int parseDateMonth(char *line) {
    char temp[strlen(line)]; // временная строка
    strcpy(temp, line);
    int startIndex = getDateStartIndex(temp);
    if (startIndex == -1) {
        // если дата не корректна
        return 0;
    }
    return getInt(temp[startIndex + 3]) * 10 + getInt(temp[startIndex + 4]);
}

// функция обработки строки в год даты
int parseDateYear(char *line) {
    char temp[strlen(line)]; // временная строка
    strcpy(temp, line);
    int startIndex = getDateStartIndex(temp);
    if (startIndex == -1) {
        // если дата не корректна
        return 0;
    }
    return getInt(temp[startIndex + 6]) * 1000 + getInt(temp[startIndex + 7]) * 100
           + getInt(temp[startIndex + 8]) * 10 + getInt(temp[startIndex + 9]);
}

// функция обработки суммы
double parseSum(char *line) {
    if (strspn(line, "0123456789. \n") != strlen(line)) {
        // если в строке есть что-то кроме этих символов
        return 0;
    }
    return atof(line);
}

// функция заполнение структуры newDoc по строкам line
// Возвращает 0 если структура полностью записана
// 1 - структура записана не до конца
int parseLine(struct Document *newDoc, char *line) {
    if (line[0] == '\n' || line[0] == '\0') {
        // если пустая строка, то пропускаем её;
        return 1;
    }

    switch (docLineIndex) {
        case 0:
            // если это первая строка(индекс 0), то в ней номер
            //newDoc = doc;
            newDoc->numb = parseNumb(line);
            if (newDoc->numb == 0) {
                printf("Incorrect document on %d line\n", lineIndex + 1);
            }
            break;
        case 1:
            // вторая - дата в формате dd.mm.yyyy
            newDoc->date.day = parseDateDay(line);
            newDoc->date.month = parseDateMonth(line);
            newDoc->date.year = parseDateYear(line);
            if (newDoc->date.day == 0 || newDoc->date.month == 0 || newDoc->date.year == 0) {
                printf("Incorrect date format on %d line\n", lineIndex + 1);
            }
            break;
        case 2:
            // сумма
            newDoc->sum = parseSum(line);
            if (newDoc->sum == 0) {
                printf("Incorrect document on %d line\n", lineIndex + 1);
            }
            break;

        case 3:
            // имя
            strncpy(newDoc->name, line, 20);
            newDoc->name[20] = '\0';
            //docList = realloc(docList, sizeof(struct Document) * (listSize + 1));

            //docList[listSize] = newDoc; // сохраняем структуру в массив
            docLineIndex = 0;
            //listSize++;
            return 0;
            //continue;
    }
    docLineIndex = docLineIndex + 1;
    return 1;
}

// функция поиска структур, дата которых равна date
// (будут удалены все несоответствующие структуры из docList)
void findByDate(struct Document *docList, struct Date *date) {
    if (date->day == 0 || date->month == 0 || date->year == 0) {
        return;
    }

    for (int i = 0; i < listSize; i++) {
        struct Date docDate = docList[i].date;
        if (docDate.day != date->day || docDate.month != date->month || docDate.year != date->year) {
            // если струтруктура не подходит
            listSize--;
            // смещаем все последующие в списке на её место
            for (int j = i; j < listSize + 1; j++) {
                docList[j] = docList[j + 1];
            }
        }
    }

}

// функция отображения содержимого бинарного файла
void showMeTheFile(char *filePath) {
    FILE *file = fopen(filePath, "rb"); // открываем для чтения
    if (file == NULL) {
        printf("Cannot open the file: %s\n", filePath);
        return;
    }

    struct Document doc;
    int res = fread(&doc, sizeof(struct Document), 1, file); // пытаемся прочитать первую струтуру

    printf("\n");
    for (int i = 0; res == 1; i++) { // если и пока значения считаны успешно (не конец файла)
        // рисуем структуру в консоль
        printf("%15s%d\n", "FILE # ", i + 1);
        printf("numb: %d\n", doc.numb);
        struct Date date = doc.date;
        printf("date: %d.%d.%d\n", date.day, date.month, date.year);
        printf("sum: %g\n", doc.sum);
        printf("name: %s\n\n", doc.name);

        res = fread(&doc, sizeof(doc), 1, file); // читаем следующую структуру
    }
    printf("\n");
    fclose(file);
}

int main(int argc, char **argv) {
    char *filePath;
    if (argc == 2) {
        filePath = argv[1];
    } else {
        printf("Please, enter the file path: ");
        filePath = malloc(sizeof(char) * 256); // выделям место в памяти под путь к файлу
        scanf("%s", filePath);
        getchar();
    }

    struct Document *docList = NULL;
    struct Document newDoc;
    char buffer[256]; // буфер для чтения каждой строки исходного файл
    int result;

    FILE *file = fopen(filePath, "r"); // Открываем файл для чтения
    if (file != NULL) {
        // успешно нашли и открыли файл
        for (; !feof(file); lineIndex++) { // пока не конец файла
            fgets(buffer, 256, file); // читаем строку в буфер
            result = parseLine(&newDoc, buffer);
            if (result == 0) {
                // выделаям память в массиве под новую структуру
                docList = realloc(docList, sizeof(struct Document) * (listSize + 1));
                docList[listSize] = newDoc; // сохраняем структуру в массив
                listSize++;
            }
        }
    } else {
        // Если не удалось открыть файл
        printf("Cannot open the file: %s\n", filePath);
        printf("Please, enter the structure line by line:\n\n");
        for (; 1; lineIndex++) {
            switch (docLineIndex) {
                case 0:
                    printf("Number: ");
                    break;
                case 1:
                    printf("Date (dd.mm.yyyy): ");
                    break;
                case 2:
                    printf("Sum: ");
                    break;
                case 3:
                    printf("Name: ");
                    break;
            }
            gets(buffer);
            if (buffer[0] == '\n' || buffer[0] == '\0') {
                break; // завершаем ввод структур, если введена пустая строка
            } else {
                result = parseLine(&newDoc, buffer);
                if (result == 0) {
                    printf("\n");
                    // выделаям память в массиве под новую структуру
                    docList = realloc(docList, sizeof(struct Document) * (listSize + 1));
                    docList[listSize] = newDoc; // сохраняем структуру в массив
                    listSize++;
                }
            }
        }

    };


    printf("List size: %d\n", listSize);

    printf("\nEnter the date(dd.mm.yyyy): ");
    char dateLine[256];
    gets(dateLine);
    struct Date dateToFound;
    dateToFound.day = parseDateDay(dateLine);
    dateToFound.month = parseDateMonth(dateLine);
    dateToFound.year = parseDateYear(dateLine);
    if (dateToFound.day == 0 || dateToFound.month == 0 || dateToFound.year == 0) {
        printf("Incorrect date format!\n");
    }

    findByDate(docList, &dateToFound);

    if (listSize == 0) {
        // если не нашли ни одной структуры с нужно датой
        printf("No data with date %d.%d.%d found. Nothing to binary save!\n",
               dateToFound.day, dateToFound.month, dateToFound.year);
    } else {
        char *postPtr = strchr(filePath, '.'); // получаем указатель на расширение файла: .txt
        int postLent = postPtr == NULL ? 0 : strlen(postPtr); // считаем кол-во символов в расширении всместе с точкой

        char resultFilePath[strlen(filePath) - postLent + 4];
        // Обявляем строку с названием файла результата:
        // длинна исходного названия файла
        // минус кол-во символов расширения в исходном файле
        // плюс 4 - количество символов в новом расширении: .bin

        strncpy(resultFilePath, filePath, strlen(filePath) - postLent); // копируем старое название без расширения
        strcat(resultFilePath, ".bin"); // добавляем новое расширение

        FILE *resultFile = fopen(resultFilePath, "wb+");
        for (int i = 0; i < listSize; i++) {
            struct Document document = docList[i];
            fwrite(&document, sizeof(struct Document), 1, resultFile);
        }
        fclose(resultFile);

        showMeTheFile(resultFilePath);
    }


    system("pause");
    return 0;
}