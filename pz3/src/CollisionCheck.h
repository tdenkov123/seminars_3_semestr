#include <iostream>
#include <fstream>
#include <string>
#include <vector>


using namespace std;

int collisionCheck(string filename) {
    ifstream file;
    file.open("../files/" + filename);
    if (!file.is_open()) throw fstream::badbit;

    string tmp;
    vector<string> v;
    int collisions = 0;
    while (getline(file, tmp)) v.push_back(tmp);
    // Мы умные? Да, делаем перебор
    for (int i = 0; i < 3600; i++) {
        for (int j = i + 1; j < 3600; j++) {
            if (v[i] == v[j]) {
                collisions++;
                // cout << i << ' ' << j << '\n';
            }
        }
    }
    return collisions;
}