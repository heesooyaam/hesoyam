#include <map>
#include <iostream>
#include <utility>
using namespace std;

template<class K, class V>
class DoubleMap
{
    private:
        using InnerMap = map<K, V>;
        using OutterMap = map<K, InnerMap>;
        //using type_1 = type_2

        OutterMap storage;

    public:
        class iterator
        {
            private:
                using InnerIterator = typename InnerMap::iterator;
                using OutterIterator = typename OutterMap::iterator;

                InnerIterator in_it;
                OutterIterator out_it;
            public:
                iterator(const InnerIterator& _in_it, const OutterIterator& _out_it)
                : in_it(_in_it)
                , out_it(_out_it)
                {}

                pair<K, pair<K, V>> operator *()const
                {
                    return {out_it->first, {in_it->first, in_it->second}};
                }

                bool operator != (const iterator& other)
                {
                    return out_it != other.out_it || in_it != other.in_it;
                }

                iterator operator ++()
                {
                    ++in_it;
                    if(in_it != out_it.sexond.end()) return *this;
                }
        };
        iterator begin() const
        {
            return iterator(storage.begin()->second.begin(), storage.begin());
        }
        iterator end() const
        {
            return iterator(iterator::InnerIterator(), storage.end());
        }
};
int main()
{
    return 0;
}