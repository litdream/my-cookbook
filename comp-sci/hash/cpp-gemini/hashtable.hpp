#ifndef HASHTABLE_HPP
#define HASHTABLE_HPP

#include <vector>
#include <list>
#include <string>
#include <utility> // For std::pair
#include <functional> // For std::hash
#include <stdexcept> // For std::out_of_range (KeyError equivalent)

template <typename Key, typename Value>
class HashTable {
public:
    // Default capacity 10
    HashTable(size_t capacity = 10);

    // Disable copy constructor and assignment operator for simplicity
    // If deep copy is needed, implement them explicitly
    HashTable(const HashTable&) = delete;
    HashTable& operator=(const HashTable&) = delete;

    void put(const Key& key, const Value& value);
    Value get(const Key& key) const;
    void remove(const Key& key); // Renamed from 'delete' to avoid keyword conflict

    // Convenience methods (operator overloads)
    Value& operator[](const Key& key);
    const Value& operator[](const Key& key) const;

private:
    size_t _hash(const Key& key) const;

    size_t capacity;
    std::vector<std::list<std::pair<Key, Value>>> buckets;
};

#endif // HASHTABLE_HPP
