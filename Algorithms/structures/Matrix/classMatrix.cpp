#include <bits/stdc++.h>
#include "matrix.h"

int main()
{
    matrix<int> a(2, 2, 1), b(2, 2, 1);

    a.print("matrix a:");
    b.print("matrix b:");
    std::cout << std::endl;

    a *= b;
    a.print("matrix a after \"a *= b\":");
    b.print("matrix b after \"a *= b\":");
    std::cout << std::endl;

    auto c = a + b;
    c.print("matrix c = (a + b):");
    std::cout << std::endl;

    matrix<int>::print(a + b, "(a + b) =");
    std::cout << std::endl;

    auto d = a * b;
    d.print("matrix (a * b)");

    a *= b;
    a.print("matrix a after \"a *= b\":");
    b.print("matrix b after \"a *= b\":");

    a = matrix(2, 2, 1);
    a.print("new a:");

    b ^= 4;
    b.print("b mat powered to 5");

    c = a ^ 5;
    c.print("a ^ 5:");

    a += static_cast<matrix<int>>(std::vector<std::vector<int>>({{1, 0}, {1, 2}}));
    a.print("a += {{1, 0}, {1, 2}}");

    a ^= 2;
    a.print("a after (a ^= 2):");

    matrix<int> e = (std::vector<std::vector<int>>({{1, 0}, {1, 2}}));
    matrix<int>::print(e, "matrix e:");

    matrix<int>::print(2 * (matrix<int>(std::vector<std::vector<int>>({{2, 0}, {7, 3}}))
    + matrix<int>(std::vector<std::vector<int>>({{1, 0}, {1, 2}})))
    , "2 * ({2, 0}, {7, 3}} + {{1, 0}, {1, 2}}) = ");


    matrix<int> f({1, 0, 0, 1}, 2, 2);
    matrix<int>::print(f, "f created by list: ");

    std::vector<std::vector<int>> mat(3, std::vector<int> (4, 10));
    matrix g = mat;

    if(g == mat)
    {
        std::cout << "g is equal to mat" << std::endl;
    }
    g.print("matrix g:");
    int divisor = 2;
    g /= 5;
    g.print("g / 5:");
    g /= divisor;
    g.print("g / 5 / 2:");
    g.clear();
    g.print("is g clear?");
    std::cout << g.size() << std::endl;
    return 0;
}