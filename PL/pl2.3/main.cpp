
#include <cstdio>
#include <cstdlib>
#include <cmath>

void incorrectInputException() {
    printf("Incorrect input! Try again.\n");
}

void printArray(int arraySize, float array[]) {
    for (int j = 0; j < arraySize; ++j) {
        printf("%g ", array[j]);
    }
    printf("\n");
}

void printArray(int arraySize, int array[]) {
    for (int j = 0; j < arraySize; ++j) {
        printf("%d ", array[j]);
    }
    printf("\n");
}

void printMatrix(int matrixSize, float **matrix) {
    for (int i = 0; i < matrixSize; i++) {
        for (int j = 0; j < matrixSize; j++) {
            printf("%g\t", matrix[i][j]);
        }
        printf("\n");
    }
}


float getMatrixDet(int matrixSize, float **matrix) {
    if (matrixSize == 1) return matrix[0][0]; // точка выхода рекурсии

    float det = 0;
    for (int i = 0; i < matrixSize; ++i) { // перебор матрицы
        // matrix[строка][столбец]
        float ad = (((i + 1) % 2 == 0) ? -1 : 1) * matrix[0][i]; // дополнительный множитель

        int smMatrixSize = matrixSize - 1;
        float **smMatrix = new float *[smMatrixSize]; // уменьшиная матрица

        for (int l = 1; l < matrixSize; ++l) { // перебор строк со второй
            smMatrix[l - 1] = new float[smMatrixSize]; // добавляем новый массив-строку
            for (int k = 0; k < matrixSize; ++k) { // перебор столбцов
                if (k == i) continue; // пропускаем, если столбец равен столбцу доп. мнж.
                int jColon = k > i ? k - 1 : k; // номер столбеца малой матрицы
                smMatrix[l - 1][jColon] = matrix[l][k];
            }
        }
        det += ad * getMatrixDet(smMatrixSize, smMatrix);
    }
    return det;
} // определитель матрицы

float **divideMatrix(int matrixSize, float **matrix, float divider) {
    for (int i = 0; i < matrixSize; i++) {
        for (int j = 0; j < matrixSize; j++) {
            matrix[i][j] = matrix[i][j] / divider;
        }
    }
    return matrix;
} // деление каждого элемента матрицы на число

float getCofactorByElement(int matrixSize, float **matrix, int row, int colon) {
    // matrix[строка][столбец]
    float ad = (float) pow(-1, row + colon + 2); // дополнительный множитель

    int smMatrixSize = matrixSize - 1;
    float **smMatrix = new float *[smMatrixSize]; // уменьшиная матрица

    for (int l = 0; l < matrixSize; ++l) { // перебор строк со второй
        if (l == row) continue;
        int jRow = l > row ? l - 1 : l; // номер строки малой матрицы
        smMatrix[jRow] = new float[smMatrixSize]; // добавляем новый массив-строку
        for (int k = 0; k < matrixSize; ++k) { // перебор столбцов
            if (k == colon) continue; // пропускаем, если столбец равен столбцу доп. мнж.
            int jColon = k > colon ? k - 1 : k; // номер столбеца малой матрицы
            smMatrix[jRow][jColon] = matrix[l][k];
        }
    }
    float det = getMatrixDet(smMatrixSize, smMatrix);

    return det * ad;
} // алгебраическое дополнение для элемента

float **getMatrixCofactor(int matrixSize, float **matrix) {
    float **result = new float *[matrixSize]; // дополнительная матрица
    for (int i = 0; i < matrixSize; i++) { // получение алгебраических дополнений матрицы А
        result[i] = new float[matrixSize];
        for (int j = 0; j < matrixSize; j++) {
            result[i][j] = getCofactorByElement(matrixSize, matrix, i, j);
        }
    }
    delete (matrix);
    return result;
} // матрица алгебраических дополнений

float **getTransposedMatrix(int matrixSize, float **matrix) {
    for (int l = 0; l < matrixSize; ++l) { // транспонирование
        for (int k = l + 1; k < matrixSize; ++k) {
            int row1 = l;
            int colon1 = k;

            int row2 = k;
            int colon2 = l;

            float el1 = matrix[colon1][row1];
            matrix[colon1][row1] = matrix[colon2][row2];
            matrix[colon2][row2] = el1;
        }
    }
    return matrix;
} // транспонирование матрицы

int main() {
    // Member 7


    // Task 1
    /*
    int arraySize;
    printf("Enter array size: ");
    if (scanf("%d", &arraySize) != 1) {
        incorrectInputException();
        return 1;
    };


    float array[arraySize];

    printf("Enter array: ");
    for (int i = 0; i < arraySize; ++i) {
        if (scanf("%g", &array[i]) != 1) {
            incorrectInputException();
            return 1;
        };
    }


    // 1 -4 8 -3 -7 -5 :
    //
    // 1 -7 8 -3 -4 -5
    // 1 -7 8 -4 -3 -5
    // 1 -7 8 -4 -5 -3


    for (int j = 0; j < arraySize; ++j) {
        for (int i = 0; i < arraySize - 1; ++i) {
            float currentNumb = array[i];
            if (currentNumb < 0) {

                // Поиск следующего отрицательного
                int nextMinusNumbIndex = 0;
                for (int k = i + 1; k < arraySize; ++k) {
                    if (array[k] < 0) {
                        nextMinusNumbIndex = k;
                        break;
                    }
                }

                // сравнение текущего со следеющим
                if (currentNumb > array[nextMinusNumbIndex]) {
                    array[i] = array[nextMinusNumbIndex];
                    array[nextMinusNumbIndex] = currentNumb;
                }
            }
        }


    }

    printf("\n%s\n", "======================");
    printArray(arraySize, array);
    */

    //Task 2
    /*
    int arraySize;
    printf("Enter array size: ");
    if (scanf("%d", &arraySize) != 1) {
        incorrectInputException();
        return 1;
    };


    int array[arraySize];
    printf("Enter array: ");
    for (int i = 0; i < arraySize; ++i) {
        if (scanf("%d", &array[i]) != 1) {
            incorrectInputException();
            return 1;
        };
    }


    int posC = 0;
    for (int j = 0; j < arraySize; ++j) {
        int cItem = array[j];
        if (cItem != 0 && cItem % 2 == 0) {
            for (int i = j - 1; i >= posC; i--) {
                array[i + 1] = array[i];
            }
            array[posC] = cItem;
            printArray(arraySize, array);
            posC++;
        }
    }
*/


    // Task 3
    /*
    int matrixSize;
    printf("Enter the matrix's size: "
     );
    if (scanf("%d", &matrixSize) != 1) {
        incorrectInputException();
        return 1;
    };

    // Ввод первой матрицы
    float **matrixA = new float *[matrixSize];
    printf("Enter the first matrix:\n");
    for (int i = 0; i < matrixSize; i++) {
        matrixA[i] = new float[matrixSize];
        printf("\t");
        for (int j = 0; j < matrixSize; j++) {
            if (scanf("%f", &matrixA[i][j]) != 1) {
                incorrectInputException();
                return 1;
            };
        }
    }



    float **matrixB = new float *[matrixSize];
    printf("Enter the second matrix: ");
    for (int i = 0; i < matrixSize; i++) {
        matrixB[i] = new float[matrixSize];
        printf("\t");
        for (int j = 0; j < matrixSize; j++) {
            if (scanf("%f", &matrixB[i][j]) != 1) {
                incorrectInputException();
                return 1;
            };
        }
    }

    float detA = getMatrixDet(matrixSize, matrixA); // определитель матрицы
    if (detA == 0) { // определитель равен 0, невозможно найти обратную матрицу
        printf("Revert matrix is not exist! Determinant A = 0.\n");
    } else {

        matrixA = getMatrixCofactor(matrixSize, matrixA); // получаем матрицу алгебраических дополнений
        matrixA = getTransposedMatrix(matrixSize, matrixA); // транспонируем
        matrixA = divideMatrix(matrixSize, matrixA, detA); // деление на определитель

        printf("\n");
        printMatrix(matrixSize, matrixA);
        printf("\n");

        int mistakesNumb = 0;
        for (int i = 0; i < matrixSize; i++) {
            for (int j = 0; j < matrixSize; j++) {
                if (matrixA[i][j] != matrixB[i][j]) mistakesNumb++;
            }
        }
        delete(matrixA);
        delete(matrixB);
        if (mistakesNumb == 0) {
            printf("\ntrue\n"); // если матрица В обратная матрице А
        } else {
            printf("\nfalse\n");
        }
    }
    */

    // Task 4
    /*
    int matrixSize;
    printf("Enter the matrix's size: ");
    if (scanf("%d", &matrixSize) != 1) {
        incorrectInputException();
        return 1;
    };

    float **matrix = new float *[matrixSize];
    printf("Enter the matrix:\n");
    for (int i = 0; i < matrixSize; i++) {
        matrix[i] = new float[matrixSize];
        printf("\t");
        for (int j = 0; j < matrixSize; j++) {
            if (scanf("%f", &matrix[i][j]) != 1) {
                incorrectInputException();
                return 1;
            };
        }
    }
    float det = getMatrixDet(matrixSize, matrix);
    printf("Determinant: %g\n", det);
    */



    system("pause");
    return 0;
}