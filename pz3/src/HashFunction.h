#include <fstream>

using namespace std;

void hashFunction() {
    ifstream strings;
    strings.open("../files/strings.txt");
    if (!strings.is_open()) throw fstream::badbit;

    ofstream hashes;
    hashes.open("../files/hashes.txt");
    if (!hashes.is_open()) throw fstream::badbit;

    string tmp = "";
    while (getline(strings, tmp)) {
        unsigned long long sum1 = 0, sum2 = 0;
        string hash = "", sum = "";
        for (unsigned char ch : tmp) {
            sum1 = (sum1 + ch) * ch * 0x78425662623;
            sum2 = (sum2 + sum1) * ch * 0x92376516666;
        }
        sum = to_string(sum1) + to_string(sum2);
        sum = sum.substr(0, 32);
        hashes << sum << '\n';
    }
    strings.close();
    hashes.close();
}