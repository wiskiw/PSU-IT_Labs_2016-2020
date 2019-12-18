//Реализовать функцию UpCase, преобразующую все строчные буквы строки S (переданной в качестве параметра) 
//в прописные (остальные символы строки S не изменяются). Используя эту функцию, преобразовать N строк, введенных пользователем.
#include <iostream>
#include <cstdio>
#include <cstdlib>

int upCase(char *str) {
    int count = 0;
    for (int j = 0; str[j] != '\0'; j++) {
        char c = str[j];
        if (c >= 'a' && c <= 'z') {
            count++;
            str[j] = (char) (c - 32);
            // 32 - разница между 'А' и 'а'
        }
    }
    return count;
}

int main() {
    // Member 23

    printf("\n ");
    char buffer[256] = "";
    while (1) {
        int tsN = -1;
        printf("\t[1] - scan string[255 max];\n");
        printf("\t[0] - exit \t\n: ");

        scanf("%d", &tsN);
        getchar();
        switch (tsN) {
            case 0:
                system("cls");
                return 0;
            case 1:
                system("cls");
                printf("string: ");
                gets(buffer);
                upCase(buffer);
                printf("new string: '%s'\n", buffer);
                break;
            default:
                system("cls");
                printf("\tUnknown command, try again");
        }
        printf("\n");
    }
}
