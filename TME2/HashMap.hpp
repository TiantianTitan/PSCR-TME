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

            size_t count (iterator begin, iterator end){
                size_t count = 0;
                while(begin != end){
                    begin++;
                    count++;
                }
                return count;
            }

            size_t count_if_equal(iterator begin, iterator end, const T &val){
                size_t count = 0;
                while(begin != end){
                    if(*begin == val) count++;
                    begin++;
                }
                return begin;
            }

            iterator find (const K & key){
                size_t hashcode = std::hash(key);
                size_t index = hashcode % buckets.size();
                for(auto it = buckets[index].begin(); it != buckets[index].end(); it++){
                    if(it->key == key) return it;
                }
                return end();
            }

            std::pair<iterator,bool> insert (const Entry & entry){
                size_t index = std::hash<K>(entry.key) % buckets.size();
                std::pair<iterator,bool> ret;
                ret.first = buckets[index].begin();
                ret.second = false;
                for(;ret.first != buckets[index].end();ret.first++){
                    if(*ret.first == entry.key){
                        ret.second = false;
                        return ret;
                    }
                }
                buckets[index].emplace_front(entry);
                ret.second = true;
                return ret;
            }


    };




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


