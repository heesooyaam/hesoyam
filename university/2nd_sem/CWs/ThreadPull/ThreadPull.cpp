#include <thread>
#include <shared_mutex>
#include <vector>
#include <queue>
#include <functional>
#include <condition_variable>
#include <atomic>
#include <stdexcept>
#include <cassert>
#include <iostream>
#include <chrono>


/*
 * Требуется написать класс ThreadPool, реализующий пул потоков, которые выполняют задачи из общей очереди.
 * С помощью метода PushTask можно положить новую задачу в очередь
 * С помощью метода Terminate можно завершить работу пула потоков.
 * Если в метод Terminate передать флаг wait = true,
 *  то пул подождет, пока потоки разберут все оставшиеся задачи в очереди, и только после этого завершит работу потоков.
 * Если передать wait = false, то все невыполненные на момент вызова Terminate задачи, которые остались в очереди,
 *  никогда не будут выполнены.
 * После вызова Terminate в поток нельзя добавить новые задачи.
 * Метод IsActive позволяет узнать, работает ли пул потоков. Т.е. можно ли подать ему на выполнение новые задачи.
 * Метод GetQueueSize позволяет узнать, сколько задач на данный момент ожидают своей очереди на выполнение.
 * При создании нового объекта ThreadPool в аргументах конструктора указывается количество потоков в пуле. Эти потоки
 *  сразу создаются конструктором.
 * Задачей может являться любой callable-объект, обернутый в std::function<void()>.
 */
class ThreadPool 
{
public:
    using unique_lock = std::unique_lock<std::shared_mutex>;
    using shared_lock = std::shared_lock<std::shared_mutex>;

    ThreadPool(int amount_of_threads)
    : active_(true)
    , waitForEmpty_(false)
    {
        for(int i = 0; i < amount_of_threads; ++i)
        {
            threads_.emplace_back(&ThreadPool::ThreadFunction, this);
        }
    }

    class ThreadPoolisClosed : std::exception
    {
        const char* what() const noexcept override 
        {
            return "Thread Pool has alrady been closed";
        }
    };

    void PushTask(std::function<void()> task)
    {
        unique_lock lock(mutex_);
        if(!active_) throw std::exception();

        FunctionsQueue_.push(task);
        // std::cout << "pushing..." << std::endl;

        cv_for_threads_.notify_one();
    }

    bool IsActive() const
    {
        shared_lock lock(mutex_);
        return active_;
    }

    size_t QueueSize() const
    {
        shared_lock lock(mutex_);
        return FunctionsQueue_.size();
    }

    void Terminate(bool wait = false)
    {
        unique_lock lock(mutex_);

        if(!active_) throw std::exception();

        active_ = false;

        if(wait)
        {
            waitForEmpty_ = true;
            cv_for_terminate_call_.wait(lock, [this]()->bool {return FunctionsQueue_.empty();});
        }
        else waitForEmpty_ = false;

        cv_for_threads_.notify_all();

        lock.unlock();

        for(auto& thread : threads_)
        {
            thread.join();
        }
    }

private:
    bool active_;
    bool waitForEmpty_;
    std::queue<std::function<void()>> FunctionsQueue_;
    std::vector<std::thread> threads_;
    mutable std::shared_mutex mutex_;
    std::condition_variable_any cv_for_threads_, cv_for_terminate_call_;

    void ThreadFunction()
    {
        while(true)
        {
            unique_lock lock(mutex_);

            cv_for_threads_.wait(lock, [this]()->bool {return !FunctionsQueue_.empty() || !active_;});

            if(!active_)
            {
                if(!waitForEmpty_) return;
                else
                {
                    if(FunctionsQueue_.empty())
                    {
                        cv_for_terminate_call_.notify_one();
                        return;
                    }
                    else
                    {
                        std::function<void()> foo = FunctionsQueue_.front();
                        FunctionsQueue_.pop();
                        lock.unlock();
                        foo();
                    }
                }
            }
            else
            {
                std::function<void()> foo = FunctionsQueue_.front();
                FunctionsQueue_.pop();
                lock.unlock();
                foo();
            }
        }
    }

    // void runTask(unique_lock& lock)
    // {
    //     assert(lock.owns_lock() && FunctionsQueue_.size());
    //     std::function<void()> foo = FunctionsQueue_.front();
    //     FunctionsQueue_.pop();
    //     lock.unlock();
    //     std::cout << std::endl;
    //     foo();
    // }
};

using namespace std::literals::chrono_literals;

/*
 * Складывает числа на полуинтервале [from, to)
 */
uint64_t SumNumbers(uint64_t from, uint64_t to) {
    uint64_t sum = 0;
    for (uint64_t number = from; number < to; ++number) {
        sum += number;
    }
    return sum;
}

void TestSimple() {
    ThreadPool pool(10);

    std::mutex mutex;
    uint64_t sum = 0;

    constexpr int step = 1000;
    constexpr uint64_t maxNumber = 500000000;
    for (uint64_t l = 0, r = l + step; l <= maxNumber; l = r, r = l + step) {
        if (r > maxNumber + 1) {
            r = maxNumber + 1;
        }
        pool.PushTask([&sum, &mutex, l, r]() {
            std::this_thread::sleep_for(100us);
            const uint64_t subsum = SumNumbers(l, r);
            std::lock_guard<std::mutex> lockGuard(mutex);
            sum += subsum;
        });
    }

    std::cout << "QueueSize before terminate is " << pool.QueueSize() << std::endl;
    assert(pool.QueueSize() > 100000);
    pool.Terminate(true);
    std::cout << "Terminated. Queue size is " << pool.QueueSize() << ". IsActive: " << pool.IsActive() << std::endl;

    const uint64_t expectedSum = SumNumbers(1, maxNumber + 1);
    assert(expectedSum == sum);

    try {
        pool.PushTask([](){
            std::cout << "I am a new task!" << std::endl;
        });
        assert(false);
    } catch (const std::exception& e) {
        std::cout << "Cannot push tasks after termination" << std::endl;
    }
}

void TestTerminationWithoutWait() {
    std::cout << "TestWithoutWait" << std::endl;
    ThreadPool pool(10);

    std::mutex mutex;
    uint64_t sum = 0;

    constexpr int step = 1000;
    constexpr uint64_t maxNumber = 500000000;
    for (uint64_t l = 0, r = l + step; l <= maxNumber; l = r, r = l + step) {
        if (r > maxNumber + 1) {
            r = maxNumber + 1;
        }
        pool.PushTask([&sum, &mutex, l, r]() {
            std::this_thread::sleep_for(100us);
            const uint64_t subsum = SumNumbers(l, r);
            std::lock_guard<std::mutex> lockGuard(mutex);
            sum += subsum;
        });
    }

    std::cout << "QueueSize before terminate is " << pool.QueueSize() << std::endl;
    assert(pool.QueueSize() > 100000);
    pool.Terminate(false);
    std::cout << "Terminated. Queue size is " << pool.QueueSize() << ". IsActive: " << pool.IsActive() << std::endl;

    const uint64_t expectedSum = SumNumbers(1, maxNumber + 1);
    assert(expectedSum > sum);

    try {
        pool.PushTask([](){
            std::cout << "I am a new task!" << std::endl;
        });
        assert(false);
    } catch (const std::exception& e) {
        std::cout << "Cannot push tasks after termination" << std::endl;
    }
}

void TestConcurrentTaskPush() {
    ThreadPool pool(10);

    std::atomic<int> counter = 0;

    std::vector<std::thread> pusherThreads;
    for (int i = 0; i < 1000; ++i) {
        pusherThreads.emplace_back([&](){
            std::this_thread::sleep_for(10us);
            for (int j = 0; j < 1000; ++j) {
                pool.PushTask([&](){
                    std::this_thread::sleep_for(5us);
                    counter++;
                });
            }
        });
    }

    for (auto& thread : pusherThreads) {
        thread.join();
    }
    pool.Terminate(true);

    assert(counter == 1000000);
}

void TestConcurrentSelfTaskPush() {
    ThreadPool pool(10);

    std::atomic<int> counter = 0;
    std::atomic<int> pusherThreadDoneCounter = 0;

    for (int i = 0; i < 1000; ++i) {
        pool.PushTask([&](){
            std::this_thread::sleep_for(10us);
            for (int j = 0; j < 1000; ++j) {
                pool.PushTask([&](){
                    std::this_thread::sleep_for(10us);
                    counter++;
                });
            }
            pusherThreadDoneCounter++;
        });
    }

    while(pusherThreadDoneCounter != 1000) {
        std::this_thread::sleep_for(10ms);
    }
    pool.Terminate(true);

    assert(counter == 1000000);
}

int main() {
    TestSimple();
    std::cout << "1" << std::endl;
    TestTerminationWithoutWait();
    std::cout << "2" << std::endl;
    TestConcurrentSelfTaskPush();
    std::cout << "3" << std::endl;
    TestConcurrentTaskPush();
    std::cout << "4" << std::endl;
    return 0;
}