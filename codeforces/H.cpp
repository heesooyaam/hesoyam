//
// Created by topcr on 04.04.2024.
//
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define eb emplace_back
#define pb push_back
#define pf push_front
#define ppb pop_back
#define ppf pop_front
#define ss second
#define ff first
#define mp make_pair
#define all(x) (x).begin(),(x).end()
#define print(x); for(auto& val : x){cout << val << ' ';}cout << endl;
#define input(x); for(auto& val : x){cin >> val;}
#define make_unique(x) sort(all((x))); (x).resize(unique(all((x))) - (x).begin())
#define endl '\n'

ld find_len(vector<ld>& r1, vector<ld>& r2)
{
    return sqrtl((r1[0] - r2[0]) * (r1[0] - r2[0]) + (r1[1] - r2[1]) * (r1[1] - r2[1]) + (r1[2] - r2[2]) * (r1[2] - r2[2]));
}

ld find_len(vector<ld>& l)
{
    return sqrtl(l[0] * l[0] + l[1] * l[1] + l[2] * l[2]);
}

ld scalar(vector<ld>& l1, vector<ld>& l2) {
    return l1[0] * l2[0] + l1[1] * l2[1] + l1[2] * l2[2];
}

ld mult(vector<ld>& a, vector<ld>& b) {
    vector<ld> res = {a[1] * b[2] - a[2] * b[1], a[2] * b[0] - a[0] * b[2], a[0] * b[1] - a[1] * b[0]};
    return find_len(res);
}

vector<ld> find_r(ld xa, ld ya, ld za, ld xb, ld yb, ld zb, ld xc, ld yc, ld zc)
{
    vector<ld> A = {xa, ya, za};
    vector<ld> B = {xb, yb, zb};
    vector<ld> C = {xc, yc, zc};
    vector<ld> ab = {xb - xa, yb - ya, zb - za};
    vector<ld> ac = {xc - xa, yc - ya, zc - za};


    ld AB = find_len(A, B);
    ld AC = find_len(A, C);
    ld BC = find_len(B, C);
    vector<ld> l = {(xb - xa) / AB + (xc - xa) / AC, (yb - ya) / AB + (yc - ya) / AC, (zb - za) / AB + (zc - za) / AC};
    ld len_l = find_len(l);
    l[0] /= len_l;
    l[1] /= len_l;
    l[2] /= len_l;

    ld AO = mult(ab, ac) * sqrtl(2.0) * AB * AC / (AB + AC + BC) / (AB * AC - scalar(ab, ac));
    l[0] *= AO;
    l[1] *= AO;
    l[2] *= AO;
    l[0] += xa;
    l[1] += ya;
    l[2] += za;
    return l;
}

vector<ld> multt(vector<ld>& a, vector<ld>& b) {
    return {a[1] * b[2] - a[2] * b[1], a[2] * b[0] - a[0] * b[2], a[0] * b[1] - a[1] * b[0]};
}

long double xuy(ld a) {
    if (a < 0) return -a;
    return a;
}

ld dist(vector<ld>& now, vector<ld>& A, vector<ld>& B, vector<ld>& C) {
    vector<ld> ac = {C[0] - A[0], C[1] - A[1], C[2] - A[2]};
    vector<ld> ab = {B[0] - A[0], B[1] - A[1], B[2] - A[2]};

    vector<ld> norm = multt(ac, ab);

    return xuy((norm[0] * (now[0] - B[0]) + norm[1] * (now[1] - B[1]) + norm[2] * (now[2] - B[2]))) / (find_len(norm));
}


const ld eps = 1e-6;

void solve()
{
    ld xa1, ya1, xb1, yb1, xc1, yc1; cin >> xa1 >> ya1 >> xb1 >> yb1 >> xc1 >> yc1;
    ld xp, yp, zp; cin >> xp >> yp >> zp;
    zp = xuy(zp);
    ld h; cin >> h;
    ld xa2 = (h - zp) / (-zp) * (xa1 - xp) + xp;
    ld ya2 = (h - zp) / (-zp) * (ya1 - yp) + yp;
    ld za2 = h;

    ld xb2 = (h - zp) / (-zp) * (xb1 - xp) + xp;
    ld yb2 = (h - zp) / (-zp) * (yb1 - yp) + yp;
    ld zb2 = h;

    ld xc2 = (h - zp) / (-zp) * (xc1 - xp) + xp;
    ld yc2 = (h - zp) / (-zp) * (yc1 - yp) + yp;
    ld zc2 = h;

    vector<ld> r1 = find_r(xa1, ya1, 0, xb1, yb1, 0, xc1, yc1, 0);
    vector<ld> r2 = find_r(xa2, ya2, h, xb2, yb2, h, xc2, yc2, h);

    vector<ld> A1 = {xa1, ya1, 0};
    vector<ld> B1 = {xb1, yb1, 0};
    vector<ld> C1 = {xc1, yc1, 0};
    vector<ld> A2 = {xa2, ya2, h};
    vector<ld> B2 = {xb2, yb2, h};
    vector<ld> C2 = {xc2, yc2, h};
    vector<ld> P = {xp, yp, zp};

    ld LEN = find_len(r1, r2);
    ld l = 0, r = h;
    while (r - l > eps) {
        ld mid = (l + r) / 2;
        ld x = (h - mid) / h * (r2[0] - r1[0]) + r1[0];
        ld y = (h - mid) / h * (r2[1] - r1[1]) + r1[1];
        ld z = h - mid;
        vector<ld> point = {x, y, z};

        ld res1 = dist(point, A1, B1, P);
        ld res2 = dist(point, B1, C1, P);
        ld res3 = dist(point, A1, C1, P);

        if (min({res1, res2, res3}) <= mid) {
            r = mid;
        } else {
            l = mid;
        }
    }
    cout << l << endl;
    cout << fixed << setprecision(6) << 4.0 / 3.0 * 3.14159265358979323846 * l * l * l;
}
int32_t main()
{
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0);
    int ttest = 1;
//    cin >> ttest;
    while(ttest--) solve();
    return 0;
}