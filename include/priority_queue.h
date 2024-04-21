#pragma once

#include <vector>
#include <algorithm>

namespace myStd{
template <typename T,typename Container=std::vector<T>>
class priority_queue{
public:
    priority_queue() = default;

    priority_queue(const Container& container)
    :m_data(container)
    {
        std::make_heap(std::begin(m_data),std::end(m_data));
    }

    ~priority_queue() = default;

    bool empty() { return m_data.empty(); }

    size_t size() { return m_data.size(); }

    void push(const T& value){
        m_data.push_back(value);
        std::push_heap(std::begin(m_data),std::end(m_data));
    }

    void pop(){
        if(!empty()){
            std::pop_heap(std::begin(m_data),std::end(m_data));
            m_data.pop_back();
        }else{
            throw std::runtime_error("priority_queue is empty");
        }
    }

    T& top(){
        if(!empty()){
            return m_data.front();
        }else{
            throw std::runtime_error("priority_queue is empty");
        }
    }


private:
    Container m_data;
};
}//namespace myStd