#pragma once
#include <string>
#include <stdexcept>
#include <functional>
#include <iostream>

template<typename T>
struct Node {
    T data;
    Node* next;
    Node* prev;

    Node(const T& value = T(), Node* n = nullptr, Node* p = nullptr)
        : data(value), next(n), prev(p) {
    }
};

template<typename T>
class DoubleList {
private:
    Node<T>* head;
    Node<T>* tail;
    int count;

    // Безопасный обмен данными между узлами (без нарушения связей)
    void safeSwapData(Node<T>* a, Node<T>* b) {
        if (a == b || !a || !b) return;
        std::swap(a->data, b->data);
    }

    // Безопасный доступ к узлу по индексу
    Node<T>* getNodeAt(int index) const {
        if (index < 0 || index >= count) return nullptr;

        Node<T>* current = head;
        for (int i = 0; i < index; i++) {
            if (!current) return nullptr;
            current = current->next;
        }
        return current;
    }

    // Вспомогательная функция для бинарного поиска позиции
    int findInsertPosition(const T& value, Node<T>* start, Node<T>* end, int size) {
        int left = 0;
        int right = size - 1;

        while (left <= right) {
            int mid = left + (right - left) / 2;
            Node<T>* midNode = getNodeAt(mid);
            if (!midNode) break;

            if (midNode->data == value) {
                return mid;
            }
            else if (midNode->data < value) {
                left = mid + 1;
            }
            else {
                right = mid - 1;
            }
        }
        return left;
    }

public:
    DoubleList() : head(nullptr), tail(nullptr), count(0) {}

    ~DoubleList() {
        clear();
    }

    // Очистка списка
    void clear() {
        while (!empty()) {
            pop_front();
        }
    }

    // Основные операции
    void push_back(const T& value) {
        Node<T>* newNode = new Node<T>(value, nullptr, tail);

        if (tail) {
            tail->next = newNode;
        }
        else {
            head = newNode;
        }

        tail = newNode;
        count++;
    }

    void push_front(const T& value) {
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

    void pop_back() {
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

    void pop_front() {
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

    void insert(int pos, const T& value) {
        if (pos < 0 || pos > count) return;

        if (pos == 0) {
            push_front(value);
            return;
        }

        if (pos == count) {
            push_back(value);
            return;
        }

        Node<T>* current = getNodeAt(pos);
        if (!current) return;

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

    // Доступ к элементам
    T& at(int index) const {
        Node<T>* node = getNodeAt(index);
        if (!node) throw std::out_of_range("Index out of range");
        return node->data;
    }

    T& operator[](int index) const {
        return at(index);
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

    Node<T>* begin() const { return head; }
    Node<T>* end() const { return nullptr; }


    // Шейкерная сортировка 
    void cocktailSort() {
        if (count <= 1) return;

        bool swapped = true;
        int start = 0;
        int end = count - 1;

        while (swapped) {
            swapped = false;

            // Проход слева направо
            for (int i = start; i < end; i++) {
                Node<T>* current = getNodeAt(i);
                Node<T>* nextNode = getNodeAt(i + 1);

                if (current && nextNode && current->data > nextNode->data) {
                    safeSwapData(current, nextNode);
                    swapped = true;
                }
            }

            if (!swapped) break;

            swapped = false;
            end--;  // Последний элемент на своем месте

            // Проход справа налево
            for (int i = end - 1; i >= start; i--) {
                Node<T>* current = getNodeAt(i);
                Node<T>* nextNode = getNodeAt(i + 1);

                if (current && nextNode && current->data > nextNode->data) {
                    safeSwapData(current, nextNode);
                    swapped = true;
                }
            }

            start++;  // Первый элемент на своем месте
        }
    }

    //  Сортировка вставками с бинарным поиском 
    void insertionSortWithBinarySearch() {
        if (count <= 1) return;

        for (int i = 1; i < count; i++) {
            T key = at(i);

            // Бинарный поиск позиции для вставки
            int left = 0;
            int right = i - 1;
            int pos = left;

            while (left <= right) {
                int mid = left + (right - left) / 2;
                if (at(mid) == key) {
                    pos = mid + 1;
                    break;
                }
                else if (at(mid) < key) {
                    left = mid + 1;
                    pos = left;
                }
                else {
                    right = mid - 1;
                }
            }

            // Сдвиг элементов вправо
            for (int j = i; j > pos; j--) {
                at(j) = at(j - 1);
            }

            // Вставка элемента на найденную позицию
            at(pos) = key;
        }
    }

    // 3. Простая сортировка вставками (для отладки)
    void insertionSort() {
        if (count <= 1) return;

        for (int i = 1; i < count; i++) {
            T key = at(i);
            int j = i - 1;

            while (j >= 0 && at(j) > key) {
                at(j + 1) = at(j);
                j--;
            }
            at(j + 1) = key;
        }
    }

    // Проверка отсортированности
    bool isSorted() const {
        if (count <= 1) return true;

        Node<T>* current = head;
        while (current && current->next) {
            if (current->data > current->next->data) {
                return false;
            }
            current = current->next;
        }
        return true;
    }

    // Проверка целостности списка (для отладки)
    bool isValid() const {
        if (count == 0) {
            return head == nullptr && tail == nullptr;
        }

        if (!head || !tail) return false;
        if (head->prev != nullptr) return false;
        if (tail->next != nullptr) return false;

        // Подсчет узлов при обходе вперед
        int forwardCount = 0;
        Node<T>* current = head;
        while (current) {
            forwardCount++;
            if (current->next && current->next->prev != current) {
                return false;
            }
            current = current->next;
        }

        // Подсчет узлов при обходе назад
        int backwardCount = 0;
        current = tail;
        while (current) {
            backwardCount++;
            if (current->prev && current->prev->next != current) {
                return false;
            }
            current = current->prev;
        }

        return forwardCount == count && backwardCount == count;
    }

    // Вывод для отладки
    void print() const {
        Node<T>* current = head;
        std::cout << "[";
        while (current) {
            std::cout << current->data;
            if (current->next) std::cout << " <-> ";
            current = current->next;
        }
        std::cout << "]" << std::endl;
    }

    std::string toString() const {
        std::string result;
        Node<T>* current = head;
        while (current) {
            result += std::to_string(current->data);
            if (current->next) result += " ";
            current = current->next;
        }
        return result;
    }

    std::string toStringStr() const {
        std::string result;
        Node<T>* current = head;
        while (current) {
            result += current->data;
            if (current->next) result += " ";
            current = current->next;
        }
        return result;
    }
};
