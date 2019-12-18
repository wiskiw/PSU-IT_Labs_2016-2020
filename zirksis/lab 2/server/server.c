#include <errno.h>
#include <unistd.h>
#include <malloc.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <resolv.h>
#include "openssl/ssl.h"
#include "openssl/err.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <dirent.h>
#include <pthread.h>

#define FAIL    -1


int openListener(int port){
	int sd;
    struct sockaddr_in addr;

    sd = socket(PF_INET, SOCK_STREAM, 0);
    bzero(&addr, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = INADDR_ANY;
    if (bind(sd, (struct sockaddr*)&addr, sizeof(addr)) != 0 ) {
        perror("Can't bind port");
        abort();
    }
    if ( listen(sd, 10) != 0 ) {
        perror("Can't configure listening port");
        abort();
    }
    return sd;
}

int isRoot() {
    if (getuid() != 0) {
        return 0;
    }
    else {
        return 1;
    }

}
SSL_CTX* initServerCTX(void) {   SSL_METHOD *method;
    SSL_CTX *ctx;

    OpenSSL_add_all_algorithms();
    SSL_load_error_strings();
    method = TLSv1_2_server_method();
    ctx = SSL_CTX_new(method);
    if ( ctx == NULL ) {
      ERR_print_errors_fp(stderr);
      abort();
    }
    return ctx;
}

void loadCertificates(SSL_CTX* ctx, char* CertFile, char* KeyFile) {

    if ( SSL_CTX_use_certificate_file(ctx, CertFile, SSL_FILETYPE_PEM) <= 0 ) {
      ERR_print_errors_fp(stderr);
      abort();
    }
    if ( SSL_CTX_use_PrivateKey_file(ctx, KeyFile, SSL_FILETYPE_PEM) <= 0 ) {
      ERR_print_errors_fp(stderr);
      abort();
    }
    if ( !SSL_CTX_check_private_key(ctx) ) {
      fprintf(stderr, "Private key does not match the public certificate\n");
      abort();
    }
}

void showCerts(SSL* ssl) {   X509 *cert;
    char *line;

    cert = SSL_get_peer_certificate(ssl);
    if ( cert != NULL ) {
      line = X509_NAME_oneline(X509_get_subject_name(cert), 0, 0);
      free(line);
      line = X509_NAME_oneline(X509_get_issuer_name(cert), 0, 0);
      free(line);
      X509_free(cert);
    }
}

void exec(const char* cmd) {
    char buffer[128];
    FILE* pipe = popen(cmd, "r");
    if (!pipe) {
			printf("popen() failed! %s\n", cmd);
		}
    pclose(pipe);
    //return result;
}

void* clientFlow(void* sslka) {
    SSL* ssl = (SSL*) sslka;
    char buf[1024] = {0};

    int sd, bytes;

    if ( SSL_accept(ssl) == FAIL )
      ERR_print_errors_fp(stderr);
    else {
      showCerts(ssl);
      bytes = SSL_read(ssl, buf, sizeof(buf));
      buf[bytes] = '\0';

      printf("Command from client: %s\n", buf);

      if ( bytes > 0 ) {
  			char str[1024] = "";
  			char buff[64];

				exec(buf);
  			SSL_write(ssl, str, sizeof(str));

			} else {
					ERR_print_errors_fp(stderr);
			}
    }
    sd = SSL_get_fd(ssl);
    SSL_free(ssl);
    close(sd);
    return NULL;
}




int main(int count, char *argc[]) {
    SSL_CTX *ctx;
    int server;
    char *portnum;
	  pthread_t thread;

    if(!isRoot()) {
        printf("This program must be run as root/sudo user!!");
        exit(0);
    }
    if ( count != 2 ) {
        printf("Usage: %s <portnum>\n", argc[0]);
        exit(0);
    }

    SSL_library_init();

    portnum = argc[1];
    ctx = initServerCTX();
    loadCertificates(ctx, "mycert.pem", "mycert.pem");
    server = openListener(atoi(portnum));
    while (1) {
        struct sockaddr_in addr;
        socklen_t len = sizeof(addr);
        SSL *ssl;

        int client = accept(server, (struct sockaddr*)&addr, &len);
        printf("Connection: %s:%d\n",inet_ntoa(addr.sin_addr), ntohs(addr.sin_port));


        ssl = SSL_new(ctx);
        SSL_set_fd(ssl, client);
        if(pthread_create(&thread, NULL, clientFlow, (void*) ssl) != 0){
               close(client);
        }
    }
    close(server);
    SSL_CTX_free(ctx);
}
