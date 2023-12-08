// Exo FTP:

// server
//     socket
//     bind
//     listen
//     sock::accept
//     while(){
//         read(sock)
//         decode -> List
//                   Up
//                   Down
//                   Exit
    
//         decode argument
//         exécute opération
//     }

// Serveur FTP
//     LIST -> lister les fichiers
//     UP      }- >   {  écrire/lire un fichier
//     DOWN    }/     { depuis/ vers un fd

// copy (int fdsrv,int fddest){
//     while(){
//         read(fdsrc);
//         write(fddest);
//     }
// }

#ifndef FTPSERVER_H_
#define FTPSERVER_H_

#include "ServerSocket.h"
#include <vector>
#include <thread>

class FTPServer {







};

#endif /* FTPSERVER_H_ */