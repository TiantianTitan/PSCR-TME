#include "List.h"
#include <string>
#include <iostream>
#include <cstring>

int main () {

	std::string abc = "abc";
	char * str = new char [3];
	str[0] = 'a';
	str[1] = 'b';
	str[2] = 'c';
	size_t i = 0;

	if (! strcmp (str, abc.c_str())) {
		std::cout << "Equal !";
	}

	pr::List list;
	list.push_front(abc);
	list.push_front(abc);

	std::cout << "Liste : " << list.tete->data << std::endl;
	std::cout << "Taille : " << list.size() << std::endl;

	// Affiche à l'envers
	for (i= list.size() - 1 ; i >= 0 ; i--) {
		std::cout << "elt " << i << ": " << list[i] << std::endl;
	}

	// liberer les char de la chaine
	for (char *cp = str ; *cp ; cp++) {
		delete cp;
	}
	// et la chaine elle meme
	delete str;

}
