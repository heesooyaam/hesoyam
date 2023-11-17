#include <iostream>
#include <vector>

template <typename T>
struct SharedData
{
    T* ptr_;
    size_t sharedCounter;
    size_t weakCounter;
};

template<typename T>
class SharedPtr
{
private:
    SharedData<T>* data;
    SharedPtr(SharedData<T>* otherData) 
        : data_(otherData) {}
public:
    friend WeakPointer;
    SharedPtr()
        : data(new SharedData<T>(ptr_ = new T(), sharedCounter = 1, weakCounter = 0)) {
    } 

    SharedPtr(const SharedPtr& other) 
        : data(other.data) {}

    ~SharedPtr() {
        data->sharedCounter -= 1;
        if (data->sharedCounter == 0 && data->ptr != nullptr) {
            delete data->ptr_;
            data->ptr_ = nullptr;
        }
        if(data->sharedCounter + data->weakCounter == 0)
        {
            delete data;
        }
    }
    T& operator*() {
        return *ptr_;
    }
    const T& operator*() const {
        return *ptr_;
    }

    T* operator->() {
        return ptr_;
    }
    const T* operator->() const {
        return ptr_;
    }

    T* Get() {
        return ptr_;
    }
    const T* Get() const {
        return ptr_;
    }
};

template <typename T>
class WeakPointer
{
private:
    SharedData<T>* data;
public:
    WeakPointer(SharedPointer<T>& shdPtr)
    : data(shdPtr.data)
    {
        ++data->weakCounter;
    }
    ~WeakPointer()
    {
        --(data->weakCounter);
        if(data->sharedCounter + data->weakCounter == 0)
        {
            delete data;
        }
    }
    SharedPtr<T> lock() const;
    {
        return SharedPtr(data);
    }
};

SharedPtr<int> Foo(int x) {
    SharedPtr<int> result;
    *result = x;
    return result;
}

int main() {
    /* FIRST

        SharedPtr<int> p;
        std::cout << *p << " " << p.Get() << std::endl;
        *p = 5;
        std::cout << *p << " " << p.Get() << std::endl;
    
    */

        std::vector<SharedPtr<int>> ptrs;
        for (int i = 0; i < 1e8; ++i) {
            auto p = Foo(i);
            std::cout << *p << "\n";
            ptrs.push_back(p);
        }
   /* Second

    */
    return 0;
}