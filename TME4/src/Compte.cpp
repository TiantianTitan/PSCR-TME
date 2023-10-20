#include "Compte.h"

using namespace std;

namespace pr {
	
	void Compte::crediter (unsigned int val) {
		unique_lock<recursive_mutex> g(m);
		solde+=val ;
	}

	bool Compte::debiter (unsigned int val) {
		unique_lock<recursive_mutex> g(m);
		bool doit = solde >= (int) val;
		if (doit) {
			solde-=val ;
		}
		return doit;
	}

	int Compte::getSolde() const  {
		unique_lock<recursive_mutex> g(m);
		return solde;
	}


	// TME4 Question 3 **************************
	void Compte::lock() const {
		this->m.lock();
	}

	void Compte::unlock() const {
		this->m.unlock();
	}

	void Compte::try_lock() const {
		this->m.try_lock();
	}

	// ******************************************
	// TME4 Question 3 **************************
	std::recursive_mutex& Compte::getMutex(){
		return m;
	}

	// ******************************************

	// NB : vector exige Copyable, mais mutex ne l'est pas...
	Compte::Compte(const Compte & other) {
		other.m.lock();
		solde = other.solde;
		other.m.unlock();
	}

}
