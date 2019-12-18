#include <stdio.h>
#include <winsock2.h>
#include <windows.h>
#include <string>
#include <fstream>

#define PORT 31337
#define SERVERADDR "127.0.0.1"

/*	CLIENT */



int symbols;
char file[] = "file1.txt";
char buf[1024];

int main(int argc, char *argv[]) {
    char buff[1024];
    printf("CLIENT\n");
    if (WSAStartup(0x0202, (WSADATA *) buff)) {
        printf("WSAStart error %d\n", WSAGetLastError());
        return -1;
    }
    SOCKET my_sock;
    my_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (my_sock < 0) {
        printf("Socket() error %d\n", WSAGetLastError());
        return -1;
    }
    sockaddr_in dest_addr;
    dest_addr.sin_family = AF_INET;
    dest_addr.sin_port = htons(PORT);
    HOSTENT *hst;
    if (inet_addr(SERVERADDR) != INADDR_NONE)
        dest_addr.sin_addr.s_addr = inet_addr(SERVERADDR);
    else if (hst = gethostbyname(SERVERADDR))
        ((unsigned long *) &dest_addr.sin_addr)[0] = ((unsigned long **) hst->h_addr_list)[0][0];
    else {
        printf("Invalid address %s\n", SERVERADDR);
        closesocket(my_sock);
        WSACleanup();
        return -1;
    }
    if (connect(my_sock, (sockaddr *) &dest_addr, sizeof(dest_addr))) {
        printf("Connect error %d\n", WSAGetLastError());
        return -1;
    }

    send(my_sock, file, sizeof(file), 0);
    recv(my_sock, buf, 1024, 0);

    printf("server msg: %s", buf);
    closesocket(my_sock);
    WSACleanup();
    return -1;
}