#include <bits/stdc++.h>
#define ll long long
using namespace std;

const ll llINF = 9223372036854775807;

bool ok(ll& x)
{
    return x;
}

int main()

{
    ll l, r;
    l = 0; r = llINF;
    while(l + 1 < r)
    {
        ll mid = (l + r) / 2;
        if(ok(mid))
        {
            l = mid;
        }
        else{
            r = mid;
        }
    }
    if(ok(l)) cout << l;
    else cout << r;
}