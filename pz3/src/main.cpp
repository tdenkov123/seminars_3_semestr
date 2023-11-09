#include <iostream>
#include <fstream>

#include "Generator.h"
#include "HashFunction.h"
#include "CollisionCheck.h"

using namespace std;

int main(int argc, char* argv[]) {
    generate(3);
    cout << "Strings generated succesfully!\n";

    ifstream strings;
    strings.open("../files/strings.txt");
    if (!strings.is_open()) throw fstream::badbit;

    hashFunction();
    cout << "Hashes generated succesfully!\n";
    
    vector<long long> collisionsStrings = collisionCheck("strings.txt");
    vector<long long> collisionsHashes = collisionCheck("hashes.txt");
    cout << "Collisions for strings: " << collisionsStrings[0] << ", elapsed time: " << collisionsStrings[1] << '\n';
    cout << "Collisions for hashes: " << collisionsHashes[0] << ", elapsed time: " << collisionsHashes[1] << '\n';;

    return 0;
}