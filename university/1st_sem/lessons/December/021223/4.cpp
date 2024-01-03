#include <bits/stdc++.h>
#include <map>
 
using namespace std;
 
int MAX = 10;
 
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
// 3) подотрезок с макс суммой и set(pos, x)
// 3) неявная реализация ДО
// 4) сжатие координат (пример задачи)
// 5) найти наидлиннейший подотрезок в массиве чисел, где все элементы имеют бит 1 в какой-то позиции
// 6) сведение задачи +на отрезке get в точке к задаче +в точке, get на отрезке (в прошлый раз скомкано вышло)
// 7) прикол с путями в дереве (???)
 
 
// pos < 10^5
// pos < 10^18
 
// operations < 10^5
// set()
// get()
 
int index = 1; 
std::vector<Node> tr{MAX}; //(LOG MAX POS) * кол-во операций
 
struct SegTree {
    struct Node {
        Node* l = nullptr;
        Node* r = nullptr;
        int sum;
 
        void upd() {
            sum = (l == -1 ? 0 : tr[l].sum) + (r == -1 ? 0 : tr[r].sum);
        }
    };
 
    int getSum(Node* n) {
        return n == nullptr ? 0 : n->sum;
    }
 
    int newNode(int sum = 0) {
        tr[index].sum = sum;
        return index++;
    }
 
    SegTree(){};
 
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
 
    // [l, r)
    int get(int k, int i, int cl, int cr) {
        if (tr[i].s < k) {
            return -1;
        }
        if (cl + 1 == cr) {
            return cl;
        }
        int mid = (cl + cr) >> 1;
        int left_count = tr[(i << 1) + 1].mp[x];
        if (left_count >= k) {
            return get(x, k, (i << 1) + 1, cl, mid);
        } else {
            return get(x, k - left_count, (i << 1) + 2, mid, cr);
        }
    }
 
    using ll = long long;
 
    inline static int MAX2 = 1000l;
    void upd(ll pos, int val) {
        upd(pos, val, 0, 0, MAX2);
        // vec[pos] = val;
    }
 
    void upd(ll pos, int val, int i, ll l, ll r) {
        if (l + 1 == r) {
            tr[i].sum = val;
            return;
        }
        ll mid = (l + r) >> 1;
        if (pos < mid) {
            if (tr[i].l == -1) {
                tr[i].l = newNode();
            }
            upd(pos, val, tr[i].l, l, mid);
        } else {
            if (tr[i].r == -1) {
                tr[i].r = newNode();
            }
            upd(pos, val, tr[i].r, mid, r);
        }
        tr[i].upd();
    }
private:
    vector<int> vec;
    size_t n;
};
 
int main() {
    // vector<int> arr = {1, 2, 3, 5, 8};
    // SegTree 
}