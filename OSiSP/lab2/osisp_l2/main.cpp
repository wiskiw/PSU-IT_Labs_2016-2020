#include <iostream>
#include <fstream>
#include <algorithm>

// 3) Вывод всех символов и их количество встречаемых в текстом файле;

using namespace std;

#define THREAD_COUNT 6
#define ASYNC_MODE true
#define SYNC_MODE true

#define CHAR_LOG false
#define TIME_LOG true

struct Data {
    char c;
    string fileContent;
    long count;
    long charCount[127];
};


typedef long Timer;

Timer startTimer() {
    return clock();
}

long stopTimer(Timer tm) {
    return clock() - tm;
}

string getFileContent(const string &filePath) {
    ifstream myReadFile;
    myReadFile.open(filePath);
    char output[1000];
    string resultContent;
    if (myReadFile.is_open()) {
        while (!myReadFile.eof()) {
            myReadFile >> output;
            resultContent.append(output);
        }
    } else {
        cout << "error\n";
    }
    myReadFile.close();
    return resultContent;
}

long getCharIncludesCount(const string dataString, char c) {
    return count(dataString.begin(), dataString.end(), c);
}


void syncSearch(string fileContent) {
    Timer t = startTimer();
    for (int i = 32; i < 127; ++i) {
        char c = (char) i;
        long count = getCharIncludesCount(fileContent, c);
        if (CHAR_LOG && count > 0) {
            printf("'%c' - %li\n", c, count);
        }
    }
    if (TIME_LOG) cout << " sync: " << stopTimer(t) << endl;
}


void *threadMethod(void *args) {
    auto *data = (Data *) args;
    for (int i = 32; i < 127; ++i) {
        data->charCount[i] = getCharIncludesCount(data->fileContent, (char) i);
    }
    pthread_exit(data);
}

void asyncSearch(string fileContent) {
    pthread_t threads[THREAD_COUNT];

    Timer t = startTimer();

    // Деление строки на части
    int cutsSize = 0; // кол-во 'срезанных' со строки символов
    const auto partLen = int(fileContent.size() / THREAD_COUNT); // длинна одной части
    string fileContentParts[THREAD_COUNT];
    for (int k = 0; k < THREAD_COUNT; ++k) {
        if (k + 1 == THREAD_COUNT) {
            fileContentParts[k] = fileContent.substr((unsigned long) cutsSize, fileContent.size() - cutsSize);
        } else {
            fileContentParts[k] = fileContent.substr((unsigned long) cutsSize, (unsigned long) partLen);
            cutsSize += partLen;
        }
    }


    Data charDataArgs[THREAD_COUNT];

    // цикл запуска потоков
    int rc;
    for (int j = 0; j < THREAD_COUNT; ++j) {
        charDataArgs[j].fileContent = fileContentParts[j];

        rc = pthread_create(&threads[j], NULL, threadMethod, (void *) &charDataArgs[j]);
        if (rc) {
            cout << "Error:unable to create thread," << rc << endl;
            exit(-1);
        }
    }

    // синхронизация потоков
    int status_addr;
    for (int j = 0; j < THREAD_COUNT; ++j) {
        pthread_join(threads[j], (void **) &status_addr);
    }

    // подсчет результатов со всех потоков
    for (int i = 32; i < 127; ++i) {
        long currentCharCount = 0;
        for (int j = 0; j < THREAD_COUNT; ++j) {
            currentCharCount += charDataArgs[j].charCount[i];
        }

        // вывод результатов
        if (CHAR_LOG && currentCharCount > 0) {
            printf("'%c' - %li\n", (char)i, currentCharCount);
        }
    }

    /*
    for (int i = 32; i < 127; ++i) {
        Data charDataArgs[THREAD_COUNT];

        // цикл запуска потоков
        for (int j = 0; j < THREAD_COUNT; ++j) {
            charDataArgs[j].c = (char) i;
            charDataArgs[j].fileContent = fileContentParts[j];

            rc = pthread_create(&threads[j], NULL, threadMethod, (void *) &charDataArgs[j]);
            if (rc) {
                cout << "Error:unable to create thread," << rc << endl;
                exit(-1);
            }
        }

        // синхронизация потоков
        int status_addr;
        long currentCharCount = 0;
        for (int j = 0; j < THREAD_COUNT; ++j) {
            pthread_join(threads[j], (void **) &status_addr);
            currentCharCount += charDataArgs[j].count;

            if (CHAR_LOG && currentCharCount > 0) {
                printf("'%c' - %li\n", charDataArgs[0].c, currentCharCount);
            }
        }
    }
     */
    if (TIME_LOG) cout << "async: " << stopTimer(t) << endl;
}

int main() {
    string fileContent = getFileContent("input/file1");

    if (SYNC_MODE) {
        syncSearch(fileContent);
    }

    if (ASYNC_MODE) {
        asyncSearch(fileContent);
    }
}