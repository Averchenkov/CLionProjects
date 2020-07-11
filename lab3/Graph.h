//
// Created by Aver on 20.04.2019.
//

#ifndef LAB3_GRAPH_H
#define LAB3_GRAPH_H


#include <cmath>
#include <iostream>
#include <vector>

using namespace std;
typedef std::pair<int,int > Edge;

class Graph{

private:
    vector<vector<int>> matrix;

public:
    Graph();
    ~Graph();
    void add(int a, int b);
    void print();
    bool haveLoops();
    vector<int> isolatedVertices();
    vector<int> powerVertices();
    vector<Edge> edges();
    int power(int vertex);


    int getSize() const;
};


#endif //LAB3_GRAPH_H
