#include <iostream>
using namespace std;
template <typename T>
class UniquePtr
{
private:
    T* data = nullptr;
    void MoveAssignment(UniquePtr&& other)
    {
        Reset();
        data = other.data;
        other.data = nullptr;
    }
public:
    UniquePtr(){}
    UniquePtr(T* data)
    : data(data)
    {}
    UniquePtr(UniquePtr&& other)
    {
        MoveAssignment(move(other));
    }
    ~UniquePtr()
    {
        if(data != nullptr)
        {
            delete data;
            data = nullptr;
        }        
    }
    UniquePtr(const UniquePtr&) = delete; // удалили констркутор копирования
    UniquePtr operator =(const UniquePtr&) = delete;
    // т.к. = работает как конструктор, а конструктор копирования мы удалили,
    // то этот оператор не будет работать и так
    // автоматически перестанет работать и move(чтобы он заработал, нужно его переопределить)
    UniquePtr& operator =(UniquePtr&& other)
    {
        MoveAssignment(move(other));
        return *this;
    }
    T& operator()
    {
        return *data;
    }
    const T& operator *() const
    {
        return *data;
    }
    void Reset()
    {
        if(data != nullptr)
        {
            delete data;
            data = nullptr;
        }
    }
};
UniquePtr<int> Foo(int x)
{
    return new int(x);
}
int main()
{
    return 0;
}