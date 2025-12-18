#pragma once
#include <string>
#include <stdexcept>

//для одного элемента
template<typename T>
struct Node {
    T data;        // данные
    Node* next;    // указатель на следующий
    Node* prev;    // указатель на предыдущий

    Node(const T& value = T(), Node* n = nullptr, Node* p = nullptr)
        : data(value), next(n), prev(p) {
    }
};

//для цепочки
template<typename T>
class DoubleList {
    // Основные поля
    Node<T>* head; // начало списка
    Node<T>* tail; // конец списка
    int count;     // количество элементов

public:
    DoubleList() : head(nullptr), tail(nullptr), count(0) {} //конструктор

    ~DoubleList() { //диструктор
        while (!empty()) {
            pop_front(); // Удаляем все элементы при закрытии
        }
    }

    void push_back(const T& value) { //добавление назад
        Node<T>* newNode = new Node<T>(value, nullptr, tail);

        if (tail) { // Старый хвост теперь указывает на новый
        
            tail->next = newNode;
        }
        else {
            head = newNode; // Если список был пуст, новый узел - и голова и хвост
        }

        tail = newNode;
        count++;
    }

    void push_front(const T& value) { //прицепить в начало
        Node<T>* newNode = new Node<T>(value, head, nullptr);

        if (head) {
            head->prev = newNode;
        }
        else {
            tail = newNode;
        }

        head = newNode;
        count++;
    }

    void pop_back() { //отцепить от конца
        if (empty()) return;

        Node<T>* temp = tail;
        tail = tail->prev;

        if (tail) {
            tail->next = nullptr;
        }
        else {
            head = nullptr;
        }

        delete temp;
        count--;
    }

    void pop_front() { //отцепить от начала
        if (empty()) return;

        Node<T>* temp = head;
        head = head->next;

        if (head) {
            head->prev = nullptr;
        }
        else {
            tail = nullptr;
        }

        delete temp;
        count--;
    }

    void insert(int pos, const T& value) { //прицепить куда то
        if (pos < 0 || pos > count) return;

        if (pos == 0) {
            push_front(value);
            return;
        }

        if (pos == count) {
            push_back(value);
            return;
        }

        Node<T>* current = head;
        for (int i = 0; i < pos; i++) {
            current = current->next;
        }

        Node<T>* newNode = new Node<T>(value, current, current->prev);
        current->prev->next = newNode;
        current->prev = newNode;
        count++;
    }

    void remove(const T& value) {
        Node<T>* current = head;
        while (current) {
            if (current->data == value) {
                Node<T>* toDelete = current;

                if (current->prev) {
                    current->prev->next = current->next;
                }
                else {
                    head = current->next;
                }

                if (current->next) {
                    current->next->prev = current->prev;
                }
                else {
                    tail = current->prev;
                }

                current = current->next;
                delete toDelete;
                count--;
            }
            else {
                current = current->next;
            }
        }
    }

    int size() const { return count; }
    bool empty() const { return count == 0; }

    T& front() const {
        if (empty()) throw std::out_of_range("List is empty");
        return head->data;
    }

    T& back() const {
        if (empty()) throw std::out_of_range("List is empty");
        return tail->data;
    }

    // Простой итератор
    Node<T>* begin() const { return head; }
    Node<T>* end() const { return nullptr; }
};
