#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h>
#include <resolv.h>
#include <arpa/inet.h>
#include <errno.h>
#include <pthread.h>

#define MY_PORT		9999
#define MAXBUF		1024

FILE *fp;
char *filename;
char *htmlText;

char* concat(char *s1, char *s2)
{
    char *result = malloc(strlen(s1)+strlen(s2)+1);
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}

FILE *File;
void *connection_handler(void *client)
{
    int cl = *(int*)client;
    char buffer[MAXBUF];
    //printf("connected\n");
    bzero(buffer, 256);

    int isRead = read(cl, buffer, 255);
    if (isRead < 0) {
        error("ERROR reading from socket");
    }
    int i = 0;

    send(cl, htmlText, strlen(htmlText), 0);
    close(cl);
}

int main(int Count, char *Strings[])
{   int sockfd;
	struct sockaddr_in address;
	char buffer[MAXBUF];
	int status = 200;

    // create html response
    filename = "index.html";

    fp = fopen(filename, "r");
    char * x, *responseText="";
    while (fscanf(fp, "%s", x) != EOF) {
        printf("%s",x);
        responseText = concat(responseText, x);
    }
    printf("%s", responseText);

    char * res;

    if(status == 200) {
        res = "HTTP/1.1 200 OK\n";
    } else if(status == 500) {
        res= "HTTP/1.1 500 Internal Server Error\n";
    }

    res = concat(res, "Content-Type: text/html\n"
"Content-Length: 2000\n"
"Accept-Ranges: bytes\n"
"Connection: close\n"
"\n");

    if(status == 500) {
        res = concat(res, "<h1>Page not found</h1>");
    }

    printf("%s",buffer);

    res = concat(res, responseText);
    htmlText = res;

    if ( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0 )
	{
		perror("Socket");
		exit(errno);
	}
	bzero((char *) &address, sizeof(address));

	bzero(&address, sizeof(address));
	address.sin_family = AF_INET;
	address.sin_port = htons(MY_PORT);
	address.sin_addr.s_addr = INADDR_ANY;

    if ( bind(sockfd, (struct sockaddr*)&address, sizeof(address)) != 0 )
	{
		perror("socket--bind");
		exit(errno);
	}

	if ( listen(sockfd, 20) != 0 )
	{
		perror("socket--listen");
		exit(errno);
	}
    int  n;

	while (1)
	{
        int client;
		struct sockaddr_in client_addr;
		int addrlen=sizeof(client_addr);

		client = accept(sockfd, (struct sockaddr*)&client_addr, &addrlen);
        pthread_t thread_id;
        if( pthread_create( &thread_id , NULL , connection_handler , (void*) &client) < 0)
        {
            perror("could not create thread");
            return 1;
        }
	}

	close(sockfd);
	return 0;
}
