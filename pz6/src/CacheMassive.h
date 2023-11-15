#pragma once

#include <iostream>

using namespace std;

template <typename T> class CacheMassive {
    private:
        struct Node {
            Node* next;
            T data;
            int id, accessCount;
            Node(T p_data, int p_id) {
                data = p_data;
                next = nullptr;
                id = p_id;
                accessCount = 0;
            } 
        } *head;
        int size;
    public:
        CacheMassive() : head(nullptr), size(0) {}
        CacheMassive(CacheMassive& p_mas) {
            head = p_mas.head;
            size = p_mas.size;
        }
        ~CacheMassive() {
            Node* curr = head;
            while (curr) {
                Node* next = curr->next;
                free(curr);
                curr = next;
            }
        }

        void raiseAccessCount(int p_id) {
            Node* tmp = head;
            if (p_id == tmp->id) {
                tmp->accessCount++;
            }
            while (tmp->next != nullptr) {
                tmp = tmp->next;
                if (p_id == tmp->id) {
                    tmp->accessCount++;
                }
            }
        }

        int getSize() const {return size;}

        Node* getElemPointer(int p_id) {
            Node* tmp = head;
            if (p_id == tmp->id) return tmp;
            while (tmp->next != nullptr) {
                tmp = tmp->next;
                if (p_id == tmp->id) return tmp;
            }
            return nullptr;
        }

        void push_back(T elem, int p_id) {
            Node* tmp = head;
            Node* newNode = new Node(elem, p_id);
            if (head) {
                for (int i = 0; i < size; i++) {
                    if (!tmp->next) break;
                    tmp = tmp->next;
                }
                tmp->next = newNode;
            } else head = newNode;
            size++;
        }

        void print() {
            Node* tmp = head;
            while (tmp) {
                cout << "{" << tmp->id << ' ' << tmp->accessCount << ' ' << tmp->data << "} ";
                tmp = tmp->next;
            }
            cout << '\n';
        }

        void sort() {
            Node* tmp = head;

        }

        string search(T elem) {
            Node* tmp = head;
            bool flag = false;
            for (int i = 0; i < size; i++) {
                if (tmp->data == elem) flag = true;
            }
            if (flag) return "YES\n";
            else return "NO\n";
        }

        void update(int p_id, T elem) {
            Node* tmp = getElemPointer(p_id);
            if (tmp == nullptr) throw invalid_argument("std::invalid_argument");

        }
};
