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
        int8_t getNum(int index) {
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
        void append(int8_t newNum) {
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

        // Функция сложения массивов
        void add(dynamicMassive &mas) {
            for (int i = 0; i < mas.getLen();i++) {massive[i] += mas.getNum(i);}
        }

        // Функция вычитания массивов
        void substract(dynamicMassive mas) {
            for (int i = 0; i < mas.getLen();i++) {massive[i] -= mas.getNum(i);}
        }
};


int main() {
    int n1;
    cin >> n1;
    dynamicMassive cat{n1};

    int n2;
    cin >> n2;
    dynamicMassive dawg{n2};

    cat.add(dawg);
    cat.print();

    return 0;
}