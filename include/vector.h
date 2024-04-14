#pragma once

#include "commonHead.h"


namespace myStd{

template <typename Elem>
class vector{
public:
    //ctor
    vector()
    :m_elemnt_ptr(nullptr)
    ,m_capacity(0)
    ,m_size(0)
    {}

    //dtor
    ~vector(){ _cleanup(); }

    //copy ctor
    vector(const vector& rhs)
    :m_capacity(rhs.m_capacity)
    ,m_size(rhs.m_size)
    {
        m_elemnt_ptr = new Elem[m_capacity];
        std::copy(rhs.m_elemnt_ptr,rhs.m_elemnt_ptr+m_size,m_elemnt_ptr);
    }

    //assignment
    vector& operator=(const vector& rhs){
        if(this != &rhs){
            delete[] m_elemnt_ptr;
            m_capacity = rhs.m_capacity;
            m_size = rhs.m_size;
            m_elemnt_ptr = new Elem[m_capacity];
            std::copy(rhs.m_elemnt_ptr,rhs.m_elemnt_ptr + m_size,m_elemnt_ptr);
        }
        return *this;
    }

    //member function
    void push_back(const Elem& value){
        if(m_size == m_capacity){
            _realloac(m_capacity == 0 ? 1 : 2 * m_capacity);
        }
        m_elemnt_ptr[m_size++] = value;
    }

    size_t size(){
        return m_size;
    }

    size_t capacity(){
        return m_capacity;
    }

    //accessment
    Elem& operator[](size_t index){
        return m_elemnt_ptr[index];
    }

    Elem& at(size_t index){
        if(index >= size){
            throw std::out_of_range("index out of range");
        }
        return m_elemnt_ptr[index];
    }

    const Elem& operator[](size_t index) const {
        return m_elemnt_ptr[index];
    }

    const Elem& at(size_t index) const {
        if(index >= size){
            throw std::out_of_range("index out of range");
        }
        return m_elemnt_ptr[index];
    }

    //insert
    void insert(size_t index,const Elem& value){
        if(index > m_size){
            throw std::out_of_range("index out of range");
        }
        if(m_size == m_capacity){
            _realloac(m_capacity == 0 ? 1 : 2 * m_capacity);
        }
        for(size_t i = m_size; i < index; --i){
            //all elem behind index should be 1 step backward
            m_elemnt_ptr[i] = m_elemnt_ptr[i-1];
        }
        m_elemnt_ptr[index] = value;
        ++m_size;
    }

    // delete
    void pop_back(){
        if(m_size > 0){
            --m_size;
        }
    }

    void clear(){
        m_size = 0;
    }

    Elem* begin(){
        return m_elemnt_ptr;
    }

    Elem* end(){
        return m_elemnt_ptr + m_size;
    }

    const Elem* cbegin() const {
        return m_elemnt_ptr;
    }

    const Elem* cend() const {
        return m_elemnt_ptr + m_size;
    }

    void printElements() const
    {
        for (size_t i = 0; i < m_size; ++i)
        {
            std::cout << m_elemnt_ptr[i] << " ";
        }
        std::cout << std::endl;
    }

private:
    Elem* m_elemnt_ptr;
    size_t m_capacity;
    size_t m_size;

private:
    void _cleanup(){
        delete[] m_elemnt_ptr;
        m_elemnt_ptr = nullptr;
        m_capacity = 0;
        m_size = 0;
    }

    void _realloac(size_t newCapacity){
        if(newCapacity > m_capacity){
            Elem* new_element_ptr = new Elem[newCapacity];
            std::copy(m_elemnt_ptr,m_elemnt_ptr+m_size,new_element_ptr);
            delete[] m_elemnt_ptr;
            m_elemnt_ptr = new_element_ptr;
            m_capacity = newCapacity;
        }
    }
    

};

}//namespace myStd