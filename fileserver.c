#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

//fileserver ip_to_bind port_to_listen
int main(int argc, char *argv[]){
	int sockfd, portnum, n, s;
    struct sockaddr_in serv_addr;
    char buffer[256];

    if (argc < 2) {
         fprintf(stderr, "insufficient ammount of arguments\n");
         exit(1);
     }
     //create the socket
     sockfd = socket(AF_INET, SOCK_STREAM, 0);
     if (sockfd < 0) 
        perror("ERROR opening socket");

    //fill in the address info
    memset((char *) &serv_addr, '\0', sizeof(serv_addr));
    portnum = atoi(argv[2]);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(portnum);
  	s = inet_pton(AF_INET, argv[1], &(serv_addr.sin_addr));
  	if (s <= 0) {
        if (s == 0)
            fprintf(stderr, "Not in presentation format");
        else
            perror("inet_pton");
        exit(EXIT_FAILURE);
    }
    //bind
	if (bind(sockfd, (struct sockaddr *) &serv_addr, 
		sizeof(serv_addr)) < 0) 
			perror("ERROR on binding");
}