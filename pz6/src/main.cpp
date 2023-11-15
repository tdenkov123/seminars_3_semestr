#include <iostream>
#include "CacheMassive.h"

int main(int argc, char** argv) {
    CacheMassive<int> m;
    int n, command, command_count, id, elem;
    std::cin >> n;
    for (int i = 0; i < n; i++) {
        std::cin >> id >> elem;
        m.push_back(elem, id);
    }
    
    std::cin >> command_count;
    for (int i = 0; i < command_count; i++) {
        std::cin >> command;
        switch (command) {
        case 1:
            std::cin >> id >> elem;
            m.update(id, elem);
            break;
        case 2:
            std::cin >> id;
            m.raiseAccessCount(id);
            break;
        case 3:
            std::cin >> elem;
            m.search(elem);
            break;
        case 4:
            m.print();
            break;
        default:
            std::cout << "Enter other command from 1 to 4.\n";
        }
    }

    return 0;
}