#include <iostream>

struct Node {
    int data;
    Node* next;
    Node(int val) : data(val), next(nullptr) {}
};

class LinkedList {
public:
    Node* head;
    LinkedList() : head(nullptr) {}

    void insert(int val) {
        Node* newNode = new Node(val);
        newNode->next = head;
        head = newNode;
    }

    int countOccurrences(int x) {
        Node* current = head;
        int count = 0;
        while (current) {
            if (current->data == x) {
                count++;
            }
            current = current->next;
        }
        return count;
    }

    bool exists(int x) {
        return countOccurrences(x) > 0;
    }
};

int main() {
    LinkedList list;
    list.insert(10);
    list.insert(20);
    list.insert(10);
    list.insert(30);
    list.insert(10);
    
    int x = 10;
    if (list.exists(x)) {
        std::cout << "El valor " << x << " existe en la lista y aparece " << list.countOccurrences(x) << " veces.\n";
    } else {
        std::cout << "El valor " << x << " no existe en la lista.\n";
    }
    return 0;
}
