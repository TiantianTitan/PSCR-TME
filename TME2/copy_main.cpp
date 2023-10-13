#include <iostream>
#include <fstream>
#include <regex>
#include <chrono>
#include "HashMap.hpp"

// TME2
// Q1 : au début,  il y a 566193 mots   runtime: 1s

// Q2 : il y a 20333 mots diférent   runtime: 13s

// Q3 : Word:  warCount:  298
//		Word:  peaceCount:  114
//		Word:  totoCount:  0 			runtime 13s

// Q4: O(n^2)

class Personne{
	public:
    std::string nom;
    std::string prenom;
    int age;
	std::string sexe;
};




int main () {
	using namespace std;
	using namespace std::chrono;

	cout << "test1" << endl;

	ifstream input = ifstream("./WarAndPeace.txt");

	auto start = steady_clock::now();
	cout << "Parsing War and Peace" << endl;

	size_t nombre_lu = 0;
	// prochain mot lu
	string word;
	// une regex qui reconnait les caractères anormaux (négation des lettres)
	regex re( R"([^a-zA-Z])");

	//vecteur
	//vector<pair<string,int>> vec;
	//map
	size_t size = 1000;
	
	HashMap<string,size_t> map (size);

    // iterator
    buckets_it it = map.begin();


	while (input >> word) {
		// élimine la ponctuation et les caractères spéciaux
		word = regex_replace ( word, re, "");
		// passe en lowercase
		transform(word.begin(),word.end(),word.begin(),::tolower);


				
        if (map.get(word) != nullptr) {
            size_t setValue = *(map.get(word)) + 1;
            map.set(word, setValue);
        } else {
            map.put(word, 1);
        }


	}
	input.close();


	string tab [3];
	tab[0] = "war";
	tab[1] = "toto";
	tab[2] = "peace";

	for(string checkWord: tab){
		size_t* Count = map.get(checkWord);
		if (Count != nullptr) {
        	cout << "Word: " << checkWord << "Count: " << *Count << endl;
    	} else {
        	cout << "Word: " << checkWord << "Count: " << 0 << endl;
    	}

	}


	auto end = steady_clock::now();
    cout << "Parsing took "
              << duration_cast<milliseconds>(end - start).count()
              << "ms.\n";

    cout << "Found a total of " << nombre_lu << " words." << endl;


	/****************** TME3 Q7   **************************/
 	std::unordered_map<std::string, size_t> myHashMap;
    myHashMap["clé1"] = 42;
    myHashMap["clé2"] = 99;

    // Accéder à un élément et afficher le
    std::cout << "Valeur associée à clé1 : " << myHashMap["clé1"] << std::endl;

    if (myHashMap.find("clé3") != myHashMap.end()) {
        std::cout << "clé3 existe." << std::endl;
    } else {
        std::cout << "clé3 n'existe pas." << std::endl;
    }

    // Afficher le contenu de la unordered_map
    std::cout << "Contenu de la unordered_map :" << std::endl;
    for (const auto& pair : myHashMap) {
        std::cout << "Clé : " << pair.first << ", Valeur : " << pair.second << std::endl;
    }

	/******************** TME3 Q8  *****************************/


	std::unordered_map<std::string, int> wordFrequency;
	wordFrequency["clé1"] = 10;
	wordFrequency["clé2"] = 10;
	wordFrequency["clé3"] = 10;
	wordFrequency["clé4"] = 12;

    std::unordered_map<int, std::forward_list<std::string>> frequencyToWords;
    for (const auto& pair : wordFrequency) {
        const std::string& word = pair.first;
        int frequency = pair.second;

        // Ajoutez le mot à la liste correspondante dans la nouvelle table
        frequencyToWords[frequency].push_front(word);
    }

    	int N = 10;

    // Affichez les mots ayant N occurrences
    if (frequencyToWords.find(N) != frequencyToWords.end()) {
        std::cout << "Mots ayant " << N << " occurrences : ";
        for (const std::string& word : frequencyToWords[N]) {
            std::cout << word << " ";
        }
        std::cout << std::endl;
    } else {
        std::cout << "Aucun mot n'a " << N << " occurrences." << std::endl;
    }


	/********************** TME3 Q9 *************************/


   	std::vector<Personne> personnes;

    // Initialisation
    personnes.push_back(Personne{"Nom1", "Prenom1", 25, "Masculin"});
    personnes.push_back(Personne{"Nom2", "Prenom2", 30, "Féminin"});
    personnes.push_back(Personne{"Nom3", "Prenom3", 25, "Masculin"});
    personnes.push_back(Personne{"Nom4", "Prenom4", 30, "Masculin"});
	personnes.push_back(Personne{"Nom5", "Prenom5", 45, "Féminin"});
    // Créer un unordered_map pour regrouper les personnes par âge.
    std::unordered_map<int, std::vector<Personne>> personnesParAge ;


    for (const Personne& personne : personnes) {
        personnesParAge[personne.age].push_back(personne);
    }

	// test
    int ageRecherche = 30; 
    if (personnesParAge.find(ageRecherche) != personnesParAge.end()) {
        std::cout << "Personnes ayant " << ageRecherche << " ans :" << std::endl;
        for (const Personne& personne : personnesParAge[ageRecherche]) {
            std::cout << personne.prenom << " " << personne.nom << std::endl;
        }
    } else {
        std::cout << "Aucune personne trouvée avec " << ageRecherche << " ans." << std::endl;
    }

    return 0;
}




