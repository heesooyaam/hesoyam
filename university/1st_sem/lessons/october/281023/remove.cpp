#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void DeleteSomeNumbersFromVector (vector<int>& a, bool even)
{
    a.erase(remove_if(a.begin(), a.end(), [even](int x) {return x % 2 == (((int) even) ^ 1);}));
}

int main()
{
    return 0;
}