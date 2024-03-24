#include <cassert>
#include <iostream>
#include <optional>
#include <random>
#include <vector>

using namespace std;

struct TTreapNode
{
    int Count;
    int Value;
    int Priority;
    int Left;
    int Right;
};

int GeneratePriority()
{
    static std::mt19937 Generator(42);
    return std::uniform_int_distribution<int>()(Generator);
}

class TTreap
{
public:
    void PushBack(int value)
    {
        Nodes_.emplace_back();

        auto& newNode = Nodes_.back();
        newNode.Count = 1;
        newNode.Value = value;
        newNode.Priority = GeneratePriority();
        newNode.Left = newNode.Right = -1;

        Root_ = Merge(Root_, Nodes_.size() - 1);
    }

    int Get(int key)
    {
        assert(0 <= key);
        assert(key < (int) Nodes_.size());

        int current = Root_;
        while (true) {
            int currentKey = GetCount(Nodes_[current].Left);
            if (key == currentKey) {
                return Nodes_[current].Value;
            } else if (key < currentKey) {
                current = Nodes_[current].Left;
            } else {
                key -= (currentKey + 1);
                current = Nodes_[current].Right;
            }
        }
    }

    void MoveToFront(int l, int r)
    {
        assert(0 <= l && l <= r && r < (int) Nodes_.size());
        if (l == 0) {
            return;
        }

        auto [left, middleRight] = Split(Root_, l - 1);
        auto [middle, right] = Split(middleRight, r - l);

        Root_ = Merge(middle, Merge(left, right));
    }

private:
    std::vector<TTreapNode> Nodes_;

    int Root_ = -1;

    int GetCount(int root) const
    {
        return root == -1 ? 0 : Nodes_[root].Count;
    }

    void UpdateCount(int root)
    {
        Nodes_[root].Count = 1 + GetCount(Nodes_[root].Left) + GetCount(Nodes_[root].Right);
    }

    std::pair<int, int> Split(int current, int key)
    {
        if (current == -1) {
            return {-1, -1};
        }
        int currentKey = GetCount(Nodes_[current].Left);
        if (currentKey <= key) {
            key -= (currentKey + 1);
            auto [rightLeft, rightRight] = Split(Nodes_[current].Right, key);
            Nodes_[current].Right = rightLeft;
            UpdateCount(current);
            return {current, rightRight};
        } else {
            auto [leftLeft, leftRight] = Split(Nodes_[current].Left, key);
            Nodes_[current].Left = leftRight;
            UpdateCount(current);
            return {leftLeft, current};
        }
    }

    int Merge(int left, int right)
    {
        if (left == -1) {
            return right;
        }
        if (right == -1) {
            return left;
        }
        if (Nodes_[left].Priority >= Nodes_[right].Priority) {
            Nodes_[left].Right = Merge(Nodes_[left].Right, right);
            UpdateCount(left);
            return left;
        } else {
            Nodes_[right].Left = Merge(left, Nodes_[right].Left);
            UpdateCount(right);
            return right;
        }
    }
};

int n, m;
vector<pair<int, int>> qs;

void Solve()
{
    TTreap t;
    for (int i = 1; i <= n; ++i) {
        t.PushBack(i);
    }

    for (int i = 0; i < m; ++i) {
        t.MoveToFront(qs[i].first, qs[i].second);
    }

    for (int i = 0; i < n; ++i) {
        cout << t.Get(i) << " ";
    }
    cout << endl;
}

bool Read()
{
    if (!(cin >> n >> m)) {
        return false;
    }
    qs.resize(m);
    for (int i = 0; i < m; ++i) {
        cin >> qs[i].first >> qs[i].second;
        --qs[i].first;
        --qs[i].second;
    }
    return true;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    freopen("movetofront.in", "r", stdin);
    // freopen("movetofront.out", "w", stdout);

    while (Read()) {
        Solve();
    }

    return 0;
}