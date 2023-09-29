#include <cstdio>
#include <string>
#include <iostream>
#include <regex>
#include <chrono>
using namespace std;





// struct Entry
// {
//     const string key;
//     size_t value;
// };

template<typename K, typename V>


class HashMap
{

    private:
    
        /* data */
        size_t size;
        size_t n;
        vector<pair<K,V>>  *tab ;
    public:
        HashMap(size_t size);
        ~HashMap();
        void push(pair<K,V> entry);
        size_t hashcode(K key);
        bool isMember(K key);
        V getValue(K key);
        
};

template<typename K, typename V>
HashMap<K,V>::HashMap(size_t size)
{   
    this->size = size;
    this->tab = new vector<pair<K,V>>[size]();
}

template<typename K, typename V>
HashMap<K,V>::~HashMap()
{
    delete[] this->tab;
}
template<typename K, typename V>
void HashMap<K,V>::push(pair<K,V> entry){
    size_t code = hashcode(entry.first);
    code %= size; 
    entry.second++;
    tab[code].push_back(entry);
    
}

template<typename K, typename V>
size_t HashMap<K,V>::hashcode(K key){
    std::hash<std::string> hash;
    size_t hashcode = hash(key);
    return hashcode;
}

template<typename K, typename V>
bool HashMap<K,V>::isMember(K key){
    size_t code = hashcode(key);
    code %= size;
    for (const std::pair<K, V>& entry : tab[code]) {
        if (entry.first == key) {
            return true;
        }
    }

    return false; 
}


template<typename K, typename V>
V HashMap<K,V>::getValue(K key){
    size_t code = hashcode(key);
    code %= size;
    for (const std::pair<K, V>& entry : tab[code]) {
        if (entry.first == key) {
            return entry.second;
        }
    }

    return 0; 
}
    













