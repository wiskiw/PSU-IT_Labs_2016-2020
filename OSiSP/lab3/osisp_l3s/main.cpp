#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstdio>
#include <cstdlib>
#include <zconf.h>
#include <string>
#include <algorithm>
#include <cstring>

using namespace std;

/*
 3) Вывод всех символов и их количество встречаемых в текстом файле.
 Клиент передает содержимое файла на север.
 Сервер выдает информацию клиенту. Протокол взаимодействия TCP;
 */

#define CLIENT_BUFFER_SIZE 2048

long getCharIncludesCount(const string dataString, char c) {
    return count(dataString.begin(), dataString.end(), c);
}


string syncSearch(string fileContent) {
    //string res = "";
    char res[1024] = "";
    for (int i = 32; i < 127; ++i) {
        char c = (char) i;
        long count = getCharIncludesCount(fileContent, c);
        if (count > 0) {
            //printf("char %c\n", c);
            char buff[256];
            sprintf(buff, "'%c' - %li\n", c, count);
            strcat(res, buff);
        }
    }
    //printf("res %s\n", res);
    return string(res);
}

int main() {
    int sock, listener;
    struct sockaddr_in addr;
    char buf[CLIENT_BUFFER_SIZE];
    int bytes_read;

    listener = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (listener < 0) {
        perror("socket");
        exit(1);
    }

    addr.sin_family = AF_INET;
    addr.sin_port = htons(3426);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);

    // Для явного связывания сокета с некоторым адресом используется функция bind
    if (bind(listener, (struct sockaddr *) &addr, sizeof(addr)) < 0) {
        perror("bind");
        exit(2);
    }

    // На следующем шаге создаётся очередь запросов на соединение.
    // При этом сокет переводится в режим ожидания запросов со стороны клиентов.
    listen(listener, 1);

    while (1) {
        // Функция accept создаёт для общения с клиентом новый сокет и возвращает его дескриптор
        sock = accept(listener, NULL, NULL);
        if (sock < 0) {
            perror("accept");
            exit(3);
        }

        // цикл чтения данных от клиента
        while (1) {
            bytes_read = recv(sock, buf, CLIENT_BUFFER_SIZE, 0);

            // если клиент перестал присылать данные
            if (bytes_read <= 0) break;

            printf("receive from client[%d]: %s\n", sock, buf);

            string resString = syncSearch(buf);
            printf("send to client: %s\n", resString.c_str());
            send(sock, resString.c_str(), resString.size(), 0);
            //send(sock, args, sizeof(args), 0);
        }

        close(sock);
    }

    return 0;
}