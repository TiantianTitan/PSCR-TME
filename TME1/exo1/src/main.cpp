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

	// Question 4 afficher un tableau
	std::cout << "Q4: Afficher un tableau qui contient 0 - 9" << std::endl;

	// La création du tableau
	int size = 10;
	int* tab = new int[size];
	for(int i = 0; i < size; i++){
		tab[i] = i;
	}
	// Print ce tableau
	for(int i = 0; i < size - 1; i ++){
		std::cout << tab[i] << "," ;
	}
	std::cout<< tab[size-1] << std::endl;
	std::cout << "******************************************" << std::endl;

	// Question 5 Découverte du debugger
	for (size_t i=10; i != 0 ; i--) { // dans ce cas, i vaut avoir ce type de uint, lorsqu'il atteint 0 et i--, ça vaut être un entier positif et hyper grand
		if (tab[i] - tab[i-1] != 1) {
		std::cout << "probleme !";
		}
	}	
	//Question 6
	std::cout << "Question 6" << std::endl;
	std::cout << "Dans ce tableau, il contient que 0 et i vaut 9 au début." << std::endl;


std::cout << "******************************************" << std::endl;
	if (! strcmp (str, abc.c_str())) {
		std::cout << "Equal !";
	}

	pr::List list;
	list.push_front(abc);
	list.push_front(abc);

	std::cout << "Liste : " << list.tete->data << std::endl; // Faute: on peut pas envoyer ce genre d'élément tel que List, on doit accéder à cette structure pour récupérer le data qu'on a besoin
	std::cout << "Taille : " << list.size() << std::endl;

	// Affiche à l'envers


	// for (i= list.size()-1; i >= 0 ; i--) {
	// 	std::cout << "elt " << i << ": " << list<< std::endl;
	// }

	// std::string * tab_list = new std::string[list.size()];

	// int size = list.size()/sizeof(size_t);

	// for (int x = 0; x< size; x++) {
	// 	// tab_list[i] = list.tete->data;
	// 	// list.tete = list.tete->next;
	
	//  }
	// for(i = 0; i< list.size(); i++){
	// 	 std::cout << "elt " << i-1 << ": " << tab_list[list.size()-i] << std::endl;
	// }
	
	// liberer les char de la chaine
	for (char *cp = str ; *cp ; cp++) {
		if(cp != NULL) delete []cp; // Faute: pour delete il faut rajouter les crochets juste devant la variable
	}
	// et la chaine elle meme
	if(str!= NULL) delete []str; // Faute: pour delete il faut rajouter les crochets juste devant la variable
	

}
