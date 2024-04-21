#pragma once


#include "hashtable.h"

namespace myStd{
template <typename Key,typename Value>
class unordered_map{
public:
    unordered_map()
    :m_hashtable()
    {}

    ~unordered_map()
    {}

    bool empty() const { return m_hashtable.size() == 0; }

    size_t size() const { return m_hashtable.size(); }

    void clear() { m_hashtable.clear(); }

    void insert(const Key& key,const Value& value){
        m_hashtable.insert(key,value);
    }

    void erase(const Key& key) { m_hashtable.erase(key); }

    bool find(const Key& key) { return m_hashtable.find(key) != nullptr; }

    Value& operator[](const Key& key){
        auto* value_of_key_ptr = m_hashtable.find(key);
        if(value_of_key_ptr != nullptr){
            return *value_of_key_ptr;
        }
        
        m_hashtable.insertKey(key);
        value_of_key_ptr = m_hashtable.find(key);
        return *value_of_key_ptr;
    }

private:
    HashTable<Key,Value> m_hashtable;
};
}//namespace myStd