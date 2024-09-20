#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <deque>
#include <algorithm>

/*
борис владимирович
Методические указания.
1. В части № 1 тип контейнера и встроенный тип данных выбирается самостоятельно.
2. В части № 2 в качестве пользовательского типа данных использовать свой
пользовательский класс(придумать самостоятельно, например: студент, кот, сотрудник,
товар, автомобиль, книга, банковский счёт и т.д.).
3. При создании контейнеров в части № 2 объекты выгружать и загружать из потока
(файла).
4. Для вставки и удаления элементов контейнера в части № 2 использовать
соответствующие операции, определенные в классе контейнера.
5. Для создания второго контейнера в части № 3 можно использовать либо алгоритм
remove_copy_if, либо алгоритм copy_if.
6. Для поиска элемента в коллекции можно использовать алгоритм find_if, либо for_each,
либо binary_search, если контейнер отсортирован.
7. Для сравнения элементов при сортировке по возрастанию используется операция <<,
которая должна быть перегружена в пользовательском классе. Для сортировки по
убыванию следует написать функцию comp и использовать вторую версию алгоритма sort.
8. Условия поиска и замены элементов выбираются самостоятельно и для них пишется
функция-предикат.
9. Для ввода-вывода объектов пользовательского класса следует перегрузить операции
>> и <<.
10. Некоторые алгоритмы могут не поддерживать используемые в вашей программе
контейнеры. Например, алгоритм sort не поддерживает контейнеры, которые не имеют
итераторов произвольного доступа. В этом случае следует написать свой алгоритм.
Например, для стека алгоритм сортировки может выполняться следующим образом:
переписать стек в вектор, отсортировать вектор, переписать вектор в стек.
*/

class Rectangle
{
private:
	double width;
	double height;

public:
    // Конструкторы, деструктор и перегруженные операторы

    // Перегрузка операторов ввода/вывода для класса Rectangle
	friend std::ostream& operator << (std::ostream&, const Rectangle&);
	friend std::istream& operator >> (std::istream&, Rectangle&);
	// Метод для чтения списка прямоугольников из файла
	friend void read_list_of_rectangles_from_file(std::list<Rectangle>&);

	explicit Rectangle(double width = 0.0, double height = 0.0): width(width), height(height) {};
	Rectangle(const Rectangle&) = default;
	Rectangle(Rectangle&&) = default;
	Rectangle& operator = (const Rectangle& other) { 
		if (this == &other ) {return *this; }
		width = other.width;
		height = other.height;
		return *this;
	}
	Rectangle& operator = (Rectangle&& other) { 
		if (this == &other ) {return *this; }
		width = std::move(other.width);
		height = std::move(other.height);
		other.height = other.width = 0.0;
		return *this;
	}
	~Rectangle() = default;

	bool operator < (const Rectangle& other) const { return get_square() < other.get_square(); }

	double get_square() const {	return width*height; }
};

std::ostream& operator << (std::ostream& stream, const Rectangle& rectangle)
{
	stream << "{ Ширина: { " << rectangle.width << " }, Высота: { " << rectangle.height << " } }";
	return stream;
}

std::istream& operator >> (std::istream& stream, Rectangle& rectangle)
{
	stream >> rectangle.width >> rectangle.height;
	return stream;
}

void read_list_of_rectangles_from_file(std::list<Rectangle>& list) {
	std::ifstream file("data.txt");
	if (file.is_open()) {
		Rectangle temp;
		while (file >> temp) {
			list.push_back(temp);
		}
		file.close();	
	}
}

int main() {
	/*==================================================================
	ПЕРВАЯ ЧАСТЬ
	==================================================================*/

	// 1) Создать объект-контейнер и заполнить его данными.
	std::vector<int> vector { 1, 2, 3, 4, 5, 6, 7 };

	// 2) Просмотреть контейнер.
	std::cout << "Данные вектора:" << std::endl;
	for (size_t i = 0; i < vector.size(); ++i) {
		std::cout << vector[i] << '\t';
	}
	std::cout << std::endl;

	// 3) Изменить контейнер, удалив из него одни элементы и заменив другие.
	vector.pop_back();
	vector[3] = vector[0];

	// 4) Просмотреть контейнер, используя для доступа к его элементам итераторы.
	std::cout << "Вывод данных вектора через итераторы: " << std::endl;
	for (std::vector<int>::iterator it = vector.begin(); it != vector.end(); ++it)	{
		std::cout << *it << '\t';
	}
	std::cout << std::endl;

	// 5) Создать второй контейнер этого же класса и заполнить его данными того же типа, что и
	// первый контейнер.
	std::vector<int> second_vector = vector;
	std::cout << "Данные второго вектора: " << std::endl;
	for (const int item : second_vector )
	{
		std::cout << item << '\t';
	}
	std::cout << std::endl;

	// 6) Изменить первый контейнер, удалив из него n элементов после заданного и добавив
	// затем в него все элементы из второго контейнера.
	const std::size_t n = 3; 
	vector.erase(vector.begin(),vector.begin() + n);
	vector.insert(vector.end(),second_vector.begin(),second_vector.end());

	// 7) Просмотреть первый и второй контейнеры.
	std::cout << "Данные первого вектора: " << std::endl;
	for (const int item : vector )
	{
		std::cout << item << '\t';
	}
	std::cout << std::endl;
	std::cout << "Данные второго вектора: " << std::endl;
	for (const int item : second_vector )
	{
		std::cout << item << '\t';
	}
	std::cout << std::endl;

	/*==================================================================
	ВТОРАЯ ЧАСТЬ
	==================================================================*/

	// 1) Создать объект-контейнер и заполнить его данными.
	std::list<Rectangle> list;
	read_list_of_rectangles_from_file(list);
	// 2) Просмотреть контейнер.
	std::cout << "Данные списка:" << std::endl;
	for (const Rectangle& item : list) {
		std::cout << item << '\t';
	}
	std::cout << std::endl;

	// 3) Изменить контейнер, удалив из него одни элементы и заменив другие.
	list.pop_back();
	*(list.begin()++) = *list.begin();

 	// 4) Просмотреть контейнер, используя для доступа к его элементам итераторы.
	std::cout << "Вывод данных списка через итераторы: " << std::endl;
	for (std::list<Rectangle>::iterator it = list.begin(); it != list.end(); ++it)	{
		std::cout << *it << '\t';
	}
	std::cout << std::endl;

	// 5) Создать второй контейнер этого же класса и заполнить его данными того же типа, что и
	// первый контейнер.
	std::list<Rectangle> second_list = list;
	std::cout << "Данные второго списка: " << std::endl;
	for (const Rectangle& item : second_list )
	{
		std::cout << item << '\t';
	}
	std::cout << std::endl;

	// 6) Изменить первый контейнер, удалив из него n элементов после заданного и добавив
	// затем в него все элементы из второго контейнера.
	std::list<Rectangle>::iterator it = list.begin();
	for (std::size_t i; i < n; ++i) {
		++it;
	}
	list.erase(list.begin(), it);
	list.insert(list.end(),second_list.begin(),second_list.end());

	// 7) Просмотреть первый и второй контейнеры.
	std::cout << "Данные первого списка: " << std::endl;
	for (const Rectangle& item : list )
	{
		std::cout << item << '\t';
	}
	std::cout << std::endl;
	std::cout << "Данные второго списка: " << std::endl;
	for (const Rectangle& item: second_list )
	{
		std::cout << item << '\t';
	}
	std::cout << std::endl;


	/*==================================================================
	ТРЕТЬЯ ЧАСТЬ
	==================================================================*/

	// 1. Создать контейнер, содержащий объекты пользовательского типа.
	std::deque<Rectangle> deque { Rectangle{1.0,2.0}, Rectangle{9.0,2.0}, Rectangle{0.0, 1.0}, Rectangle{3.0,3.0}};

	// 2. Отсортировать его по убыванию элементов.
	std::sort(deque.rbegin(), deque.rend());
	// std::sort(deque.begin(), deque.end(),[](const Rectangle& first_rectangle, const Rectangle& second_rectangle) {return first_rectangle.get_square() >= second_rectangle.get_square(); }); По заданию


	// 3. Просмотреть контейнер.
	std::cout << "Данные двухсторонней очереди: " << std::endl;
	for (const Rectangle& item : deque) {
		std::cout << item << '\t';
	}
	std::cout << std::endl;
	// 4. Используя подходящий алгоритм, найти в контейнере элемент, удовлетворяющий
	// заданному условию.
	std::cout << *std::find_if(deque.begin(),deque.end(),[](const Rectangle& rectangle){ return rectangle.get_square() < 10.0 && rectangle.get_square() > 6.0; });
	std::cout << std::endl;
	// 5. Переместить элементы, удовлетворяющие заданному условию в другой
	// (предварительно пустой) контейнер.

	std::deque<Rectangle> second_deque;
	second_deque.resize(std::count_if(deque.begin(),deque.end(), [](const Rectangle& rectangle) { return rectangle.get_square() < 5.0; }));
	std::remove_copy_if(deque.begin(),deque.end(),second_deque.begin(),[](const Rectangle& rectangle) { return rectangle.get_square() < 5.0; });

	// 6. Просмотреть второй контейнер.
	std::cout << "Данные второй двухсторонней очереди: " << std::endl;
	for (const Rectangle& item : second_deque) {
		std::cout << item << '\t';
	}
	std::cout << std::endl;

	// 7. Отсортировать первый и второй контейнеры по возрастанию элементов.
	std::sort(deque.begin(), deque.end());
	std::sort(second_deque.begin(), second_deque.end());

	// 8. Просмотреть их.
	std::cout << "После сортировки:\nДанные первой двухсторонней очереди: " << std::endl;
	for (const Rectangle& item : deque) {
		std::cout << item << '\t';
	}
	std::cout << std::endl;
	std::cout << "Данные второй двухсторонней очереди: " << std::endl;
	for (const Rectangle& item : second_deque) {
		std::cout << item << '\t';
	}
	std::cout << std::endl;

	// 9. Получить третий контейнер путем слияния первых двух.
	std::deque<Rectangle> third_deque;
	third_deque.resize(deque.size() + second_deque.size());
	std::merge(deque.begin(), deque.end(), second_deque.begin(), second_deque.end(),third_deque.begin());
	
	// 10. Просмотреть третий контейнер.
	std::cout << "Данные третьей двухсторонней очереди: " << std::endl;
	for (const Rectangle& item : third_deque) {
		std::cout << item << '\t';
	}
	std::cout << std::endl;

	// 11 .Подсчитать, сколько элементов, удовлетворяющих заданному условию, содержит
	// третий контейнер.
	std:: cout << std::count_if(third_deque.begin(),third_deque.end(), [](const Rectangle& rectangle) { return rectangle.get_square() < 5.0; });
	std::cout << std::endl;
	// 12. Определить, есть ли в третьем контейнере элемент, удовлетворяющий заданному
	// условию.
	std:: cout << (std::find_if(third_deque.begin(),third_deque.end(), [](const Rectangle& rectangle) { return rectangle.get_square() > 21.0; }) == third_deque.end());
	std::cout << std::endl;
	return 0;
}