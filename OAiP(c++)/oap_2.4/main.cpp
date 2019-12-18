#include <cstdio>
#include <cstdlib>
#include <cstring>

struct GitRep {
    char name[101];
    char pl[101];
    char author[101];
    float rate;
    long int createDate;
    long int editDate;
    int commitNumb;
    int errorNumb;
    int fixErrorNumb;
    int branchNumb;
};

struct Str {
    int id;
    float price;
    float size;
    char name[101];
};

void task1() {
    struct GitRep {
        char name[101];
        char pl[101];
        char author[101];
        float rate;
        long int createDate;
        long int editDate;
        int commitNumb;
        int errorNumb;
        int fixErrorNumb;
        int branchNumb;
    };

    GitRep gitRep1;
    printf("   Scanning new repository: \n");
    printf("rep. name: ");
    scanf("%s", gitRep1.name);

    printf("programing language: ");
    scanf("%s", gitRep1.pl);

    printf("rate: ");
    scanf("%f", &gitRep1.rate);
    printf("... and so on ... \n");

}

void task2() {
    GitRep *gitRepPrt;
    gitRepPrt = (GitRep *) malloc(sizeof(GitRep)); //  = new GitRep - ?

    /*
    printf("rep. name: ");
    scanf("%s", gitRepPrt->name);
    printf("name: %s", gitRepPrt->name);
     */
}

void task3(){
    Str **str = (Str **) malloc(0); // инициализируем пустой массив указателей
    for (int i = 1; 1; ++i){
        str = (Str **) realloc(str, i * sizeof(Str)); // расширяем памяь под новую запись в массиве
        printf("Enter new struct(id, name, price, size): \n");
        Str str1;
        scanf("%d", &str1.id);
        scanf("%s", str1.name);
        scanf("%f", &str1.price);
        scanf("%f", &str1.size);
        str[i-1] = &str1; // записваем в массив

        getchar();
        printf("Press Enter to continue or '0' to exit\n");
        if (getchar() == '0') break;

    }

}

void printStr(Str str){
    printf("Structure (id:%d):\n", str.id);
    printf("Name: %s\n", str.name);
    printf("Price: %g\n", str.price);
    printf("Size: %g\n", str.size);
}

void printTableHead(){
    printf("%-3s     ", "ID:");
    printf("%-15s     ", "NAME:");
    printf("%-10s     ", "SIZE:");
    printf("%-10s     ", "PRISE:");
    printf("\n");
}

void printStrTable(Str str){
    printf("%3d     ", str.id);
    printf("%15s     ", str.name);
    printf("%10.3f     ", str.size);
    printf("%10.2f     ", str.price);
    printf("\n");
}

void task4(){
    Str str;
    str.id = 15;
    strcpy(str.name, "Big Ball");
    str.size = 135.5f;
    str.price = 15.1f;
    printStr(str);
}

void task5(){
    Str str1, str2;
    str1.id = 15;
    strcpy(str1.name, "Big Ball");
    str1.size = 135.5f;
    str1.price = 15.1f;

    str2.id = 18;
    strcpy(str2.name, "Bill Cipher");
    str2.size = 35.9f;
    str2.price = 66.6f;

    printTableHead();
    printStrTable(str1);
    printStrTable(str2);
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
            case 4:
                printf("\n");
                task4();
                break;
            case 5:
                printf("\n");
                task5();
                break;
            default:
                printf("\tUnknown command, try again");
        }
        printf("\n");
    }
}