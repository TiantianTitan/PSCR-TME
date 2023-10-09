#include <iostream>
#include <vector>
#include <forward_list>
#include <functional>




struct Entry{
	const std::string key;
	size_t value;
	Entry(const std::string& k, const size_t& v) : key(k), value(v) {};
};



typedef std::vector<std::forward_list<Entry>> buckets_t;
typedef buckets_t::iterator buckets_it;



template <typename K, typename V>
class HashMap {
public:


private:
    std::vector<std::forward_list<Entry>> buckets;

public:
    HashMap(size_t size) : buckets(size) {}

    V* get(const K& key) {
        size_t h = std::hash<K>()(key);
        size_t bucketIndex = h % buckets.size();

        for (Entry& e : buckets[bucketIndex]) {
            if (e.key == key) {
                return &(e.value);
            }
        }

        return nullptr;
    }

    void set(const K& key, const V& value) {
        size_t h = std::hash<K>()(key);
        size_t bucketIndex = h % buckets.size();

        for (Entry& e : buckets[bucketIndex]) {
            if (e.key == key) {
                e.value = value;
            }
        }
    }


    bool put(const K& key, const V& value) {
        size_t h = std::hash<K>()(key);
        size_t bucketIndex = h % buckets.size();

        for (Entry& e : buckets[bucketIndex]) {
            if (e.key == key) {
                e.value = value;
                return true; // La clé existait déjà et a été mise à jour
            }
        }

        Entry newEntry(key, value);
        buckets[bucketIndex].emplace_front(newEntry);
        return false; // La clé n'existait pas et a été insérée
    }

    size_t size() const {
        size_t count = 0;
        for (const std::forward_list<Entry>& bucket : buckets) {
            count += std::distance(bucket.begin(), bucket.end());
        }
        return count;
    }


    buckets_it begin(){
         size_t index = 0;
            for (; index < buckets.size(); ++index) {
                if (!buckets[index].empty()) {
                    break;
                }
            }
            return buckets.begin() + index;
    
    }

    buckets_it end() {
        size_t index = buckets.size();
        return buckets.begin() + index;
    }
};




template <typename T>
class iterator{
    
    // attribut
    private:
        size_t index;
        std::forward_list<Entry>::iterator it;
        buckets_t &buckets;
    public:
        // constructeur
        iterator(){
            
        }

        iterator(buckets_t &buckets,size_t index,std::forward_list<Entry>::iterator it){
            this->index = index;
            this->it = it;
            this->buckets = buckets;
        }

        // méthode
        Entry& operator*(){
            return *it;
        }

        T* operator->(){
            return &it;
        }

        iterator & operator++(){
            if(it != end()){
                ++it;
                return it;    
            }
            return end();
        }

        bool operator!=(const iterator & other){
            if(it == other) return true;
            else return false;
        }

        iterator begin(){
            size_t index = 0;
            for(;index < buckets.size();++index){
                if(!buckets[index].empty()){
                  break;  
                }
            }
            return iterator(buckets,index,buckets[index].begin);
        }

        iterator end(){
            iterator index = begin();
            for(; index != nullptr; index++ ){}
            return index;
        }

};

