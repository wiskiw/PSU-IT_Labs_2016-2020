#include <cstdlib>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>


int main() {

    // var 12
    /*
    // Task 1
    char *ptr;
    ptr = (char *) malloc(sizeof(char));
    scanf("%c", ptr);
    printf("value: %c\n", *ptr);
*/
    // Task 2
    /*
    int n;
    char *str;
    printf("n=");
    scanf("%d", &n);
    if (n < 5) {
        printf("Minimal string length - 5\n");
    } else {
        str = (char *) calloc(n + 1, sizeof(char)); // n + 1 - для '\0'
        getchar();
        scanf("%s", str);


        // 1)
        n = n - 5;
        str = (char *) realloc(str, (n + 1) * sizeof(char));
        str[n] = '\0';
        printf("1)new string: %s\n", str); // Строка после удаления 5-и символов


        // 2)
        int m;
        printf("m=");
        scanf("%d", &m);
        str = (char *) realloc(str, (n + m + 1) * sizeof(char));
        for (int i = n; i < n + m; i++) {
            str[i] = '*';
        }
        str[n + m] = '\0';
        printf("2)new string: %s\n", str); // Строка, после присоединения m символов

        for (int i = 0; i < n + m + 1; i++)
            free((void *) str[i]);
    }
     */


    // Task 3
    int n, ic = 0;
    char trash[256];
    printf("n=");
    scanf("%d", &n);

    int *array;
    array = (int *) calloc(n, sizeof(int));
    for (int i = 0; i < n; ++i) {
        int k = scanf("%d", &array[i]);
        gets(trash);
        if (trash[0] != 0 || k != 1) {
            printf("Incorrect input!\n");
            ic = 1;
            break;
        }
    }

    if (ic == 0) {
        printf("array: \n\t");
        for (int i = 0; i < n; ++i) {
            printf("%d ", array[i]);
        }
        printf("\n");
    }
    free(array);


    /*
    // Task 4
    int **a;
    int i, j, n, *m;
    printf("row numb n=");
    scanf("%d", &n);

    a = (int **) malloc(n * sizeof(int *));

    m = (int *) malloc(n * sizeof(int));
    // массив кол-ва элементов строк

    // Ввод элементов массива
    for (i = 0; i < n; i++) {
        printf("str colon numb i= ");
        scanf("%d", &i);
        a[i] = (int *) malloc(m[i] * sizeof(int));

        for (j = 0; j < m[i]; j++) {
            printf("a[%d][%d] = %d", i, j, a[i][j]);
            scanf("%d", &i);
        }
    }
    // Вывод элементов массива
    for (i = 0; i < n; i++) {
        for (j = 0; j < m[i]; j++) {
            printf("%d", a[i][j]);
        }
        printf("\n");
    }
    getchar();
     */

    system("pause");
    return 0;
}