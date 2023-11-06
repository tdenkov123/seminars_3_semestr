#include <iostream>
#include <fstream>

#include "Generator.h"
#include "HashFunction.h"
#include "CollisionCheck.h"

using namespace std;

int main(int argc, char* argv[]) {
    generate();
    cout << "Strings generated succesfully!\n";

    ifstream strings;
    strings.open("../files/strings.txt");
    if (!strings.is_open()) throw fstream::badbit;

    hashFunction();
    cout << "Hashes generated succesfully!\n";
    
    cout << "Collisions for strings: " << collisionCheck("strings.txt") << '\n';
    cout << "Collisions for hashes: " << collisionCheck("hashes.txt") << '\n';

    return 0;
}