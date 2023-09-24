#include <bits/stdc++.h>

using namespace std;
char* func_3(char* a)
{
    int i = 1;
    for(; *(a++) != 0; i++) {}
    return --a - i / 2;
}
int main()
{
    /*
    2nd
    int a = 0;
    float b = 0;
    void* pointer = &a;
    *((int*) pointer) = 3;
    pointer = &b;
    *((float*) pointer) = 3.4;
    std::cout << a << ' ' << b << std::endl;
    */
    int n; cin >> n;
    char a[n];
    for(int i = 0; i < n - 1; i++)
    {
        cin >> a[i];
    }
    a[n - 1] = 0;
    cout << *func_3(&a[0]) << endl;
    return 0;
}
