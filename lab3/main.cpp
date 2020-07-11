#include <iostream>
#include <iomanip>
#include "Graph.h"
typedef std::pair<int,int > Edge;

int main() {
    Graph graph;
    int n;
    cout << "Enter the4 number of edges: ";
    cin >> n;
    cout << "Enter pairs of vertices that connect edges:" << endl;
    for (int j = 0; j < n; ++j) {
        int a,b;
        cin >> a >> b;
        graph.add(a,b);
    }
    graph.print();
    bool f = graph.haveLoops();
    if (f){
        cout << "Yes, there are loops in the graph." << endl;
    }
    else
    {
        cout << "No, there are no loops in the graph." << endl;
    }
    vector<int> isolatedVertices = graph.isolatedVertices();
    if (isolatedVertices.size() > 0){
        cout << endl;
        cout << "Isolated vertices: ";
        for(int temp : isolatedVertices){
            cout  << temp << " ";
        }
        cout << endl;
    } else{
        cout << "There are no isolated vertices in the graph" << endl;
    }
    int i = 0;
    vector<int> powerVertices = graph.powerVertices();
    for (int temp : powerVertices) {
        i++;
        cout << endl << "Vertice "<< i << " - " << temp << " degree";
    }
    cout << endl;
    cout << endl;
    cout << "Edge list:" << endl;
    vector <Edge> edges = graph.edges();
    for (Edge edge : edges) {
        cout << edge.first << " - " << edge.second << endl;
    }
    return 0;
}