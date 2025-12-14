#include "hashtable.hpp"
#include <iostream>

template <typename Key, typename Value>
HashTable<Key, Value>::HashTable(size_t capacity) : capacity(capacity) {
    buckets.resize(capacity);
}

template <typename Key, typename Value>
size_t HashTable<Key, Value>::_hash(const Key& key) const {
    return std::hash<Key>{}(key) % capacity;
}

template <typename Key, typename Value>
void HashTable<Key, Value>::put(const Key& key, const Value& value) {
    size_t index = _hash(key);
    std::list<std::pair<Key, Value>>& chain = buckets[index];

    for (auto& pair : chain) {
        if (pair.first == key) {
            pair.second = value;
            return;
        }
    }
    chain.emplace_back(key, value);
}

template <typename Key, typename Value>
Value HashTable<Key, Value>::get(const Key& key) const {
    size_t index = _hash(key);
    const std::list<std::pair<Key, Value>>& chain = buckets[index];

    for (const auto& pair : chain) {
        if (pair.first == key) {
            return pair.second;
        }
    }
    throw std::out_of_range("Key not found.");
}

template <typename Key, typename Value>
void HashTable<Key, Value>::remove(const Key& key) {
    size_t index = _hash(key);
    std::list<std::pair<Key, Value>>& chain = buckets[index];

    for (auto it = chain.begin(); it != chain.end(); ++it) {
        if (it->first == key) {
            chain.erase(it);
            return;
        }
    }
    throw std::out_of_range("Key not found.");
}

template <typename Key, typename Value>
Value& HashTable<Key, Value>::operator[](const Key& key) {
    size_t index = _hash(key);
    std::list<std::pair<Key, Value>>& chain = buckets[index];

    for (auto& pair : chain) {
        if (pair.first == key) {
            return pair.second;
        }
    }
    // If key not found, insert a new one with default-constructed value
    // This mimics std::map behavior
    chain.emplace_back(key, Value{});
    return chain.back().second;
}

template <typename Key, typename Value>
const Value& HashTable<Key, Value>::operator[](const Key& key) const {
    size_t index = _hash(key);
    const std::list<std::pair<Key, Value>>& chain = buckets[index];

    for (const auto& pair : chain) {
        if (pair.first == key) {
            return pair.second;
        }
    }
    throw std::out_of_range("Key not found.");
}

// Explicit instantiations for common types (e.g., string to string, int to string)
// This is often needed when template implementations are in a .cpp file
// If not explicitly instantiated, the linker might not find the template functions
template class HashTable<std::string, std::string>;
template class HashTable<int, std::string>;
template class HashTable<int, int>;
// Add more as needed based on common usage
