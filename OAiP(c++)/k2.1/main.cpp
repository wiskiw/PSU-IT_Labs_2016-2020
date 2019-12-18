#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>

int main() {

/*
    // Task 2
    char str[101];
    char numberSet[] = "0123456789";
    gets(str);
    int sum = 0;


    char *sp;
    sp = strtok(str, " "); // при вервом вызове передаем строку - str и разделитель - " "
                        // возвращает строку со словом
    while (sp != NULL) {  // аналогично while (sp)
        int pos = strspn(sp, numberSet); // присваивает pos индекс последнего элемента строки sp,
                                            // если в sp не найдены символы из numberSet

        if (pos == strlen(sp)){ // если
            sum += atoi(sp); // переобразование строки в int и суммирование с sum
        }

        sp = strtok(NULL, " "); // при втором и последующих вызовах вместо строки передаем NULL
                                // возвращает следующее слово
                                // возвращает NULL если слов больше нет
    }
    printf("%d\n", sum);
*/


    /*
    // Task 4
    char str[101];
    gets(str);

    char minChar;
    int minCharNumb = -1;

    int i = 0;
    char parentChar = str[i]; // берем первый символ строки
    for (; parentChar != '\0'; i++) { // пока не конец строки

        int charNumb = 0; // конечество символа parentChar строке
        int j = 0;
        char childChar = str[j];
        for (; childChar != '\0'; ++j) { // пока не конец строки, ищем еще вхождения parentChar
            if (childChar == parentChar) charNumb++; // если находим - увеличиваем счетчик
            childChar = str[j]; // обновляем проверяемый символ
        }

        if (minCharNumb >= charNumb || minCharNumb < 0) { // если вол-во вхождений parentChar меньше или равно
                                            // предыдушему числу вхождений символы в строу, или нету предыдущего числа вхождений
            minCharNumb = charNumb; // обновляем количество вхождений символа
            minChar = parentChar; // сохраняем символ с минимальным числом вхожнением
        }
        parentChar = str[i];
    }

    printf("%c\n", minChar);
     */


    /*
    // Task 5
    char str[101];
    gets(str);

    char word[101];
    gets(word);

    int numb = 0;

    char *sp;
    sp = strtok(str, " "); // при вервом вызове передаем строку - str и разделитель - " "
                            // возвращает строку со словом из строки
    while (sp) {
        if (strcmp(sp, word) == 0){ // если слово из строки равно введенному слову
            numb++;
        }
        sp = strtok(NULL, " "); // при втором и последующих вызовах вместо строки передаем NULL
                                // возвращает следующее слово строки
                                // возвращает NULL если слов больше нет
    }
    printf("%d\n", numb);
    */


    system("pause");
    return 0;
}