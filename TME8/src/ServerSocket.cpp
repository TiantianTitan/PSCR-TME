#include "ServerSocket.h"
#include <netinet/in.h>
#include <arpa/inet.h>		
#include <unistd.h>		
#include <iostream>

const int NB = 10;

pr::ServerSocket::ServerSocket(int port) {
	struct sockaddr_in adr;
	adr.sin_family = AF_INET;
	adr.sin_port = htons(port);
	adr.sin_addr.s_addr = INADDR_ANY;

	if((socketfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) <0) {
		perror("socket");
		exit(1);
	}

	if(bind(socketfd, (struct sockaddr*)&adr, sizeof(adr)) <0) {
		perror("bind");
		exit(2);
	}

	int i = 1;
	setsockopt(socketfd,SOL_SOCKET,SO_REUSEADDR,&i,sizeof(i));

	if(listen(socketfd, NB) <0) {
		perror("listen");
		exit(3);
	}

}

pr::Socket pr::ServerSocket::accept() {
    struct sockaddr_in exp;

    socklen_t sz = sizeof(exp);
    int fd;

    if ((fd = ::accept(socketfd, (struct sockaddr*)&exp, &sz)) == -1) {
        perror("accept");
        exit(4);
    }

    std::cout << "Connexion from " << inet_ntoa(exp.sin_addr) << ":" << ntohs(exp.sin_port) << std::endl;
    return Socket(fd);
}

void pr::ServerSocket::close() {
	if(isOpen()) {
		shutdown(socketfd, SHUT_RDWR);
		::close(socketfd);
	}
}