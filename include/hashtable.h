#pragma once

#include <list>
#include <functional>
#include "commonHead.h"


namespace myStd{
template <typename Key, typename Value,typename Hash = std::hash<Key>>
class HashTable{
public:
    HashTable(size_t size = 10,const Hash& hasher = Hash())
    :m_buckets(size)
    ,m_hasher(hasher)
    ,m_table_size(size)
    ,m_num_of_elements(0)
    {}

    ~HashTable(){ _cleanup(); }

    void insert(const Key& key,const Value& value){
        // if overload,rehash
        if((m_num_of_elements + 1) > m_max_load_factor * m_table_size){
            if(m_table_size == 0) m_table_size = 1;
            _rehash(m_table_size * 2);
        }
        
        // caculate index of key
        size_t index = _hash(key);
        auto& bucket = m_buckets[index];
        // insert into bucket only if there's no same key exists
        if(std::find(std::begin(bucket),std::end(bucket),key) == std::end(bucket)){
            bucket.push_back(HashNode(key,value));
            ++m_num_of_elements;
        }
    }
    
    void insertKey(const Key& key){ insert(key,Value{}); }

    void erase(const Key& key){
        // calculate index of key
        size_t index = _hash(key);
        auto& bucket = m_buckets[index];
        // erase key if key was found
        auto it = std::find(std::begin(bucket),std::end(bucket),key);
        if(it != bucket.end()){
            bucket.erase(it);
            m_num_of_elements--;
        }
    }

    Value* find(const Key& key){
        size_t index = _hash(key);
        auto& bucket = m_buckets[index];
        auto it = std::find(std::begin(bucket),std::end(bucket),key);
        if(it != bucket.end()){
            return &it->m_value;
        }
        return nullptr;
    }

    size_t size() const { return m_num_of_elements; }

    void print() const{
        for(size_t i = 0; i < m_buckets.size(); ++i){
            for(const auto& elem : m_buckets[i]){
                elem.print();
            }
        }
        std::cout << std::endl;
    }

private:
    struct HashNode{
        Key m_key;
        Value m_value;

        explicit HashNode(const Key& key)
        :m_key(key)
        ,m_value()
        {}

        HashNode(const Key& key,const Value& value)
        :m_key(key)
        ,m_value(value)
        {}

        bool operator==(const HashNode& rhs) { return m_key == rhs.m_key; }
        bool operator!=(const HashNode& rhs) { return m_key != rhs.m_key; }
        bool operator<(const HashNode& rhs) { return m_key < rhs.m_key; }
        bool operator>(const HashNode& rhs) { return m_key > rhs.m_key; }
        bool operator==(const Key& key) { return m_key != key; }

        void print() const{
            std::cout << m_key << " " << m_value << " ";
        }
    };
    using Bucket = std::list<HashNode>; //used to represent each pos in hash table
    std::vector<Bucket> m_buckets;      //actually hash table
    Hash m_hasher;                      //used to caculate hash value
    size_t m_table_size;                //nums of buckets,aka hash table length
    size_t m_num_of_elements;           //nums of elements
    float m_max_load_factor{0.75};      //load factor of hash

    size_t _hash(const Key& key) const{
        //caculate hash index of key 
        return m_hasher(key) % m_table_size;
    }

    void _rehash(size_t newSize){
        /*
            rehash just like realloc,but with new hash value.
            inorder to avoid over conflicted in hashtable
        */
        std::vector<Bucket> newBuckets(newSize);
        // for every position(bucket) of hash table
        for(const auto& bucket:m_buckets){
            // for every elem in bucket(position)
            for(const auto& hashNode : bucket){
                //caculate new hash value and insert into new hashtable(vector)
                size_t newIndex = m_hasher(hashNode.m_key) % newSize;
                newBuckets[newIndex].push_back(hashNode);//newBuckets-->vector<list>
            }
        }//end of for(const auto& bucket:m_buckets)
        m_buckets = std::move(newBuckets);
        m_table_size = newSize;
    }

    void _cleanup(){
        m_buckets.clear();
        m_num_of_elements = 0;
        m_table_size = 0;
    }
};
}// namespace myStd