#include "pch.h"
#include "CppUnitTest.h"
#include "ext/pb_ds/assoc_container.hpp"
#include "ext/pb_ds/tree_policy.hpp"
#include <iostream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
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

namespace orderedset
{
	TEST_CLASS(orderedset)
	{
	public:
		ordered_set<mytype, mycomp> fraq;
		ordered_set<int, std::less<int>> ds;
		ordered_set<int, std::greater<>> ss;
		TEST_METHOD(TestMethod1)
		{
		}
		TEST_METHOD(TestIterator)
		{
			cout << "--- iterator test ---\n";
			// fraq.insert({ 10,12 });
			fraq.insert({ 1,2 });
			fraq.insert({ 0,3 });
			fraq.insert({ 1,3 });
			fraq.insert({ 2,3 });
			fraq.insert({ 3,3 });
			for (auto& i : fraq)
			{
				cout << i.a << '/' << i.b << '\n';
			}
			auto it = fraq.lower_bound({ 1,6 });
			Assert::AreEqual(it->a, 1);
			Assert::AreEqual(it->b, 3);
			Assert::AreEqual(fraq.order_of_key({ 2,3 }), (size_t)3);
			fraq.clear();
			cout << "--- [iterator test] ---\n";
		}
	};
}
