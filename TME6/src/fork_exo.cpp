#include <iostream>
#include <string>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

// Question 1. En comptant le processus initial, combien de processus engendre l'execution du programme ?

// main pid=3765
//1  i:j 1:3 	//2  k:j 1:0
//3  i:j 2:3	//4  k:j 1:0
				//5  k:j 2:0
//6  i:j 3:3	//7  k:j 1:0
				//8  k:j 2:0
				//9  k:j 3:0

// A1 : 1 proc initiale et 9 successeurs : 10 en total



// int main () {
// 	const int N = 3;
// 	std::cout << "main pid=" << getpid() << std::endl;

// 	for (int i=1, j=N; i<=N && j==N && fork()==0 ; i++ ) {
// 		std::cout << " i:j " << i << ":" << j << std::endl;
// 		for (int k=1; k<=i && j==N ; k++) {
// 			if ( fork() == 0) {
// 				j=0;
// 				std::cout << " k:j " << k << ":" << j << std::endl;
// 			}
// 		}
// 	}
// 	return 0;
// }

// Question 2. Modifiez le programme pour que le père ne se termine qu'après que tous les autres
// processus soient terminés. On n'attendra pas plus de fils qu'on en a crée et on ne limitera pas le
// parallélisme.

int main () {
	const int N = 3;
	int nb_fils = 0;
	std::cout << "main pid=" << getpid() << std::endl;

	for (int i=1, j=N; i<=N && j==N ; i++ ) {

		if( fork()==0) nb_fils = 0;
		else {
			nb_fils++;
			break;
		}
		std::cout << " i:j " << i << ":" << j << std::endl;
		for (int k=1; k<=i && j==N ; k++) {
			if (fork() == 0) {
				nb_fils = 0;
				j=0;
				std::cout << " k:j " << k << ":" << j << std::endl;
			}	else {
				nb_fils++;
			}
		}
	}

	// père
	for(int i = 0; i < nb_fils; i++){
		if (wait(NULL) == -1){
			std::cout << "Trop de wait de" << getpid() << std::endl;
		}
	}

	if(wait(NULL) != -1) 
		std::cout << "il en reste" << std::endl;

	std::cout << "Fin du processus " << getpid() << std::endl;
	return 0;
}

// TEST CORRECT
// main pid=9086
//  i:j 1:3
//  k:j 1:0
// Fin du processus 9088
//  i:j 2:3
//  k:j 1:0
// Fin du processus 9090
//  k:j 2:0
// Fin du processus 9091
//  i:j 3:3
//  k:j 1:0
// Fin du processus 9093
//  k:j 2:0
// Fin du processus 9094
//  k:j 3:0
// Fin du processus 9095
// Fin du processus 9092
// Fin du processus 9089
// Fin du processus 9087 
// Fin du processus 9086
