#include <iostream>
#include <string>

using std::cout;
using std::cin;

class dynamicMassive {
    private:
        int massiveSize;
        int8_t* massive;

    public:
        // Конструктор
        dynamicMassive(int p_massiveSize) : massiveSize(p_massiveSize) {
            massive = new int8_t[massiveSize];
            for(int i = 0; i < massiveSize;i++) {
                cin >> massive[i];
            }
        }

        // Конструктор копирования
        dynamicMassive(dynamicMassive &mas) {
            massiveSize = mas.getLen();
            massive = new int8_t[massiveSize];
            for (int i = 0; i < massiveSize; i++) {massive[i] = mas.getNum(i);}
        }

        // Деструктор
        ~dynamicMassive() {
            delete[] massive;
        }

        // Функция проверки на принадлежность к интервалу [-100;100]
        bool intervalCheck(int num) {
            if (num <= 100 && num >= -100) {return true;}
            else {return false;}
        }

        // Геттеры
        int getNum(int index) {
            if (index >= 0 && index < massiveSize) {return massive[index];}
            else {
                cout << "Index out of range, returned -1\n";
                return -1;
            }
        }
        int getLen() {return massiveSize;}

        // Сеттер
        void setNum(int8_t num, int index) {
            if (index >= 0 && index < massiveSize && intervalCheck(num)) {massive[index] = num;}
        }

        // Функция вывода
        void print() {
            for (int i = 0; i < massiveSize; i++) {
                cout << massive[i] << " ";
            }
            cout << '\n';
        }

        // Функция добавления в конец массива
        void massive_add(int8_t newNum) {
            if (!intervalCheck(newNum)) {
                cout << "Number out of interval\n";
            }
            else {
                int8_t* tempMas {new int8_t[massiveSize]};
                for (int i = 0; i < massiveSize; i++) {tempMas[i] = massive[i];}
                massive = {new int8_t[massiveSize+1]};
                for (int i = 0; i < massiveSize; i++) {massive[i] = tempMas[i];}
                massive[massiveSize] = newNum;
                massiveSize++;
                delete[] tempMas;
            }
        }
};

// Функция сложения массивов
dynamicMassive add_massives(dynamicMassive mas1, dynamicMassive mas2) {
    int len1 = mas1.getLen(), len2 = mas2.getLen();
    if (len1 >= len2) {
        dynamicMassive newMas{mas1};
        for (int i = 0; i < len2; i++) {newMas.setNum(newMas.getNum(i) + mas2.getNum(i), i);}
        return newMas;
    }
    else if (len2 >= len1) {
        dynamicMassive newMas{mas2};
        for (int i = 0; i < len1; i++) {newMas.setNum(newMas.getNum(i) + mas1.getNum(i), i);}
        return newMas;
    }
}

int main() {
    int n1;
    cin >> n1;
    dynamicMassive cat{n1};

    int n2;
    cin >> n2;
    dynamicMassive dawg{n2};

    cat.print();
    dawg.print();

    return 0;
}