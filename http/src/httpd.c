#include <glib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <assert.h>
#include <arpa/inet.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/sendfile.h>
#include <netdb.h>




char webpage[] = 
	"HTTP/1.1 200 OK\r\n"
	"Content-Type: text/html; charset=UTF-8\r\n\r\n"
	"<!DOCTYPE html>\r\n"
	"<html><head><title>ShellWaveX</title>\r\n"
	"<style>body {backgroung-color: #FFFF00 }</style></head>\r\n"
	"<body><center><h1>Halló!Halló!</h1><br>\r\n"
	"</center></body></html>\r\n";


void accept_client_request() {

}


int main(int argc, char *argv[])
{
	printf("hello\n");

	struct sockaddr_in server_addr, client_addr;
	socklen_t sin_len = sizeof(client_addr);

	char buf[2048]; /*content sent by browser*/
	char message[512];
	char* ip_host;

	int fd_server, fd_client;
	int fding;
	int on = 1;
	size_t i,j;


	if(argc != 2) {
		printf("Please provide two arguments");
	}
	
	//int port = strtol(argv[1], NULL, 10);

	fd_server = socket(AF_INET, SOCK_STREAM,0);
	
	if(fd_server < 0) {
		perror("socket");
		exit(1);
	}
	setsockopt(fd_server, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(int));

	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = INADDR_ANY;
	server_addr.sin_port = htons(1090);

	
	//memset(&server_addr, 0, sizeof(server_addr));

	if(bind(fd_server, (struct sockaddr *) &server_addr, sizeof(server_addr)) == -1) {
		perror("bind");
		close(fd_server);
		exit(1);
	}
	puts("Bound!!!!");

	if(listen(fd_server, 10) == -1) {
		perror("listen");
		close(fd_server);
		exit(1);
	}

	puts("Listens");

	while(1) {

		printf("Waiting for client...\n");
		
		/*accepting a tcp connection*/
		fd_client = accept(fd_server, (struct sockaddr *) &client_addr, &sin_len);
		ip_host = inet_ntoa(client_addr.sin_addr);
		

		struct timeval tmvl;

		/*timer for client timeout checkes*/
		tmvl.tv_sec = 5;
		tmvl.tv_usec = 0;

		if(fd_client == -1) {
			perror("Conection failed...");
			continue;
		}	
		
		printf("Client connection!!!\n");
		/*recieve from fd_client -> got this from slides*/
		ssize_t n = recv(fd_client, message, sizeof(message) -1, 0);
		/*Accept a request from client*/

		/*Which request are we dealing with GET, POST or HEAD*/

		//close(fd_server);
		memset(buf, 0, 2048);
		read(fd_client,buf, 2047);
	
		//printf("%s\n", buf);
		
			
		//write(fd_client, webpage, sizeof(webpage) - 1);

		close(fd_client);
		printf("closing");
		//exit(0);
		//close(fd_server);

	}

	return 0;
}
