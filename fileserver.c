#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

//fileserver ip_to_bind port_to_listen
int main(int argc, char *argv[]){
	int sockfd, portnum, n;
    struct sockaddr_in serv_addr;
    char buffer[256];
}