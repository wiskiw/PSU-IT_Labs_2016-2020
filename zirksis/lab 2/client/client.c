#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <malloc.h>
#include <string.h>
#include <sys/socket.h>
#include <resolv.h>
#include <netdb.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

#define FAIL    -1

int openConnection(const char *hostname, int port){
    int sd;
    struct hostent *host;
    struct sockaddr_in addr;

    if ( (host = gethostbyname(hostname)) == NULL ){
        perror(hostname);
        abort();
    }
    sd = socket(PF_INET, SOCK_STREAM, 0);
    bzero(&addr, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = *(long*)(host->h_addr);
    if ( connect(sd, (struct sockaddr*)&addr, sizeof(addr)) != 0 ){
        close(sd);
        perror(hostname);
        abort();
    }
    return sd;
}

SSL_CTX* initCTX(void){
    SSL_METHOD *method;
    SSL_CTX *ctx;

    OpenSSL_add_all_algorithms();
    SSL_load_error_strings();
    method = TLSv1_2_client_method();
    ctx = SSL_CTX_new(method);
    if ( ctx == NULL ){
        ERR_print_errors_fp(stderr);
        abort();
    }
    return ctx;
}

void showCerts(SSL* ssl){
    X509 *cert;
    char *line;

    cert = SSL_get_peer_certificate(ssl);
    if ( cert != NULL ){
        line = X509_NAME_oneline(X509_get_subject_name(cert), 0, 0);
        free(line);
        line = X509_NAME_oneline(X509_get_issuer_name(cert), 0, 0);
        free(line);
        X509_free(cert);
    }
}




int main(int count, char *strings[]){
    SSL_CTX *ctx;
    int server;
    SSL *ssl;
    char buf[1024];
    int bytes;
    char *hostname, *portnum;

    if ( count != 3 ){
        printf("usage: %s <hostname> <portnum>\n", strings[0]);
        exit(0);
    }
    SSL_library_init();
    hostname=strings[1];
    portnum=strings[2];

    ctx = initCTX();
    server = openConnection(hostname, atoi(portnum));
    ssl = SSL_new(ctx);
    SSL_set_fd(ssl, server);

    if ( SSL_connect(ssl) == FAIL ){
      ERR_print_errors_fp(stderr);

    } else {
        char command[256];
        printf("Enter a command: ");
        fgets(command, 255, stdin);

        printf("\n\nConnected with %s encryption\n", SSL_get_cipher(ssl));
        showCerts(ssl);
        SSL_write(ssl, command, strlen(command));
        bytes = SSL_read(ssl, buf, sizeof(buf));
        buf[bytes] = 0;
        printf("%s", buf);
        SSL_free(ssl);
    }
    close(server);
    SSL_CTX_free(ctx);
    return 0;
}
