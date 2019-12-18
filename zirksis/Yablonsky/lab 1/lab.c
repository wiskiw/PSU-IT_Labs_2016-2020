#include <openssl/md5.h>
#include <openssl/pem.h>
#include <openssl/err.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

/*
	21. Преобразование строки с использованием хеш-функции MD5. 
	На входе программы файл со списком строк, с помощью хеш-функции преобразуем все строки. 
	Затем на вход подаем искомую строку, также с помощью хеш-функции преобразовываем ее и ищем в общем списке преобразованных строк.
*/


char* search(char* search_name, char*** str, int *count){
	
	for (int i=0;i<*count;i++){
		if (strcmp(str[1][i],search_name)==0){
			return str[0][i];
		}
			
	}
	return "String not found";
}

void MD5_FUN(char* file_name, char*** str, int *count){
	
	FILE *file=fopen(file_name,"r");
	char* string=(char*)calloc(1024,sizeof(char));
	
	
    SHA_CTX ctx;
	
	SHA1_Init(&ctx);

	while (fgets(string,1024,file) != NULL) {

		(*count)++;
		string[strlen(string)-1]=0;
		
		str[0]=(char**)realloc(str[0],sizeof(char*)*(*count));
		str[0][*count-1]=calloc(strlen(string)+1,sizeof(char));
		
		str[1]=(char**)realloc(str[1],sizeof(char*)*(*count));
		str[1][*count-1]=calloc(33,sizeof(char));
		
		strcpy(str[0][*count-1], string);
		
		unsigned char md5digest[MD5_DIGEST_LENGTH];
		//MD5(string, strlen(string), md5digest);
		SHA1_Update(&ctx, md5digest, MD5_DIGEST_LENGTH);

    	SHA1_Final(md5digest, &ctx);
		
		
		for (int i=0; i < MD5_DIGEST_LENGTH; i++){
  			sprintf(str[1][*count-1],"%s%02x", str[1][*count-1], md5digest[i]);
		}
		
		printf("%s\n",str[1][*count-1]);
    	
    
	}
}


void main(int argc,char** argv){

	char*** str=(char***)calloc(2,sizeof(char**));
	str[0]=(char**)malloc(0);
	str[1]=(char**)malloc(0);
	int count=0;

	if (argc==2){
		
		MD5_FUN(argv[1],str, &count);
		
		printf("String: ");
		char  string[1024];
		scanf("%s",string);
		
		while (strlen(string)!=32) {
			printf("MD5 must be 32byte length \n");
			scanf("%s",string);
		}
		
		printf("%s\n",search(string, str, &count));
	}
}

