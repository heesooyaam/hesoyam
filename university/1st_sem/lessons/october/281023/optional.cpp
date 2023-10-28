#include <iostream>
#include <vector>
#include <optional>
using namespace std;

template<typename IteratorT, class PredT, class T>
std::optional<typename IteratorT::value_type> FindValue(IteratorT begin, IteratorT end, PredT pred)
{
    IteratorT it = find_if(begin, end, pred);
    if(it != end)
    {
        return make_optional(*it);
    }
    return std::nullopt;
}

struct S1
{
    int a;
    bool b;
    int c;
};

int main()
{
    cout << sizeof(S1);
    return 0;
}