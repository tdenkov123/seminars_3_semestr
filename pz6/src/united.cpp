#include <iostream>
#include <string>

template <typename T> class CacheMassive {
private:
    struct Node {
        Node* next;
        Node* prev;
        T data;
        int id, accessCount;
        Node(T p_data, int p_id) {
            data = p_data;
            next = nullptr;
            prev = nullptr;
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
        push_by_access_count(p_id);
    }

    int getSize() const { return size; }

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
            newNode->prev = tmp;
        }
        else head = newNode;
        size++;
    }

    void print() {
        Node* tmp = head;
        while (tmp) {
            std::cout << "{" << tmp->id << ' ' << tmp->accessCount << ' ' << tmp->data << "} ";
            tmp = tmp->next;
        }
        std::cout << '\n';
    }

    void push_by_access_count(int p_id) {
        while (head->prev != nullptr) head = head->prev;
        Node* node = head;
        while (p_id != node->id) node = node->next;
        while (node->prev != nullptr && node->accessCount >= node->prev->accessCount) {
            Node* prev_node = node->prev;
            if (prev_node->prev) prev_node->prev->next = node;
            if (node->next) node->next->prev = prev_node;
            
            Node* n_next = node->next;
            Node* p_prev = prev_node->prev;

            prev_node->prev = node;
            prev_node->next = n_next;
            node->prev = p_prev;
            node->next = prev_node;

            while (head->prev != nullptr) head = head->prev;
        }
    }

    std::string search(T elem) {
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
        if (tmp == nullptr) throw std::invalid_argument("std::invalid_argument");
        tmp->data = elem;
    }
};

int main(int argc, char** argv) {
    CacheMassive<int> m;
    int n, command, command_count, id, elem;
    std::cin >> n;
    for (int i = 0; i < n; i++) {
        std::cin >> id >> elem;
        m.push_back(elem, id);
    }

    std::cin >> command_count;
    for (int i = 0; i < command_count; i++) {
        std::cin >> command;
        switch (command) {
        case 1:
            std::cin >> id >> elem;
            m.update(id, elem);
            break;
        case 2:
            std::cin >> id;
            m.raiseAccessCount(id);
            break;
        case 3:
            std::cin >> elem;
            m.search(elem);
            break;
        case 4:
            m.print();
            break;
        default:
            std::cout << "Enter other command from 1 to 4.\n";
        }
    }

    return 0;
}