#include "Banque.h"

#include <iostream>

using namespace std;

namespace pr {

void Banque::transfert(size_t deb, size_t cred, unsigned int val) {
	Compte & debiteur = comptes[deb];
	Compte & crediteur = comptes[cred];

	unique_lock<recursive_mutex> transfertLock(transfertMutex);				
		unique_lock<recursive_mutex> debiteurLock(debiteur.getMutex());			
		std::unique_lock<std::mutex> verifieGuard(checkLock);					
		unique_lock<recursive_mutex> crediturLock(crediteur.getMutex());
	if (debiteur.debiter(val)) {
		crediteur.crediter(val);
	}
	
}
size_t Banque::size() const {
	return comptes.size();
}
bool Banque::comptabiliser (int attendu) const {
	int bilan = 0;
	int id = 0;
	for (const auto & compte : comptes) {
		if (compte.getSolde() < 0) {
			cout << "Compte " << id << " en négatif : " << compte.getSolde() << endl;
		}
		bilan += compte.getSolde();
		id++;
	}
	if (bilan != attendu) {
		cout << "Bilan comptable faux : attendu " << attendu << " obtenu : " << bilan << endl;
	}
	return bilan == attendu;
}
 std::vector<Compte> Banque::getComptes(){
	return comptes;
 }


/************* TME4 Q10 ******************/
void Banque::effectuerBilan() {
	std::lock_guard<std::mutex> lock(checkLock);
	for (auto &compte: comptes) {
		comptesCheck.insert(&compte);
    }

}


}
