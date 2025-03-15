#include <bits/stdc++.h>
using namespace std;

template<typename T = uint32_t, const uint32_t MAX_POWER = 8 * sizeof(T)>
class XORedMultiNumericTrie
{
private:
    using ui = uint32_t;
    struct Node
    {
        /*
         *  root-Node constructor
         */
        Node()
        : child({0, 0})
        , sheets(0)
        , unique_sheets(0) {}

        /*
         *  bit-Node constructor
         */
        explicit Node(bool bit)
        : child({0, 0})
        , sheets(1)
        , unique_sheets(1) {}

        ui& operator[](bool bit)
        {
            return this->child[bit];
        }
        ui operator[](bool bit) const
        {
            return this->child[bit];
        }
        ui sheets;
        ui unique_sheets;
        array<ui, 2> child;
    };

    vector<Node> tree;
    T xor_;

public:

    XORedMultiNumericTrie()
    : xor_(0) {
        tree.emplace_back();
    }

    explicit XORedMultiNumericTrie(const ui& waited_size)
    : xor_(0)
    {
        if(waited_size) tree.reserve(waited_size + 1);
        tree.emplace_back();
    }

    /*
     *  returns the smallest value not greater than 'x'
     */
    T MEX() const
    {
        ui idx = 0;
        T MEX = 0;

        for(int i = 0; i < MAX_POWER; ++i)
        {
            bool left = get_bit(xor_, i);

            if(!is_subtree_full(tree[idx][left], i + 1))
            {
                if(!is_child_alive(idx, left))
                {
                    return MEX;
                }
                idx = tree[idx][left];
            }
            else
            {
                set_bit(MEX, i, 1);

                if(!is_child_alive(idx, !left))
                {
                    return MEX;
                }
                idx = tree[idx][!left];
            }
        }

        return MEX;
    }

    /*
     *  returns the smallest value not greater than 'x'
     */
    T lower_bound(const T& x) const
    {
        ui idx = 0, last_greater = numeric_limits<ui>::max();

        bool equal = true;

        for(int i = 0; i < MAX_POWER && equal; ++i)
        {
            bool bit = get_bit(x, i) ^ get_bit(xor_, i);

            if(!get_bit(x, i) && is_child_alive(idx, 1 ^ get_bit(xor_, i)))
            {
                last_greater = idx;
            }

            if(is_child_alive(idx, bit))
            {
                idx = tree[idx][bit];
            }
            else
            {
                equal = false;
            }
        }

        if(equal) return x;

        if(last_greater == numeric_limits<ui>::max()) return numeric_limits<T>::max();


        int i = 0;
        idx = 0;
        T number = 0;

        for(; i < MAX_POWER && idx != last_greater; ++i)
        {
            for(const auto& child : tree[idx].child)
            {
                if(child == last_greater)
                {
                    set_bit(number, i, 1);
                    idx = last_greater;
                    break;
                }
            }

            if(idx != last_greater)
            {
                bool bit = get_bit(x, i) ^ get_bit(xor_, i);

                idx = tree[idx][bit];
                set_bit(number, i, get_bit(x, i));
            }
        }

        for(; i < MAX_POWER; ++i)
        {
            bool bit = get_bit(xor_, i);

            if(is_child_alive(idx, bit))
            {
                set_bit(number, i, 0);
                idx = tree[idx][bit];
            }
            else
            {
                set_bit(number, i, 1);
                idx = tree[idx][!bit];
            }
        }

        return number;
    }

    /*
     *  returns amount of values not less than 'x'
     */
    ui greater(const T& x) const
    {
        return not_less(x + 1);
    }

    /*
     *  returns amount of values not less than 'x'
     */
    ui not_less(const T& x) const
    {
        ui idx = 0;
        ui cnt = 0;
        bool equal = true;
        for(int i = 0; i < MAX_POWER && equal; ++i)
        {
            bool bit = get_bit(x, i) ^ get_bit(xor_, i);

            if(!get_bit(x, i) && is_child_alive(idx, !bit))
            {
                cnt += tree[tree[idx][!bit]].sheets;
            }

            if(is_child_alive(idx, bit))
            {
                idx = tree[idx][bit];
            }
            else
            {
                equal = false;
            }
        }

        return cnt + (equal ? tree[idx].sheets : 0);
    }

    /*
     *  returns amount of elements in segment [l, r]
     */
    ui numbers_in(const T& l, const T& r) const
    {
        return not_less(l) - not_less(r + 1);
    }

    /*
     *  returns element which gives the biggest xor with 'x'
     */
    T max_xor(const T& x) const
    {
        ui idx = 0;
        ui number = 0;
        for(int i = 0; i < MAX_POWER; ++i)
        {
            bool bit = !get_bit(x, i) ^ get_bit(xor_, i);
            if(is_child_alive(idx, bit))
            {
                set_bit(number, i, !get_bit(x, i));
                idx = tree[idx][bit];
            }
            else
            {
                set_bit(number, i, get_bit(x, i));
                idx = tree[idx][!bit];
            }
        }
        return number;
    }

    /*
     *  returns element which gives the smallest xor with 'x'
     */
    T min_xor(const T& x) const
    {
        ui idx = 0;
        ui number = 0;
        for(int i = 0; i < MAX_POWER; ++i)
        {
            bool bit = get_bit(x, i) ^ get_bit(xor_, i);
            if(is_child_alive(idx, bit))
            {
                set_bit(number, i, get_bit(x, i));
                idx = tree[idx][bit];
            }
            else
            {
                set_bit(number, i, !get_bit(x, i));
                idx = tree[idx][!bit];
            }
        }
        return number;
    }

    /*
     *  returns maximum elemnt in trie
     */
    T max() const
    {
        ui idx = 0;
        ui number = 0;
        for(int i = 0; i < MAX_POWER; ++i)
        {
            bool bit = !get_bit(xor_, i);
            if(is_child_alive(idx, bit))
            {
                set_bit(number, i);
                idx = tree[idx][bit];
            }
            else
            {
                set_bit(number, i, 0);
                idx = tree[idx][!bit];
            }
        }
        return number;
    }

    /*
     *  returns minimum element in trie
     */
    T min() const
    {
        ui idx = 0;
        ui number = 0;
        for(int i = 0; i < MAX_POWER; ++i)
        {
            bool bit = get_bit(xor_, i);
            if(is_child_alive(idx, bit))
            {
                set_bit(number, i, 0);
                idx = tree[idx][bit];
            }
            else
            {
                set_bit(number, i);
                idx = tree[idx][!bit];
            }
        }
        return number;
    }

    /*
     *  returns amount of element 'x' in trie
     */
    ui amount(T x) const
    {
        x ^= xor_;

        ui idx = 0;
        bool new_number;
        for(int i = 0; i < MAX_POWER; ++i)
        {
            bool bit = get_bit(x, i);
            new_number = !is_child_alive(idx, bit);
            if(new_number) return !new_number;
            idx = tree[idx][bit];
        }
        return !new_number ? tree[idx].sheets : 0;
    }

    /*
     *  returns amount of all elements in trie
     */
    size_t size() const
    {
        return tree.front().sheets;
    }

    /*
     *  XOR all numbers with x
     */
    void XOR(const T& x)
    {
        xor_ ^= x;
    }

    /*
     *  increases amount of elemnts 'x' in trie and returns it
     */
    ui insert(T x)
    {
        bool add_unique = !amount(x);

        x ^= xor_;

        ui idx = 0;
        tree[idx].sheets += 1;
        tree[idx].unique_sheets += add_unique;

        for(int i = 0; i < MAX_POWER; ++i)
        {
            bool bit = get_bit(x, i);
            idx = add_child(idx, bit, add_unique);
        }

        return true;
    }

    /*
     *  increases amount of elemnts 'x' in trie and returns it
     *  !!! if there are no 'x'-s in trie, returns 0 and does nothing
     */
    ui erase(T x)
    {
        ui amount = amount(x);

        if(!amount) return 0;

        bool remove_unique = amount(x) == 1;

        x ^= xor_;
        ui idx = 0;
        ui start = 0;
        ui power = 0;
        for(int i = 0; i < MAX_POWER; ++i)
        {
            if(are_both_children_alive(idx))
            {
                tree[idx].sheets -= 1;
                tree[idx].unique_sheets -= remove_unique;
                start = idx;
                power = i;
            }
            idx = tree[idx][get_bit(x, i)];
        }

        idx = start;
        while(tree[idx][0] + tree[idx][1])
        {
            idx = delete_child(idx, get_bit(x, power++), remove_unique);
        }

        return tree[idx].sheets;
    }

    /*
     *  same as XOR(T x)
     */
    void operator^=(const T& x)
    {
        XOR(x);
    }

private:

    /*
     *  returns bit on position 'idx' of number 'x'
     */
    bool get_bit(const T& x, const ui& index) const {
        return (x >> (MAX_POWER - index - 1)) & 1;
    }

    /*
     *  sets bit in number 'x' on position 'index'
     */
    void set_bit(T& x, const ui& index, bool bit = true) const
    {
        if(bit) x |= (T(1) << (MAX_POWER - index - 1));
        else x &= ~(T(0)) - (T(0) << (MAX_POWER - index - 1));
    }

    /*
     *  returns index in 'tree' of new vertex
     */
    ui add_child(const ui& parent, bool bit, const bool& add_unique) {
        if(has_child(parent, bit))
        {
            tree[tree[parent][bit]].sheets += 1;
            tree[tree[parent][bit]].unique_sheets += add_unique;

            return tree[parent][bit];
        }
        else
        {
            tree.emplace_back(bit);
            return tree[parent][bit] = tree.size() - 1;
        }
    }

    /*
     *  returns idx of deleted child
     */
    ui delete_child(const ui& parent, bool bit, const bool& remove_unique)
    {
        tree[tree[parent][bit]].sheets -= 1;
        tree[tree[parent][bit]].unique_sheets -= remove_unique;

        return tree[parent][bit];
    }

    /*
     *  returns true if child has already been made, else - false
     */
    bool has_child(const ui& idx, bool bit) const
    {
        return tree[idx][bit];
    }

    /*
     *  returns true if child is alive now, else - false
     */
    bool is_child_alive(const ui& idx, bool bit) const
    {
        return tree[idx][bit] && tree[tree[idx][bit]].sheets;
    }

    /*
     *  returns true if both children are alive now, else - false
     */
    bool are_both_children_alive(const ui& idx) const
    {
        return is_child_alive(idx, 0) && is_child_alive(idx, 1);
    }

    bool is_subtree_full(const ui& idx, const ui& power) const
    {
        return (idx) ? (tree[idx].unique_sheets == (((T) 1) << (MAX_POWER - power))) : false;
    }
};
#define MULTIBOR XORedMultiNumericTrie

template<typename T = uint32_t, const uint32_t MAX_POWER = 8 * sizeof(T)>
class XORedNumericTrie
{
private:
    using ui = uint32_t;
    struct Node
    {
        /*
         *  root-Node constructor
         */
        Node()
        : child({0, 0})
        , unique_sheets(0) {}

        /*
         *  bit-Node constructor
         */
        explicit Node(bool bit)
        : child({0, 0})
        , unique_sheets(1) {}

        ui& operator[](bool bit)
        {
            return this->child[bit];
        }
        ui operator[](bool bit) const
        {
            return this->child[bit];
        }
        ui unique_sheets;
        array<ui, 2> child;
    };

    vector<Node> tree;
    T xor_;

public:

    XORedNumericTrie()
    : xor_(0) {
        tree.emplace_back();
    }

    explicit XORedNumericTrie(const ui& waited_size)
    : xor_(0)
    {
        if(waited_size) tree.reserve(waited_size + 1);
        tree.emplace_back();
    }

    /*
     *  returns the smallest value not greater than 'x'
     */
    T MEX() const
    {
        ui idx = 0;
        T MEX = 0;

        for(int i = 0; i < MAX_POWER; ++i)
        {
            bool left = get_bit(xor_, i);

            if(!is_subtree_full(tree[idx][left], i + 1))
            {
                if(!is_child_alive(idx, left))
                {
                    return MEX;
                }
                idx = tree[idx][left];
            }
            else
            {
                set_bit(MEX, i, 1);

                if(!is_child_alive(idx, !left))
                {
                    return MEX;
                }
                idx = tree[idx][!left];
            }
        }

        return MEX;
    }

    /*
     *  returns the smallest value not greater than 'x'
     */
    T lower_bound(const T& x) const
    {
        ui idx = 0, last_greater = numeric_limits<ui>::max();

        bool equal = true;

        for(int i = 0; i < MAX_POWER && equal; ++i)
        {
            bool bit = get_bit(x, i) ^ get_bit(xor_, i);

            if(!get_bit(x, i) && is_child_alive(idx, 1 ^ get_bit(xor_, i)))
            {
                last_greater = idx;
            }

            if(is_child_alive(idx, bit))
            {
                idx = tree[idx][bit];
            }
            else
            {
                equal = false;
            }
        }

        if(equal) return x;

        if(last_greater == numeric_limits<ui>::max()) return numeric_limits<T>::max();


        int i = 0;
        idx = 0;
        T number = 0;

        for(; i < MAX_POWER && idx != last_greater; ++i)
        {
            for(const auto& child : tree[idx].child)
            {
                if(child == last_greater)
                {
                    set_bit(number, i, 1);
                    idx = last_greater;
                    break;
                }
            }

            if(idx != last_greater)
            {
                bool bit = get_bit(x, i) ^ get_bit(xor_, i);

                idx = tree[idx][bit];
                set_bit(number, i, get_bit(x, i));
            }
        }

        for(; i < MAX_POWER; ++i)
        {
            bool bit = get_bit(xor_, i);

            if(is_child_alive(idx, bit))
            {
                set_bit(number, i, 0);
                idx = tree[idx][bit];
            }
            else
            {
                set_bit(number, i, 1);
                idx = tree[idx][!bit];
            }
        }

        return number;
    }

    /*
     *  returns amount of values not less than 'x'
     */
    ui greater(const T& x) const
    {
        return not_less(x + 1);
    }

    /*
     *  returns amount of values not less than 'x'
     */
    ui not_less(const T& x) const
    {
        ui idx = 0;
        ui cnt = 0;
        bool equal = true;
        for(int i = 0; i < MAX_POWER && equal; ++i)
        {
            bool bit = get_bit(x, i) ^ get_bit(xor_, i);

            if(!get_bit(x, i) && is_child_alive(idx, !bit))
            {
                cnt += tree[tree[idx][!bit]].unique_sheets;
            }

            if(is_child_alive(idx, bit))
            {
                idx = tree[idx][bit];
            }
            else
            {
                equal = false;
            }
        }

        return cnt + (equal ? tree[idx].sheets : 0);
    }

    /*
     *  returns amount of elements in segment [l, r]
     */
    ui numbers_in(const T& l, const T& r) const
    {
        return not_less(l) - not_less(r + 1);
    }

    /*
     *  returns element which gives the biggest xor with 'x'
     */
    T max_xor(const T& x) const
    {
        ui idx = 0;
        ui number = 0;
        for(int i = 0; i < MAX_POWER; ++i)
        {
            bool bit = !get_bit(x, i) ^ get_bit(xor_, i);
            if(is_child_alive(idx, bit))
            {
                set_bit(number, i, !get_bit(x, i));
                idx = tree[idx][bit];
            }
            else
            {
                set_bit(number, i, get_bit(x, i));
                idx = tree[idx][!bit];
            }
        }
        return number;
    }

    /*
     *  returns element which gives the smallest xor with 'x'
     */
    T min_xor(const T& x) const
    {
        ui idx = 0;
        ui number = 0;
        for(int i = 0; i < MAX_POWER; ++i)
        {
            bool bit = get_bit(x, i) ^ get_bit(xor_, i);
            if(is_child_alive(idx, bit))
            {
                set_bit(number, i, get_bit(x, i));
                idx = tree[idx][bit];
            }
            else
            {
                set_bit(number, i, !get_bit(x, i));
                idx = tree[idx][!bit];
            }
        }
        return number;
    }

    /*
     *  returns maximum elemnt in trie
     */
    T max() const
    {
        ui idx = 0;
        ui number = 0;
        for(int i = 0; i < MAX_POWER; ++i)
        {
            bool bit = !get_bit(xor_, i);
            if(is_child_alive(idx, bit))
            {
                set_bit(number, i);
                idx = tree[idx][bit];
            }
            else
            {
                set_bit(number, i, 0);
                idx = tree[idx][!bit];
            }
        }
        return number;
    }

    /*
     *  returns minimum element in trie
     */
    T min() const
    {
        ui idx = 0;
        ui number = 0;
        for(int i = 0; i < MAX_POWER; ++i)
        {
            bool bit = get_bit(xor_, i);
            if(is_child_alive(idx, bit))
            {
                set_bit(number, i, 0);
                idx = tree[idx][bit];
            }
            else
            {
                set_bit(number, i);
                idx = tree[idx][!bit];
            }
        }
        return number;
    }

    /*
     *  returns amount of element 'x' in trie
     */
    bool contains(T x) const
    {
        x ^= xor_;

        ui idx = 0;
        bool new_number;
        for(int i = 0; i < MAX_POWER; ++i)
        {
            bool bit = get_bit(x, i);
            new_number = !is_child_alive(idx, bit);
            if(new_number) return false;
            idx = tree[idx][bit];
        }
        return true;
    }

    /*
     *  returns amount of all elements in trie
     */
    size_t size() const
    {
        return tree.front().unique_sheets;
    }

    /*
     *  XOR all numbers with x
     */
    void XOR(const T& x)
    {
        xor_ ^= x;
    }

    /*
     *  returns true if inserted succesfully, false if already exists
     */
    bool insert(T x)
    {
        if(contains(x)) return false;
        x ^= xor_;

        ui idx = 0;
        tree[idx].unique_sheets += 1;

        for(int i = 0; i < MAX_POWER; ++i)
        {
            bool bit = get_bit(x, i);
            idx = add_child(idx, bit);
        }

        return tree[idx].sheets;
    }

    /*
     *  return true if erased successfully, false if there is no 'x'
     */
    bool erase(T x)
    {
        if(!contains(x)) return false;

        x ^= xor_;
        ui idx = 0;
        ui start = 0;
        ui power = 0;
        for(int i = 0; i < MAX_POWER; ++i)
        {
            if(are_both_children_alive(idx))
            {
                tree[idx].unique_sheets -= 1;
                start = idx;
                power = i;
            }
            idx = tree[idx][get_bit(x, i)];
        }

        idx = start;
        while(tree[idx][0] + tree[idx][1])
        {
            idx = delete_child(idx, get_bit(x, power++));
        }

        return true;
    }

    /*
     *  same as XOR(T x)
     */
    void operator^=(const T& x)
    {
        XOR(x);
    }

private:

    /*
     *  returns bit on position 'idx' of number 'x'
     */
    bool get_bit(const T& x, const ui& index) const {
        return (x >> (MAX_POWER - index - 1)) & 1;
    }

    /*
     *  sets bit in number 'x' on position 'index'
     */
    void set_bit(T& x, const ui& index, bool bit = true) const
    {
        if(bit) x |= (T(1) << (MAX_POWER - index - 1));
        else x &= ~(T(0)) - (T(0) << (MAX_POWER - index - 1));
    }

    /*
     *  returns index in 'tree' of new vertex
     */
    ui add_child(const ui& parent, bool bit) {
        if(has_child(parent, bit))
        {
            tree[tree[parent][bit]].unique_sheets += 1;

            return tree[parent][bit];
        }
        else
        {
            tree.emplace_back(bit);
            return tree[parent][bit] = tree.size() - 1;
        }
    }

    /*
     *  returns idx of deleted child
     */
    ui delete_child(const ui& parent, bool bit)
    {
        tree[tree[parent][bit]].unique_sheets -= 1;

        return tree[parent][bit];
    }

    /*
     *  returns true if child has already been made, else - false
     */
    bool has_child(const ui& idx, bool bit) const
    {
        return tree[idx][bit];
    }

    /*
     *  returns true if child is alive now, else - false
     */
    bool is_child_alive(const ui& idx, bool bit) const
    {
        return tree[idx][bit] && tree[tree[idx][bit]].unique_sheets;
    }

    /*
     *  returns true if both children are alive now, else - false
     */
    bool are_both_children_alive(const ui& idx) const
    {
        return is_child_alive(idx, 0) && is_child_alive(idx, 1);
    }

    bool is_subtree_full(const ui& idx, const ui& power) const
    {
        return (idx) ? (tree[idx].unique_sheets == (((T) 1) << (MAX_POWER - power))) : false;
    }
};
#define BOR XORedNumericTrie
