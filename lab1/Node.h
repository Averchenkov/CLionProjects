//
// Created by Aver on 02.03.2019.
//

#ifndef LAB1_NODE_H
#define LAB1_NODE_H


template <typename T>
class Node{
public:
    Node *pNext;
    T data;
    Node(T data = T(), Node *pNext = nullptr){
        this->data = data;
        this-> pNext = pNext;
    }
};


#endif //LAB1_NODE_H
