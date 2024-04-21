#pragma once

#include "rbtree.h"


namespace myStd{
template <typename Key>
class multiset{
public:
    multiset()
    :m_size(0)
    {}

    ~multiset(){
        
    };

    void insert(const Key& key){
        const auto size_of_key_ptr = m_rbtree.at(key);
        //if key already exist
        if(size_of_key_ptr != nullptr){
            (*size_of_key_ptr)++;
            m_size++;
            return;
        }
        m_rbtree.insert(key,1);
        m_size++;
    }

    void erase(const Key& key){
        const auto size_of_key_ptr = m_rbtree.at(key);
        //if key doesn't exist
        if(size_of_key_ptr == nullptr){
            return;
        }
        (*size_of_key_ptr)--;
        m_size--;
        if(*size_of_key_ptr == 0){
            m_rbtree.remove(key);
        }
    }

    size_t size() const { return m_size; }

    bool empty() const { return m_size == 0; }

    size_t count(const Key& key){
        const auto size_of_key_ptr = m_rbtree.at(key);
        if(size_of_key_ptr != nullptr){
            return *size_of_key_ptr;
        }
        return 0;
    }

    void clear(){
        m_size = 0;
        m_rbtree.clear();
    }


private:
    RBTree<Key,size_t> m_rbtree;
    size_t m_size;
};
}//namespace myStd