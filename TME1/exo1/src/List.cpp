#include "List.h" 		// Faute: Associer les bibliothèques.h et .cpp
#include <iostream>
#include <cstddef>
#include <cstring>


namespace pr {

// ******************* Chainon
Chainon::Chainon (const std::string & data, Chainon * next):data(data),next(next) {};

size_t Chainon::length() {
	// Faute: pour calculer correcte la longueur de cette chaine, le code corrigé est ci-dessous:
	size_t len = 1;
	if (next != nullptr) {
		len ++;
		next = next->next;
	}
	return len;
}

void Chainon::print (std::ostream & os) const { // Faute: accorder const 
	os << data ;
	if (next != nullptr) {
		os << ", ";
		next->print(os); // Faute: récursive sous la condition != nullptr
	}
}

// ******************  List
const std::string & List::operator[] (size_t index) const  {
	Chainon * it = tete;
	for (size_t i=0; i < index ; i++) {
		it = it->next;
	}
	return it->data;
}

void List::push_back (const std::string& val) {
	if (tete == nullptr) {
		tete = new Chainon(val);
	} else {
		Chainon * fin = tete;
		while (fin->next) {
			fin = fin->next;
		}
		fin->next = new Chainon(val);
	}
}

void List::push_front (const std::string& val) {
	tete = new Chainon(val,tete);
}

bool List::empty() { // Faute: pour invoquer les méthodes d'une classe, il faut utiliser ::
	return tete == nullptr;
}

size_t List::size() const {
	if (tete == nullptr) {
		return 0;
	} else {
		return tete->length();
	}
}

} // namespace pr
std::ostream & operator<< (std::ostream & os, const pr::List & vec)
{
	os << "[";
	if (vec.tete != nullptr) {
		vec.tete->print (os) ;
	}
	os << "]";
	return os;
}

