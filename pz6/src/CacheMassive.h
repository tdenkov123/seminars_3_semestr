#pragma once

#include <iostream>

using namespace std;

template <typename T>
class CacheMassive {
    private:
        struct Node {
            Node* next;
            Node* prev;
            T data;
            int id, accessCount;
            Node(T p_data, Node* p_prev, Node* p_next, int p_id) {
                T data = p_data;
                Node* prev = p_prev;
                Node* next = p_next;
                int id = p_id;
                int accessCount = 0;
            }
        } *head;
        int last_id = 0;
    public:
        CacheMassive(T p_data) {
            head = new Node(p_data, nullptr, nullptr, last_id);
            last_id++;
        };
        CacheMassive(CacheMassive& p_mas) {
            head = p_mas.head;
        }
        ~CacheMassive() {
            Node* curr = head;
            while (curr) {
                Node* next = curr->next;
                free(curr);
                curr = next;
            }
        }

        void print() {
            if (head) {
                Node* tmp = head;
                do {
                cout << tmp->id << ' ' << tmp->accessCount << ' ' << tmp->data << '\n';
                tmp->accessCount++;
                } while (tmp->next);
            }
        }

        T getElem(int id) {
            Node* tmp = head;
            if (id >= last_id || id < 0) throw out_of_range("std::out_of_range::id");
            while (tmp->id != id) tmp = tmp->next;
            return tmp->id;
            call_sorting();
        }
        
        void push_back(T elem) {
            Node* tmp = head;
            while (tmp->next) {
                tmp = tmp->next;
            }
            tmp->next = new Node(elem, tmp, nullptr, last_id);
            last_id++;
        }

        /*
        void call_soorting() {
            Node* tmp = head;
            bool flag = true;
            while (flag) {
                while (tmp->next) {
                    
                }
            }
        }
        */
};
