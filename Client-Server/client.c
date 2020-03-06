#include <stdio.h>      /* printf, sprintf */
#include <stdlib.h>     /* exit, atoi, malloc, free */
#include <unistd.h>     /* read, write, close */
#include <string.h>     /* memcpy, memset */
#include <sys/socket.h> /* socket, connect */
#include <netinet/in.h> /* struct sockaddr_in, struct sockaddr */
#include <netdb.h>      /* struct hostent, gethostbyname */
#include <arpa/inet.h>
#include "helpers.h"
#include "requests.h"
#include "parson.h"


#define MAXLEN 5000

int main(int argc, char *argv[])
{
    int i;
    char *message;
    char *response;
    int sockfd;
    char *msg, *msg2;
    //char *cokie, *cookie1, *cookie2;
    /*
    *   Ex 0: Get cs.curs.pub.ro
    *   
    *   Pas 1: Se deschide conexiunea (open_connection)
    *   Pas 2: Se creaza mesajul de request (compute_get_request)
    *   Pas 3: Se trimite la server mesajul (send_to_server)
    *   Pas 4: Se primeste raspuns de la server (receive_from_server)
    *   Pas 5: Se inchide conexiunea cu serverul (close_connection)
    */
    sockfd = open_connection("185.118.200.35", 8081, AF_INET, SOCK_STREAM, 0);
    message = compute_get_request(IP_SERVER, "/task1/start", NULL,NULL,NULL,NULL);
    send_to_server(sockfd, message);
    response = receive_from_server(sockfd);
    printf("%s",message);
    printf("%s",response);
    close_connection(sockfd);
    
    //task2
    

    msg = response;
    while(*msg != '{'){
    	msg++;
    }
    
 	JSON_Value * v = json_parse_string(msg);
 	JSON_Object *  val= json_value_get_object (v);
 	//scot url
 	const char * url = json_object_get_string (val, "url");
 	//scot metoda
 	const char * method = json_object_get_string (val, "method");
 	//scot type-ul
 	const char * type = json_object_get_string (val, "type");
 	//scot data
 	JSON_Object * data = json_object_get_object (val, "data");
 	const char * username = json_object_get_string (data, "username");
 	const char * password = json_object_get_string (data, "password");
 	printf("\n\n");
 
    char data1[MAXLEN];
    strcpy(data1,"username=");
    strcat(data1,username);
    strcat(data1,"&password=");
    strcat(data1,password);
    
    msg2 = response;

    char *test;
    test = strdup(msg2);
    char *total;
    char *anterior, *preanterior;
    char *cookie1, *cookie2;
    
    total = strtok(test,"\n");
    total = strtok(NULL,"\n");
    total = strtok(NULL,"\n");
    
    anterior = total;
    
    total = strtok(NULL,"\n");
    
    preanterior = total;
    
    while(total != NULL){
        total = strtok(NULL, "\n");
    }

    cookie1 = strtok(anterior," ");
    cookie1 = strtok(NULL,";");

    cookie2 = strtok(preanterior," ");
    cookie2 = strtok(NULL,";");

    free(total);
    free(test);

 	if(strcmp(method,"POST") == 0) {
        sockfd = open_connection("185.118.200.35", 8081, AF_INET, SOCK_STREAM, 0);
 		message = compute_post_request(IP_SERVER, url,data1,type,cookie1,cookie2);
 		send_to_server(sockfd, message);
    	response = receive_from_server(sockfd);
    	printf("%s",message);
    	printf("%s",response);
    	printf("\n\n");
    }
    close_connection(sockfd);

    //task3

    char *msg3 = response;
    char *test_get;
    test_get = strdup(msg3);
    char *total_get, *anterior_get, *preanterior_get;
    char *cookie1_get, *cookie2_get;

    total_get = strtok(test_get,"\n");
    total_get = strtok(NULL,"\n");
    total_get = strtok(NULL,"\n");
    anterior_get = total_get;

    total_get = strtok(NULL,"\n");
    preanterior_get = total_get;
    while(total_get != NULL){
    	total_get = strtok(NULL,"\n");
    }
    cookie1_get = strtok(anterior_get," ");
    cookie1_get = strtok(NULL,";");

    cookie2_get = strtok(preanterior_get," ");
    cookie2_get = strtok(NULL,";");

    char *raspuns1 = "omul", *raspuns2 = "numele";
    char *msg4 = response;

    while(*msg4 != '{'){
    	msg4++;
    }

    JSON_Value * v_get = json_parse_string(msg4);
 	JSON_Object *  val_get = json_value_get_object (v_get);
 	//scot url
 	const char * url_get = json_object_get_string (val_get, "url");
 	//scot metoda
 	const char * method_get = json_object_get_string (val_get, "method");
 	JSON_Object * data_get = json_object_get_object (val_get, "data");
 	const char * token = json_object_get_string (data_get, "token");
 	JSON_Object * queryParams = json_object_get_object (data_get, "queryParams");
 	const char * id = json_object_get_string(queryParams,"id");

 	char url_params[MAXLEN];
 	strcpy(url_params,"raspuns1=");
 	strcat(url_params,raspuns1);
 	strcat(url_params,"&raspuns2=");
 	strcat(url_params,raspuns2);
 	strcat(url_params,"&id=");
 	strcat(url_params,id);

 	if(strcmp(method_get,"GET") == 0){
 		sockfd = open_connection("185.118.200.35", 8081, AF_INET, SOCK_STREAM, 0);
   		message = compute_get_request(IP_SERVER, url_get, url_params,token,
   		 												cookie1_get,cookie2_get);
    	send_to_server(sockfd, message);
    	response = receive_from_server(sockfd);
    	printf("%s",message);
    	printf("%s",response);
    	printf("\n\n");
    	close_connection(sockfd);
    }

    //task 4
    char *msg6 = response;
    char *test_get4;
    test_get4 = strdup(msg6);
    char *total_get4, *anterior_get4, *preanterior_get4;
    char *cookie1_get4, *cookie2_get4;

    total_get4 = strtok(test_get4,"\n");
    total_get4 = strtok(NULL,"\n");
    total_get4 = strtok(NULL,"\n");
    anterior_get4 = total_get4;

    total_get4 = strtok(NULL,"\n");
    preanterior_get4 = total_get4;
    while(total_get4 != NULL){
    	total_get4 = strtok(NULL,"\n");
    }
    cookie1_get4 = strtok(anterior_get4," ");
    cookie1_get4 = strtok(NULL,";");

    cookie2_get4 = strtok(preanterior_get4," ");
    cookie2_get4 = strtok(NULL,";");

    char *msg5 = response;

    while(*msg5 != '{'){
    	msg5++;
    }
    JSON_Value * v_get4 = json_parse_string(msg5);
    JSON_Object *  val_get4 = json_value_get_object (v_get4);
    const char * url_get4 = json_object_get_string (val_get4, "url");
   	const char * method_get4 = json_object_get_string (val_get4, "method");


 	if(strcmp(method_get4,"GET") == 0){
 		sockfd = open_connection("185.118.200.35", 8081, AF_INET, SOCK_STREAM, 0);
   		message = compute_get_request(IP_SERVER, url_get4, NULL,token,
   		 												cookie1_get4,cookie2_get4);
    	send_to_server(sockfd, message);
    	response = receive_from_server(sockfd);
    	printf("%s",message);
    	printf("%s",response);
    	printf("\n\n");
    	close_connection(sockfd);
    }

    free(message);
    return 0;
}
