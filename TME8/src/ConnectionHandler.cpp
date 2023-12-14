#include "ConnectionHandler.h"
#include <iostream>
#include <unistd.h>


void pr::ConnectionHandler::handleConnection(pr::Socket sc) {
    int fd = sc.getFD();
    ssize_t msz = sizeof(int);
    while (1) {
        int lu;
        auto nblu = read(fd, &lu, msz);
        if (nblu == 0) {
            std::cout << "Fin connexion par client" << std::endl;
            break;
        } else if (nblu < msz) {
            perror("read");
            break;
        }
        std::cout << "lu =" << lu << std::endl;

        if (lu == 0) {
            break;
        }
        lu++;
        if (write(fd, &lu, msz) < msz) {
            perror("write");
            break;
        }
        std::cout << "envoyé =" << lu << std::endl;
    }
    sc.close();
}