#include <stdio.h>
#include <malloc.h>

typedef unsigned long long int big;
const char DEFAULT_FILE_PATH[] = "file"; // путь к файлу при генерации

// функция генирации бинарного файла
void generateFile(big *values, int arrLen) {
    FILE *vFile = fopen(DEFAULT_FILE_PATH, "wb+"); // для записи в бинарном виде
    for (int i = 0; i < arrLen; i++) {
        big v = values[i];

        fwrite(&v, sizeof(big), 1, vFile);
        //fwrite(указатель на буффер, размер одного элемента
        //буфера, кол-во элементов, указатель на файл)
    }
    fclose(vFile);
}

// проверка на простое число
bool isSimple(big v) {
    if (v % v == 0 && v % 1 == 0) {
        for (int i = 2; i < 10; i++) {
            if (i != v && v % i == 0) {
                return false;
            }
        }
        return true;
    }
    return false;
}


int main(int argc, char **argv) {

    // простые: 1009 83 2081
    // sum = 5254
    big valuesToWrite[] = {2081, 12, 2081, 15, 16, 22, 2015, 20, 1009, 83}; // что записать в файл
    int arrLen = sizeof(valuesToWrite) / sizeof(big);
    generateFile(valuesToWrite, arrLen);


    char *filePath;
    if (argc == 2) {
        filePath = argv[1];
    } else {
        printf("Please, enter the file path: ");
        filePath = (char *) malloc(sizeof(char) * 256); // выделям место в памяти под путь к файлу
        scanf("%s", filePath);
    }

    FILE *file = fopen(filePath, "rb");
    if (file == NULL) {
        printf("Cannot open the file: %s\n", filePath);
        return 1;
    }

    big d = 0;
    big bigSum = 0;

    int res = fread(&d, sizeof(big), 1, file);
    while (res == 1) {// пока значения считаны успешно
        if (isSimple(d)) {
            bigSum += d;
        }
        res = fread(&d, sizeof(big), 1, file);
    }
    fclose(file);
    printf("Sum: %lld\n", bigSum);


    system("pause");
    return 0;
}