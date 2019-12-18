#include <errno.h>
#include <unistd.h>
#include <time.h>
#include <malloc.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <resolv.h>
#include "openssl/ssl.h"
#include "openssl/err.h"
#include <pthread.h>
#include <dirent.h>
#include <netdb.h>
#include <errno.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>

#define FAIL    -1



void generate(char** str,int count){
	bool used[count];
	for (int i=0;i<count;i++){
		int num;
		while(1){
			num=rand()%count;
			if (!used[num]) {
				used[num]=true;
				break;
			}
		}
		printf("%s ",str[num]);
	}
	printf("\n");
}

int OpenListener(int port){
    int sd;
    struct sockaddr_in addr;
    sd = socket(PF_INET, SOCK_STREAM, 0);
    bzero(&addr, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = INADDR_ANY;
    if (bind(sd, (struct sockaddr*)&addr, sizeof(addr)) != 0 ){
        perror("can't bind port");
        abort();
    }
    if ( listen(sd, 10) != 0 ){
        perror("Can't configure listening port");
        abort();
    }
    return sd;
}


SSL_CTX* InitServerCTX(void){
    SSL_METHOD *method;
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


void LoadCertificates(SSL_CTX* ctx, char* CertFile, char* KeyFile)
{
    /* set the local certificate from CertFile */
    if ( SSL_CTX_use_certificate_file(ctx, CertFile, SSL_FILETYPE_PEM) <= 0 ){
        ERR_print_errors_fp(stderr);
        abort();
    }
    /* set the private key from KeyFile (may be the same as CertFile) */
    if ( SSL_CTX_use_PrivateKey_file(ctx, KeyFile, SSL_FILETYPE_PEM) <= 0 ){
        ERR_print_errors_fp(stderr);
        abort();
    }
    /* verify private key */
    if ( !SSL_CTX_check_private_key(ctx) ){
        fprintf(stderr, "Private key does not match the public certificate\n");
        abort();
    }
}


void ShowCerts(SSL* ssl){
    X509 *cert;
    char *line;
    cert = SSL_get_peer_certificate(ssl);
    if ( cert != NULL ) {
        printf("Server certificates:\n");
        line = X509_NAME_oneline(X509_get_subject_name(cert), 0, 0);
        printf("Subject: %s\n", line);
        free(line);
        line = X509_NAME_oneline(X509_get_issuer_name(cert), 0, 0);
        printf("Issuer: %s\n", line);
        free(line);
        X509_free(cert);
    }
    else printf("No certificates.\n");
}





int main(int argv, char* Argc[]){
	srand(time(NULL));
    SSL_CTX *ctx;
    int server;
    char* portnum;
   
    int bytes_read;

    if ( argv != 2 ) {
        printf("Usage: %s <portnum>\n", Argc[0]);
        exit(0);
    }

    SSL_library_init();
    portnum = Argc[1];
    ctx = InitServerCTX();
    LoadCertificates(ctx, "mycert.pem", "mycert.pem");
    

	char** str=(char**)malloc(0); 
	int count=0;
	server = OpenListener(atoi(portnum));
    while (1) {
		struct sockaddr_in addr;
    	socklen_t len = sizeof(addr);
    	SSL *ssl;
    	ssl = SSL_new(ctx);
		int client = accept(server, (struct sockaddr*)&addr, &len);
		SSL_set_fd(ssl, client);
        SSL_accept(ssl);
        
		count++;
		int count_byte;
		SSL_read(ssl, &count_byte, sizeof(int));
		str=(char**)realloc(str,sizeof(char*)*count);
		str[count-1]=(char*)calloc(count_byte,sizeof(char));
		SSL_read(ssl, str[count-1] , count_byte);
		generate(str,count);
		SSL_free(ssl);
		
	}
	
    
}

