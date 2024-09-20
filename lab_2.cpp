#include <iostream>
#include <memory> // Для умных указателей
#include <vector> // Для использования стандартных контейнеров

// Абстрактный базовый класс Number
class Number {
public:
    virtual Number* add(const Number& other) const = 0;
    virtual Number* subtract(const Number& other) const = 0;
    virtual Number* multiply(const Number& other) const = 0;
    virtual Number* divide(const Number& other) const = 0;
    virtual void print() const = 0;
    virtual ~Number() {} // Виртуальный деструктор для полиморфизма
};

// Производный класс Integer (целое)
class Integer : public Number {
private:
    int value;
public:
    Integer(int val) : value(val) {}
    Number* add(const Number& other) const override {
        const Integer* intPtr = dynamic_cast<const Integer*>(&other);
        if (intPtr) {
            return new Integer(value + intPtr->value);
        }
        return nullptr;
    }
    // Определите другие арифметические операции по аналогии с add()
    void print() const override {
        std::cout << value;
    }
};

// Производный класс Real (действительное)
class Real : public Number {
private:
    double value;
public:
    Real(double val) : value(val) {}
    Number* add(const Number& other) const override {
        const Real* realPtr = dynamic_cast<const Real*>(&other);
        if (realPtr) {
            return new Real(value + realPtr->value);
        }
        return nullptr;
    }
    // Определите другие арифметические операции по аналогии с add()
    void print() const override {
        std::cout << value;
    }
};

// Функция вывода, демонстрирующая виртуальный вызов
void displayNumber(const Number& num) {
    num.print();
}programming

int main() {
    // Запрос пользовательского ввода для создания объекта Integer
    int intValue;
    std::cout << "Введите целое число: ";
    std::cin >> intValue;
    std::unique_ptr<Number> intNumber = std::make_unique<Integer>(intValue);

    // Запрос пользовательского ввода для создания объекта Real
    double realValue;
    std::cout << "Введите действительное число: ";
    std::cin >> realValue;
    std::unique_ptr<Number> realNumber = std::make_unique<Real>(realValue);

    // Выполнение арифметических операций и вывод результата
    std::unique_ptr<Number> resultAdd = intNumber->add(*realNumber);
    std::cout << "Результат сложения: ";
    if (resultAdd)
        resultAdd->print();
    else
        std::cout << "Невозможно выполнить операцию";
    std::cout << std::endl;

    // Другие операции можно добавить по аналогии с вышеуказанным
    // Например, вычитание, умножение, деление и т.д.

    return 0;
}

