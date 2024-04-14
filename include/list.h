#pragma once

#include "commonHead.h"

namespace myStd{
template <typename Elem>
class list
{
    struct Node;
public:
    list()
    :m_head_ptr(nullptr)
    ,m_tail_ptr(nullptr)
    ,m_size(0)
    {}

    ~list(){ _cleanup(); }

    // modifier 
    // this kind of function,there're only two situation need to be considered
    // 1.the original situation:if list is not empty,only need to modify head/tail
    // 2.the boundery situation:if list is empty,head&tail both should be modified;
    void push_back(const Elem& value){
        // new Node's pre should be tail,next should be null
        Node* newNode = new Node(value,nullptr,m_tail_ptr);
        if(m_tail_ptr){
            // if list is not empty,tail's next should be the new Node;
            m_tail_ptr->m_next_ptr = newNode;
        }else{
            // if list is empty,the new Node should be the head Node;
            m_head_ptr = newNode;
        }
        // update tailptr and size
        m_tail_ptr = newNode;
        ++m_size;
    }

    void push_front(const Elem& value){
        // new Node's next should be head,pre should be null
        Node* newNode = new Node(value,m_head_ptr,nullptr);
        if(m_head_ptr){
            // if list not empty,newNode should insert at head's prev
            m_head_ptr->m_prev_ptr = newNode;
        }else{
            // if list is empty,tail should be head Node
            m_tail_ptr = newNode;
        }
        // update head and size
        m_head_ptr = newNode;
        ++m_size;
    }

    void pop_back(){
        if(m_size > 0){
            Node* newTail = m_tail_ptr->m_prev_ptr;
            delete m_tail_ptr;
            m_tail_ptr = newTail;
            if(m_tail_ptr){
                // if list not empty after delete
                m_tail_ptr->m_next_ptr = nullptr;
            }else{
                // if list is empty after delete,head should be null as well
                m_head_ptr = nullptr;
            }

            --m_size;
        }
    }

    void pop_front(){
        if(m_size > 0){
            Node* newHead = m_head_ptr->m_next_ptr;
            delete m_head_ptr;
            m_head_ptr = newHead;
            if(m_head_ptr){
                m_head_ptr->m_prev_ptr = nullptr;
            }else{
                m_tail_ptr = nullptr;
            }
            --m_size;
        }
    }

    void remove(const Elem& value){
        Node* dood = m_head_ptr;
        while(dood != nullptr && dood->m_data != value){
            dood = dood->m_next_ptr;
        }
        if(dood == nullptr){
            // not found
            return;
        }
        if(dood != m_head_ptr && dood != m_tail_ptr){
            // original situation
            dood->m_prev_ptr->m_next_ptr = dood->m_next_ptr;
            dood->m_next_ptr->m_prev_ptr = dood->m_prev_ptr;
        }else if(dood == m_head_ptr && dood == m_tail_ptr){
            m_head_ptr = nullptr;
            dood = nullptr;
        }else if(dood == m_head_ptr){
            m_head_ptr = dood->m_next_ptr;
            m_head_ptr->m_prev_ptr = nullptr;
        }else{
            m_tail_ptr = dood->m_prev_ptr;
            m_tail_ptr->m_next_ptr = nullptr;
        }

        delete dood;
        dood = nullptr;
        --m_size;
    }

    void clear(){
        while(m_head_ptr){
            Node* dood = m_head_ptr;
            m_head_ptr = m_head_ptr->m_next_ptr;
            delete dood;
        }
        m_tail_ptr = nullptr;
        m_size = 0;
    }

    //accessor
    size_t size() const { return m_size; }

    bool empty() const { return m_size == 0; }

    Node* begin() { return m_head_ptr; }

    Node* end() { return m_tail_ptr; }

    const Node* cbegin() const { return m_head_ptr; }

    const Node* cend() const { return m_tail_ptr; }

    Elem& operator[](size_t index){
        if(index >= m_size){
            throw std::out_of_range("index out of range");
        }

        Node* slave = m_head_ptr;
        while(index--){
            slave = slave->m_next_ptr;
        }

        return slave->m_data;
    }

    const Elem& operator[](size_t index) const {
        if(index >= m_size){
            throw std::out_of_range("index out of range");
        }
        size_t dood = index;
        Node* slave = m_head_ptr;
        while(dood--){
            slave = slave->m_next_ptr;
        }

        return slave->m_data;
    }

    Node* getNode(const Elem& value){
        Node* slave = m_head_ptr;
        while(slave != nullptr && slave->m_data != value){
            slave = slave->m_next_ptr;
        }

        return slave;
    }

    Elem* find(const Elem& value){
        Node* slave = getNode(value);
        if(slave == nullptr){
            return nullptr;
        }
        return &slave->m_data;
    }


    // used to debug
    template <typename T>
    friend std::ostream &operator<<(std::ostream&os,const list<T>&rhs);
    void printElements() const
    {
        for (Node *current = m_head_ptr; current; current = current->m_next_ptr)
        {
            std::cout << current->m_data << " ";
        }
        std::cout << std::endl;
    }
private:
    void _cleanup()
    {
        while(m_head_ptr){
            Node* dood = m_head_ptr;
            m_head_ptr = m_head_ptr->m_next_ptr;
            delete dood;
        }
        m_tail_ptr = nullptr;
        m_size = 0;
    }

    struct Node{
        Elem m_data;
        Node *m_next_ptr;
        Node *m_prev_ptr;

        Node(const Elem& value,Node *nextNode = nullptr,Node* preNode = nullptr)
        :m_data(value)
        ,m_next_ptr(nextNode)
        ,m_prev_ptr(preNode)
        {}
    };

    Node* m_head_ptr;
    Node* m_tail_ptr;
    size_t m_size;
};

template <typename T>
std::ostream& operator<<(std::ostream& os,const list<T>& rhs){
    for(typename list<T>::Node* current = rhs.m_head_ptr;current;current = current->m_next_ptr){
        os << " " << current->m_data;
    }
    os << std::endl;
    return os;
}

} // namespace myStd