#include <iostream>
#include <vector>
using namespace std;

class Multiplicator {
private:
    const vector<int>& v;

public:
    class iterator {
    private:
        vector<int>::const_iterator it;
    public:
        iterator(vector<int>::const_iterator _it) : it(_it) {}

        int operator*() const {
            return (*it) * 2;
        }

        iterator operator++() {
            return ++it;
        }

        bool operator!=(const iterator& other) const {
            return it != other.it;
        }
    };

    Multiplicator(const vector<int>& _v) : v(_v) {}

    iterator begin() const {
        return iterator(v.begin());
    }

    iterator end() const {
        return iterator(v.end());
    }
};

int main() {
    vector<int> v = {1, 2, 3};
    Multiplicator m(v);

    for (int mi : m) {
        cout << mi << ' ';
    }
    cout << endl;
}