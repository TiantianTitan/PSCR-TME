#include <iostream>
#include <fstream>
#include <regex>
#include <chrono>

// Q1 : au début,  il y a 566193 mots   runtime: 1s

// Q2 : il y a 20333 mots diférent   runtime: 13s

// Q3 : Word:  warCount:  298
//		Word:  peaceCount:  114
//		Word:  totoCount:  0 			runtime 13s

// Q4: O(n^2)


int main () {
	using namespace std;
	using namespace std::chrono;

	ifstream input = ifstream("./WarAndPeace.txt");

	auto start = steady_clock::now();
	cout << "Parsing War and Peace" << endl;

	size_t nombre_lu = 0;
	// prochain mot lu
	string word;
	// une regex qui reconnait les caractères anormaux (négation des lettres)
	regex re( R"([^a-zA-Z])");

	//vecteur
	vector<pair<string,int>> vec;
	//map
	map<string,size_t> map;

	while (input >> word) {
		// élimine la ponctuation et les caractères spéciaux
		word = regex_replace ( word, re, "");
		// passe en lowercase
		transform(word.begin(),word.end(),word.begin(),::tolower);
			
		
		bool connu = false;
	
		
		for( pair<string,int> & motCount: vec){
			if(motCount.first == word){
				connu = true;
				(motCount.second)++;
				break;
			}
		}




		// for(const auto & elt: conteneur)

		if(!connu){
			// word est maintenant "tout propre"
			if (nombre_lu % 100 == 0)
			// on affiche un mot "propre" sur 100
			// cout << nombre_lu << ": "<< word << endl;
			nombre_lu++;
			pair<string,size_t> ele;
			ele.first = word;
			ele.second = 1;
			vec.push_back(ele);
		}
	
	}
	input.close();

	for(pair<string,int> & motCount : vec){
		if(motCount.first == "war" || motCount.first == "peace" || motCount.first == "toto")
			cout << "Word:  " << motCount.first << "Count:  " << motCount.second << endl;
	}

	cout << "Word:  " << "toto" << "Count:  " << "0" << endl;

	cout << "Finished Parsing War and Peace" << endl;

	auto end = steady_clock::now();
    cout << "Parsing took "
              << duration_cast<milliseconds>(end - start).count()
              << "ms.\n";

    cout << "Found a total of " << nombre_lu << " words." << endl;



    return 0;
}


