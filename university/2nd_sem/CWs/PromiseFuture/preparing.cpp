//
// Created by topcr on 06.04.2024.
//
#include <vector>
#include <iostream>
#include <thread>
#include <future>
#include <shared_mutex>
#include <algorithm>
#include <numeric>
#include <cassert>
int main()
{
    std::vector<int> vec(1'00'000'000);
    std::iota(vec.begin(), vec.end(), 0);
    std::shared_mutex m;
    std::vector<std::future<int64_t>> results;
    for(int i = 0; i < 5; ++i)
    {
        int l_ = i * vec.size() / 5;
        int r_ = l_ + vec.size() / 5;
        results.push_back(std::move(std::async([&](int l, int r) mutable ->int64_t
        {std::shared_lock<std::shared_mutex> varname(m);
            int64_t sum = 0; for(int k = l; k < r; ++k){sum += vec[k];}
            return sum;}, l_, r_)));
    }
    int64_t res = 0;
    for(auto& fut : results)
    {

        res += 1ll * fut.get();
    }
    std::cout << res << std::endl;
    std::cout << (0ll + 1'00'000'000ll - 1) * 1'00'000'000 / 2 << std::endl;
    assert(res == (0ll + 1'00'000'000ll - 1) * 1'00'000'000 / 2);
}