#include <iostream>
#include <memory>
#include <vector>

/*Создать абстрактный базовый класс Number с виртуальными методами - арифметическими
операциями. Создать производные классы Integer (целое) и Real (действительное).*/

class Number{
    public:
        virtual void sum() const = 0;
        virtual void subtract() const = 0;
        virtual void multiply() const = 0;
        virtual void divide() const = 0;
        virtual ~Number() {} // деструктор
};

class Integer: public Number{
    private:
        int a;
        int b;
    public:
        Integer() : a(0), b(0) {}
        Integer(int a, int b): a(a), b(b) {}
        void sum() const override {std::cout<<a+b<<std::endl;} // Метод override предоставляет новую реализацию метода, унаследованного от базового класса.
        void subtract() const override {std::cout<<a-b<<std::endl;}
        void multiply() const override {std::cout<<a*b<<std::endl;}
        void divide() const override {std::cout<<a/b<<std::endl;}
};

class Real: public Number{
private:
    double a;
    double b;
public:
    Real() : a(0), b(0) {}
    Real(int a, int b): a(a), b(b) {}
    void sum() const override {std::cout<<a+b<<std::endl;}
    void subtract() const override {std::cout<<a-b<<std::endl;}
    void multiply() const override {std::cout<<a*b<<std::endl;}
    void divide() const override {std::cout<<a/b<<std::endl;}
};

int main() {
    std::vector<std::unique_ptr<Number>> number; // std::unique_ptr — умный указатель, владеющий динамически выделенным ресурсом

    number.emplace_back(std::make_unique<Integer>(6, 2)); // emplace'у просто передаются аргументы, как конструктору. 
    number.emplace_back(std::make_unique<Real>(7, 3)); //  used to create a unique_ptr object, which is a smart pointer that manages the lifetime of dynamically allocated objects. 



    for (const auto& number : number) {
        number->sum();
        number->subtract();
        number->multiply();
        number->divide();
    }
    return 0;
}