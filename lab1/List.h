//
// Created by Aver on 02.03.2019.
//

#ifndef LAB1_LIST_H
#define LAB1_LIST_H

#include <cmath>
#include "Node.h"
#include <iostream>
using namespace std;

template <typename T>
class List {

private:
    int Size;
    Node<T> *head;
public:
    List();
    ~List();
    void push_back(T data);
    int getSize() const;
    T& operator[](const int index);
    void pop_front();
    void clear();
    void push_front(T data);
    void insert(T value, int index);
    void removeAt(int index);
    void pop_back();
    Node<T> is(const int index);
    int have(T data);
    int countHave(T data);
    bool isSymmetric();
    bool isOdered();
    int numberUniqueValues();
    void deleteUniqueValues();
};

template<typename T>
void List<T>::push_back(T data) {
    if (head == nullptr){
        head = new Node<T>(data);
    }
    else{
        Node<T> *current = this->head;
        while (current->pNext != nullptr){
            current = current->pNext;
        }
        current->pNext = new Node<T>(data);
    }
    Size++;
}

template<typename T>
List<T>::List(){
    Size = 0;
    head = nullptr;
}

template<typename T>
List<T>::~List() {
    clear();
}

template<typename T>
int List<T>::getSize() const {
    return Size;
}

template<typename T>
T &List<T>::operator[](const int index) {
    Node<T> *current = this->head;
    int counter = 0;
    while(current!= nullptr){
        if(counter == index){
            return current->data;
        }
        current = current->pNext;
        counter++;
    }
}

template<typename T>
void List<T>::pop_front() {
    Node<T> *temp = this->head;
    head = head->pNext;
    delete temp;
    Size--;
}

template<typename T>
void List<T>::clear() {
    while(Size){
        pop_front();
    }
}

template<typename T>
void List<T>::push_front(T data) {
    head = new Node<T>(data, head);
    Size++;
}

template<typename T>
void List<T>::insert(T value, int index) {

    if(index == 0){
        push_front(value);
    }
    else {
        Node<T> *previous = this->head;
        for (int i = 0; i < index - 1; ++i) {
            previous = previous->pNext;
        }
        previous->pNext = new Node<T>(value, previous->pNext);
        Size++;
    }
}

template<typename T>
void List<T>::removeAt(int index) {
    if(index == 0){
        pop_front();
    }
    else{
        Node<T> *previous = this->head;
        for (int i = 0; i < index - 1; ++i) {
            previous = previous->pNext;
        }
        Node<T> *toDelete = previous->pNext;
        previous->pNext = toDelete->pNext;
        delete toDelete;
        Size--;
    }
}

template<typename T>
void List<T>::pop_back() {
    removeAt(Size - 1);
}

template<typename T>
int List<T>::countHave(T data) {
    Node<T> *current = this->head;
    int counter = 0;
    while(current != nullptr){
        if(current->data == data){
            counter++;
        }
        current = current->pNext;
    }
    return counter;
}

template<typename T>
int List<T>::have(T data) {
    Node<T> *current = this->head;
    int counter = 0;
    while((current != nullptr) && (current->data != data)){
        current = current->pNext;
        counter++;
    }
    if(current == nullptr){
        return 0;
    } else{
        return counter + 1;
    }
}

template<typename T>
Node<T> List<T>::is(const int index) {
    Node<T> *current = this->head;
    int counter = 0;
    while(current!= nullptr){
        if(counter == index){
            return *current;
        }
        current = current->pNext;
        counter++;
    }
}

template<typename T>
bool List<T>::isSymmetric() {
    Node<T> *right = this->head;
    for (int i = 0; i < ceil((float)Size/2); ++i) {
        right = right->pNext;
    }
    int n = Size/2 - 1;
    while (n && (right->pNext != nullptr) && (is(n).data == right->data)){
        n--;
        right = right->pNext;
    }
    if (n){
        return false;
    } else{
        return true;
    }
}

template<typename T>
bool List<T>::isOdered() {
    Node<T> *current = this->head;
    int counter = 0;
    while(current->pNext != nullptr){
        if(current->pNext->data >= current->data){
            current = current->pNext;
        }
        else{
            while ((current->pNext != nullptr) && (current->pNext->data < current->data)){
                current = current->pNext;
                counter++;
            }
        }
    }
    if (counter > 2){
        return false;
    } else{
        return true;
    }

}

template<typename T>
int List<T>::numberUniqueValues() {
    List<T> list;
    Node<T> *current = this->head;
    int counter = 0;
    while(current != nullptr){
        if(!list.have(current->data)){
            list.push_back(current->data);
        }
        current = current->pNext;
    }
    return list.getSize();
}

template<typename T>
void List<T>::deleteUniqueValues() {
    Node<T> *current = this->head;
    Node<T> *temporary;
    int counter = 0;
    while(current != nullptr){
        if(countHave(current->data) > 1){
            temporary = current->pNext;
            removeAt(counter);
            current = temporary;
            counter--;
        } else{
            current = current->pNext;
        }
        counter++;
    }
}

#endif //LAB1_LIST_H
