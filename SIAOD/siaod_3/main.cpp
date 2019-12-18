#include <iostream>
#include <cstring>

using namespace std;

/*
 VAR = 3
 Задан набор записей следующей структуры: фамилия автора, название книги и год
издания. По названию книги найти всю остальную информацию.
 */

size_t TABLE_SIZE = 1000; // размер хэш таблицы

struct Item {
    char name[256];
    char bookName[256];
    int year;
    bool used = false;
};

// получение хэша по ключу (keyBuffer)
int hashIndex(char *keyBuffer) {
    int sum = 0;
    for (int i = 0; i < strlen(keyBuffer); i++) {
        sum += keyBuffer[i];
    }
    return sum % TABLE_SIZE;
}

void getItemKey(Item item, char *buffer) {
    char buf[256];
    buf[0] = '\0';
    strcat(buffer, item.name);
    strcat(buffer, item.bookName);
    strcat(buffer, to_string(item.year).c_str());
}

void scanItem(Item *item) {
    system("clear");
    cin.get();
    cout << "Author Name: \n";
    cin.getline(item->name, 256);
    cout << "Boot Name: \n";
    cin.getline(item->bookName, 256);
    cout << "Year: \n";
    char yearBuffer[10] = "";
    cin.getline(yearBuffer, 256);
    item->year = stoi(yearBuffer);
}

void printItem(Item item) {
    cout << "Author Name: " << item.name << "\n";
    cout << "Boot Name: " << item.bookName << "\n";
    cout << "Boot Year: " << item.year << "\n";
}

void add(Item *&hash) {
    Item newItem;
    scanItem(&newItem);

    int ind = hashIndex(newItem.bookName);
    while (ind < TABLE_SIZE) {
        if (hash[ind].used) {
            ind++;
        } else {
            hash[ind] = newItem;
            hash[ind].used = true;
            break;
        }
    }
}

void find(Item *&hash) {
    Item item;
    system("clear");
    cin.get();
    cout << "Book Name: \n";
    cin.getline(item.bookName, 256);

    int ind = hashIndex(item.bookName);
    if (!hash[ind].used){
        cout << "Element is not found\n";
    } else {
        for (int i = ind; i < TABLE_SIZE; ++i) {
            if (hash[i].used && strcmp(hash[i].bookName, item.bookName) == 0){
                if (i == ind + 1){
                    cout << "------------------\n";
                }
                printItem(hash[i]);
            } else {
                break;
            }
        }
        cout << "\n";
    }
    system("pause");
}

// печать всех элементов
void printItems(Item *&hash) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (hash[i].used) {
            cout << "=======" << i + 1 << "=======\n";
            printItem(hash[i]);
        }
    }
    cout << "\n";
}

int main() {
    Item *hashTable = (Item *) calloc(TABLE_SIZE, sizeof(Item));
    int y;
    while (1) {
        system("clear");
        cout << "1.Enter the record" << endl;
        cout << "2.Search" << endl;
        cout << "3.Print All" << endl;
        cout << "0.Exit " << endl;
        cin >> y;
        switch (y) {
            case 1:
                add(hashTable);
                break;
            case 2:
                find(hashTable);
                break;
            case 3:
                printItems(hashTable);
                system("pause");
                break;
        }
        if (y == 0) break;
    }

}