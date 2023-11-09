#include <fstream>
#include <string>
#include <vector>
#include <random>
#include <ctime>

using namespace std;

void generate(int str_len) {
    string chars;
    for (int i = 65; i < 91; i++) chars += char(i);
    for (int i = 48; i < 58; i++) chars += char(i);
    
    ofstream file;
    file.open("../files/strings.txt");
    if (!file.is_open()) throw std::ofstream::badbit;
    
    // Заполняем вектор 100 первичных строк
    vector<string> str_vector;
    for (int i = 0; i < 100; i++) {
        string tmp = "";
        srand(i * 295689 + int(time(NULL)));
        for (int j = 0; j < str_len; j++) tmp += chars[rand() % 36];
        str_vector.push_back(tmp);
    }
    // Пишем в файл вариации каждой строки
    for (int i = 0; i < 100; i++) {
        srand(i * 16336 + int(time(NULL)));
        string tmp = str_vector[i];
        int rand_index = rand() % tmp.length();
        for (int j = 0; j < 36; j++) {
            tmp[rand_index] = chars[j];
            file << tmp << '\n';
        }
    }
    file.close();
}