#include <iostream>
#include <vector>
#include <fcntl.h>
#include <semaphore.h>
#include "chat_common.h"
#include <cstring> 
#define SERVER_NAME_DEFAULT "server_sv"
#define BUFFER_SIZE 1024
#define CLIENT_LIMIT 10

using namespace std;
myshm serverSharedMem;
sem_t syncMutex; 
char *clientList[CLIENT_LIMIT];
int clientCount = 0;
struct message *sharedMsg;


void broadcastMessage(){
    cout << "Broadcasting message: " << sharedMsg->content << endl;
    for(int i = 0; i < CLIENT_LIMIT; i++){
        if(clientList[i] != nullptr){
            int fileDescriptor = shm_open(clientList[i], O_RDWR, 0600);
            ftruncate(fileDescriptor, BUFFER_SIZE);
            void *sharedMem = mmap(0, BUFFER_SIZE, PROT_WRITE | PROT_READ, MAP_SHARED, fileDescriptor, 0);
            char* messageBuffer = new(sharedMem) char();
            strcpy(messageBuffer, sharedMsg->content);
            munmap(sharedMem, BUFFER_SIZE);
            close(fileDescriptor);
            sem_t *clientSemaphore = sem_open(clientList[i], O_RDWR, 0600, 0);
            sem_post(clientSemaphore);
            sem_close(clientSemaphore);
        }
    }
}

int main(int argc, char** argv){

    sem_init(&syncMutex, -1, 1);
    const char* serverID = (argc > 1) ? argv[1] : SERVER_NAME_DEFAULT;
    int messageSize = sizeof(struct message);
    cout << "Server: " << serverID << endl;

    // Shared memory setup
    shm_unlink(serverID);
    int fd = shm_open(serverID, O_CREAT | O_RDWR | O_EXCL, 0600);
    ftruncate(fd, messageSize);
    void *sharedMemory = mmap(0, messageSize, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    sharedMsg = new(sharedMemory) struct message;

    // Semaphore initialization
    sem_unlink(serverID);
    serverSharedMem.sem = sem_open(serverID, O_CREAT | O_EXCL | O_RDWR, 0600, 0);

    // Main loop
    while(true){
        sem_wait(serverSharedMem.sem);
        cout << "Processing type: " << sharedMsg->type << endl;
        if(sharedMsg->type == 1){ // Connection
            sem_wait(&syncMutex);
            for(int i = 0; i < CLIENT_LIMIT; i++){
                if(clientList[i] == nullptr){
                    clientList[i] = new char[strlen(sharedMsg->content)];
                    strcpy(clientList[i], sharedMsg->content);
                    clientCount++;
                    break;
                }
            }
            sem_post(&syncMutex);
        } else if(sharedMsg->type == 2){ // Message broadcast
            broadcastMessage();
        } else if(sharedMsg->type == 3){ // Disconnection
            sem_wait(&syncMutex);
            for(int i = 0; i < CLIENT_LIMIT; i++){
                if(clientList[i] != nullptr && (strcmp(clientList[i], sharedMsg->content) == 0)){
                    delete[] clientList[i];
                    clientList[i] = nullptr;
                    clientCount--;
                }
            }
            sem_post(&syncMutex);
        } else {
            cout << "Other type" << endl;
        }
        for(int i = 0; i < clientCount; i++){
            if(clientList[i] != nullptr){
                cout << "Client: " << clientList[i] << endl;
            }
        }
    }
    return 0;
}



// test de commande:  ./chat_server sv