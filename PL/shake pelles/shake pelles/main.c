#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>
#include <locale.h>
int main(int argc, char *argv[]) {
   
	setlocale(LC_ALL,"ru");
	srand(time(0));

   printf("ѕидор ли ты?\n");
   scanf("");

	((rand()%2) == 0) ? printf("YES!:)") : printf("NO!:");

}


