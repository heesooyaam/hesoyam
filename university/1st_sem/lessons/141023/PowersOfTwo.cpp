#include <iostream>
#include <algorithm>
using namespace std;


class PowersOfTwo {
private:
    int max_power;
public:
    class iterator {
        private:
            int current_power;

        public:
            using iterator_category = std::bidirectional_iterator_tag;
            using difference_type   = std::ptrdiff_t;
            using value_type        = int;
            using pointer           = int*;
            using reference         = int&;

            iterator(int power_of_two) : current_power(power_of_two) {}

            value_type operator*() const {
                return 1 << current_power;
            }

            iterator operator--() {
                current_power -= 1;
                return *this;
            }

            iterator operator++() {
                current_power += 1;
                return *this;
            }

            difference_type operator-(const iterator& other) const {
                return current_power - other.current_power;
            }

            bool operator!=(const iterator& other) const {
                return current_power != other.current_power;
            }
    };

    PowersOfTwo(int _max_power) : max_power(_max_power) {};

    iterator begin() const {
        return iterator(0);
    }

    iterator end() const {
        return iterator(max_power + 1);
    }
};


int main() {
    PowersOfTwo iterable(10);

    auto it1 = iterable.begin();
    auto it2 = next(next(next(it1)));

    cout << distance(it1, it2) << endl;
}