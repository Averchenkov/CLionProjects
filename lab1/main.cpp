#include <iostream>
#include "List.h"
#include <cmath>
#include <fstream>

using namespace std;

int main() {
    List<int > list;
    string name = "C:\\Users\\Aver\\Documents\\GitHub\\CLionProjects\\lab1\\text.txt";
    std::ifstream from_file;
    from_file.open(name);
    int s;
    if(from_file.is_open()){
        for(from_file >> s; !from_file.eof(); from_file >> s)
            list.push_back(s);
    }
    list.push_back(s);

    if (list.isSymmetric()){
        cout << "List is simmetric" << endl;
    }
    else{
        cout << "List is not simmetric" << endl;
    }

    if (list.isOdered()){
        cout << "If you delete two items, the list will be ordered" << endl;
    }
    else {
        cout << "If you delete two items, the list will is not ordered" << endl;
    }
    if (list.numberUniqueValues() == 1){
        cout << "In the list of one unique item" << endl;
    }
    else if (list.numberUniqueValues() > 1){
        cout << "In the list of " << list.numberUniqueValues() << " unique items" << endl;
    }

    list.deleteUniqueValues();

    for (int i = 0; i < list.getSize(); ++i) {
        cout << list[i] << " ";
    }
}