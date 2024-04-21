#pragma once

#include "commonHead.h"
#include <deque>

namespace myStd{
template <typename T,typename Container = std::deque<T>>
class stack{
public:
    stack() = default;
    ~stack() = default;

    bool empty() { return m_data.empty(); }

    size_t size() const { return m_data.size(); }

    void push(const T& value){
        m_data.push_back(value);
    }

    void pop(){
        if(!empty()){
            m_data.pop_back();
        }else{
            throw std::runtime_error("stack is empty");
        }
    }

    T& top(){
        if(!empty()){
            return m_data.back();
        }else{
            throw std::runtime_error("stack is empty");
        }
    }

private:
    Container m_data;
};
}//namespace myStd