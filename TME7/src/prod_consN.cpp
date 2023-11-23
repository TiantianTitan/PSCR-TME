
#include "Stack.h"
#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <vector>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <signal.h>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>

using namespace std;
using namespace pr;



mutex mtx; // mutex for critical section
condition_variable cv_producer, cv_consumer; // condition variables for producers and consumers
Stack<char> *s; // shared stack
string tache; // shared task string
int shm_id;
int task_index = 0; // Index to keep track of the next character to be processed

atomic<bool> exit_flag(false); // Global exit flag for threads

void producteur(int id, int M) {
    while (true) {
        unique_lock<mutex> lock(mtx);
        cv_producer.wait(lock, [id, M]{ return (task_index % M == id) || exit_flag; });

        if (exit_flag || task_index >= tache.length()) {
            break;
        }

        char task_char = tache[task_index++];
        s->push(task_char);
        cout << "Producer " << id+1 << " pushed: " << task_char << endl;

        cv_consumer.notify_all();
    }
}

void consomateur(int id) {
    while (true) {
        unique_lock<mutex> lock(mtx);
        cv_consumer.wait(lock, []{ return s->getSz() > 0 || exit_flag; });

        if (exit_flag || (task_index >= tache.length() && s->getSz() == 0)) {
            break;
        }

        char task_char = s->pop();
        cout << "Consumer " << id+1 << " popped: " << task_char << endl;

        lock.unlock();
        cv_producer.notify_all();
        sleep(1); // sleep for a second
    }
}

void signal_handler(int signal) {
    if (signal == SIGINT) {
        cout << "\n********terminer proprement***********\n" << endl;
        exit_flag = true; // Set the exit flag for all threads
        cv_producer.notify_all(); 
        cv_consumer.notify_all(); 
    }
}

int main() {

	signal(SIGINT, signal_handler);

	int M, N;
	cout << "Saisir le nombre de producteur\n";
	cin >> M;
	cout << "Saisir le nombre de consommateur\n";
	cin >> N;
	

	cout << "Enter the task string: ";
    cin.ignore(); 
    getline(cin, tache);


	// Créer un segment de mémoire partagée
    shm_id = shmget(IPC_PRIVATE, sizeof(Stack<char>), IPC_CREAT | 0666);
    s = (Stack<char>*) shmat(shm_id, NULL, 0);

	
	// threads
    vector<thread> producers;
    vector<thread> consumers;

    for (int i = 0; i < M; ++i) {
        producers.push_back(thread(producteur, i, M));
    }

    for (int i = 0; i < N; ++i) {
        consumers.push_back(thread(consomateur, i));
    }

    for (auto& th : producers) {
        th.join();
    }
    for (auto& th : consumers) {
        th.join();
    }

    // cleanup code 

    shmdt(s); 
    shmctl(shm_id, IPC_RMID, NULL);

    return 0;
}

