#pragma once

#include <iostream>
#include <stdexcept>
#include <utility>

template<class T>
class List {
private:
    T elements_[100];
    int index = 0;
public:
    List();
    virtual ~List();
    void add(T const& item, int pos);
    T get(int pos) const;
    void Sap_Xep(int i, int j);
};

// ==== Định nghĩa các hàm template ở đây ====

template <class T>
List<T>::List() 
{
    index = 0;
}

template <typename T>
List<T>::~List() {}

template<class T>
void List<T>::add(T const& item, int pos) 
{
    if (pos >= 100) {
        throw std::overflow_error("List full");
    }
    elements_[pos] = item;

    if (pos >= index) {
        index = pos + 1;  // tự cập nhật số lượng phần tử đang có
    }
}

template<class T>
T List<T>::get(int pos) const {
    if (pos < 0 || pos >= index) throw std::out_of_range("Invalid index");
    return elements_[pos];
}


//Đổi chỗ 2 thành viên

template<class T>
void List<T>::Sap_Xep(int i, int j) {
    if (i >= 0 && j >= 0 && i < index && j < index) {
        std::swap(elements_[i], elements_[j]);
    }
}

