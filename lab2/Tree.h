//
// Created by Aver on 11.04.2019.
//

#ifndef LAB2_TREE_H
#define LAB2_TREE_H



#include <cmath>
#include "Node.h"
#include <iostream>
using namespace std;

template <typename T>
class Tree {

private:
    int maxList;
    Node<T> *head;
public:
    Tree(int count);
    Tree();
    ~Tree();

    void push_back(T data);
    int getSize() const;
    void clear();
    void print();
    void print(Node<T> *current);
    Node<T> * search(int data);

    void is(int a, int b);

    int getMaxList() const;
    int toLevel(int level);
    int getLevel(int a);


};




template<typename T>
void Tree<T>::push_back(T data) {
    if (head == nullptr){
        head = new Node<T>(data);
    }
    else{
        Node<T> *current = this->head;
        while ((current->pLeft != nullptr && data >= current->data) || (current->pRight != nullptr && data < current->data)){
            if (data >= current->data)
                current = current->pLeft;
            else
                current = current->pRight;
        }
        if (data >= current->data)
            current->pLeft = new Node<T>(data, current->level + 1, nullptr, nullptr, current);
        else
            current->pRight = new Node<T>(data, current->level + 1, nullptr, nullptr, current);
        if(current->level + 1 > maxList)
            maxList = current->level + 1;
    }
}


template<typename T>
Tree<T>::Tree(int count){
    head = nullptr;
    maxList = 0;
    bool temp[count];
    for (int i = 0; i < count; ++i) {
        temp[i] = false;
    }

    int k = 0;
    int number;
    srand(time(NULL));

    while (k < count){
        number = rand() % count;
        if (!temp[number]){
            temp[number] = true;
            push_back(number);
            k++;
        }
    }
}

template<typename T>
Tree<T>::~Tree() {
    clear();
}

template<typename T>
int Tree<T>::getMaxList() const {
    return maxList;
}

template<typename T>
void Tree<T>::clear() {
}

template<typename T>
void Tree<T>::print(Node<T> *current) {
    if (current == nullptr)
        return;
    else
    {
        print(current->pLeft);
        for (int i = 0; i < toLevel(current->level) - maxList; ++i)
            cout << " ";
        cout << current->data << endl;
    }
    print(current->pRight);
}

template<typename T>
void Tree<T>::print() {
    Node<T> *current = this->head;
    print(current);
}

template<typename T>
Tree<T>::Tree() {
    head = nullptr;
    maxList = 0;
}

template<typename T>
Node<T> * Tree<T>::search(int data) {
    Node<T> *current = this->head;
    while ((current->pLeft != nullptr && data > current->data) || (current->pRight != nullptr && data < current->data) || current->data == data){
        if (data == current->data)
            return current;
        else if (data > current->data)
            current = current->pLeft;
        else
            current = current->pRight;
    }
    cout << endl << "No" << endl;
    return nullptr;
}

template<typename T>
void Tree<T>::is(int a, int b) {
    Node<T> *currentA = search(a);
    Node<T> *currentB = search(b);

    if((currentB->pParent == currentA)){
        cout << endl << "A(" << a << ") predok B(" << b << ")"<< endl;
    }
    else if(currentA->pParent == currentB){
        cout << endl << "B(" << b << ") predok A(" << a << ")"<< endl;
    }
    else if(currentA->pParent == currentB->pParent){
        cout << endl << "C(" << currentA->pParent->data << ") predok A(" << a << ") and B(" << b << ")"<< endl;
    }
    else cout << "No";
}

template<typename T>
int Tree<T>::toLevel(int level) {
    int count = 0;
    for (int i = 0; i < level; ++i) {
        count += maxList - i;
    }
    return count;
}

template<typename T>
int Tree<T>::getLevel(int a) {
    return toLevel(search(a)->level) - maxList;
}


#endif //LAB2_TREE_H
