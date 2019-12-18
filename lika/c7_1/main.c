#include <stdio.h>
#include <stdlib.h>


// Функция преобразования символа цифры(char) в цифру(int)
int getInt(int c) {
    return c - '0';
}

int main(int argc, char **argv) {
    char *filePath;
    if (argc == 2) {
        filePath = argv[1];
    } else {
        printf("Please, enter the file path: ");
        filePath = malloc(sizeof(char) * 256); // выделям место в памяти под путь к файлу
        scanf("%s", filePath);
    }

    FILE *file = fopen(filePath, "r"); // Открываем файл для чтения
    if (file == NULL) { // Если не удалось открыть файл
        printf("Cannot open the file: %s\n", filePath);
        return 1;
    }


    int twoNumbCounter = 0;
    int threeNumbCounter = 0;

    int tempN = 0;
    while (!feof(file)) { // пока не конец файла
        int c = fgetc(file); // читаем символ
        if (c >= '0' && c <= '9') { // если символ - цифра
            // считаем конкретное число
            tempN = tempN * 10 + getInt(c);
        } else if (tempN != 0) {
            // закончили чтение конкретного числа
            if (tempN % 2 == 0) {
                // проверяем на кратность 2
                twoNumbCounter++;
            }
            if (tempN % 3 == 0) {
                // проверяем на кратность 3
                threeNumbCounter++;
            }
            tempN = 0;
        }
    }
    fclose(file);

    if (twoNumbCounter > threeNumbCounter) {
        // Кратных двум больше
        printf("A multiple of two numbers more (two:%d > three:%d)\n", twoNumbCounter, threeNumbCounter);
    } else if (threeNumbCounter > twoNumbCounter) {
        // Кратных трем больше
        printf("A multiple of three numbers more (two:%d < three:%d)\n", twoNumbCounter, threeNumbCounter);
    } else {
        // кол-во равно
        printf("Their number is equal (%d)\n", twoNumbCounter);
    }


    system("pause");
    return 0;
}