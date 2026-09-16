// ordered_set_2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include "../ordered_set/ext/pb_ds/assoc_container.hpp"
#include "../ordered_set/ext/pb_ds/tree_policy.hpp"

template <typename T, typename C>
using ordered_set = std::__gnu_pbds::tree<T, std::__gnu_pbds::null_type, C, std::__gnu_pbds::rb_tree_tag, std::__gnu_pbds::tree_order_statistics_node_update>;
using std::cout;

struct mytype
{
	int a, b;
	// mytype(const mytype&) = delete;
	mytype(int x, int y) :a(x), b(y) {}

	mytype& operator^=(const mytype& oth)
	{
		a += oth.a;
		b ^= oth.b;
		a *= b;
		return *this;
	}
};

struct mycomp
{
	mycomp() {}
	bool operator()(const mytype& a, const mytype& b) const
	{
		return a.a * b.b - a.b * b.a < 0;
	}
};


int main()
{
	ordered_set<mytype, mycomp> fraq;
	ordered_set<int, std::less<int>> ds;
	ordered_set<int, std::greater<>> ss;
	fraq.insert({ 1,2 });
	fraq.insert({ 0,3 });
	fraq.insert({ 1,3 });
	fraq.insert({ 2,3 });
	fraq.insert({ 3,3 });
	for (auto& i : fraq)
	{
		cout << i.a << '/' << i.b << '\n';
	}
	for (size_t i = 0; i < 10; i++)
	{
		ds.insert(rand());
	}
	for (auto& i : ds)
	{
		cout << i << ' ';
	}
	cout << '\n';
	ordered_set<int, std::less<int>> a;
	ordered_set<int, std::less<int>>* b;
	{
		ordered_set<int, std::less<int>> x = move(ds);
		// a = x;
		b = new ordered_set<int, std::less<int>>(move(x));
	}
	a = *b;
	a = move(*b);
	for (auto& i : a)
	{
		cout << i << ' ';
		ss.insert(i);
	}
	std::prev(a.end());
	cout << '\n';
	for (auto& i : ss)
	{
		cout << i << ' ';
	}
	cout << '\n';
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
