/*
 * name: Alex Shatberashvili	
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <libgen.h> 

//fileclient ip_of_fileserver port_to_connect file_to_send
int main(int argc, char *argv[]){
	int sockfd, portnum, s;
	char *server_ip, *file_addr, *file_name;
	struct sockaddr_in serv_addr;

	//checking the arg count
	if (argc < 4) {	
		fprintf(stderr,"insufficient arguments\n");
		exit(0);
	}
	//fetch the arguments
	server_ip = argv[1];
	file_addr = argv[3];
	file_name = basename(file_addr);
	portnum = atoi(argv[2]);

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0){ 
        fprintf(stderr,"ERROR opening socket");
        exit(0);
    }
	//fill in the socket
	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(portnum);
	s = inet_pton(AF_INET, server_ip, &(serv_addr.sin_addr));
  	if (s <= 0) {
        if (s == 0)
            fprintf(stderr, "Not in presentation format");
        else
            fprintf(stderr,"inet_pton");
        exit(EXIT_FAILURE);
    }
    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0){
        fprintf(stderr, "ERROR connecting");
        exit(0);
    }
    return 0;
}