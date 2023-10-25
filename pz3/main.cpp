#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>

int main(int argc, char* argv[]) {
    std::vector<int> mas;
    int num, len;
    double s, quad;
    while (true) {
        std::cin >> num;
        if (num != 0) {
            mas.push_back(num);
        } else {
            break;
        }
    }
    len = mas.size();
    for (auto& elem : mas) {
        s += elem;
    }
    s /= len;

    for (size_t i = 0; i < len; i++) {
        quad += pow(mas[i] - s, 2);
    }
    quad = sqrt(quad / (len - 1));
    if (quad < 1e-50) {
        quad = 0;
    }

    std::cout << std::setprecision(12) << quad;
    return 0;
}
