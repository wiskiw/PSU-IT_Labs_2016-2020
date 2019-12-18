#include <iostream>

using namespace std;

/*
 VAR 3
 Выполнить сортировку целых чисел алгоритмом сбалансированного много-
путевого слияния.


 https://habrahabr.ru/post/281675/
 */


int getNumber(int *number);

int cleanBuf();


int *aData; // один файл - А

int **bFiles; // несколько файлов b (b1, b2, ... b)
int *bFileSizes; // количество записей в каждом конкретном B - "файле"

int *cFileSizes; // количество записей в каждом конкретном C - "файле"
int **cFiles; // несколько файлов c (c1, c2, ... c)

void initBuffers(size_t aFileLength) {
    aData = static_cast<int *>(calloc(aFileLength, sizeof(int)));


    /*
     массивы bFiles и cFiles -  двумерные, размером aFileLength*aFileLength .
     Т.к. в наихудшем случае максимальная длинна всех последовательностей может быть 1,
     следовательно, тогда, понадобится aFileLength временных файлов
     */

    bFileSizes = static_cast<int *>(calloc(aFileLength, sizeof(int)));
    bFiles = static_cast<int **>(calloc(aFileLength, aFileLength * sizeof(int *)));
    for (int i = 0; i < aFileLength; i++) {
        bFiles[i] = (int *) malloc(sizeof(int) * aFileLength);
    }

    cFileSizes = static_cast<int *>(calloc(aFileLength, sizeof(int)));
    cFiles = static_cast<int **>(calloc(aFileLength, aFileLength * sizeof(int *)));
    for (int i = 0; i < aFileLength; i++) {
        cFiles[i] = (int *) malloc(sizeof(int) * aFileLength);
    }
}

void fillTextValue() {
    aData[0] = 8;
    aData[1] = 10;
    aData[2] = 4;
    aData[3] = 6;
    aData[4] = 7;
    aData[5] = 5;
    aData[6] = 12;
    aData[7] = 1;
}


void printArray(int *arr, int len) {
    if (len > 0) {
        cout << "=== ARRAY(len=" << len << "):\n";
        for (int i = 0; i < len; ++i) {
            cout << "[" << i << "]: " << arr[i] << endl;
        }
        cout << "==================\n";
    }
}

void divideFileForFiles(int srcLen, const int *src, int *fileLens, int **files) {
    // делит содержимое файла по другим файлам, группируя сортированные
    /*
     src - массив исходных данных
     srcLen - количество исходных данных

     files - двумерный массив для сохранения группированных данных
     fileLens - массив размеров массивов с группированными данными
     */


    int currentFileIndex = 0;
    for (int i = 0; i < srcLen; ++i) {
        int newInt = src[i];
        if (i - 1 >= 0 && src[i - 1] > newInt) {
            //cout << "------------\n";
            currentFileIndex++;
        }
        //cout << "src[i]: " << i << " : " << newInt << endl;
        files[currentFileIndex][fileLens[currentFileIndex]] = newInt;
        fileLens[currentFileIndex]++;

    }
}

void concateArrays(int lenT1, int *t1, int lenT2, int *t2, int *destLen, int *dest) {
    int currentIndexT1 = 0;
    int currentIndexT2 = 0;

    int temp = 0;
    int *arrInTemp;

    *destLen = lenT1 + lenT2;

    for (int i = 0; i < *destLen; ++i) {
        if (i == 0) {
            if (t1[currentIndexT1] < t2[currentIndexT2]) {
                dest[i] = t1[currentIndexT1];
                currentIndexT1++;
                arrInTemp = t2;
                temp = t2[currentIndexT2];
            } else {
                dest[i] = t2[currentIndexT2];
                currentIndexT2++;
                arrInTemp = t1;
                temp = t1[currentIndexT1];
            }
        } else {
            if (arrInTemp == t1) {
                // temp из t1
                if (currentIndexT2 < lenT2) {
                    if (temp > t2[currentIndexT2]) {
                        dest[i] = t2[currentIndexT2];
                        currentIndexT2++;
                    } else {
                        dest[i] = temp;
                        arrInTemp = t2;
                        currentIndexT1++;
                        temp = t2[currentIndexT2];
                    }
                } else {
                    dest[i] = t1[currentIndexT1];
                    currentIndexT1++;
                }
            } else {
                // temp из t2
                if (currentIndexT1 < lenT1) {
                    if (temp > t1[currentIndexT1]) {
                        dest[i] = t1[currentIndexT1];
                        currentIndexT1++;
                    } else {
                        dest[i] = temp;
                        arrInTemp = t1;
                        currentIndexT2++;
                        temp = t1[currentIndexT1];
                    }
                } else {
                    dest[i] = t2[currentIndexT2];
                    currentIndexT2++;
                }
            }
        }
        //cout << i <<" : " << dest[i] << endl;

    }
}


int main() {

    const int INPUT_LEN = 8;

    initBuffers(INPUT_LEN);

    fillTextValue();
    //printArray(aData, INPUT_LEN);


    divideFileForFiles(INPUT_LEN, aData, bFileSizes, bFiles);
    int **src = bFiles;
    int **dest = cFiles;

    int *srcSizes = bFileSizes;
    int *destSizes = cFileSizes;

    // destSizes[1] > 0 || i == 0
    for (int i = 0; i < INPUT_LEN; ++i) {
        for (int j = 0; j + 1 < INPUT_LEN; j+=2) {
            if (srcSizes[j] != 0 && srcSizes[j + 1] != 0) {
                // есть пара для проверки
                int *t1 = src[j];
                int *t2 = src[j + 1];
                int sizeT1 = srcSizes[j];
                int sizeT2 = srcSizes[j + 1];

                concateArrays(sizeT1, t1, sizeT2, t2, &destSizes[j/2], dest[j/2]);
                srcSizes[j] = 0;
                srcSizes[j+1] = 0;

            } else if (srcSizes[j] != 0) {
                // есть только первый
                dest[j/2] = src[j];
                destSizes[j/2] = srcSizes[j];
                srcSizes[j] = 0;
            } else if (srcSizes[j + 1] != 0) {
                // есть только второй
                dest[j/2] = src[j + 1];
                destSizes[j/2] = srcSizes[j+1];
                srcSizes[j+1] = 0;
            } else {
                break;
            }
        }
        //printArray(dest[0], destSizes[0]);


        int ** tempArr = src;
        src = dest;
        dest = tempArr;

        int *tempSizes = srcSizes;
        srcSizes = destSizes;
        destSizes = tempSizes;
    }



    printArray(bFiles[0], bFileSizes[0]);
    printArray(cFiles[0], cFileSizes[0]);


    return 0;
}


int getNumber(int *number) {
    if (!(cin >> *number)) {
        cout << "\n#### Error ####" << endl << ">> ";
        cleanBuf();
        cin.clear();
        return 0;
    }
    if (cleanBuf()) {
        cout << "\n#### Error ####" << endl << ">> ";
        return 0;
    }

    return 1;
}

int cleanBuf() {
    char one;
    int loop = 0;
    while ((one = getchar()) != '\n') {
        loop++;
        continue;
    }
    if (loop > 0) return 1;
    return 0;
}