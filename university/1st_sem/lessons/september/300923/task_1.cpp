#include <bits/stdc++.h>
using namespace std;

template <class T>
T middle(const T& a, const T& b, const T& c)
{
    return ((b <= a && a <= c || c <= a && a <= b) ? a : ((a <= b && b <= c || c <= b && b <= a) ? b : c));
}

template <typename T>
class point
{
    public:
        T x;
        T y;
        T z;
        point() = default;
        point(T& a, T& b, T& c)
        {
            x = a;
            y = b;
            z = c;
        }

        bool operator < (point Q) const
        {
            return(1ll * x * x + y * y + z * z < 1ll * Q.x * Q.x + Q.y * Q.y + Q.z * Q.z);
        }
        bool operator == (point Q) const
        {
            return(1ll * x * x + y * y + z * z == 1ll * Q.x * Q.x + Q.y * Q.y + Q.z * Q.z);
        }
        bool operator <= (point Q) const
        {
            return (*this == Q or *this < Q);
        }
};

int main()
{
    /*
    vector<pair<int, int>> m(3);
    for(int i = 0; i < 3; ++i)
    {
        int x, y;
        cin >> x >> y;
        m[i] = {x, y};
    }
    auto mid = middle(m[0], m[1], m[2]);
    cout << mid.first << ' ' << mid.second << endl;*/
    vector<point<int>> pt(3);
    for(int i = 0; i < 3; ++i)
    {
        cin >> pt[i].x >> pt[i].y >> pt[i].z;
    }
    auto mid = middle(pt[0], pt[1], pt[2]);
    cout << mid.x << ' ' << mid.y << ' ' << mid.z << endl;
}