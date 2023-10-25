#include <iostream>
struct C
{
    void foo()
    {
        std::cout << "a->foo() <=> ((a.b).c).foo()" << std::endl;
    }
    C* operator ->()
    {
        return this;
    }
};
struct B
{
    C& c;
    C& operator ->()
    {
        return c;
    }
};
struct A
{
    B& b;
    B operator ->()
    {
        return b;
    }
};
int main()
{
    C c;
    B b {c};
    A a {b};

    a->foo();

    return 0;
}