#include <bits/stdc++.h>
using namespace std;

struct SegTree
{
    struct Node
    {
        int mn;
    };
    SegTree(const vector<int>& vec)
    : tree(vec.size() << 2)
    {}
    Node combine(const Node& l, const Node& r)
    {
        return {.mn = min(l.mn, r.mn)};
    }
    void build(int index, int l, int r, const vector<int>& vec)
    {
        if(l >= r) return;
        if(l + 1 == r)
        {
            tree[index] = {.mn = vec[l]};
            return;
        }
        int mid = (l + r) / 2;
        build((index << 1) + 1, l, mid, vec);
        build((index << 1) + 2, mid, r, vec);
        tree[index] = combine(tree[(index << 1) + 1], tree[(index << 1) + 2]);
    }
    int get(int l, int r)
    {
        return get(l, r, 0, 0, tree.size()).mn;
    }
    Node get(int l, int r, int i, int cl, int cr)
    {
        if(l >= r)
        {
            return { .mn = INT_MAX};
        }
        if(l == cl && r == cr)
        {
            return tree[i];
        }
        int mid = (cl + cr) >> 1;
        return combine
        (get(l, min(mid, r), (i << 1) + 2, cl, mid),
        get(max(l, mid), r, (i << 1) + 2, mid, cr));
    }
    void update(int pos, int val)
    {
        update(pos, val, 0, 0, );
    }
    void update(int pos, int val, int i, int l, int r)
    {
        if(l + 1 == r)
        {
            tree[i].mn = val;
            return;
        }
        int mid = (l + r) >> 1;
        if(pos < mid)
        {
            update(pos, val, (i << 1) + 1, l, mid);
        }
        else
        {
            update(pos, val, (i << 1) + 2, mid, r);
        }
        tree[i] = combine(tree[(i << 1) + 1], tree[(i << 1) + 2]);
    }
private:
    vector<Node> tree;
};