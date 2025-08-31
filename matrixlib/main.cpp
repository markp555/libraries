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

#pragma region Matrix Library
#include <complex>
#include <cstring>
#include <list>

namespace std
{
    namespace Math
    {
        template <typename T, unsigned N, unsigned K>
        struct vector
        {
            T a[N][K];

            vector()
            {
                memset(a, 0, sizeof(a));
            }
            vector(T null)
            {
                for (size_t i = 0; i < N; i++)
                {
                    for (size_t j = 0; j < K; j++)
                    {
                        a[i][j] = null;
                    }
                }
            }

            vector(std::initializer_list<std::initializer_list <T>> x)
            {
#ifdef _DEBUG
                if (x.size() != N)
                    _CrtDbgBreak();
                if ((*x.begin()).size() != K)
                    _CrtDbgBreak();
#endif // _DEBUG
                auto it = x.begin();
                for (size_t i = 0; i < N && it != x.end(); i++, it++)
                {
                    const std::initializer_list <T>& l = *it;
                    copy(l.begin(), l.end(), a[i]);
                }
            }

            static unsigned size()
            {
                return N;
            }

            T* operator[](unsigned x)
            {
                return a[x];
            }

            const T* operator[](unsigned x) const
            {
                return a[x];
            }

            void print(ostream& out)
            {
                for (size_t i = 0; i < N; i++)
                {
                    for (size_t j = 0; j < K; j++)
                    {
                        out << a[i][j] << ' ';
                    }
                    out << '\n';
                }
            }

            template <unsigned M>
            vector <T, N, M> operator*(const vector<T, K, M>& x) const
            {
                vector <T, N, M> res;
                for (size_t i = 0; i < N; i++)
                {
                    for (size_t j = 0; j < M; j++)
                    {
                        for (size_t t = 0; t < K; t++)
                        {
                            res[i][j] = res[i][j] + (*this)[i][t] * x[t][j];
                        }
                    }
                }
                return res;
            }

            vector <T, N, K> operator+(const vector <T, N, K>& x) const
            {
                vector <T, N, K> res;
                for (size_t i = 0; i < N; i++)
                {
                    for (size_t j = 0; j < K; j++)
                    {
                        res[i][j] = (*this)[i][j] + x[i][j];
                    }
                }
                return res;
            }

            vector <T, N, K> operator-(const vector <T, N, K>& x) const
            {
                vector <T, N, K> res;
                for (size_t i = 0; i < N; i++)
                {
                    for (size_t j = 0; j < K; j++)
                    {
                        res[i][j] = (*this)[i][j] - x[i][j];
                    }
                }
                return res;
            }
        };
    }
}
#pragma endregion


using namespace std;
using ll = long long;
using ld = long double;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
    std::Math::vector <float, 3, 2> a;
    a.print(cout);
    std::Math::vector <float, 1, 3> pt = { {2,3,1} };
    pt.print(cout);
    a = { {1,0},{0,1},{1,1} };
    (pt * a).print(cout);
    a = std::Math::vector <float, 3, 2>(1);
    (pt * a).print(cout);
    // test binary multiplication
    std::Math::vector <float, 3, 3> x = { {0.7,0.1,0.2},{0.05,0.35,0.6},{0.25,0.55,0.2} };
    x.print(cout);
    for (size_t i = 0; i < 10; i++)
    {
        x = x * x;
    }
    x.print(cout);
    (pt * x).print(cout);
    x = { {0.5,0.5,0},{0.5,0.5,0},{1,0,0} };
    x.print(cout);
    for (size_t i = 0; i < 1000; i++)
    {
        x = x * x;
    }
    x.print(cout);
    (pt * x).print(cout);
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
