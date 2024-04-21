#pragma once

#include <deque>

namespace myStd{
template <typename T,typename Container = std::deque<T>>
class queue{
public:
    queue() = default;
    ~queue() = default;

    bool empty() { return m_data.empty(); }

    size_t size() { return m_data.size(); }

    void push(const T& value){
        m_data.push_back(value);
    }

    void pop(){
        if(!empty()){
            m_data.pop_front();
        }else{
            throw std::runtime_error("queue is empty");
        }
    }

    T& front(){
        if(!empty()){
            return m_data.front();
        }else{
            throw std::runtime_error("queue is empty");
        }
    }

    T& back(){
        if(!empty()){
            return m_data.back();
        }else{
            throw std::runtime_error("queue is empty");
        }
    }
private:
    Container m_data;
};
}// namespace myStd