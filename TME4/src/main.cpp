#include "Banque.h"

#include <iostream>
#include <unistd.h>

#define TIMES 1000

using namespace std;
using namespace pr;

const int NB_THREAD = 10;

pthread_mutex_t lock_for;

void travail( Banque * bank){
	// il y a 3 tâches à faire : 
	
	// 1- Choisir i et j deux indices de comptes aléatoires, et un montant aléatoire m compris entre 1 et 100.
	// srand((unsigned)time(NULL));
	size_t nb_compte = bank->size();
	size_t i = rand() % nb_compte; 
	size_t j = rand() % nb_compte;
	unsigned int m = 1 + rand()% 99;

	// 3- Dormir une durée aléatoire de 0 à 20 ms.
	unsigned int pause = rand()%20;
	usleep(pause * 1000);
	pthread_mutex_lock(&lock_for);

	// 2- Essayer de transférer le montant m de i à j.
	// zone pour la unique utilisation en même temps
	bank->transfert(i,j,m);
	printf("On a transféré de Compte%d à Compte%d le montant%d\n",(int)i,(int)j,(int)m);

	int iSolde = (int) bank->getComptes()[i].getSolde();
	int jSolde = (int) bank->getComptes()[j].getSolde();

	printf("Compte%d: Solde=%d, Compte%d:  Solde=%d\n", (int)i, iSolde, (int)j, jSolde);
	pthread_mutex_unlock(&lock_for);


}

/**********TME4 Q7************/
// Il n’est pas encore possible de bien protéger toutes les ressources partagées.
// Il y a un risque de blocage,
// La granularité du verrou n'est pas très appropriée (peut provoquer une surcharge)



int main () {

	size_t nb_compte = 100;
	size_t solde = 1000;
	Banque bank(nb_compte,solde);
	Compte cpt;

	vector<thread> threads;
	pthread_mutex_init(&lock_for,0);

	/****************  TME4 Q1  *****************/
	threads.reserve(NB_THREAD);

	for(int i = 0; i< TIMES; i++){
		// faire du travail
		fflush(nullptr);
		threads.push_back(thread(travail,&bank));
		fflush(nullptr);
		threads.emplace_back(travail,&bank);
		fflush(nullptr);
	}

	/****************  TME4 Q2  *****************/
	// Il y a un risque de datarace lors de l'accès simultané aux comptes dans la méthode travail()
	// et sans datarace c'est correct
	
	bank.effectuerBilan();

	for (auto & t : threads) {
		t.join();	
	}
	pthread_mutex_destroy(&lock_for);

	return 0;
}





	/***********************************************************/
	// Le code enregistré pendant le TME4
	// Banque b;
	// thread(& pr::Banque::transfert,&b,10,12);
	// thread(std::mem_fn(&pr::Banque::transfert),ref(b),10,12);
	/***********************************************************/
