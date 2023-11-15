#include <iostream>

#include "CacheMassive.h"

using namespace std;

int main(int argc, char** argv) {
    CacheMassive<int> m;
    m.push_back(10, 1);
    m.push_back(20, 2);
    m.push_back(5, 3);
    m.push_back(100, 4);

    if (m.getSize()) cout << m.getSize();
    else cout << ';';
 
    cout << m.getElem(4) << '\n';
    m.print();

    return 0;
}