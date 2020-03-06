#include <stdlib.h>     /* exit, atoi, malloc, free */
#include <stdio.h>
#include <unistd.h>     /* read, write, close */
#include <string.h>     /* memcpy, memset */
#include <sys/socket.h> /* socket, connect */
#include <netinet/in.h> /* struct sockaddr_in, struct sockaddr */
#include <netdb.h>      /* struct hostent, gethostbyname */
#include <arpa/inet.h>
#include "helpers.h"
#include "requests.h"

char *compute_get_request(char *host,const char *url,const char *url_params,
    const char *authorization,
    const char *cookie1_get,const char *cookie2_get)
{
    char *message = calloc(BUFLEN, sizeof(char));
    char *line = calloc(LINELEN, sizeof(char));

    if (url_params != NULL)
    {
        sprintf(line, "GET %s?%s HTTP/1.1", url, url_params);
    }
    else
    {
        sprintf(line, "GET %s HTTP/1.1", url);
    }
    compute_message(message, line);

    sprintf(line, "HOST: %s", host);
    compute_message(message, line);

    memset(line, 0, LINELEN);
    sprintf(line, "Authorization: Bearer %s", authorization);
    compute_message(message, line);

    memset(line, 0, LINELEN);
    sprintf(line,"Cookie: %s",cookie1_get);
    compute_message(message,line);

    memset(line, 0, LINELEN);
    sprintf(line,"Cookie: %s",cookie2_get);
    compute_message(message,line);

    strcpy(line, "\r\n");
    strcat(message, line);
    free(line);
    return message;
}
char *compute_post_request(char *host,const char *url,char *form_data,const char *type,
                            const char *cookie1,const char *cookie2) {

    char *message = calloc(BUFLEN, sizeof(char));
    char *line = calloc(LINELEN, sizeof(char));

    sprintf(line, "POST %s HTTP/1.1", url);
    compute_message(message, line);

    sprintf(line, "HOST: %s", host);
    compute_message(message, line);

    memset(line, 0, LINELEN);
    sprintf(line,"Cookie: %s",cookie1);
    compute_message(message,line);

    memset(line, 0, LINELEN);
    sprintf(line,"Cookie: %s",cookie2);
    compute_message(message,line);

    memset(line, 0, LINELEN);
    sprintf(line, "Content-Type: %s", type);
    compute_message(message, line);

    memset(line, 0, LINELEN);
    sprintf(line, "Content-Length: %ld", strlen(form_data));
    compute_message(message, line);

    strcpy(line, "\r\n");
    strcat(message, line);

    strcpy(line, form_data);
    compute_message(message, line);
    free(line);

    return message;
}