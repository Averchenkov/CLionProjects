#include <iostream>
#include <ctime>
#include "Tree.h"

int main() {
    Tree<int> *tree = new Tree<int>(19);
    cout << endl;
    tree->print();
    int a, b;
    while (cin >> a && cin >> b){
        tree->is(a, b);
    }
    return 0;
}