#include <iostream>

using std::cout;
using std::cin;

class dynamicMassive {
    private:
        int massiveSize;
        int* massive;

    public:
        // Конструктор
        dynamicMassive(int p_massiveSize) : massiveSize(p_massiveSize) {
            massive = new int[massiveSize];
        }

        // Конструктор копирования
        dynamicMassive(dynamicMassive &mas) {
            massiveSize = mas.getLen();
            massive = new int[massiveSize];
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
        void setNum(int num, int index) {
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
        void massive_add(int newNum) {
            if (!intervalCheck(newNum)) {
                cout << "Number out of interval\n";
            }
            else {
                int* tempMas {new int[massiveSize]};
                for (int i = 0; i < massiveSize; i++) {tempMas[i] = massive[i];}
                massive = {new int[massiveSize+1]};
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
    dynamicMassive cat{5};
    dynamicMassive dog{10};

    cat.setNum(49, 0);
    cat.setNum(23, 1);
    cat.setNum(11, 2);
    cat.setNum(12, 3);
    cat.setNum(19, 4);

    dog.setNum(49, 0);
    dog.setNum(23, 1);
    dog.setNum(11, 2);
    dog.setNum(12, 3);
    dog.setNum(19, 4);
    dog.setNum(5, 5);
    dog.setNum(1, 6);
    dog.setNum(95, 7);
    dog.setNum(59, 8);
    dog.setNum(34, 9);

    add_massives(cat, dog).print();

    dog.print();
    cat.print();

    return 0;
}