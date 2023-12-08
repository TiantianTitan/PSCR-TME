#ifndef SRC_TCPSERVER_H_
#define SRC_TCPSERVER_H_

#include <vector>
#include <thread>
#include "ServerSocket.h"
#include "ConnectionHandler.h"

namespace pr {

// un serveur TCP, la gestion des connections est déléguée
class TCPServer {
	ServerSocket * ss; // la socket d'attente si elle est instanciee
	ConnectionHandler * handler; // le gestionnaire de session passe a la constru
	std::vector<std::thread> threads;// Conteneur pour les threads de gestion des clients
public :
	TCPServer(ConnectionHandler * handler): ss(nullptr),handler(handler) {}
	~TCPServer(); // Destructeur
	bool startServer (int port);
	void stopServer () ;
};

} // ns pr

#endif /* SRC_TCPSERVER_H_ */
