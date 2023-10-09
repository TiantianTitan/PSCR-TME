#include <iostream>
#include <fstream>
#include <regex>
#include <chrono>
#include "HashMap.hpp"


// Q1 : au début,  il y a 566193 mots   runtime: 1s

// Q2 : il y a 20333 mots diférent   runtime: 13s

// Q3 : Word:  warCount:  298
//		Word:  peaceCount:  114
//		Word:  totoCount:  0 			runtime 13s

// Q4: O(n^2)








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





		// bool connu = false;


		// for( pair<string,int> & motCount: vec){
		// 	if(motCount.first == word){
		// 		connu = true;
		// 		(motCount.second)++;
		// 		break;
		// 	}
		// }


				
        if (map.get(word) != nullptr) {
            size_t setValue = *(map.get(word)) + 1;
            map.set(word, setValue);
        } else {
            map.put(word, 1);
        }


		// incomplet
		for(;it!=map.end();it++){
			

		}


 


		// if(!connu){
		// 	// word est maintenant "tout propre"
		// 	if (nombre_lu % 100 == 0)
		// 	// on affiche un mot "propre" sur 100
		// 	// cout << nombre_lu << ": "<< word << endl;
		// 	nombre_lu++;
		// 	pair<string,size_t> ele;
		// 	ele.first = word;
		// 	ele.second = 1;
		// 	vec.push_back(ele);
		// }

	}
	input.close();

	// for(pair<string,int> & motCount : vec){
	// 	if(motCount.first == "war" || motCount.first == "peace" || motCount.first == "toto")
	// 		cout << "Word:  " << motCount.first << "Count:  " << motCount.second << endl;
	// }

	// cout << "Word:  " << "toto" << "Count:  " << "0" << endl;

    // Compter l'occurrence du mot "war"

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





	// for(string checkWord : tab){
	// 	//  int* Count = map.get(checkWord);
    // if (Count != nullptr) {
    //     cout << "Word: " << checkWord << "Count: " << *Count << endl;
    // } else {
    //     cout << "Word: " << checkWord << "Count: " << 0 << endl;
    // }
	// }
   


	auto end = steady_clock::now();
    cout << "Parsing took "
              << duration_cast<milliseconds>(end - start).count()
              << "ms.\n";

    cout << "Found a total of " << nombre_lu << " words." << endl;



    return 0;
}




