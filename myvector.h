
#ifndef GRAPH2_0_MYVECTOR_H
#define GRAPH2_0_MYVECTOR_H

#include <iostream>

template<typename T>
class MyVector {
private:
    struct Node {
        T data;
        Node* next;
        Node(const T& d) : data(d), next(nullptr) {}
    };
    Node* head;
    size_t sz;

public:
    MyVector() : head(nullptr), sz(0) {}


//funkcja push back wkłada na stos
    void push_back(const T& val) {
        Node* newNode = new Node(val);
        if (!head) {
            head = newNode;
        } else {
            Node* temp = head;
            while (temp->next) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
        sz++;

    }
//poczatek
    Node* begin() const {
        return head;
    }
//koniec
    Node* end() const {
        if (!head) {
            return nullptr;
        }
        Node* temp = head;
        while (temp->next) {
            temp = temp->next;
        }
        return temp->next;
    }

    size_t size() const {
        return sz;
    }

     T& operator[](size_t index) const {
        Node* temp = head;
        for (size_t i = 0; i < index; ++i) {
            temp = temp->next;
        }
        return temp->data;
    }

    ~MyVector() {}
};


#endif //GRAPH2_0_MYVECTOR_H
