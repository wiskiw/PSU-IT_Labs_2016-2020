#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
using namespace std;

int main(int argc, char* argv[]){


    if (argc == 1){
        cout << "Не указан параметр.." << endl;
        exit(0);
    }

    char filename[255];
    strcpy(filename, argv[1]);

    FILE * in = fopen(filename, "rb");
    if (!in) {
        cout << "Файл не найден...\n";
        exit(0);
    }

    int sock;
    struct sockaddr_in addr;
    sock = socket(AF_INET, SOCK_STREAM, 0);

    if(sock < 0){
    perror("socket");
    exit(1);
    }


    addr.sin_family = AF_INET;
    addr.sin_port = htons(3425);
    addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    if(connect(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0){
    perror("connect");
    exit(2);
    }


    int b, i = 1;


    send(sock, filename, sizeof(filename), 0);

    struct stat buffk;
    stat(filename, &buffk);
    long sz, left;
    left = sz = buffk.st_size;

    send(sock, &sz, sizeof(__off_t), 0);

    char bufer;
    int size, percent = 0, percentNow;

    while(left) {
        b = fread(&bufer, 1, sizeof(bufer), in);
        size = ftell(in);

        percentNow = (int)(float(size)/float(sz)*100);
        if (percent != percentNow) {
            system("clear");
            cout << "Передача: " << percentNow << "%" << endl;
            percent = percentNow;
        }
        if(b != 0)
        send(sock, &bufer, b, 0);
        left--;
    }




    cout << "\n\nФайл был передан...\n\n";
    fclose(in);


    int index = 1, pos, len;
    len = pos = strlen(filename)-1;
    for (int i = len; i >= 0; i--){
        if(filename[i] == '/') break;
        pos = i;
    }


    char onlyName[255];
    onlyName[0] = '~';
    for (int i = pos; i <= len; i++){
        onlyName[index] = filename[i];
        index++;
    }
    onlyName[index] = '\0';
    filename[pos] = '\0';
    strcat(filename, onlyName);



    int out = open(filename, O_WRONLY | O_CREAT, S_IWRITE | S_IREAD);
    char buf;
    i = 0;

    percent = 0;
    left = sz;
        while (left){

          int nbytes = recv(sock, &buf, sizeof(buf), 0);
          if (nbytes < 0)
          {
               cout << "Ошибка передачи... " << endl;
               return 0;
          }
            write(out, &buf, nbytes);
            i++;
            percentNow = (int)(float(i)/float(sz)*100);
            if (percent != percentNow) {
                system("clear");
                cout << "Принято: " << percentNow << "%" << endl;
                percent = percentNow;
            }
            left--;
        }



        cout << "Сессия окончена..." << endl;
        close(out);

    close(sock);
    return 0;
}
