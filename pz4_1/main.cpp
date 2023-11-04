#include <iostream>
#include <map>
#include <string>
#include <sstream>

using namespace std;

int main(int argc, char** argv) {
    map<std::string, unsigned> cont;
    string s, str;
    getline(cin, s);
    stringstream ss(s);
    
    while (getline(ss, str, ' ')) {
        if (!cont.count(str)) {
            cont[str] = 0;
        }
        cont[str] += 1;
    }
    for (const auto& [k, c] : cont) {
        cout << k << " " << c << endl;
    }

    return 0;
}