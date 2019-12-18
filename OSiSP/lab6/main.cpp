#include <windows.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <algorithm>
#include <time.h>
#include <fstream>

#define THREADS 2
#define CHAR_LOG true
#define TIME_LOG true

std::string fileList[] = {"file1.txt", "file2.txt"};

typedef long Timer;

Timer startTimer() {
    return clock();
}

long stopTimer(Timer tm) {
    return clock() - tm;
}

using namespace std;

std::string getFileContent(std::string fileName) {
    string fileStr;
    ifstream fin(fileName, ios_base::in);
    while (!fin.eof()) {
        fileStr += fin.get();
    }
    fin.close();
    return fileStr;
}

void search(std::string fileContent) {
    for (int i = 32; i < 127; ++i) {
        char c = (char) i;
        long count = std::count(fileContent.begin(), fileContent.end(), c);
        if (CHAR_LOG && count > 0) {
            printf("'%c' - %li\n", c, count);
        }
    }
}

DWORD WINAPI ThreadProc(CONST LPVOID lpParam) {
    CONST HANDLE hMutex = (CONST HANDLE) lpParam;
    DWORD i;

  
	WaitForSingleObject(hMutex, INFINITE);

	string str = getFileContent(fileList[i]);
	cout << "--- File: " << i + 1 << " ---" << endl;
	search(str);
	cout << endl << endl;
	ReleaseMutex(hMutex);
	//Sleep(PAUSE);
    

    ExitThread(0);
}

INT main() {
    DWORD i;
    HANDLE hThreads[THREADS];
	Timer t = startTimer();
    /*
     Таким образом, в любой момент времени мьютекс может принадлежать только одному потоку, что исключает конфликты между потоками.
     Вместе с тем поток, являющийся владельцем мьютекса , может попытаться стать владельцем мьютекса повторно.
     Если поток присваивал себе мьютекс несколько раз,
     он обязан освободить его такое же количество раз и это расценивается как одно o бpaщение
     */

    CONST HANDLE hMutex = CreateMutex(NULL, FALSE, NULL);
    if (NULL == hMutex) {
        std::cout << "Failed to create mutex.\r\n";
        return -1;
    }

    for (i = 0; i < THREADS; i++) {
        /*
         * При каждом вызове этой функции система создает объект ядра (поток). Это не сам поток,
         * а компактная структура данных,
         * которая используется операционной системой для управления потоком и хранит статистическую информацию о потоке.
         */
        hThreads[i] = CreateThread(NULL, 0, &ThreadProc, hMutex, 0, NULL);
        if (NULL == hThreads[i]) {
            std::cout << "Failed to create thread.\r\nn";
        }
    }

    WaitForMultipleObjects(THREADS, hThreads, TRUE, INFINITE);
	
    for (i = 0; i < THREADS; i++) {
        CloseHandle(hThreads[i]);
    }
    CloseHandle(hMutex);
	
	if (TIME_LOG) cout << "time: " << stopTimer(t) << endl;
}