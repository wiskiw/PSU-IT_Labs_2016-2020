#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstdio>
#include <cstdlib>
#include <zconf.h>
#include <string>
#include <fstream>
#include <iostream>
#include <cstring>

using namespace std;

#define SERVER_BUFFER_SIZE 2048


/*
 3) Вывод всех символов и их количество встречаемых в текстом файле.
 Клиент передает содержимое файла на север.
 Сервер выдает информацию клиенту. Протокол взаимодействия TCP;
 */


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

string callServer(string content) {
    /*
     Тип сокета определяет способ передачи данных по сети. Чаще других применяются:
        SOCK_STREAM. Передача потока данных с предварительной установкой соединения.
     Обеспечивается надёжный канал передачи данных, при котором фрагменты отправленного блока не теряются,
     не переупорядочиваются и не дублируются.

     Cовместно с доменом Unix используется только тип SOCK_STREAM.
     С другой стороны, для Internet-домена можно задавать любой из перечисленных типов.

     Для Internet-домена для реализации SOCK_STREAM используется протокол TCP по умолчанию
     */

    int sock;
    struct sockaddr_in addr;
    sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (sock < 0) {
        perror("socket");
        exit(1);
    }

    addr.sin_family = AF_INET;
    addr.sin_port = htons(3426); // или любой другой порт...
    addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK); // локальная сеть
    if (connect(sock, (struct sockaddr *) &addr, sizeof(addr)) < 0) {
        perror("connect");
        exit(2);
    }

    send(sock, content.c_str(), content.size(), 0);

    char resultBuff[SERVER_BUFFER_SIZE];
    recv(sock, resultBuff, SERVER_BUFFER_SIZE, 0);

    close(sock);

    //printf("server msg: %s\n", resultBuff);
    return string(resultBuff);
}

int main() {
    string filePath = "../file.test";
    //cin >> filePath;
    string fileContent = getFileContent(filePath);
    //fileContent = "abc\n123";
    string serverResult = callServer(fileContent);
    printf("serverResult: %s\n", serverResult.c_str());
    return 0;
}