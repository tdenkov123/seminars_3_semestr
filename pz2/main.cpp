#include <iostream>
#include <string>

using std::cout;
using std::cin;
using std::endl;
using std::exception;

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
            for (int i = 0; i < massiveSize; i++) {
                massive[i] = mas.getNum(i);
            }
        }

        // Деструктор
        ~dynamicMassive() {
            delete[] massive;
        }

        // Функция проверки на принадлежность к интервалу [-100;100]
        void intervalCheck(int num, int command) {
            if (abs(num) > 100) {
                if (command == 1) {
                    throw std::invalid_argument("std:invalid_argument:set");
                } else {
                    throw std::invalid_argument("std:invalid_argument:push_back");
                }
            }
        }
        // Функция проверки индекса
        void indexCheck(int index, int massiveSize, int command) {
            if (index < 0 || index >= massiveSize) {
                if (command == 1) {
                    throw std::out_of_range("std:out_of_range:get");
                } else {
                    throw std::out_of_range("std:out_of_range:set");
                }
            }
        }

        // Геттеры
        int16_t getNum(int index) {
            indexCheck(index, massiveSize, 1);
            return massive[index];
        }

        int getLen() {
            return massiveSize;
        }

        // Сеттер
        void setNum(int16_t num, int index) {
            indexCheck(index, massiveSize, 2);
            intervalCheck(num, 1);
            massive[index] = num;
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
            intervalCheck(newNum, 2);
            massiveSize++;
            massive = (int16_t*) realloc(massive, massiveSize*sizeof(int16_t));
            if (massive == nullptr) {
                throw std::bad_alloc();
            }
            massive[massiveSize-1] = newNum;
        }

        // Функция сложения массивов
        void add(dynamicMassive &mas) {
            for (int i = 0; i < mas.getLen();i++) {
                massive[i] += mas.getNum(i);
            }
        }

        // Функция вычитания массивов
        void substract(dynamicMassive mas) {
            for (int i = 0; i < mas.getLen();i++) {
                massive[i] -= mas.getNum(i);
            }
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

        try {
            switch (command) {
                case 1:
                    cin >> index;
                    if (arr_index == 1) {
                        cout << mas1.getNum(index) << endl;
                    }
                    else {
                        cout << mas2.getNum(index) << endl;
                    }
                    break;
                case 2:
                    cin >> index >> num;
                    if (arr_index == 1) {
                        mas1.setNum(num, index);
                        }
                    else {
                        mas2.setNum(num, index);
                    }
                    break;
                case 3:
                    cin >> num;
                    if (arr_index == 1) {
                        mas1.append(num);
                        }
                    else {
                        mas2.append(num);
                    }
                    break;
                case 4:
                    if (arr_index == 1) {
                        mas1.print();
                    }
                    else {
                        mas2.print();
                    }
                    break;
                case 5:
                    if (arr_index == 1) {
                        mas1.add(mas2);
                    }
                    else {
                        mas2.add(mas1);
                    }
                    break;
                case 6:
                    if (arr_index == 1) {
                        mas1.substract(mas2);
                    }
                    else {
                        mas2.substract(mas1);
                    }
                    break;
            }
        } catch (std::bad_alloc) {
            cout << "std:bad_alloc\n";
            exit(1);
        } catch (const std::exception &ex) {
            cout << ex.what() << endl;
        }
    }
    return 0;
}