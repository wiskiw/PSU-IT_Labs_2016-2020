#pragma comment(lib, "WS2_32.lib")
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <windows.h>
#include <locale.h>
#include <tchar.h>
#include <cstdio>
#include <string>
#include <algorithm>
#include <iostream>
#include <fstream>

#define MY_PORT 31337

/* SERVER */

int sizeBuff = 0;
char buff[1024];
char buff2[1024] = "";
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

std::string search(std::string fileContent) {
	std::string res = "";
    for (int i = 32; i < 127; ++i) {
        char c = (char) i;
        long count = std::count(fileContent.begin(), fileContent.end(), c);
        if (CHAR_LOG && count > 0) {
			std::string buff = ""; 
            sprintf(buff, "'%c' - %li\n", c, count);
			res += buff;
        }
    }
	return res;
}


DWORD WINAPI SendToClient(LPVOID client_socket) {
    SOCKET my_sock;
    my_sock = ((SOCKET *) client_socket)[0];
    char buff[1024] = "";

    int bytes_recv;
    while ((bytes_recv = recv(my_sock, buff, sizeof(buff), 0)) &&
           bytes_recv != SOCKET_ERROR) {
        //printf("receive from client[%d]: %s\n", my_sock, buff);
        if (buff != " ") {
            string str = getFileContent(buff);
			resContent = search(str)
            send(my_sock, resContent.c_str(), strlen(resContent.c_str()), 0);
        }
    }
    printf("Disconnect\n");
    closesocket(my_sock);
    return 0;
}

int main(int argc, char *argv[]) {
    // Инициализация Библиотеки Сокетов
	if (WSAStartup(0x0202, (WSADATA *) &buff[0])) {
        printf("Error WSAStartup %d\n", WSAGetLastError());
        return -1;
    }

    SOCKET mysocket;
	
	
    // AF_INET - сокет Интернета
    // SOCK_STREAM - потоковый сокет (с установкой соединения)
    // 0 - по умолчанию выбирается TCP протокол
    if ((mysocket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("Error socket %d\n", WSAGetLastError());
        WSACleanup();
        return -1;
    }

    // Связывание сокета с локальным адресом
    sockaddr_in local_addr;
    local_addr.sin_family = AF_INET;
    local_addr.sin_port = htons(MY_PORT); // не забываем о сетевом порядке!!!
    local_addr.sin_addr.s_addr = 0; // сервер принимает подключения
    // на все свои IP-адреса

    // вызываем bind для связывания
	// Связывает локальный адрес с сокетом.
    if (bind(mysocket, (sockaddr *) &local_addr, sizeof(local_addr))) {
        printf("Error bind %d\n", WSAGetLastError());
        closesocket(mysocket);
        WSACleanup();
        return -1;
    }

    // Ожидание подключений
	// Переводит сокет в состояние ожидания входящих соединений
    if (listen(mysocket, 0x100)) {
        printf("Error listen %d\n", WSAGetLastError());
        closesocket(mysocket);
        WSACleanup();
        return -1;
    }

    // Извлекаем сообщение из очереди
    SOCKET client_socket; // сокет для клиента
    sockaddr_in client_addr; // адрес клиента (заполняется системой)

    // функции accept необходимо передать размер структуры
    int client_addr_size = sizeof(client_addr);

    // цикл извлечения запросов на подключение из очереди
    while ((client_socket = accept(mysocket, (sockaddr *) &client_addr, &client_addr_size))) {
        // пытаемся получить имя хоста
        HOSTENT *hst;
        hst = gethostbyaddr((char *) &client_addr.sin_addr.s_addr, 4, AF_INET);
        DWORD thID;
        CreateThread(NULL, NULL, SendToClient, &client_socket, NULL, &thID);
    }
    return 0;
}