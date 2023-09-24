#include <iostream>
#include <string>

using std::cout;
using std::cin;
using std::endl;

class dynamicMassive {
    private:
        int massiveSize;
        int16_t* massive;

    public:
        // Конструктор
        dynamicMassive(int p_massiveSize) : massiveSize(p_massiveSize) {
            massive = new int16_t[massiveSize];
            for(int i = 0; i < massiveSize;i++) {
                cin >> massive[i];
            }
        }

        // Конструктор копирования
        dynamicMassive(dynamicMassive &mas) {
            massiveSize = mas.getLen();
            massive = new int16_t[massiveSize];
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
        int16_t getNum(int index) {
            if (index >= 0 && index < massiveSize) {return massive[index];}
            else {
                cout << "Index out of range, returned -1\n";
                return -1;
            }
        }
        int getLen() {return massiveSize;}

        // Сеттер
        void setNum(int16_t num, int index) {
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
        void append(int16_t newNum) {
            if (!intervalCheck(newNum)) {
                cout << "Number out of interval\n";
            }
            else {
                int16_t* tempMas {new int16_t[massiveSize]};
                for (int i = 0; i < massiveSize; i++) {tempMas[i] = massive[i];}
                massive = {new int16_t[massiveSize+1]};
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
    dynamicMassive mas1{n1};

    int n2;
    cin >> n2;
    dynamicMassive mas2{n2};
    
    int comm_quantity;
    cin >> comm_quantity;

    for (int i = 0; i < comm_quantity; i++) {
        int command, arr_index, index;
        int16_t num;
        cin >> command >> arr_index;        

        switch (command) {
            case 1:
                cin >> index;
                if (arr_index == 1) {cout << mas1.getNum(index) << endl;}
                else {cout << mas2.getNum(index) << endl;}
                break;
            case 2:
                cin >> index >> num;
                if (arr_index == 1) {mas1.setNum(num, index);}
                else {mas2.setNum(num, index);}
                break;
            case 3:
                cin >> num;
                if (arr_index == 1) {mas1.append(num);}
                else {mas1.append(num);}
                break;
            case 4:
                if (arr_index == 1) {mas1.print();}
                else {mas1.print();}
                break;
            case 5:
                if (arr_index == 1) {mas1.add(mas2);}
                else {{mas2.add(mas1);}}
                break;
            case 6:
                if (arr_index == 1) {mas1.substract(mas2);}
                else {{mas2.substract(mas1);}}
                break;
        }
    }
    return 0;
}