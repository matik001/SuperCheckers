/// Konieczna byla zamiana .cpp na plik .h bo linker nie radzi sobie z template, gdy jest rozbity na .cpp i .h
/// https://bytefreaks.net/programming-2/c/c-undefined-reference-to-templated-class-function

#include "DynamicArray.h"
#include <iostream>
template <typename T>
void DynamicArray<T>::copy(T *to) const{
    for (int i = 0; i < amountOfElements; i++) {
        to[i] = t[i];
    }
}

template <typename T>
void DynamicArray<T>::resize(int size) {
    if(size < amountOfElements){
        std::cout << "Can't resize, more elements than desired size";
        exit(1);
    }

    length = size;
    T *newT = new T[length];
    copy(newT);
    delete[] t;
    t = newT;
}

template <typename T>
void DynamicArray<T>::increaseLength() {
    resize(length*2);
}

template <typename T>
DynamicArray<T>::DynamicArray() {
    length = 1;
    amountOfElements = 0;
    t = new T[length];
}
template<typename T>
void DynamicArray<T>::operator=(const DynamicArray<T> &arr) {
    if(t != nullptr){
        delete[] t;
        t = nullptr;
    }
    length = arr.length;
    amountOfElements = arr.amountOfElements;
    t = new T[length];
    arr.copy(t);
}
template<typename T>
DynamicArray<T>::DynamicArray(const DynamicArray<T>& toCopy) {
    *this = toCopy;
}




template <typename T>
void DynamicArray<T>::push(T elem) {
    amountOfElements++;
    if (amountOfElements > length)
        increaseLength();
    t[amountOfElements - 1] = elem;
}

template <typename T>
T &DynamicArray<T>::operator[](int idx) const {
    return t[idx];
}

// nie mozna tu zwalniac pamieci, bo by sie zrobila zlozonosc kwadratowa
// gydby na zmiane dodawac i odejmowac na granicy
template <typename T>
T DynamicArray<T>::pop() {
    amountOfElements--;
    return t[amountOfElements];
}

template <typename T>
DynamicArray<T>::~DynamicArray() {
    if(t!= nullptr){
        delete[] t;
        t = nullptr;
    }
}

template<typename T>
int DynamicArray<T>::size() const{
    return amountOfElements;
}

template<typename T>
T *DynamicArray<T>::begin() const{
    return t;
}

template<typename T>
T *DynamicArray<T>::end() const{
    return t+amountOfElements;
}

template<typename T>
void DynamicArray<T>::clear() {
    amountOfElements = 0;
    length = 1;
    delete[] t;
    t = new T[length];
}

template<typename T>
DynamicArray<T> DynamicArray<T>::clone() const{
    DynamicArray<T> res =  DynamicArray<T>();
    res.resize(length);
    copy(res.t);
    res.amountOfElements = amountOfElements;
    return res;
}

template<typename T>
void DynamicArray<T>::push_many(const DynamicArray<T> &arr) {
    int new_amount_of_elements = amountOfElements + arr.amountOfElements;
    if(size() < new_amount_of_elements){
        resize(new_amount_of_elements*2);
    }
    for(int i = 0; i<arr.size(); i++){
        push(arr[i]);
    }
}




