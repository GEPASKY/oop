#include <iostream>
#include <sstream>
#include <memory>


/* Создать класс для работы с денежными суммами. Денежная сумма представлена двумя
числами: типа long для рублей и типа unsigned char для копеек. При выводе на экран дробная
часть от целой должна отделяться запятой. Реализовать сложение, вычитание, деление сумм,
деление и умножение суммы на дробное число и операции сравнения.*/

class Money {
private:
    long rubles;//4
    unsigned char kopecks;//256
public:
    Money() : rubles(0), kopecks(0) {
    
    } // конструктор по умолчанию
    Money(long rub, long kop){
        Init(rub,kop);
    } // конструктор с параметрами
    Money(const Money &other) : rubles(other.rubles), kopecks(other.kopecks) {} // конструктор копирования
    Money(Money&& other) noexcept : rubles(std::exchange(other.rubles, 0)), kopecks(std::exchange(other.kopecks, 0)) {}
    // конструктор перемещения

    // Метод инициализации
    void Init(long rub, long kop) {

        rub += kop / 100;
        kop = abs(kop % 100);

        
        rubles = rub;
        kopecks = kop;
    }
    // Метод для ввода с клавиатуры
    void Read() {
        std::cout << "Введите сумму в рублях и копейках через пробел: ";
        std::cin >> rubles >> kopecks;
    }
    // Метод преобразования в строку
    std::string toString() const {
        std::stringstream ss;
        ss << rubles << "," << static_cast<int>(kopecks);
        return ss.str();
    }
    // Оператор копирующего присваивания
    Money& operator=(const Money &other) {
        if (this != &other) {
            rubles = other.rubles;
            kopecks = other.kopecks;
        }
        return *this;
    }
    // Оператор перемещающего присваивания
    Money& operator=(Money &&other) noexcept {
        if (this != &other) {
            rubles = other.rubles;
            kopecks = other.kopecks;
            other.rubles = 0;
            other.kopecks = 0;
        }
        return *this;
    }
    // Деструктор
    ~Money() {}
    // Операция сложения
    Money operator+(const Money &other) const {
        Money result;
        result.rubles = rubles + other.rubles;
        result.kopecks = kopecks + other.kopecks;
        if (result.kopecks >= 100) {
            result.rubles++;
            result.kopecks -= 100;
        }
        return result;
    }
    // Операция вычитания
    Money operator-(const Money &other) const {
        Money result;
        long total1 = rubles * 100 + kopecks;
        long total2 = other.rubles * 100 + other.kopecks;
        long diff = total1 - total2;
        if (diff < 0) {
            std::cerr << "negative amount!\n";
        } else {
            result.rubles = diff / 100;
            result.kopecks = diff % 100;
        }
        return result;
    }
    // Операция деления суммы на дробное число
    Money operator/(double divisor) const {
        Money result;
        double total = rubles * 100 + kopecks;
        total /= divisor;
        result.rubles = static_cast<long>(total);
        result.kopecks = static_cast<unsigned char>((total - result.rubles) * 100);
        return result;
    }
    // Операция умножения суммы на дробное число
    Money operator*(double factor) const {
        Money result;
        double total = rubles * 100 + kopecks;
        total *= factor;
        result.rubles = static_cast<long>(total);
        result.kopecks = static_cast<unsigned char>((total - result.rubles) * 100);
        return result;
    }
    // Операции сравнения
    bool operator==(const Money &other) const {
        return rubles == other.rubles && kopecks == other.kopecks;
    }
    bool operator!=(const Money &other) const {
        return !(*this == other);
    }
    bool operator<(const Money &other) const {
        if (rubles == other.rubles) {
            return kopecks < other.kopecks;
        }
        return rubles < other.rubles;
    }
    bool operator<=(const Money &other) const {
        return *this < other || *this == other;
    }
    bool operator>(const Money &other) const {
        return !(*this <= other);
    }
    bool operator>=(const Money &other) const {
        return !(*this < other);
    }
};

int main() {
    setlocale(LC_ALL,"rus");
    //system("chcp 1250");
    Money m1, m2(10, 50);
    Money m3;
    m1.Init(5, 2550);
    // m3 = std::move(m2);
    std::cout << m1.toString() << " m1\n";
    std::cout << m2.toString() << " m2\n";
    
    std::cout << "m1: " << m1.toString() << std::endl;
    std::cout << "m2: " << m2.toString() << std::endl;

    std::cout << "m1 + m2: " << (m1 + m2).toString() << std::endl;

    Money m4 = m1 - m2;
    std::cout << "m1 - m2: " << m4.toString() << std::endl;
    
    Money m4_1 = m2 - m1;
    std::cout << "m2 - m1: " << m4_1.toString() << std::endl;

    Money m5 = m1 / 2.0;
    std::cout << "m1 / 2.0: " << m5.toString() << std::endl;

    Money m6 = m1 * 1.5;
    std::cout << "m1 * 1.5: " << m6.toString() << std::endl;
    
    Money m7 = m1 / 3;
    std::cout << "m1 / 3: " << m7.toString() << std::endl;

    Money m8 = m1 * 5;
    std::cout << "m1 * 5: " << m8.toString() << std::endl;

    std::cout << "m1 == m2: " << (m1 == m2) << std::endl;
    std::cout << "m1 != m2: " << (m1 != m2) << std::endl;
    std::cout << "m1 < m2: " << (m1 < m2) << std::endl;
    std::cout << "m1 <= m2: " << (m1 <= m2) << std::endl;
    std::cout << "m1 > m2: " << (m1 > m2) << std::endl;
    std::cout << "m1 >= m2: " << (m1 >= m2) << std::endl;

    return 0;
}
