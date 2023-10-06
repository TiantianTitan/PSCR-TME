#include <iostream>
#include <vector>
#include <forward_list>
#include <functional>

template <typename K, typename V>
class HashMap {
public:
    struct Entry {
        const K key;
        V value;
        Entry(const K& k, const V& v) : key(k), value(v) {}
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
};