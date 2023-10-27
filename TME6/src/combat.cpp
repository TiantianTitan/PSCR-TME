#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <time.h>
#include <cstdio>
#include <cstdlib>
#include <csignal>
#include "rsleep.h"

static int vie = 10;

void handler (int sig){
    if(sig == SIGUSR1){
        vie--;
        printf("on a été attaqué, j'ai la vie: %d pour l'instant\n",vie);
        if(vie == 0){
            printf("on a plus de vie, on a perdu\n");
            exit(1);
        }
    }
}

void attaque(pid_t adversaure){
    signal(SIGUSR1,handler);
    kill(adversaure,SIGUSR1) ; 
    randsleep();
}

void defense(){
    signal(SIGUSR1,SIG_IGN);
    randsleep();
}

void combat(pid_t adversaire){
    while(1){
        defense();
        attaque(adversaire);
    }
}

int main() {
    pid_t pere = getpid();
    pid_t pid = fork();
    srand(pid);
    if (pid == 0) combat(pere); 
    else combat(pid);
    return 0;
}


// Question 6. Le combat est-il encore équitable ? Expliquez pourquoi.
/*  A6:
    Variable Globale Partagée : Chaque processus a sa propre copie de la variable vie post-fork,
     ce qui signifie qu'il n'y a pas de véritable interaction entre les adversaires, mais deux combats séparés avec un compteur.

    Gestion des Signaux : La réinitialisation répétée des gestionnaires de signaux entre l'attaque et la défense peut 
     conduire à une complexité accrue et à des comportements inattendus si les signaux sont envoyés pendant une période d'ignorance temporaire.

    Synchronisation : L'absence de synchronisation entre les processus peut entraîner des attaques et des défenses désordonnées,
     sans garantie d'alternance stricte, affectant l'équité du combat.

    Initialisation du générateur de nombres aléatoires : L'initialisation de srand avec pid peut conduire à des séquences de nombres
     aléatoires très similaires entre les processus, affectant la randomisation des délais entre l'attaque et la défense.

    Terminaison : Un processus qui perd ne notifie pas l'autre processus de sa défaite, laissant l'autre processus dans une boucle indéfinie,
     tentant d'attaquer un processus qui n'existe plus.
*/
