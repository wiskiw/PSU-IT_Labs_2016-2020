#include <stdio.h>
#include <stdlib.h>
#include <cmath>


int main(int argc, char **argv) {
    char *filePath;
    if (argc == 2) {
        filePath = argv[1];
    } else {
        printf("Please, enter the file path: ");
        filePath = (char *) malloc(sizeof(char) * 256); // выделям место в памяти под путь к файлу
        scanf("%s", filePath);
    }

    FILE *file = fopen(filePath, "r"); //для чтения
    if (file == NULL) {
        printf("Cannot open the file: %s\n", filePath);
        return 1;
    }


    float fSum = 0;
    while (!feof(file)) { // пока не конец файла
        float fNumb = 0;
        fscanf(file, "%g", &fNumb);
        if (fNumb < 0 && fabs(fNumb - (int) fNumb) <= 0.5) {
            fSum += fNumb;
        }
    }
    fclose(file);

    printf("Sum: %g\n", fSum);
    system("pause");
    return 0;
}