//
// Created by Aver on 11.04.2019.
//

#ifndef LAB2_NODE_H
#define LAB2_NODE_H

template <typename T>
class Node{
public:
    Node *pLeft;
    Node *pRight;
    Node *pParent;
    T data;
    int level;
    Node(T data = T(), int level = 1, Node *pLeft = nullptr, Node *pRight = nullptr, Node *pParent = nullptr){
        this->data = data;
        this->pLeft = pLeft;
        this->pRight = pRight;
        this->pParent = pParent;
        this->level = level;
    }
};

#endif //LAB2_NODE_H
