// main.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#define _CRT_SECURE_NO_WARNINGS

#include <cstring>
#include <array>
#include <algorithm>
#include <bitset>
#include <deque>
#include <fstream>
#include <functional>
#include <iostream>
#include <map>
#include <queue>
#include <random>
#include <set>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
#include <variant>

using namespace std;
using ll = long long;
using ld = long double;

#define EXT
#pragma region SegmentTree
#if 0 // TESTING
#include "C:\Users\User\Documents\Visual Studio 2019\SegmentTree.h"
#else
// SegmentTree.h
// Mark_Pr (c) 2024

#pragma once
#include <vector>
#include <functional>

namespace std
{
#pragma message("Mark_Pr (c) SegmentTree.h")
	template <typename _Type, typename _Result = _Type>
	class SegmentTree
	{
	protected:
		size_t tsize;
		vector <_Result> tree;
		function<_Type(const _Type&, const _Type&)> func;

		_Result nullval;

	protected:
		void build(vector <_Type>& l, size_t x, size_t lx, size_t rx)
		{
			if (lx + 1 == rx) {
				if (lx < l.size())
					tree[x] = l[lx];
			}
			else {
				size_t m = (lx + rx) / 2;
				build(l, 2 * x + 1, lx, m);
				build(l, 2 * x + 2, m, rx);
				tree[x] = func(tree[2 * x + 1], tree[2 * x + 2]);
			}
		}

		template <typename _Iter>
		void build(_Iter& first, _Iter& last, size_t x, size_t lx, size_t rx)
		{
			if (lx + 1 == rx) {
				if (first != last)
				{
					tree[x] = *first;
					++first;
				}
			}
			else {
				size_t m = (lx + rx) / 2;
				build(first, last, 2 * x + 1, lx, m);
				build(first, last, 2 * x + 2, m, rx);
				tree[x] = func(tree[2 * x + 1], tree[2 * x + 2]);
			}
		}

		void set(size_t i, const _Type& val, size_t x, size_t lx, size_t rx)
		{
			if (lx == rx - 1) {
				tree[x] = val;
			}
			else {
				size_t m = (lx + rx) / 2;
				if (i < m)
					set(i, val, 2 * x + 1, lx, m);
				else
					set(i, val, 2 * x + 2, m, rx);
				tree[x] = func(tree[2 * x + 1], tree[2 * x + 2]);
			}
		}

		_Result segment(size_t l, size_t r, size_t x, size_t lx, size_t rx)
		{
			if (rx <= l || r <= lx)
				return nullval;
			if (l <= lx && rx <= r)
				return tree[x];
			size_t m = (lx + rx) / 2;
			return func(segment(l, r, 2 * x + 1, lx, m), segment(l, r, 2 * x + 2, m, rx));
		}
	public:
		SegmentTree(function<_Type(const _Type&, const _Type&)> function, const _Result& nullarg) :nullval(nullarg)
		{
			this->func = function;
		}

		void init(size_t n)
		{
			tsize = 1;
			while (tsize < n) {
				tsize *= 2;
			}
			tree.assign(2 * tsize - 1, nullval);
		}

		void init(size_t n, const _Result& nullelem)
		{
			this->nullval = nullelem;
			this->init(n);
		}

		void set(size_t i, const _Type& t)
		{
			if (i >= tsize)
				return;
			set(i, t, 0, 0, tsize);
		}

		void build(vector <_Type>& a)
		{
			this->init(a.size());
			a.resize(tsize, nullval);
			this->build(a, 0, 0, tsize);
		}

		template <typename _Iter>
		void build(_Iter first, _Iter last)
		{
			this->init(distance(first, last));
			this->build(first, last, 0, 0, tsize);
		}

		size_t assign(size_t n, const _Result& elem)
		{
			init(n);
			vector <_Result> tmp(tsize, elem);
			build(tmp);
			return tsize;
		}

		_Result segment(size_t i, size_t j)
		{
			j = min(j, tsize);
			if (i >= j)
				return nullval;
			return segment(i, j, 0, 0, tsize);
		}

		void build()
		{
			vector <_Type> empty;
			build(empty, 0, 0, tsize);
		}

		size_t size()
		{
			return tsize;
		}

		const _Result& get(size_t i)
		{
			if (i >= tsize)
				return nullval;
			return tree[tsize - 1 + i];
		}
	};
#pragma message("Mark_Pr (c) SegmentTree.hpp")
#pragma message("#define EXT: This template is not tested")
#pragma message("#define EXT: Don't use \"using namespace ext\"")
	namespace ext
	{
		template <typename _Type, typename _Add, typename _Result = _Type>
		class SegmentTree
		{
			//#pragma warning("_Type must have operator+(_Type, _Add)")
		protected:
			long long tsize;
			vector <_Result> tree;
			vector <_Add> upd;
			function<_Result(const _Result&, const _Result&)> func;
			function<_Add(const _Add&, const _Add&)> uniq;
			function<void(_Result&, const _Add&, size_t)> bf;
			_Result nullval;
			_Add nulladd;

		protected:
			void push(size_t v, size_t l, size_t r)
			{
				if (upd[v] != nulladd)
				{
					bf(tree[v], upd[v], r - l);
					if (l != r - 1)
					{
						upd[2 * v + 1] = uniq(upd[2 * v + 1], upd[v]);
						upd[2 * v + 2] = uniq(upd[2 * v + 2], upd[v]);
					}
					upd[v] = nulladd;
				}
			}

			void build(vector <_Type>& l, size_t x, size_t lx, size_t rx)
			{
				if (lx + 1 == rx) {
					if (lx < l.size())
						tree[x] = l[lx];
				}
				else {
					size_t m = (lx + rx) / 2;
					build(l, 2 * x + 1, lx, m);
					build(l, 2 * x + 2, m, rx);
					tree[x] = func(tree[2 * x + 1], tree[2 * x + 2]);
				}
			}

			template <typename _Iter>
			void build(_Iter& first, _Iter& last, size_t x, size_t lx, size_t rx)
			{
				if (lx + 1 == rx) {
					if (first != last)
					{
						tree[x] = *first;
						++first;
					}
				}
				else {
					size_t m = (lx + rx) / 2;
					build(first, last, 2 * x + 1, lx, m);
					build(first, last, 2 * x + 2, m, rx);
					tree[x] = func(tree[2 * x + 1], tree[2 * x + 2]);
				}
			}

			void set(size_t i, const _Type& val, size_t x, size_t lx, size_t rx)
			{
				push(x, lx, rx);
				if (i < lx || i >= rx)
					return;
				if (lx == rx - 1) {
					tree[x] = val;
				}
				else {
					size_t m = (lx + rx) / 2;
					set(i, val, 2 * x + 1, lx, m);
					set(i, val, 2 * x + 2, m, rx);
					tree[x] = func(tree[2 * x + 1], tree[2 * x + 2]);
				}
			}

			_Result segment(size_t l, size_t r, size_t x, size_t lx, size_t rx)
			{
				push(x, lx, rx);
				if (rx <= l || r <= lx)
					return nullval;
				if (l <= lx && rx <= r)
					return tree[x];
				size_t m = (lx + rx) / 2;
				return func(segment(l, r, 2 * x + 1, lx, m), segment(l, r, 2 * x + 2, m, rx));
			}

			void update(size_t v, size_t l, size_t r, size_t ql, size_t qr, const _Add& adv)
			{
				push(v, l, r);
				if (ql >= r || qr <= l)
					return;
				if (ql <= l && r <= qr) {
					upd[v] = uniq(upd[v], adv);
					push(v, l, r);
					return;
				}
				size_t m = (l + r) / 2;
				update(2 * v + 1, l, m, ql, qr, adv);
				update(2 * v + 2, m, r, ql, qr, adv);
				tree[v] = func(tree[2 * v + 1], tree[2 * v + 2]);
			}

			void confirm(size_t v, size_t l, size_t r)
			{
				push(v, l, r);
				if (l == r - 1)
					return;
				size_t m = (l + r) / 2;
				confirm(2 * v + 1, l, m);
				confirm(2 * v + 2, m, r);
			}

		public:
			/// <summary>
			/// Initialize SegmentTree
			/// </summary>
			/// <param name="func">segment(l, r) = func(a_l, ..., a_r-1)</param>
			/// <param name="unique">using to add two updates</param>
			/// <param name="plus">update element function; update(l, r, x) -> plus(a_l,x),...,plus(a_r-1,x)</param>
			/// <param name="nullarg">func(x, nullarg) = x</param>
			/// <param name="nulladd">unique(x, nulladd) = x</param>
			SegmentTree(
				function<_Result(const _Result&, const _Result&)> func,
				function<_Add(const _Add&, const _Add&)> unique,
				function<void(_Result&, const _Add&, size_t)> plus,
				const _Result& nullarg, const _Add& nulladd) :nullval(nullarg), nulladd(nulladd)
			{
				this->func = func;
				this->uniq = unique;
				this->bf = plus;
			}

			/// <summary>
			/// Initialize for n elements
			/// </summary>
			/// <param name="n"></param>
			inline void init(size_t n)
			{
				tsize = 1;
				while (tsize < n) {
					tsize *= 2;
				}
				tree.assign(2 * tsize - 1, nullval);
				upd.assign(2 * tsize - 1, nulladd);
			}

			inline void init(size_t n, const _Result& val, const _Add& add)
			{
				this->nullval = val;
				this->nulladd = add;
				tsize = 1;
				while (tsize < n) {
					tsize *= 2;
				}
				tree.assign(2 * tsize - 1, nullval);
				upd.assign(2 * tsize - 1, nulladd);
			}

			inline void set(size_t i, const _Type& t)
			{
				set(i, t, 0, 0, tsize);
			}

			inline void build(vector <_Type>& a)
			{
				this->init(a.size());
				a.resize(tsize, nullval);
				this->build(a, 0, 0, tsize);
			}

			/// <summary>
			/// Initialize for n elements and assign all values to elem
			/// </summary>
			/// <param name="n"></param>
			/// <param name="nullelem"></param>
			/// <returns>real tree size</returns>
			inline size_t assign(size_t n, const _Type& elem)
			{
				init(n);
				vector <_Type> l(n, elem);
				build(l);
				return tsize;
			}

			inline _Result segment(size_t i, size_t j)
			{
				return segment(i, j, 0, 0, tsize);
			}

			inline size_t size()
			{
				return tsize;
			}

			inline void update(size_t ql, size_t qr, const _Add& adv)
			{
				update(0, 0, tsize, ql, qr, adv);
			}

			inline void confirm()
			{
				confirm(0, 0, tsize);
			}

			inline _Result get_confirmed(size_t i)
			{
#pragma message("get_confirmed(i): Call get_confirmed only after confirm() operation")
				return tree[i + tsize - 1];
			}

			template <typename _Iter>
			inline void build(_Iter first, _Iter last)
			{
				this->init(distance(first, last));
				this->build(first, last, 0, 0, tsize);
			}
		};
	}
}

#endif
#pragma endregion

void expect(bool x, const char* expr)
{
	if (!x)
	{
		cout << "TEST FAILED: " << expr;
#ifdef _DEBUG
		_ASSERT_EXPR(x, _CRT_WIDE_("TEST FAILED"));
#endif
		abort();
	}
}

#define EXPECT(x) expect(x, #x)
#define EQUAL(a, b) EXPECT((a) == (b))

using obj1 = SegmentTree<int>;
using obj2 = ext::SegmentTree<int, int>;

struct Executor
{
	variant <obj1, obj2> var;
	vector <int> arr;

	void init(int n)
	{
		arr.assign(n, 0);
		visit([n](auto& x) {x.init(n); }, var);
	}

	void set(int i, int x)
	{
		if (i < 0 || i >= arr.size())
			return;
		arr[i] = x;
		visit([i, x](auto& y) {y.set(i, x); }, var);
	}

	void segment(int l, int r)
	{
		int ans = 0;
		for (int i = l; i < r; i++)
			ans += arr[i];
		visit([l, r, ans](auto& x) { EQUAL(x.segment(l, r), ans); }, var);
	}

	void update(int l, int r, int x)
	{
		if (var.index() == 1)
		{
			get<obj2>(var).update(l, r, x);
			for (size_t i = l; i < r; i++)
			{
				arr[i] += x;
			}
		}
	}

	void check()
	{
		if (var.index() == 1)
		{
			get<obj2>(var).confirm();
			for (size_t i = 0; i < arr.size(); i++)
			{
				EQUAL(arr[i], get<obj2>(var).get_confirmed(i));
			}
		}
		else
		{
			for (size_t i = 0; i < arr.size(); i++)
			{
				EQUAL(arr[i], get<obj1>(var).segment(i, i + 1));
			}
		}
	}
};

Executor random_sets_and_updates(Executor ex)
{
	int K = 1e6 / ex.arr.size();
	while (K--)
	{
		if (rand() & 1)
		{
			ex.set(rand() % ex.arr.size(), rand() * 1e4 + rand());
		}
		else
		{
			int r = rand() % ex.arr.size() + 1;
			ex.update(rand() % r, r, rand() * 1e4 + rand());
		}
	}
	return ex;
}

Executor random_sets_and_gets(Executor ex)
{
	int K = 1e6 / ex.arr.size();
	while (K--)
	{
		if (rand() & 1)
		{
			ex.set(rand() % ex.arr.size(), rand() * 1e4 + rand());
		}
		else
		{
			int r = rand() % ex.arr.size() + 1;
			ex.segment(rand() % r, r);
		}
	}
	return ex;
}

Executor random_ops(Executor ex)
{
	int K = 1e6 / ex.arr.size();
	while (K--)
	{
		int x = rand() % 3;
		if (x == 0)
		{
			ex.set(rand() % ex.arr.size(), rand() * 1e4 + rand());
		}
		else if (x == 1)
		{
			int r = rand() % ex.arr.size() + 1;
			ex.segment(rand() % r, r);
		}
		else
		{
			int r = rand() % ex.arr.size() + 1;
			ex.update(rand() % r, r, rand() * 1e4 + rand());
		}
	}
	return ex;
}

Executor random_gets_and_check(Executor ex)
{
	int K = 1e6 / ex.arr.size();
	while (K--)
	{
		int r = rand() % ex.arr.size() + 1;
		ex.segment(rand() % r, r);
	}
	ex.check();
	return ex;
}

Executor all_sets(Executor ex)
{
	int K = min<int>(ex.arr.size(), 1e6 / ex.arr.size());
	for (size_t i = 0; i < K; i++)
	{
		ex.set(i, rand());
	}
	return ex;
}

Executor all_gets(Executor ex)
{
	int K = min<int>(ex.arr.size() * ex.arr.size(), 1e6 / ex.arr.size());
	int l = 0, r = 1;
	for (size_t i = 0; i < K && l < ex.arr.size(); i++)
	{
		ex.segment(l, r);
		if (r == ex.arr.size())
		{
			l++;
			r = l + 1;
		}
		else
		{
			r++;
		}
	}
	return ex;
}

Executor all_updates(Executor ex)
{
	int K = min<int>(ex.arr.size() * ex.arr.size(), 1e6 / ex.arr.size());
	int l = 0, r = 1;
	for (size_t i = 0; i < K && l < ex.arr.size(); i++)
	{
		ex.update(l, r, rand());
		if (r == ex.arr.size())
		{
			l++;
			r = l + 1;
		}
		else
		{
			r++;
		}
	}
	return ex;
}

void test1(Executor ex)
{
	cout << "TEST 1 STARTED" << endl;
	Executor setted = random_sets_and_updates(ex);
	random_gets_and_check(setted);
	setted = random_ops(ex);
	random_gets_and_check(setted);
	setted = random_sets_and_gets(ex);
	random_gets_and_check(setted);
}

void test2(Executor ex)
{
	cout << "TEST 2 STARTED" << endl;
	ex = random_sets_and_updates(ex);
	ex = all_gets(ex);
	ex = all_updates(ex);
	ex = all_gets(ex);
	ex = random_ops(ex);
	ex = all_gets(ex);
	ex = all_sets(ex);
	ex = all_gets(ex);
	ex = random_gets_and_check(ex);
}

void test3(Executor ex)
{
	cout << "TEST 3 STARTED" << endl;
	Executor ex1 = random_sets_and_updates(ex);
	Executor ex2 = all_updates(ex);
	random_gets_and_check(ex2);
	ex2 = random_ops(ex2);
	ex2 = random_gets_and_check(ex2);
	all_gets(ex2);
	ex1 = random_sets_and_gets(ex1);
	ex1 = random_sets_and_updates(ex1);
	ex1 = random_sets_and_gets(ex1);
	random_gets_and_check(ex1);
	all_gets(ex1);
}

void run_tests_n(Executor ex, int N)
{
	cout << "STARTING TESTS FOR " << (ex.var.index() ? "extSegmentTree" : "SegmentTree") << " WITH N = " << N << endl;
	ex.init(N);
	Executor beg = all_sets(ex);
	test1(beg);
	test2(beg);
	test3(beg);
}

void run_tests(Executor ex)
{
	run_tests_n(ex, 1);
	run_tests_n(ex, 10);
	run_tests_n(ex, 15);
	run_tests_n(ex, 16);
	run_tests_n(ex, 17);
	run_tests_n(ex, 50);
	run_tests_n(ex, 100);
	run_tests_n(ex, 127);
	run_tests_n(ex, 128);
	run_tests_n(ex, 129);
	run_tests_n(ex, 150);
	run_tests_n(ex, 500);
	run_tests_n(ex, 1500);
	run_tests_n(ex, 5000);
	run_tests_n(ex, 10000);
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
	srand(0x16082025);
	Executor e1 = { obj1([](int a,int b) {return a + b; }, 0), {} };
	Executor e2 = { obj2([](int a,int b) {return a + b; }, [](int a,int b) {return a + b; }, [](int& x,int y, int z) {x += y * z; }, 0, 0), {} };
	run_tests(e1);
	run_tests(e2);
    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
