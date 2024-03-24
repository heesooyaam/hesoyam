#include <condition_variable>
#include <mutex>
#include <queue>
#include <iostream>
#include <thread>
std::mutex coutMutex;
template<typename T>
class BufferedChannel
{
public:
    explicit BufferedChannel(size_t size)
    : maxMessageCount_(size) {}
    class ChannelClosed : std::exception {};

    template<typename K>
    void Push(K&& message)
    {
        std::unique_lock(std::mutex) lock(mutex_); 
        if(closed_)
        {
            throw ChannelClosed();
        }
        while(messages_.size() == maxMessageCount_)  
        {
            if(closed_)
            {
                throw ChannelClosed();
            }
            cv_for_writer_.wait(lock);
        }     
        messages_.push(std::forward<K>(message));

        // ToDo: notify wiating reader thread
        cv_for_reader_.notify_one();
    }

    T Get()
    {
        std::unique<std::mutex> lock(mutex_);
        if(closed_)
        {
            throw ChannelClosed();
        }
        cv_for_reader_.wait(lock, [this](){return !messages_.empty() || closed_;});
        if(closed_)
        {
            throw ChannelClosed();
        }
        auto result = meassages_.front();
        messages_.pop();
        cv_for_writer_.notify_one();
        return result;
    }
    void Close(bool waitForEmptyQueue = false)
    {
        std::unique_lock<std::mutex> lock(mutex_);
        if(closed_) throw ChannelClosed();
        if(waitForEmptyQueue)
        {
            cv_for_writer_.wait(lock, [this]() {return !messages_.empty();})
        }
        closed_ = true;
        cv_for_reader_.notify_all();
        cv_for_writer_.notify_all();
    }
private:
    const size_t maxMessageCount_;
    std::queue<T> messages_;
    std::mutex mutex_;
    std::condition_variable cv_for_reader_, cv_for_writer_;
    bool closed = false;
};
void Write(BufferedChannel<int>& channel, size_t num)
{
    try
    {
        for(size_t i = 0; i < num; ++i)
        {
            channel.Push(i);
        }    
    } catch (const BufferedChannel<int>::ChannelClosed& ex)
    {
        std::lock_guard<std::mutex> lock(coutMutex);
        std::cout << std::this_thread::get_id() << "(writer): channel is closed" << std::endl;
    }
}
void Read(BufferedChannel<int>& channel)
{
    int64_t sum = 0;
    try
    {
        while(true)
        {
            sum += channel.Get();            
        }
    }
    catch(const BufferedChannel<int>::ChannelClosed& ex)
    {
        std::lock_guard<std::mutex> lock(coutMutex);
        std::cout << std::this_thread::get_id() << " (reader): Channel is closed" << std::endl;
    }
    std::lock_guard<std::mutex> lock(coutMutex);
    std::cout << " sum = " << sum << std::endl;
    
}
int main()
{
    using namespace std::chrono_literals;
    BufferedChannel<int> channel(10);
    std::vector<std::thread> readers, writers;

    for(size_t i = 0; i < 10; ++i)
    {
        readers.emplace_back(Read, std::ref(channel));
    } 

    for(size_t i = 0; i < 100; ++i)
    {
        writers.emplace_back(Write, std::ref(channel));
    }

    channel.Close();

    for(auto& thread : readers)
    {
        thread.join();
    }
    for(auto& thread : writers)
    {
        thread.join();
    }
}