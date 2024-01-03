#include <vector>
#include <map>
#include <bits/stdc++.h>
 
using namespace std;
 
// i -  (i << 1) + 1, (i << 1) + 2
 
// prefix (sum[0, pos])
// upd(l, r +=x )
// prefix[l] += x, prefix[r] -= x
// get(pos,)
// [l, r)
// prefix[r - 1] - prefix[l - 1]
 
// ЗАДАЧИ:
// 1) найти k-ый ноль
// 2) найти первый префикс с суммой >=x
// 3) подотрезок с макс суммой и set(pos, x) !!!
// 3) неявная реализация ДО
// 4) сжатие координат (пример задачи)
// 5) найти наидлиннейший подотрезок в массиве чисел, где все элементы имеют бит 1 в какой-то позиции
// 6) сведение задачи +на отрезке get в точке к задаче +в точке, get на отрезке (в прошлый раз скомкано вышло)
// 7) прикол с путями в дереве (???)
 
struct SegTree {
    struct Node {
        int ans;
        int sum;
        int suf;
        int pref;
        Node(int val = 0) {
            sum = val;
            val = max(val, 0);
            sum = val;
            suf = val;
            pref = val;
        }
    };
 
    SegTree(const vector<int>& vec) : vec(vec), tr(vec.size() << 2), n(vec.size()) {
        build(0, 0, vec.size(), vec);
    }
 
    Node combine(const Node& l, const Node& r) {
        Node res;
        res.sum = l.sum + r.sum;
        res.pref = max(l.pref, l.sum + r.pref);
        res.suf = max(r.suf, l.suf + r.sum);
        res.ans = max({l.ans, r.ans, l.suf + r.pref});
        return res;
    }
    
    void build(int index, int l, int r, const vector<int>& vec) {
        if (l + 1 == r) {
            tr[index] = Node(vec[l]);
            return;
        }
        int mid = (l + r) >> 1;
        build((index << 1) + 1, l, mid, vec);
        build((index << 1) + 2, mid, r, vec);
        tr[index] = combine(tr[(index << 1) + 1], tr[(index << 1) + 2]);
    }
 
    int get() {
        return tr[0].ans;
    }
 
    // // [l, r)
    // int get(int x, int k, int i, int cl, int cr) {
    //     if (tr[i].mp[x] < k) {
    //         return -1;
    //     }
    //     if (cl + 1 == cr) {
    //         return cl;
    //     }
    //     int mid = (cl + cr) >> 1;
    //     int left_count = tr[(i << 1) + 1].mp[x];
    //     if (left_count >= k) {
    //         return get(x, k, (i << 1) + 1, cl, mid);
    //     } else {
    //         return get(x, k - left_count, (i << 1) + 2, mid, cr);
    //     }
    // }
 
    void upd(int pos, int val) {
        upd(pos, val, 0, 0, n);
        // vec[pos] = val;
    }
 
    void upd(int pos, int val, int i, int l, int r) {
        if (l + 1 == r) {
            tr[i] = Node(val);
            return;
        }
        int mid = (l + r) >> 1;
        if (pos < mid) {
            upd(pos, val, (i << 1) + 1, l, mid);
        } else {
            upd(pos, val, (i << 1) + 2, mid, r);
        }
        tr[i] = combine(tr[(i << 1) + 1], tr[(i << 1) + 2]);
    }
private:
    std::vector<Node> tr;
    vector<int> vec;
    size_t n;
};
 
int main() {
    // vector<int> arr = {1, 2, 3, 5, 8};
    // SegTree 
}