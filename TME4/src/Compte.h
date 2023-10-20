#pragma once
#include <thread>
#include <mutex>

namespace pr {

class Compte {
	// mutable std::mutex m;
	/***************TME4 Q6******************/
	//Permet au même thread d'acquérir le même verrou recursive_mutex plusieurs fois.
	mutable std::recursive_mutex m;
	int solde;
public :
	Compte(int solde=0):solde(solde) {}
	Compte(const Compte & other);
	void crediter (unsigned int val) ;
	bool debiter (unsigned int val) ;
	int getSolde() const  ;
	// TME4 Q3*****************
	void lock() const;
	void unlock() const;
	void try_lock() const;
	//*************************
	// TME4 Q4*****************
	std::recursive_mutex & getMutex();
	//*************************

};

}
