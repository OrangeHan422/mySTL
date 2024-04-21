#pragma once
#include "hashtable.h"
#include <cstddef>

namespace myStd{
template <typename Key>
class unordered_set{
public:
    unordered_set()
    :m_hashtable()
    {}

    ~unordered_set() = default;

    bool empty() const { return m_hashtable.size() == 0 ; }

    size_t size() const { return m_hashtable.size(); }

    void clear() { m_hashtable.clear(); }

    void insert(const Key& key) { m_hashtable.insertKey(key); }

    void erase(const Key& key) { m_hashtable.erase(key); }

    bool find(const Key& key) { return m_hashtable.find(key) != nullptr; }
private:
    HashTable<Key,Key> m_hashtable;
};
}//namespace myStd