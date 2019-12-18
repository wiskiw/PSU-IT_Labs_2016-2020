#include <iostream>
#include <cstdio>
#include <fstream>
#include <cstdlib>
#include <cstring>

void removeDB(char name[]) {
    if (remove(name) == 0) {
        printf("Database file successfully removed!\n");
    } else {
        printf("Cannot remove the database file!\n");
    }
}

std::ofstream newDB() {
    std::ofstream dbFile("database.data");
    if (dbFile.is_open()) {
        printf("Database file successfully created!\n");
    } else {
        printf("Cannot create the database file!\n");
    }
    return dbFile;
}

void task1() {
    std::ofstream file = newDB();
    file.close();
}

void task2() {
    removeDB("database.data");
}


int main() {
    while (true) {
        int tsN = -1;
        printf("\t[1] - create the new database;\n");
        printf("\t[2] - remove the database;\n");
        printf("\t[0] - exit \t\n: ");
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
            default:
                printf("\tUnknown command, try again");
        }
        printf("\n");
    }
}