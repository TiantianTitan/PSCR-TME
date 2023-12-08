#include "TCPServer.h"
#include <unistd.h>
#include <thread>

pr::TCPServer::~TCPServer() {
    for(auto& t : threads) {
        if (t.joinable()) {
            t.join();
        }
    }
    delete ss;
    ss = nullptr; // Éviter les dangling pointers
}

void handleClient(pr::Socket dc) {
    int N;
    if (read(dc.getFD(), &N, sizeof(N)) != sizeof(N)) {
        // Gérer l'erreur de lecture
        perror("lecture");
        exit(1);
    }
    N = 20;
    if (write(dc.getFD(), &N, sizeof(N)) != sizeof(N)) {
        // Gérer l'erreur d'écriture
        perror("écriture");
        exit(1);
    }
    dc.close();
}

bool pr::TCPServer::startServer(int port) {
    ss = new ServerSocket(port);
    while (true) { 
        Socket dc = ss->accept();
        threads.emplace_back(handleClient, std::move(dc));
    }
    return true;
}


void pr::TCPServer::stopServer (){
    if (ss != nullptr) {
        ss->close(); 
        delete ss;
        ss = nullptr;
    }

    for (auto& t : threads) {
        if (t.joinable()) {
            t.join();
        }
    }

    threads.clear();
}
