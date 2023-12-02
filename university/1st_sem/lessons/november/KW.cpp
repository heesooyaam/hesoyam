#include <iostream>

/*
 * Intrusive pointer -- разновидность умных указателей, аналогично std::shared_ptr позволяющий совместное владение
 * указателем с подсчетом количества ссылок и автоматическим освобождением памяти.
 * Разница с shared_ptr состоит в том, что intrusive pointer хранит счетчик ссылок в самом объекте, на который ссылается.
 *
 *
 * В данном задании требуется реализовать шаблонный класс IntrusivePtr, который обладает следующими свойствами:
 *
 * - Хранит внутри указатель на объект (т.н. "сырой" указатель)                                    - 
 * - Ведет подсчет ссылок на хранимый объект, при этом счетчик хранится в самом хранимом объекте   -
 *      (для этого хранимые объекты должны наследоваться от базового класса IntrusivePtrCounter, код которого уже дан в задании)
 * - Владеет хранимым указателем и должен освобождать память, когда счетчик достигнет нуля         - 
 * - Позволяет создавать свои копии, увеличивая при создании каждой копии счетчик ссылок в объекте -
 * - Предоставляет доступ к содержимому как посредством оператора *, так и ->                      -
 * - Позволяет принимать для хранений "сырой" указатель при конструировании объекта IntrusivePtr   -
 * - Позволяет принимать для хранений "сырой" указатель в процессе жизни объекта IntrusivePtr через оператор = -
 * - Позволяет уменьшать счетчик ссылок и сбрасывать хранимый "сырой" указатель в nullptr в процессе жизни
 *      объекта IntrusivePtr с помощью метода Reset()                                              -
 * - Позволяет получить хранимый "сырой" указатель с помощью метода Get()                          -
 * - Допускает приведение к типу bool для удобных проверок на содержание указателя nullptr         -
 * - Доступ к хранимому "сырому" указателю должен работать в том числе для const объектов IntrusivePtr -
 */


class IntrusivePtrCounter {
private:
    size_t counter_ = 0;

    void AddRef() {++counter_;}
    size_t ReleaseRef() {return --counter_;}
    size_t GetRefCount() {return counter_;}

public:
    template <class T>
    friend class IntrusivePtr;
};

template<class T>
class IntrusivePtr
{
private:
    T* data = nullptr;
public:
    IntrusivePtr(T* object)
    : data(object)
    {
        if(data) data->AddRef();
    }
    IntrusivePtr(){}
    IntrusivePtr(const IntrusivePtr& other)
    : data(other.data)
    {
        if(data) data->AddRef();
    }
    operator bool() const
    {
        return data != nullptr;
    }
    void Reset()
    {
        if(data && data->ReleaseRef() == 0)
        {
            delete data;
        }
        data = nullptr;
    }
    IntrusivePtr& operator =(const IntrusivePtr& other)
    {
        if(other == *this)
        {
            return *this;
        }

        Reset();

        data = other.data;
        if(data)
        {
            data->AddRef();
        }
        return *this;
    }
    IntrusivePtr& operator =(T* object)
    {
        Reset();
        data = object;
        data->AddRef();
        return *this;
    }
    T& operator*()
    { 
        return *data; 
    } 
    
    const T& operator*() const
    { 
        return *data; 
    } 
    
    T* operator->()
    { 
        return data; 
    } 
    
    const T* operator->() const 
    { 
        return data; 
    }
    T* Get()
    {
        return data;
    } 
    const T* Get() const
    {
        return data;
    }
    
};

// Код, помогающий в отладке:

class Foo : public IntrusivePtrCounter {
public:
    Foo(int value): value_(value) {}
    int Bar() {
        return 100500;
    }
private:
    int value_;
    friend std::ostream& operator <<(std::ostream&, const Foo&);
};

std::ostream& operator <<(std::ostream& stream, const Foo& foo) {
    return stream << "Foo(" << foo.value_ << ')';
}

int main() {
    IntrusivePtr<Foo> x (nullptr);
    IntrusivePtr<Foo> ptr1;
    IntrusivePtr<Foo> ptr2;

    ptr1 = new Foo(1);
    std::cout << "*ptr1 = " << *ptr1 << std::endl;

    ptr1 = new Foo(2);
    std::cout << "*ptr1 = " << *ptr1 << std::endl;

    ptr2 = std::move(ptr1);
    std::cout << "ptr1 = " << ptr1.Get() << std::endl;
    std::cout << "*ptr2 = " << *ptr2 << std::endl;

    ptr1 = IntrusivePtr<Foo>(new Foo(11));
    std::cout << "*ptr1 = " << *ptr1 << std::endl;

    ptr1 = new Foo(12);
    std::cout << "*ptr1 = " << *ptr1 << std::endl;

    ptr1.Reset();
    std::cout << "ptr1 = " << ptr1.Get() << std::endl;

    if (!ptr1) {
        std::cout << "ptr1 is null: " << !ptr1 << std::endl;
    } else {
        return 1;
    }

    IntrusivePtr<Foo> ptr3 = new Foo(3);
    std::cout << "ptr3->Bar() = " << ptr3->Bar() << std::endl;

    IntrusivePtr<Foo> ptr4 = new Foo(42);
    std::cout << "ptr4 is null: " << !ptr4 << std::endl;
    std::cout << "*ptr4 = " << *ptr4 << std::endl;
    ptr4 = ptr4;
    std::cout << *ptr4 << std::endl;
    // std::cout<< ptr4->GetRefCount() << std::endl;
    return 0;
}
