#pragma once
#include "rbtree.h"

namespace myStd{
template <typename Key>
class set{
public:
    set()
    :m_rbtree()
    {}

    ~set() = default;
    
    void insert(const Key& key) { m_rbtree.insert(key,key); }

    void erase(const Key& key) { m_rbtree.remove(key); }

    size_t size()  { return m_rbtree.size(); }

    bool empty()  { return m_rbtree.empty(); }

    bool contains(const Key& key) { return m_rbtree.at(key) != nullptr; }
private:
    RBTree<Key,Key> m_rbtree;
};
}// namespace myStd