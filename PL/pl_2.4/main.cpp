
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cctype>

#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCDFAInspection"


void incorrectInputException() {
    printf("Incorrect character in string! Try again.\n");
}

bool isCorrectChar(char c) {
    int bellow = 32;
    int upper = 122;
    if (c < bellow || c > upper) {
        printf("Incorrect character in string! Try again.\n");
        return false;
    }
    return true;
}

void strsub(char *str, int index, int length) {
    for (int i = index; i < index + length;) {
        int j = i;
        for (; str[j + 1] != '\0'; j++) {
            str[j] = str[j + 1];
        }
        str[j] = '\0';
        length--;
    }
} // удалает length смволов начиная с index

void hideLongWords(char *str, int length) {
    for (int i = 0; str[i] != '\0';) {
        char c = str[i];
        if (c == ' ') {
            i++;
            continue;
        }

        int startIndex = i;
        int j = i;
        for (; c != ' ' && c != '\0'; c = str[j++]); // считаем длинну текущего слова
        j--; // убираем найденый пробел
        int endIndex = j;

        if (endIndex - startIndex == length) {
            //strsub(str, startIndex, endIndex - startIndex);
            for (int r = startIndex; r < endIndex; r++) {
                str[r] = ' '; // заменяем длинные слова на пробелы
            }
        }

        //printf("\nstartIndex = %d ", startIndex);
        //printf("endIndex = %d\n", endIndex);

        i = endIndex;
    }
} // Заменяет слова с длинной length на ' '

void removeCharacter(char *str, int index) {
    int i = index;
    for (; str[i + 1] != '\0'; i++) {
        str[i] = str[i + 1];

    }
    str[i] = '\0';
} // убирает элемент с индексом index  сдвигает все влево


void task1() {
    char str[101];
    getchar();
    printf("Enter a string:\n");
    gets(str);

    int strLen = 0;
    // === Поиск максимальной длинны слова
    int maxWordLength = 0;
    for (; str[strLen] != '\0';) {
        char c = str[strLen];
        if (!isCorrectChar(c)) {
            return;
        }

        if (c == ' ') {
            strLen++;
            continue;
        }

        int j = strLen;
        for (; c != ' ' && c != '\0'; c = str[j++]);
        j--; // не считаем найденый пробел

        int currentWordLength = j - strLen;
        if (currentWordLength > maxWordLength) {
            maxWordLength = currentWordLength;
        }
        strLen = j;
    }

    //printf("maxLen = %d\n", maxWordLength);


    // === Удалям слова из строки длинной maxWordLength
    for (int i = 0; str[i] != '\0';) {
        char c = str[i];
        if (c == ' ') {
            i++;
            continue;
        }

        int startIndex = i;
        int j = i;
        for (; c != ' ' && c != '\0'; c = str[j++]); // считаем длинну текущего слова
        int endIndex = j - 1; // не учитываем '\0' или ' '

        if (endIndex - startIndex == maxWordLength) {
            strsub(str, startIndex, maxWordLength);
            i = startIndex;
        } else {
            i = j;
        }

        //printf("\nstartIndex = %d ", startIndex);
        //printf("endIndex = %d\n", endIndex);
    }

    // === Удаляет возможные множественные пробелы в середине строки
    strLen = 1;
    for (int i = 1; str[i] != '\0'; i++) {
        strLen++;
        char pc = str[i - 1];
        char cc = str[i];

        if (pc == ' ' && cc == ' ') {
            strsub(str, i - 1, 1);
            i--;
        }
    }

    // === Убираем первый символ, если он ' '
    if (str[0] == ' ') strsub(str, 0, 1);

    // === Убираем последний символ, если он ' '
    if (str[strLen - 1] == ' ') strsub(str, strLen - 1, 1);


    printf("\n'%s'\n", str);
}

void task2() {
    char strs[20][71];
    int strNumb = 0; // кол-во введенных строк
    getchar();
    printf("Enter the text: \n");
    for (; strNumb < 20; strNumb++) {
        gets(strs[strNumb]);
        if (strs[strNumb][0] == '\0') break;
    }


    char mainStr[70 * strNumb + 1] = "";
    for (int i = 0; i < strNumb; i++) {
        strcat(mainStr, " ");
        strcat(mainStr, strs[i]);
    }
    strsub(mainStr, 0, 1);


    for (int k = 0; mainStr[k] != '\0'; k++) {
        if (!isCorrectChar(mainStr[k])) {
            return;;
        }
    }


    //strcpy(mainStr, "aaa. bbb. fff. ccc");
    //printf("\n'%s'\n", mainStr);


    char **resultStrs = NULL;
    int sentNumb = 0; // кол-во предложений
    for (; strlen(mainStr) > 0; sentNumb++) {
        resultStrs = (char **) realloc(resultStrs, (sentNumb + 1) * sizeof(char *));
        resultStrs[sentNumb] = (char *) calloc((size_t) (strNumb * 70 + 1), sizeof(char *));

        int endIndex = strcspn(mainStr, ".?!");
        while (mainStr[endIndex + 1] != '\0' && mainStr[endIndex + 1] != ' ') {
            endIndex = strcspn(mainStr, ".?!");
        }
        strncpy(resultStrs[sentNumb], mainStr, (size_t) endIndex + 1);
        resultStrs[sentNumb][endIndex + 1] = '\0';
        strsub(mainStr, 0, endIndex + 2); // +2 - учет '. '
        //printf("sent: '%s'   \n", resultStrs[sentNumb]);
        //printf("mainStr: '%s'\n\n", mainStr);
    }
    free(mainStr);

    // === сортировка
    for (int j = 0; j < sentNumb; j++) {
        for (int i = sentNumb - 1; i > j; i--) {
            if (stricmp(resultStrs[i], resultStrs[i - 1]) < 0) { // без учета регистра
                char a[strNumb * 70 + 1];
                strcpy(a, resultStrs[i]);
                strcpy(resultStrs[i], resultStrs[i - 1]);
                strcpy(resultStrs[i - 1], a);
            }
        }
        printf("[%d]: %s\n", j, resultStrs[j]);
    }
    free(resultStrs);

}

void task3() {
    char charSet[] = " .?!,-";
    char strs[25][71];
    int strNumb = 0; // кол-во введенных строк


    // Ввод строк
    getchar();
    printf("Enter the text: \n");
    for (; strNumb < 20; strNumb++) {
        gets(strs[strNumb]);
        if (strs[strNumb][0] == '\0') break;
    }


    // === Слияние строк в одну строку
    char mainStr[70 * strNumb + 1] = "";
    for (int i = 0; i < strNumb; i++) {
        strcat(mainStr, " ");
        strcat(mainStr, strs[i]);
    }
    strsub(mainStr, 0, 1);
    //printf("\n'%s'\n", mainStr);

    // === Деление строк на слова
    int maxPolyLen = 0;
    char poly[71];

    int wNumb = 0;
    char *word = strtok(mainStr, charSet);
    for (; word; wNumb++) {
        int len = strlen(word);

        // === Проверка слова на полиндром
        int correct = 0;
        for (int i = 0; i < (len / 2); i++) {
            if (tolower(word[i]) == tolower(word[len - i - 1])) {
                correct++;
            }
        }
        if (correct == len / 2) {
            // то полиндром
            if (len > maxPolyLen) {
                maxPolyLen = len;
                strcpy(poly, word);
            }
        }
        printf("[%d](%d): %s\n", wNumb, correct, word);


        word = strtok(NULL, charSet);
    }

    if (maxPolyLen <= 1) {
        printf("\nPolindrom not found. \n");
    } else {
        for (int i = 0; i < maxPolyLen; i++) {
            if (!isCorrectChar(poly[i])) {
                return;
            }
        }
        printf("\nMax polindrom (len=%d): '%s'\n", maxPolyLen, poly);
    }
}


int main() {
    while (true) {
        int tsN = -1;
        printf("\tEnter task number (0 to exit) : ");
        scanf("%d", &tsN);

        switch (tsN) {
            case 0:
                return 0;
            case 1:
                printf("\n");
                task1();
                break;
            case 2:
                printf("\n");
                task2();
                break;
            case 3:
                printf("\n");
                task3();
                break;
            default:
                printf("\tUnknown command, try again");
        }
        printf("\n");
    }
}
