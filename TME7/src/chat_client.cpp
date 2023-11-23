#include <iostream>
#include <vector>
#include <fcntl.h>
#include <semaphore.h>
#include <algorithm>
#include <thread>
#include "chat_common.h"

#define BUFFER_SIZE 1024
#define SERVER_NAME_DEFAULT "server_sv"
#define CLIENT_NAME_DEFAULT "client_cl"


using namespace std;

bool isRunning = true;
struct message *sharedMsg;
char *sharedContent;

sem_t *serverSem;
sem_t *clientSem;

const char *clientName;
const char *serverName;

int sharedMemoryFD;
int sharedContentFD;
void *sharedMemoryPtr;

vector<thread> threadPool;
struct message *connectMsg;
struct message *disconnectMsg;

void sendMessage(struct message *m) {
    sharedMsg->type = m->type;
    strncpy(sharedMsg->content, m->content, BUFFER_SIZE);
    sem_post(serverSem);
}

void readMessage() {
    sem_unlink(clientName);
    clientSem = sem_open(clientName, O_CREAT | O_EXCL | O_RDWR, 0600, 0);

    shm_unlink(clientName);
    sharedContentFD = shm_open(clientName, O_CREAT | O_EXCL | O_RDWR, 0600);
    ftruncate(sharedContentFD, BUFFER_SIZE);
    sharedMemoryPtr = mmap(0, BUFFER_SIZE, PROT_WRITE | PROT_READ, MAP_SHARED, sharedContentFD, 0);
    sharedContent = new(sharedMemoryPtr) char();

    while (isRunning) {
        sem_wait(clientSem);
        if (!isRunning) {
            break;
        }
        cout << "Broadcasted message: " << sharedContent << endl;
    }
}

void writeMessage() {
    struct message *outgoingMsg = new struct message;
    outgoingMsg->type = 2; // message broadcast

    while (isRunning) {
        cin.getline(outgoingMsg->content, BUFFER_SIZE);
        if (!isRunning) {
            break;
        }
        sendMessage(outgoingMsg);
    }
    delete outgoingMsg;
}

bool sigIntHandled = false;
void terminateClient(int signal) {
    if (!sigIntHandled) {
        isRunning = false;
        sem_post(clientSem);
        close(sharedMemoryFD);
        close(sharedContentFD);
        sendMessage(disconnectMsg);
        shm_unlink(clientName);
        sem_unlink(clientName);
        munmap(sharedMemoryPtr, sizeof(struct message));
        sigIntHandled = true;
    }
}

int main(int argc, char **argv) {
    signal(SIGINT, terminateClient);
    clientName = (argc > 1) ? argv[1] : CLIENT_NAME_DEFAULT;
    serverName = (argc > 2) ? argv[2] : SERVER_NAME_DEFAULT;
    cout << "Client name: " << clientName << endl;
    cout << "Server name: " << serverName << endl;

    connectMsg = new struct message;
    connectMsg->type = 1; // connection message
    strncpy(connectMsg->content, clientName,BUFFER_SIZE);

    disconnectMsg = new struct message;
    disconnectMsg->type = 3; // disconnection message
    strncpy(disconnectMsg->content, clientName,BUFFER_SIZE);

    sharedMemoryFD = shm_open(serverName, O_RDWR, 0600);
    ftruncate(sharedMemoryFD, sizeof(struct message));
    sharedMemoryPtr = mmap(0, sizeof(struct message), PROT_READ | PROT_WRITE, MAP_SHARED, sharedMemoryFD, 0);
    sharedMsg = new(sharedMemoryPtr) struct message;

    serverSem = sem_open(serverName, O_RDWR, 0600, 0);

    sendMessage(connectMsg);

    threadPool.emplace_back(readMessage);
    threadPool.emplace_back(writeMessage);
    for (auto &t : threadPool) {
        t.join();
    }

    delete connectMsg;
    delete disconnectMsg;
}

// test de commande: ./chat_client cl sv