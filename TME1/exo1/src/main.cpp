#include "List.h"
#include <string>
#include <iostream>
#include <cstring>

void print_rec(pr::Chainon * tete){ // Implémentation d'afficher la reverse de la liste
	if(tete == NULL) return ;
	print_rec(tete->next);
	std::cout << tete->data << std::endl;
}

size_t length(const char* str){ 
	char* str_2 = (char*) str;
	while(*(str_2++)!= '\0');
	return str_2 - str;
}


char* newcopy(const char* str){
	size_t len = length(str) +1;
	char* str_2 = (char*) malloc(len* sizeof(char));
	for(size_t i = 0; i < len; i++){
		str_2[i] = str[i]; 
	}
	return str_2;
}



int main () {

	std::string abc = "abc";
	char * str = new char [3];
	str[0] = 'a';
	str[1] = 'b';
	str[2] = 'c';
	// size_t i = 0;

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
	std::cout << "*********************************************" << std::endl;

	// Question 5 Découverte du debugger
	std::cout << "Question 5" << std::endl;
	for (size_t i=10; i != 0 ; i--) { // dans ce cas, i vaut avoir ce type de uint, lorsqu'il atteint 0 et i--, ça vaut être un entier positif et hyper grand
		if (tab[i] - tab[i-1] != 1) {
		std::cout << "probleme !" << std::endl;
		}
	}	
	//Question 6
	std::cout << "Question 6" << std::endl;
	std::cout << "Dans ce tableau, il contient que 0 et i vaut 9 au début." << std::endl;


std::cout << "**************Afficher et Tester****************" << std::endl;
	if (! strcmp (str, abc.c_str())) {
		std::cout << "Equal !";
	}

	pr::List list;
	list.push_front(abc);
	list.push_front(abc);

	std::cout << "Liste : " << list.tete->data << std::endl; // Faute: on peut pas envoyer ce genre d'élément tel que List, on doit accéder à cette structure pour récupérer le data qu'on a besoin
	std::cout << "Taille : " << list.size() << std::endl;
	
	// Affiche à l'envers

	std::cout << "***********Affiche à l'envers**************" << std::endl;
	// for (i= list.size() - 1 ; i >= 0 ; i--) {
	// 	std::cout << "elt " << i << ": " << list[i] << std::endl;
	// }
	// Faute: list c'est une structure qui enregistre les instances de Class Chainon
	// il fonctionne pas à l'instar d'un tableau pour afficher les datas dedans
	list.push_back("abc1");
	list.push_back("abc2");
	list.push_back("abc3");
	print_rec(list.tete); // Invocation de la fonction récursive pour afficher l'inverse de la liste

	std::cout << "*********Q9: length et newcopy************" << std::endl;
	// L'implémentation de ces deux fonctions sont au début de main.cpp 
	std::cout <<"length = " << length(str) <<std::endl;
	char* copy = newcopy(str);
	std::cout << "copy: " << copy << "  , length de copy: " << length(copy) << std::endl;
	
	// Question 10 Implanter la classe String conformément aux instructions du TD 1.
	





	// liberer les char de la chaine
	for (char *cp = str ; *cp ; cp++) {
		// if(cp != null) ...
		if(cp == NULL) delete []cp; // Faute: Si cp est vide, c'est la correction
	}
	// et la chaine elle meme
	if(str!= NULL) delete []str; // Faute: pour delete il faut rajouter les crochets juste devant la variable
	

}
