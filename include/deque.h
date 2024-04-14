#pragma once

#include "commonHead.h"


namespace myStd{
template <typename Elem>
class deque{
public:
    //ctor
    deque()
    :m_element_ptr(nullptr)
    ,m_capacity(0)
    ,m_front_index(0)
    ,m_back_index(0)
    ,m_size(0)
    {}
    //dctor
    ~deque(){
        clear();
        delete[] m_element_ptr;
    }

    // modifier
    void push_front(const Elem& value){
        // check wheather need to resize
        if(m_size == m_capacity){
            resize();
        }

        // insert elem into one position before front index
        m_front_index = (m_front_index - 1 + m_capacity) % m_capacity;
        m_element_ptr[m_front_index] = value;
        ++m_size;
    }

    void push_back(const Elem& value){
        if(m_size == m_capacity){
            resize();
        }
        //insert elem into back index
        m_element_ptr[m_back_index] = value;
        m_back_index = (m_back_index + 1) % m_capacity;
        ++m_size;
    }

    void pop_front(){
        if(m_size == 0){
            throw std::out_of_range("deque is already empty");
        }
        //we don't actually delete elements,just update index and size
        m_front_index = (m_front_index + 1) % m_capacity;
        --m_size;
    }


    void pop_back(){
        if(m_size == 0){
            throw std::out_of_range("deque is already empty");
        }
        //we don't actually delete elements,just update index and size
        m_back_index = (m_back_index - 1 + m_capacity ) % m_capacity;
        --m_size;
    }


    void clear(){
        while(m_size > 0){
            pop_front();
        }
    }
    
    // access
    Elem& operator[](size_t index){
        if(index < 0 || index >= m_size){
            throw std::out_of_range("index out of range");
        }
        return m_element_ptr[(m_front_index + index) % m_capacity];
    }

    size_t size() const{
        return m_size;
    }

    //debug
    void printElements() const {
        size_t index = m_front_index;
        for (size_t i = 0; i < m_size; ++i) {
            std::cout << m_element_ptr[index] << " ";
            index = (index + 1) % m_capacity;
        }
        std::cout << std::endl;
    }

private:
    Elem* m_element_ptr;
    size_t m_capacity;
    size_t m_front_index;
    size_t m_back_index;
    size_t m_size;

private:
    void resize(){
        size_t tempCapacity = (m_capacity == 0) ? 1 : m_capacity * 2;
        Elem* newElements = new Elem[tempCapacity];

        size_t index = m_front_index;
        // copy old elements to new array;
        for(size_t i = 0; i < m_size; ++i){
            newElements[i] = m_element_ptr[index];
            index = (index + 1) % m_capacity;
        }

        delete[] m_element_ptr;
        m_element_ptr = newElements;
        m_capacity = m_capacity;
        m_front_index = 0;
        m_back_index = m_size;
    }
};
}// namespace myStd