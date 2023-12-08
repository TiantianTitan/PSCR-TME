#include "Socket.h"
#include <netdb.h>		// getaddrinfo, freeaddrinfo, getnameinfo
#include <cstring>		// memset
#include <unistd.h>		// close
#include <arpa/inet.h>	// inet_ntoa
#include <iostream>


void pr::Socket::connect(const std::string & host, int port){
    struct addrinfo* ai;
	struct in_addr ipv4;
    if(getaddrinfo(host.c_str(),NULL,NULL,&ai)!= 0){
        perror("DNS");
        exit(1);
    }

	for(struct addrinfo* rp = ai; rp !=NULL; rp = rp->ai_next){
		if(rp->ai_family == AF_INET  /*IPv4 */ && ai->ai_socktype == SOCK_STREAM /*TCP*/){
			ipv4 = (((struct sockaddr_in*) rp->ai_addr)->sin_addr);
			break;
		} 
	}

	freeaddrinfo(ai);
    connect(ipv4,port);
}

void pr::Socket::connect(in_addr ipv4, int port){
    
	this->fd = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);

    if(fd < 0){
        perror("socket TCP");
        exit(2);
    }

    struct sockaddr_in server;
	server.sin_family = AF_INET;
	server.sin_port = htons(port);
	server.sin_addr = ipv4;
	if(::connect(fd,(struct sockaddr *) & server,sizeof(server))<0){
		close();
		fd = -1;
		perror("connect");
	}
}

void pr::Socket::close(){
    if(fd!=-1) {
		shutdown(fd, SHUT_RDWR);
		::close(fd);
	}
}


std::ostream & operator<< (std::ostream & os, struct sockaddr_in & addr){
    
	int size_host = 1024;
	char host[size_host];

	// if(getnameinfo((struct sockaddr*)&addr, sizeof(addr), host, size_host, nullptr, 0, 0)) {
	// 	os << "host:" << host << std::endl;
	// }
	// std::cout << inet_ntoa(addr. sin_addr) << ":" <<  ntohs(addr.sin_port) << std::endl; 
	
	if(getnameinfo((struct sockaddr*)&addr, sizeof(addr), host, size_host, nullptr, 0, 0) != 0) {
		perror ("getnameinfo");
		exit(4);
	}

	os << "Adresse IPv4: " << inet_ntoa(addr.sin_addr) << std::endl;
	os << "Nom de l'hôte: " << host << std::endl;
	os << "Numéro de port: " << ntohs(addr.sin_port) << std::endl;



	return os;
}


