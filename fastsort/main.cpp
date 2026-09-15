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
#include <chrono>

using namespace std;
using ll = long long;
using ld = long double;

const int SORT_K = 10;
const int SORT_BLOCK = (1 << SORT_K);

void sort1(vector <int>& a)
{
    static int cnt[SORT_BLOCK + 1];
    //sort(a.begin(), a.end());
    int n = a.size();
    vector <int> tmp(a.size());
    for (int sh = 0; sh < SORT_K * 2; sh += SORT_K)
    {
        memset(cnt, 0, sizeof(cnt));
        for (auto& i : a)
            cnt[((i >> sh) & (SORT_BLOCK - 1)) + 1]++;
        for (int i = 0; i < SORT_BLOCK; i++)
            cnt[i + 1] += cnt[i];
        for (auto& i : a)
            tmp[cnt[(i >> sh) & (SORT_BLOCK - 1)]++] = i;
        a.swap(tmp);
    }
}

void sort2(vector <ll>& a)
{
    static int cnt[SORT_BLOCK + 1];
    //sort(a.begin(), a.end());
    int n = a.size();
    vector <ll> tmp(a.size());
    for (int sh = 0; sh < SORT_K * 6; sh += SORT_K) 
    {
        memset(cnt, 0, sizeof(cnt));
        for (auto& i : a)
            cnt[((i >> sh) & (SORT_BLOCK - 1)) + 1]++;
        for (int i = 0; i < SORT_BLOCK; i++)
            cnt[i + 1] += cnt[i];
        for (auto& i : a)
            tmp[cnt[(i >> sh) & (SORT_BLOCK - 1)]++] = i;
        a.swap(tmp);
    }
}

void sort1s(vector <int>& a)
{
    sort(a.begin(), a.end());
}

void sort2s(vector<ll>& a)
{
    sort(a.begin(), a.end());
}

int cmp_int(const void* a1, const void* a2)
{
    return *(const int*)a1 - *(const int*)a2;
}

void sort1q(vector <int>& a)
{
    qsort(a.data(), a.size(), sizeof(int), cmp_int);
}

void measure(function<void()> f, const char* name)
{
    auto s1 = chrono::high_resolution_clock::now();
    f();
    auto s2 = chrono::high_resolution_clock::now();
    cout << name << " executed in " << (s2 - s1) << endl;
}

void check1(mt19937_64& rnd, int sz)
{
    cout << "Type: int\nNumber of elements: " << sz << endl;
    uniform_int_distribution gen(0, SORT_BLOCK * SORT_BLOCK - 1);
    vector <int> a(sz);
    for (auto& i : a)
    {
        i = gen(rnd);
    }
    auto b = a;
    auto c = a;
    measure([&]() {sort1(a); }, "fast_sort");
    measure([&]() {sort1s(b); }, "std::sort");
    measure([&]() {sort1q(c); }, "qsort");
    if (a != b)
        cout << "fast_sort error" << endl;
    if (c != b)
        cout << "qsort error" << endl;
}

void check2(mt19937_64& rnd, int sz)
{
    cout << "Type: long long\nNumber of elements: " << sz << endl;
    uniform_int_distribution<ll> gen(0, 1ll * SORT_BLOCK * SORT_BLOCK * SORT_BLOCK * SORT_BLOCK * SORT_BLOCK * SORT_BLOCK - 1);
    vector <ll> a(sz);
    for (auto& i : a)
    {
        i = gen(rnd);
    }
    auto b = a;
    measure([&]() {sort2(a); }, "fast_sort");
    measure([&]() {sort2s(b); }, "std::sort");
    if (a != b)
        cout << "fast_sort error" << endl;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
    mt19937_64 rnd(15728);
    for (size_t i = 10; i <= 10000000; i *= 10)
    {
        check1(rnd, i);
        //check1(rnd, i);
        //check1(rnd, i);
    }
    for (size_t i = 10; i <= 10000000; i *= 10)
    {
        check2(rnd, i);
        //check2(rnd, i);
        //check2(rnd, i);
    }
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
