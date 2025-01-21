#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <list>

// Часть №1: Работа с контейнерами STL для встроенных типов данных


void part1() {
    // 1. Выбор типа контейнера и встроенного типа данных
    std::list<int> numbers = {1, 2, 3, 4, 5}; // Пример использования списка и целых чисел

    // 2. Просмотр контейнера
    std::cout << "Оригинальный контейнер:" << std::endl;
    for (const auto& number : numbers) {
        std::cout << number << " ";
    }
    std::cout << std::endl;

    // 3. Изменение контейнера: удаление и замена элементов
    auto it = std::next(numbers.begin(), 2); // Получение итератора на третий элемент
    numbers.erase(it); // Удаление третьего элемента

    it = std::next(numbers.begin(), 1); // Получение итератора на второй элемент
    *it = 10; // Замена второго элемента

    // 4. Просмотр контейнера через итераторы
    std::cout << "Модифицированный контейнер:" << std::endl;
    for (auto it = numbers.begin(); it != numbers.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // 5. Создание второго контейнера и заполнение данными
    std::list<int> moreNumbers = {6, 7, 8, 9, 10};

    // 6. Изменение первого контейнера и объединение с вторым
    it = std::next(numbers.begin(), 1); // Получение итератора на второй элемент
    auto itEnd = std::next(it, 2); // Получение итератора на четвертый элемент (на два дальше от второго)
    numbers.erase(it, itEnd); // Удаление двух элементов

    numbers.insert(numbers.end(), moreNumbers.begin(), moreNumbers.end()); // Добавление элементов из второго контейнера

    // 7. Просмотр обоих контейнеров
    std::cout << "Первый контейнер после модификации:" << std::endl;
    for (const auto& number : numbers) {
        std::cout << number << " ";
    }
    std::cout << std::endl;

    std::cout << "Второй контейнер:" << std::endl;
    for (const auto& number : moreNumbers) {
        std::cout << number << " ";
    }
    std::cout << std::endl;
}

// Часть №2: Работа с контейнерами STL для пользовательских типов данных

class Product {
private:
    std::string name;
    double price;
public:
    Product(std::string name, double price) : name(name), price(price) {} // конструктор с параметрами

    // Метод для получения цены
    double getPrice() const {
        return price;
    }

    // Метод для получения наименования
    std::string getName() const {
        return name;
    }

    // Перегрузка оператора сравнения для сортировки по возрастанию
    bool operator<(const Product& other) const {
        return price < other.price;
    }

    // Перегрузка операторов ввода/вывода
    friend std::ostream& operator<<(std::ostream& os, const Product& product) {
        return os << "Наименование: " << product.name << ", Цена: " << product.price;
    }
};

void part2() {
    // 1. Использование пользовательского класса Product
    std::vector<Product> products;

    // 2. Загрузка данных из файла в контейнер
    std::ifstream inputFile("products.txt");
    std::string name;
    double price;
    while (inputFile >> name >> price) {
        products.emplace_back(name, price);
    }
    inputFile.close();

    // Начальный контейнер
    std::cout << "Начальный контейнер:" << std::endl;
    for (const auto& product : products) {
        std::cout << product << std::endl;
    }

    // 3. Вставка нового элемента
    products.emplace_back("New_Product", 25.99);

    // 4. Удаление элементов, удовлетворяющих условию
    products.erase(std::remove_if(products.begin(), products.end(), [](const Product& p) {
    return p.getPrice() > 50.0; // Удаление продуктов с ценой выше 50
    }), products.end());

    // 5. Просмотр измененного контейнера
    std::cout << "Продукт после модификации:" << std::endl;
    for (const auto& product : products) {
        std::cout << product << std::endl;
    }
}

// Часть №3: Использование алгоритмов STL

void part3() {
    // 1. Создание контейнера с объектами пользовательского типа
    std::vector<Product> products = {
        Product("Laptop", 1200.0),
        Product("Phone", 800.0),
        Product("Tablet", 500.0),
        Product("TV", 1500.0)
    };

    // 2. Сортировка контейнера по убыванию цены
    std::sort(products.begin(), products.end(), [](const Product& a, const Product& b) {
        return a.getPrice() > b.getPrice();
    });

    // 3. Просмотр отсортированного контейнера
    std::cout << "Сортировка товаров по цене (по убыванию):" << std::endl;
    for (const auto& product : products) {
        std::cout << product << std::endl;
    }

    // 4. Поиск элемента, удовлетворяющего условию
    auto it = std::find_if(products.begin(), products.end(), [](const Product& p) {
        return p.getName() == "Phone"; // Поиск телефона
    });

    // 5. Просмотр результата поиска
    if (it != products.end()) {
        std::cout << "Найден: " << *it << std::endl;
    } else {
        std::cout << "Не найден." << std::endl;
    }

    // 6. Создание второго контейнера и перемещение туда элементов, удовлетворяющих условию
    std::vector<Product> affordableProducts;
    std::copy_if(products.begin(), products.end(), std::back_inserter(affordableProducts), [](const Product& p) {
        return p.getPrice() <= 1000.0; // Копирование продуктов с ценой не выше 1000
    });

    // 7. Просмотр второго контейнера
    std::cout << "Доступные продукты (<= 1000):" << std::endl;
    for (const auto& product : affordableProducts) {
        std::cout << product << std::endl;
    }

    // 8. Сортировка первого и второго контейнеров по возрастанию цены
    std::sort(products.begin(), products.end());
    std::sort(affordableProducts.begin(), affordableProducts.end());

    // 9. Просмотр отсортированного первого контейнера
    std::cout << "Сортировка товаров по цене (по возрастанию) первый контейнер:" << std::endl;
    for (const auto& product : products) {
        std::cout << product << std::endl;
    }

    // 10. Получение третьего контейнера путем слияния первых двух
    std::vector<Product> mergedProducts;
    std::merge(products.begin(), products.end(), affordableProducts.begin(), affordableProducts.end(), std::back_inserter(mergedProducts));

    // 11. Просмотр третьего контейнера
    std::cout << "Объединенные продукты:" << std::endl;
    for (const auto& product : mergedProducts) {
        std::cout << product << std::endl;
    }

    // 12. Подсчет элементов, удовлетворяющих заданному условию (цене <= 1000)
    int count = std::count_if(mergedProducts.begin(), mergedProducts.end(), [](const Product& p) {
        return p.getPrice() <= 1000.0;
    });
    std::cout << "Количество продуктов с ценой <= 1000: " << count << std::endl;

    // 13. Проверка наличия элемента, удовлетворяющего условию
    auto found = std::find_if(mergedProducts.begin(), mergedProducts.end(), [](const Product& p) {
        return p.getPrice() == 1200.0;
    });

    if (found != mergedProducts.end()) {
        std::cout << "Продукт с ценой == 1200 найден: " << *found << std::endl;
    } else {
        std::cout << "Продукт с ценой == 1200 не найден." << std::endl;
    }
}

int main() {
    std::cout << "Часть 1:" << std::endl;
    part1();

    std::cout << "\nЧасть 2:" << std::endl;
    part2();

    std::cout << "\nЧасть 3:" << std::endl;
    part3();

    return 0;
}

