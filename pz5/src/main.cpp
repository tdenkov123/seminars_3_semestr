#include <iostream>
#include <string>
#include <vector>
#include <tuple>
using namespace std;


int main(int argc, char** argv) {
    string name;
    char comparator;
    int length, width, height;
    float weight;
    int n, command_count, command, attribute;
    cin >> n;
    vector<tuple<string, int, int, int, float>> data;
    for (size_t i = 0; i < n; i++) {
        string tmp2, tmp3, tmp4, tmp5;
        cin >> name >> tmp2 >> tmp3 >> tmp4 >> tmp5;
        length = stoi(tmp2), width = stoi(tmp3), height = stoi(tmp4), weight = stof(tmp5);
        // cout << name << ' ' << length << ' ' << width << ' ' << height << ' ' << weight << '\n';
        data.push_back(tuple<string, int, int, int, float> (name, length, width, height, weight));
    }
    
    vector<tuple<string, int, int, int, float>> curr = data;
    cin >> command_count;
    for (size_t i = 0; i < command_count; i++) {
        cin >> command;
        string tmp;
        switch (command) {
            case 1:
                cin >> attribute >> comparator >> tmp;
                if (attribute == 1) {
                    for (int i = 0; i < curr.size(); i++) {
                        if (tmp.compare(get<0>(curr[i])) < 0 && comparator == '>') curr.erase(curr.begin() + i);
                        else if (tmp.compare(get<0>(curr[i])) > 0 && comparator == '<') curr.erase(curr.begin() + i);
                        else if (tmp.compare(get<0>(curr[i])) != 0 && comparator == '=') curr.erase(curr.begin() + i);
                    }
                } else if (attribute == 5) {
                    float elem = stof(tmp);
                    for (int i = 0; i < curr.size(); i++) {
                        if (elem > get<4>(curr[i]) && comparator == '>') curr.erase(curr.begin() + i);
                        else if (elem < get<4>(curr[i]) && comparator == '<') curr.erase(curr.begin() + i);
                        if (elem != get<4>(curr[i]) && comparator == '=') curr.erase(curr.begin() + i);
                    }
                } else {
                    int elem = stoi(tmp);
                    int num;
                    for (int i = 0; i < curr.size(); i++) {
                        num = (attribute == 2) ? get<1>(curr[i]) : ((attribute == 3) ? get<2>(curr[i]) : get<3>(curr[i]));
                        if (elem > num && comparator == '>') curr.erase(curr.begin() + i);
                        else if (elem < num && comparator == '<') curr.erase(curr.begin() + i);
                        else if (elem != num && comparator == '=') curr.erase(curr.begin() + i);
                    }
                }
                break;
            case 2:
                if (!curr.size()) cout << "empty\n";
                else {
                    for (tuple tup: curr) {
                        cout << get<0>(tup) << ' ' << get<1>(tup) << ' ' << get<2>(tup);
                        cout << ' ' << get<3>(tup) << ' ' << get<4>(tup) << '\n';
                    }
                }
                break;
            case 3:
                curr = data;
                break;
            default:
                cout << "Wrong command, try again\n";
                break;
        }
    }
    return 0;
}
