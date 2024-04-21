#pragma once
#include "rbtree.h"
#include <utility>

namespace myStd{
template <typename Key,typename Value>
class map{
public:
    map()
    :m_rbtree()
    {}

    void insert(const Key& key,const Value& value) { m_rbtree.insert(key,value); }

    void erase(const Key& key) { m_rbtree.remove(key); }

    size_t size() { return m_rbtree.size(); }

    bool empty() const { return m_rbtree.empty(); }

    bool contains(const Key& key) { return m_rbtree.at(key) != nullptr; }

    Value& at(const Key& key){
        auto *value_of_key_ptr = m_rbtree.at(key);
        if(value_of_key_ptr){
            return *value_of_key_ptr;
        }else{
            throw std::out_of_range("key not found");
        }
    }

    Value& operator[](const Key& key){
        auto* value_of_key_ptr = m_rbtree.at(key);
        if(value_of_key_ptr){
            return *value_of_key_ptr;
        }else{
            Value dood;
            m_rbtree.insert(key,dood);
            return *m_rbtree.at(key);
        }
    }

private:
    RBTree<Key,Value> m_rbtree;
};
}// namespace myStd