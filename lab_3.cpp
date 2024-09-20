#include <iostream>
#include <stdexcept>

// Queue через List

// Шаблонный класс List
template<typename T>
class List {
private:
    // Внутренний класс узла списка
    struct Node {
        T data;     // Данные узла
        Node* next; // Указатель на следующий узел

        // Конструктор узла
        Node(const T& value) : data(value), next(nullptr) {} // nullptr константа нулевого указателя
    };

    Node* head; // Указатель на начало списка
    Node* tail; // Указатель на конец списка
    int size;   // Размер списка

public:
    // Конструктор списка
    List() : head(nullptr), tail(nullptr), size(0) {}

    // Деструктор списка
    ~List() {
        while (head != nullptr) {
            Node* temp = head;
            head = head->next; // (*ptr).t
            delete temp;
        }
    }

    // Метод добавления элемента в конец списка
    void push_back(const T& value) {
        Node* newNode = new Node(value);
        if (head == nullptr) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
        size++;
    }

    // Метод удаления элемента из начала списка
    void pop() {
        if (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
            if (head == nullptr) {
                tail = nullptr;
            }
            size--;
        }
    }

    // Метод доступа к первому элементу списка
    T& front() {
        if (head != nullptr) {
            return head->data;
        }
        throw std::runtime_error("List is empty");
    }

    // Метод получения размера списка
    int getSize() const {
        return size;
    }

    // Метод проверки на пустоту списка
    bool isEmpty() const {
        return size == 0;
    }
};

// Шаблонный класс Queue
template<typename T>
class Queue {
private:
    List<T> l; // Объект класса List, используемый для реализации очереди

public:
    // Метод добавления элемента в конец очереди
    void enqueue(const T& value) {
        l.push_back(value);
    }

    // Метод удаления элемента из начала очереди
    void dequeue() {
        l.pop();
    }

    // Метод доступа к первому элементу очереди
    T& front() {
        return l.front();
    }

    // Метод получения размера очереди
    int getSize() const {
        return l.getSize();
    }

    // Метод проверки на пустоту очереди
    bool isEmpty() const {
        return l.isEmpty();
    }
};

int main() {
    // Создание очереди для типа int
    Queue<int> intQueue;
    intQueue.enqueue(1);
    intQueue.enqueue(2);
    intQueue.enqueue(3);

    // Вывод первого элемента очереди int
    std::cout << "Первый элемент intQueue: " << intQueue.front() << std::endl;

    // Создание очереди для типа double
    Queue<double> doubleQueue;
    doubleQueue.enqueue(1.1);
    doubleQueue.enqueue(2.2);
    doubleQueue.enqueue(3.3);

    // Вывод первого элемента очереди double
    std::cout << "Первый элемент doubleQueue: " << doubleQueue.front() << std::endl;

    // Создание очереди для типа std::string
    Queue<std::string> stringQueue;
    stringQueue.enqueue("Hello");
    stringQueue.enqueue("world");
    stringQueue.enqueue("!");

    // Вывод первого элемента очереди std::string
    std::cout << "Первый элемент stringQueue: " << stringQueue.front() << std::endl;

    return 0;
}
