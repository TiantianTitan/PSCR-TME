#include "Banque.h"

#include <iostream>
#include <unistd.h>

#define TIMES 1000

using namespace std;
using namespace pr;

const int NB_THREAD = 10;


void travail( Banque * bank){
	// il y a 3 tâches à faire : 
	// 1- Choisir i et j deux indices de comptes aléatoires, et un montant aléatoire m compris entre 1 et 100.
	size_t nb_compte = bank->size();
	size_t i = rand() % nb_compte; 
	size_t j = rand() % nb_compte;
	unsigned int m = 1 + rand()% 99;
	// 2- Essayer de transférer le montant m de i à j.
	bank->transfert(i,j,m);
	printf("On a transféré de Compte%d à Compte%d le montant%d\n",(int)i,(int)j,(int)m);
	
	int iSolde = (int) bank->getComptes()[i].getSolde();
	int jSolde = (int) bank->getComptes()[j].getSolde();
	
	printf("Compte%d: Solde=%d, Compte%d:  Solde=%d\n", (int)i, iSolde, (int)j, jSolde);
	// 3- Dormir une durée aléatoire de 0 à 20 ms.
	unsigned int pause = rand()%20 ;
	usleep(pause * 1000);
}

int main () {

	size_t nb_compte = 100;
	size_t solde = 1000;
	Banque bank(nb_compte,solde);
	Compte cpt;

	vector<thread> threads;
	// TODO : creer des threads qui font ce qui est demandé

	/****************  TME4 Q1  *****************/
	threads.reserve(NB_THREAD);

	for(int i = 0; i< TIMES; i++){
		// faire du travail
		threads.push_back(thread(travail,&bank));
		threads.emplace_back(travail,&bank);
	}
	



	for (auto & t : threads) {
		t.join();	
	}

	// TODO : tester solde = NB_THREAD * JP
	return 0;
}




	/***********************************************************/
	// Le code enregistré pendant le TME4
	// Banque b;
	// thread(& pr::Banque::transfert,&b,10,12);
	// thread(std::mem_fn(&pr::Banque::transfert),ref(b),10,12);
	/***********************************************************/
