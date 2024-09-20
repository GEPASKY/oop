#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <utility>

class Monster
{
public:
    Monster(int health = 10): health_(health)//default CTOR
    {
        std::cout << "CTOR! " << health_ << std::endl;
    }
    Monster(const Monster& m): health_(m.health_)//copy CTOR
    {
        std::cout << "Copy CTOR! " << health_ << std::endl;
    }
    Monster& operator = (const Monster& m)//copy aasignment
    {
        health_ = m.health_;
        std::cout << "Copy Assignment! " << health_ << std::endl;
        return *this;
    }
    Monster(Monster&& m): health_(std::exchange(m.health_, 0))//move CTOR
    {
        std::cout << "Move CTOR! " << health_ << std::endl;
    }
    Monster& operator = (Monster&& m)//move aasignment
    {
        health_ = std::exchange(m.health_, 0);
        std::cout << "Move Assignment! " << health_ << std::endl;
        return *this;
    }
    Monster& operator ++ () //prefix
    {
        ++health_;
        return *this;
    }
    Monster operator ++ (int) //postfix
    {
        Monster old = *this;
        ++health_;
        return old;
    }
    ~Monster()//DTOR
    {
        std::cout << "DTOR! " << health_ << std::endl;
    }
    int GetHealth() const
    {
        return health_;
    }
    void setHealth(int health)
    {
        health_ = health;
    }
private:
    int health_;
};
Monster ByVal(Monster m) //health_*10
{
    m.setHealth(m.GetHealth() * 10);
    return m;
}
Monster& ByRef(Monster& m) //health_*10
{
    m.setHealth(m.GetHealth() * 10);
    return m;
}
Monster&& ByMoveRef(Monster&& m) //health_*10
{
    m.setHealth(m.GetHealth() * 10);
    return std::move(m);
}
int main()
{
    //Exp 1
/*    Monster m;
    ++m;
    std::cout << "Hello World!" << std::endl;
    m++;
    */
    //Exp 2
/*    Monster mas[5];
    std::cout << "Hello World!" << std::endl;
    std::vector<Monster> vec(5);
*/
    //Exp 3
/*    std::vector<Monster> vec;
    vec.push_back(Monster());
    std::cout << "Hello World!" << std::endl;
    vec.emplace_back(Monster());
*/
    //Exp 4
/*    Monster m;
    //m = ByVal(m);
    //m = ByRef(m);
    m = ByMoveRef(std::move(m));
    */
    //Exp 5 ?
/*    Monster m, m1;
    m1 = std::move(m);
*/
    //Exp 6
//    std::unique_ptr<Monster> pm = std::make_unique<Monster>();

    std::cout << "Hello World!" << std::endl;
    return 0;
}
