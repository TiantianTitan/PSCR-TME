#include <sys/sem.h>
#include <unistd.h>
 #include <string.h>

namespace pr {
#define STACKSIZE 100
template<typename T>
class Stack {
    T tab [STACKSIZE];
    size_t sz;
    int semid;
    sembuf p_lock[2], v_unlock[2];

public :
    Stack() : sz(0) {
        memset(tab, 0, sizeof tab);

        // Création des sémaphores
        semid = semget(IPC_PRIVATE, 2, IPC_CREAT | 0666);
        semctl(semid, 0, SETVAL, 1); // Mutex
        semctl(semid, 1, SETVAL, STACKSIZE); // Items

        // Initialisation des opérations de semaphore
        p_lock[0] = {0, -1, 0}; // Lock Mutex
        p_lock[1] = {1, -1, 0}; // Decrement Items
        v_unlock[0] = {0, 1, 0}; // Unlock Mutex
        v_unlock[1] = {1, 1, 0}; // Increment Items
    }

    T pop() {
        // Attendre si vide
        semop(semid, &p_lock[0], 1);
        T toret = tab[--sz];
        semop(semid, v_unlock, 2); // Débloquer le mutex et incrémenter les items
        return toret;
    }

    void push(T elt) {
        // Attendre si plein
        semop(semid, p_lock, 2); // Verrouiller le mutex et décrémenter les items
        tab[sz++] = elt;
        semop(semid, &v_unlock[0], 1);
    }

    ~Stack() {
        // Nettoyage du semaphore
        semctl(semid, 0, IPC_RMID);
    }

	size_t getSz(){
		return sz;
	}

	size_t getSzMax(){
		return STACKSIZE;
	}
};

}
