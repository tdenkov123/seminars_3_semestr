#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>

using namespace std;

vector<long long> collisionCheck(string filename) {
    ifstream file;
    file.open("../files/" + filename);
    if (!file.is_open()) throw fstream::badbit;

    string tmp;
    vector<string> v;
    int collisions = 0;
    typedef chrono::high_resolution_clock Time;
    auto t0 = Time::now();
    while (getline(file, tmp)) v.push_back(tmp);
    // Мы умные? Да, делаем перебор
    for (int i = 0; i < 3600; i++) {
        for (int j = i + 1; j < 3600; j++) {
            if (v[i] == v[j]) {
                collisions++;
            }
        }
    }
    auto t1 = Time::now();
    chrono::duration<float> fs = t1 - t0;
    chrono::milliseconds durr = std::chrono::duration_cast<chrono::milliseconds>(fs);
    vector<long long> res {collisions, durr.count()};
    return res;
}