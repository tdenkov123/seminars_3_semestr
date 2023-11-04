#include <iostream>
#include <sstream>
#include <vector>
#include <stack>
#include <cstring>

using namespace std;

int main(int argc, char** argv) {
    int n;
    cin >> n;
    int massive[n][n] {};
    string str, tmp;
    getline(cin, str);
    for (int i = 0; i < n; i++) {
        getline(cin, str);

        stringstream ss(str);
        while (getline(ss, tmp, ' ')) {
            int ind = stoi(tmp) - 1;
            if (ind >= 0) {
                massive[i][ind] = 1;
            }
        }
    }

    stack<int> s;
    for (int i = 0; i < n; i++) massive[i][i] = 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (massive[i][j] == 1 && i != j) {s.push(j);}
        }
        while (s.size() != 0) {
            int x = s.top();
            s.pop();
            for (int j = 0; j < n; j++) {
                if (massive[x][j] == 1 && massive[i][j] == 0) {
                    massive[i][j] = 1;
                    s.push(j);
                }
            }
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << massive[i][j] << ' ';
        }
        cout << '\n';
    }
    

    return 0;
}