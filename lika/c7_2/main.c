#include <stdio.h>
#include <malloc.h>
#include <float.h>


const char DEFAULT_FILE_PATH[] = "file"; // путь к файлу при генерации

// функция генирации бинарного файла
void generateFile(double *values, int arrLen){
    FILE *vFile = fopen(DEFAULT_FILE_PATH, "wb+"); // для записи в бинарном виде
    for (int i = 0; i < arrLen; i++) {
        double v = values[i];

        fwrite(&v, sizeof(double), 1, vFile); // запись в бинарный файл
        //fwrite(указатель на буффер, размер одного элемента
        //буфера, кол-во элементов, указатель на файл)
    }
    fclose(vFile);
}

// функция поиска числа из массива, стремящегося к previewMin справа
double findMin(double *array, int arrLen, double previewMin){
    double min = DBL_MAX; // DBL_MAX = максимальное значение типа double
    for (int i = 0; i < arrLen; i++) {
        double d = array[i];
        if (previewMin < d && min > d){
            min = d;
        }
    }
    return min;
}

// функция поиска числа из массива, стремящегося к previewMax слева
double findMax(double *array, int arrLen, double previewMax){
    double max = DBL_MIN; // DBL_MIN = минимально значение типа double
    for (int i = 0; i < arrLen; i++) {
        double  d = array[i];
        if (previewMax > d && max < d){
            max = d;
        }
    }
    return max;
}


int main(int argc, char **argv) {

    double valuesToWrite[] = {12.5, 15.8, 16.568, 22.8, 2015, 20.15}; // что записать в файл
    int arrLen = sizeof(valuesToWrite) / sizeof(double); // вычислям длинну массивы с переменными
    generateFile(valuesToWrite, arrLen); // создание бинарного файла


    char *filePath;
    if (argc == 2) {
        filePath = argv[1];
    } else {
        printf("Please, enter the file path: ");
        filePath = malloc(sizeof(char) * 256); // выделям место в памяти под путь к файлу
        scanf("%s", filePath);
        //filePath = (char *) DEFAULT_FILE_PATH;
    }

    FILE *file = fopen(filePath, "rb"); // Открываем файл для чтения
    if (file == NULL) { // Если не удалось открыть файл
        printf("Cannot open the file: %s\n", filePath);
        return 1;
    }

    double d = 0;
    double *values = NULL;

     // читаем значение из файла и записываем в первую ячейку массива
    // (fread возвращает количество успешно считанных значений)
    int res = fread(&d, sizeof(double), 1, file);

    int count = 0;
    while (res == 1) {// пока значения считаны успешно (не конец файла)
        values = realloc(values, sizeof(d) * (count + 1)); // расширяем массив с данными на 1 ячейку для новой записи
        values[count] = d;
        res = fread(&d, sizeof(double), 1, file); // читаем и записывем новые данные
        count++;
    }
    fclose(file);


    double max1 = findMax(values, count, DBL_MAX); // Поиск первого максимума
    double max2 = findMax(values, count, max1); // Поиск второго максимума (максимум после max1)

    double min1 = findMin(values, count, DBL_MIN); // Поиск первого минимума
    double min2 = findMin(values, count, min1); // Поиск второго минимума (минимум после min1)
    double min3 = findMin(values, count, min2); // Поиск третьего минимума (минимум после min2)


    printf("Second max: %g\n", max2);
    printf("Third min: %g\n", min3);
    printf("Sum: %g\n", max2 + min3);


    system("pause");
    return 0;
}