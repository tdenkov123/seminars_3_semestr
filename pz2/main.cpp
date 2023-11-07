#include <iostream>
#include <string>
#include <type_traits>
#include <cmath>

using namespace std;

//, enable_if_t<is_arithmetic_v<T>, int> = 0
template <typename T>
class dynamicMassive {
    private:
        int massiveSize;
        T* massive;
    public:
        // Конструктор
        dynamicMassive(int p_massiveSize) : massiveSize(p_massiveSize) {
            massive = new T[massiveSize];
            for(int i = 0; i < massiveSize;i++) {
                cin >> massive[i];
            }
        }

        // Конструктор копирования
        dynamicMassive(dynamicMassive &mas) {
            massiveSize = mas.getLen();
            massive = new T[massiveSize];
            for (int i = 0; i < massiveSize; i++) {
                massive[i] = mas.getElem(i);
            }
        }

        // Деструктор
        ~dynamicMassive() {
            delete[] massive;
        }

        // Оператор <<
        friend ostream& operator<< (ostream& os, dynamicMassive mas) {
            for (int i = 0; i < mas.getLen(); i++) os << mas.getElem(i) << " ";
            os << '\n';
            return os;
        }

        // Функция проверки на принадлежность к интервалу [-100;100]
        void intervalCheck(T elem, int command) {
            if constexpr (!is_integral_v<T>) {
                if (abs(elem) > 100) {
                    if (command == 1) {
                        throw std::invalid_argument("std::invalid_argument::set");
                    } else {
                        throw std::invalid_argument("std::invalid_argument::push_back");
                    }
                }
            }
        }
        // Функция проверки индекса
        void indexCheck(int index, int massiveSize, int command) {
            if (index < 0 || index >= massiveSize) {
                if (command == 1) {
                    throw std::out_of_range("std::out_of_range::get");
                } else {
                    throw std::out_of_range("std::out_of_range::set");
                }
            }
        }

        // Геттеры
        T getElem(int index) {
            indexCheck(index, massiveSize, 1);
            return massive[index];
        }

        int getLen() {
            return massiveSize;
        }

        bool arithmertic() {
            if (is_arithmetic_v<T>) return true;
            return false;
        }

        // Сеттер
        void setElem(T elem, int index) {
            indexCheck(index, massiveSize, 2);
            intervalCheck(elem, 1);
            massive[index] = elem;
        }

        // Функция вывода
        void print() {
            for (int i = 0; i < massiveSize; i++) {
                cout << massive[i] << " ";
            }
            cout << '\n';
        }

        // Функция добавления в конец массива
        void append(T newelem) {
            intervalCheck(newelem, 2);
            massiveSize++;
            massive = (T*) realloc(massive, massiveSize*sizeof(T));
            if (massive == nullptr) {
                throw std::bad_alloc();
            }
            massive[massiveSize-1] = newelem;
        }

        // Функция сложения массивов
        void add(dynamicMassive &mas) {
            for (int i = 0; i < mas.getLen();i++) {
                massive[i] += mas.getElem(i);
            }
        }

        // Функция вычитания массивов
        void substract(dynamicMassive mas) {
            for (int i = 0; i < mas.getLen();i++) {
                massive[i] -= mas.getElem(i);
            }
        }

        int distance(dynamicMassive &mas2) {
            if (massiveSize != mas2.getLen()) throw std::invalid_argument("std::invalid_argument");
            if (!(is_arithmetic_v<T> && mas2.arithmertic())) throw std::bad_typeid();
            int sum = 0;
            for (int i = 0; i < massiveSize; i++) sum += pow(mas2.getElem(i) - massive[i], 2);
            return sum;
        }
};


int main(int argc, char* argv[]) {
    int n1, n2, comm_quantity;
    cin >> n1;
    dynamicMassive<int> mas1{n1};
    cin >> n2;
    dynamicMassive<int> mas2{n2};
    int elem;
    cin >> comm_quantity;
    for (int i = 0; i < comm_quantity; i++) {
        int command, arr_index, index;
        cin >> command >> arr_index;
        try {
            switch (command) {
                case 1:
                    cin >> index;
                    if (arr_index == 1) {
                        cout << mas1.getElem(index) << endl;
                    } else {
                        cout << mas2.getElem(index) << endl;
                    }
                    break;
                case 2:
                    cin >> index >> elem;
                    if (arr_index == 1) {
                        mas1.setElem(elem, index);
                        } else {
                        mas2.setElem(elem, index);
                    }
                    break;
                case 3:
                    cin >> elem;
                    if (arr_index == 1) {
                        mas1.append(elem);
                        } else {
                        mas2.append(elem);
                    }
                    break;
                case 4:
                    if (arr_index == 1) {
                        cout << mas1;
                    } else {
                        cout << mas2;
                    }
                    break;
                case 5:
                    if (arr_index == 1) {
                        mas1.add(mas2);
                    } else {
                        mas2.add(mas1);
                    }
                    break;
                case 6:
                    if (arr_index == 1) {
                        mas1.substract(mas2);
                    } else {
                        mas2.substract(mas1);
                    }
                    break;
                case 7:
                    cout << "Distance between massives is: " << mas1.distance(mas2) << '\n'; 
            }
        } catch (std::bad_alloc) {
            cout << "std::bad_alloc\n";
            exit(1);
        } catch (const std::exception &ex) {
            cout << ex.what() << endl;
        }
    }
    return 0;
}