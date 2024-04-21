#pragma once
#include "rbtree.h"

namespace myStd{
template <typename Key,typename Value>
class multimap{
public:
    using ValueType = std::list<Value>;

    multimap()
    :m_rbtree()
    ,m_size(0)
    {}

    void insert(const Key& key,const Value& value){
        auto* value_of_key_ptr = m_rbtree.at(key);
        if(value_of_key_ptr != nullptr){
            value_of_key_ptr->push_back(value);
        }else{
            ValueType values;
            values.push_back(value);
            m_rbtree.insert(key,values);;
        }
        m_size++;
    }

    void remove(const Key& key){
        auto* value_of_key_ptr = m_rbtree.at(key);
        if(value_of_key_ptr != nullptr){
            m_size -= value_of_key_ptr->size();
            m_rbtree.remove(key);
        }
    }

    void remove(const Key& key,const Value& value){
        auto* value_of_key_ptr = m_rbtree.at(key);
        if(value_of_key_ptr != nullptr){
            value_of_key_ptr->remove(value);
            m_size--;
            if(value_of_key_ptr->empty()){
                m_rbtree.remove(key);
            }
        }
    }

    ValueType* at(const Key& key){
        return m_rbtree.at(key);
    }

    size_t size() { return m_size; }

    bool empty() { return m_size == 0; }

private:
    RBTree<Key,ValueType> m_rbtree;
    size_t m_size;
};
}//namespace myStd