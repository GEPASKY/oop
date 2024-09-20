#include <iostream>
#include <vector>
#include <memory>
#include <utility>


Monster m1;
Monster m1;
//m = m1;
//если нужен копирующий конструктори то нужно делать все конструкоторы которые у нас в Monster тк может пригодиться


class Monster {
    public:
        Monster(int health = 10): health_(health)
        {
            std::cout << "CTOR!" << health_ << std::endl;
        } //конструктор init

        ~Monster()//декструктор очищает память, у него нет параметров, деструктор может быть только один
        {
            std::cout << "DTOR!" << health_ << std::endl;
        }

        Monster(const Monster& other): health_(other.health_) 
        {
            std::cout << "Copy CTOR!" << health_ << std::endl;
        }// копирующий конструктор

        Monster& operator = (const Monster& other) {
            health_ = other.health_;
            std::cout << "Copy Assignment!" << health_ << std::endl;
            return *this;//указатель
        }// копирующий оператор присваивания

        Monster(Monster& other): health_(std::exchange(other.health_, 0))//монтср other со здоровьем 0
        {
            std::cout << "Move CTOR!" << health_ << std::endl;
        }// контруктор перемещения

        Monster& operator = (const Monster&& other) {
            health_ = std::exchange(other.health_, 0);
            std::cout << "Move Assignment!" << health_ << std::endl;
            return *this;//указатель
        }//перемещающее присваивание

        Monster& operator ++ (int)//prefix перегружаем инкримент 
        {
            ++health_;
            return *this;
        }

        Monster& operator ++ (int) //postfix перегружаем инкримент 
        {
            Monster old = *this;
            ++health_;
            return old;
        }

        int GetHealth() const
        {
            return health_;
        } // ломаем инкапсуляцию
        void SetHealth(int health)
        {
            health_ = health;
        }

    private:
        int health_;
};

int main() {
    // Ex 1
    Monster m;
    m++; // посфиксная форма(перегруженный инкримент)
    std::cout << "Hello world" << std::endl;
    ++m; // префиксная форма, работает быстрее посфиксной

    //Ex 2
    Monster mas[5];//вызывает 5 конструкторов и 5 деструкторов


    std::cout << "Hello worl" <<std::endl;
    return 0;
}