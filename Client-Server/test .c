#include <stdlib.h>     /* exit, atoi, malloc, free */
#include <stdio.h>
#include <unistd.h>     /* read, write, close */
#include <string.h>  
#include <sys/socket.h> /* socket, connect */
#include <netinet/in.h> /* struct sockaddr_in, struct sockaddr */
#include <netdb.h>      /* struct hostent, gethostbyname */
#include <arpa/inet.h>
#include "helpers.h"
#include "requests.h"

char *cookie(char *message){
	char *test;
	test = strdup(message);
	//printf("%s\n", test );
	char *total;
	char *anterior, *preanterior;
	char *cookie1, *cookie2;
	
	total = strtok(test,"\n");
	total = strtok(NULL,"\n");
	total = strtok(NULL,"\n");
	
	anterior = total;
	//printf("%s\n\n",anterior );
	
	total = strtok(NULL,"\n");
	
	preanterior = total;
	//printf("%s\n", preanterior);
	
	while(total != NULL){
		total = strtok(NULL, "\n");
	}

	cookie1 = strtok(anterior," ");
	cookie1 = strtok(NULL,";");
	printf("%s\n", cookie1);

	cookie2 = strtok(preanterior," ");
	cookie2 = strtok(NULL,";");
	printf("%s\n", cookie2);

	free(total);
	free(test);
	return 0;
}