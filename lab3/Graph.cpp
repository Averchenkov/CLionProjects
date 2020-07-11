//
// Created by Aver on 20.04.2019.
//

#include <algorithm>
#include <iomanip>
#include "Graph.h"

void Graph::add(int a, int b) {
    int max = std::max(a, b);
    if (max > matrix.size()){
        for (vector<int> &temp : matrix) {
            for (int i = matrix.size(); i < max; ++i) {
                temp.push_back(0);
            }
        }
        for(int i = matrix.size(); i < max; ++i)
        {
            vector<int> temp;
            for(int j = 0; j < max; ++j)
                temp.push_back(0);
            matrix.push_back(temp);
        }
    }
    matrix[a - 1][b - 1] = 1;
}

Graph::Graph() {
}

Graph::~Graph() {

}

int Graph::getSize() const {
    return matrix.size();
}

void Graph::print() {
    cout << endl;

    for_each(matrix.begin(), matrix.end(), [](vector<int>& temp)
    {
        for_each(temp.begin(), temp.end(), [](int i)
        {
            cout << left << setw(3) << i;
        });
        cout << endl;
    });

    cout << endl;
}

bool Graph::haveLoops() {

    for (int i = 0; i < matrix.size(); ++i) {
        if (matrix[i][i] == 1){
            return true;
        }
    }
    return false;
}

vector<int> Graph::isolatedVertices() {
    vector<int> temp;
    for (int i = 0; i < matrix.size(); ++i) {
        if (!power(i)){
            temp.push_back(i + 1);
        }
    }
    return temp;
}

int Graph::power(int vertex) {
    int count = 0;
    for (int j = 0; j < matrix.size(); ++j) {
        if (matrix[vertex][j] == 1 || matrix[j][vertex] == 1){
            count++;
        }
    }
    if (matrix[vertex][vertex] == 1){
        count++;
    }
    return count;
}

vector<int> Graph::powerVertices() {
    vector<int> temp;
    for (int i = 0; i < matrix.size(); ++i) {
        temp.push_back(power(i));
    }
    return temp;
}

vector<Edge> Graph::edges() {
    vector<Edge> temp;
    for (int i = 0; i < matrix.size(); ++i) {
        for (int j = 0; j < matrix.size(); ++j) {
            if (matrix[i][j]){
                Edge edge;
                edge.first = i + 1;
                edge.second = j + 1;
                temp.push_back(edge);
            }
        }
    }
    return temp;
}


