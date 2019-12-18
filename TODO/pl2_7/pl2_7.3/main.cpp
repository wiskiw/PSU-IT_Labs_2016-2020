#include <stdio.h>
#include <stdlib.h>
#include <mem.h>


/*
 ФАЙЛ:
•	имя файла (строка 30 символов, уникальное поле);
•	размер файла (целое число);
•	дата создания (в формате дд.мм.гггг);
•	время создания (в формате чч:мм).

 */

/*

bbfile.txt
512
12.05.2016
22:15
ccfile.txt
816
02.04.2000
02:35
aafile.txt
816
02.04.2000
00:01


 */


struct Date {
    int day;
    int month;
    int year;
};

struct Time {
    int minute;
    int hour;
};


struct File {
    char name[31];
    unsigned int size;
    Date date;
    Time time;
};

File *fileList = NULL;
int listSize = 0; // количество считаных структур
int lineIndex = 0; // номер строки файла/консоли , которую сейчас читаем (от 0 до много-много)
int docLineIndex; // номер строки при считывание каждой стркутуры (от 0 до 3)

int getInt(int c) {
    return c - '0';
}

// функция обработки строки в номер
int parseNumb(char *line) {
    if (strspn(line, "0123456789 \n\n") != strlen(line)) {
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

int getTimeStartIndex(char *temp) {
    int startIndex = 0;
    // поиск индекса первого символа с начала строки, который не пробел
    for (; temp[startIndex] == ' '; startIndex++);
    if (temp[startIndex + 2] == ':') {
        if (strspn(temp, "0123456789: \n") != strlen(temp)) {
            // если в строке есть что-то кроме этих символов
            return -1;
        } else {
            return startIndex;
        }
    } else {
        return -1;
    };
}

// функция обработки строки в минуты времени
int parseTimeMinute(char *line) {
    char temp[strlen(line)]; // временная строка
    strcpy(temp, line);
    int startIndex = getTimeStartIndex(temp);
    if (startIndex == -1) {
        // если дата не корректна
        return -1;
    }
    return getInt(temp[startIndex]) * 10 + getInt(temp[startIndex + 1]);
}

// функция обработки строки в часы времени
int parseTimeHour(char *line) {
    char temp[strlen(line)]; // временная строка
    strcpy(temp, line);
    int startIndex = getTimeStartIndex(temp);
    if (startIndex == -1) {
        // если дата не корректна
        return -10;
    }
    return getInt(temp[startIndex + 3]) * 10 + getInt(temp[startIndex + 4]);
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

// функция заполнение структуры newDoc по строкам line
// Возвращает 0 если структура полностью записана
// 1 - структура записана не до конца
int parseLine(File *newFile, char *line) {
    if (line[0] == '\n' || line[0] == '\0') {
        // если пустая строка, то пропускаем её;
        return 1;
    }

    switch (docLineIndex) {
        case 0:
            // имя
            strncpy(newFile->name, line, 30);
            newFile->name[30] = '\0';

            break;
        case 1:
            // размер файла
            newFile->size = (unsigned int) parseNumb(line);
            if (newFile->size == 0) {
                printf("Incorrect document on %d line\n", lineIndex + 1);
            }
            break;
        case 2:
            // дата
            newFile->date.day = parseDateDay(line);
            newFile->date.month = parseDateMonth(line);
            newFile->date.year = parseDateYear(line);
            if (newFile->date.day == 0 || newFile->date.month == 0 || newFile->date.year == 0) {
                printf("Incorrect date format on %d line\n", lineIndex + 1);
            }
            break;

        case 3:
            // время
            newFile->time.hour = parseTimeHour(line);
            newFile->time.minute = parseTimeMinute(line);
            if (newFile->time.hour == -1 || newFile->time.minute == -1) {
                printf("Incorrect time format on %d line\n", lineIndex + 1);
            }
            docLineIndex = 0;
            return 0;
    }
    docLineIndex = docLineIndex + 1;
    return 1;
}

// функция отображения содержимого бинарного файла
void showMeTheFile(char *filePath) {
    FILE *resultFile = fopen(filePath, "rb"); // открываем для чтения
    if (resultFile == NULL) {
        printf("Cannot open the file: %s\n", filePath);
        return;
    }

    File fl;
    int res = fread(&fl, sizeof(File), 1, resultFile); // пытаемся прочитать первую струтуру

    printf("\n");
    for (int i = 0; res == 1; i++) { // если и пока значения считаны успешно (не конец файла)
        // рисуем структуру в консоль
        printf("%15s%d\n", "FILE # ", i + 1);
        printf("name: '%s'\n", fl.name);
        printf("size: %d\n", fl.size);
        printf("date: %02d.%02d.%02d\n", fl.date.day, fl.date.month, fl.date.year);
        printf("time: %02d:%02d\n", fl.time.minute, fl.time.hour);

        res = fread(&fl, sizeof(File), 1, resultFile); // читаем следующую структуру
    }
    printf("\n");
    fclose(resultFile);
}


void swap(File *fileA, File *fileB) {
    File fileTemp = *fileA;
    *fileA = *fileB;
    *fileB = fileTemp;
}

// Сортировка пузырем (По Возрастания)
void backwardBobbleSort() {
    for (int i = 0; i < listSize; i++) {
        for (int j = listSize - 1; j > i; j--) {
            File *fileA = &fileList[j - 1];
            File *fileB = &fileList[j];
            if (strcmp(fileA->name, fileB->name) < 0) {
                swap(fileA, fileB);
            }
        }
    }
}

// Сортировка пузырем (По Убыванию)
void forwardBobbleSort() {
    for (int i = listSize - 1; i >= 0; i--) {
        for (int j = listSize - 1; j > i; j--) {
            File *fileA = &fileList[j - 1];
            File *fileB = &fileList[j];
            if (strcmp(fileA->name, fileB->name) >= 0) {
                swap(fileA, fileB);
            }
        }
    }
}

int main(int argc, char **argv) {
    char *filePath;
    if (argc == 2) {
        filePath = argv[1];
    } else {
        printf("Please, enter the file path: ");
        filePath = (char *) malloc(sizeof(char) * 256); // выделям место в памяти под путь к файлу
        scanf("%s", filePath);
        getchar();
    }

    File newFile;
    char buffer[256]; // буфер для чтения каждой строки исходного файл
    int result;

    FILE *rFile = fopen(filePath, "r"); // Открываем файл для чтения
    if (rFile != NULL) {
        // успешно нашли и открыли файл
        for (; !feof(rFile); lineIndex++) { // пока не конец файла
            fgets(buffer, 256, rFile);
            result = parseLine(&newFile, buffer);
            if (result == 0) {
                fileList = (File *) realloc(fileList, sizeof(File) * (listSize + 1));
                fileList[listSize] = newFile; // сохраняем структуру в массив
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
                    printf("Name: ");
                    break;
                case 1:
                    printf("Size: ");
                    break;
                case 2:
                    printf("Date (dd.mm.yyyy): ");
                    break;
                case 3:
                    printf("Time (mm:hh): ");
                    break;
            }
            gets(buffer);
            if (buffer[0] == '\n' || buffer[0] == '\0') {
                break; // завершаем ввод структур, если введена пустая строка
            } else {
                result = parseLine(&newFile, buffer);
                if (result == 0) {
                    printf("\n");
                    fileList = (File *) realloc(fileList, sizeof(File) * (listSize + 1));
                    fileList[listSize] = newFile; // сохраняем структуру в массив
                    listSize++;
                }
            }
        }

    };


    printf("List size: %d\n", listSize);

    printf("Sort direction\n");
    printf("\ta->Z: 1\n");
    printf("\tZ->a: 2\n");
    printf(":");
    int dir = 0;
    scanf("%d", &dir);
    switch (dir) {
        case 1:
            forwardBobbleSort();
            break;
        case 2:
            backwardBobbleSort();
            break;
        default:
            printf("Unknown direction!\n");
    }

    if (listSize > 0) {
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
            File file = fileList[i];
            fwrite(&file, sizeof(File), 1, resultFile);
        }
        fclose(resultFile);
        showMeTheFile(resultFilePath);
    }


    system("pause");
    return 0;
}