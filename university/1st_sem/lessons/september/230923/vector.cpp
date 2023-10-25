#include <iostream>

class Vector{
    private:
        size_t Size, Capacity;
        int* data;
        void copyMemory(int* from, int* to)
        {
            for(size_t i = 0; i < Size; i++)
            {
                to[i] = from[i];
            }
        }
    public:

        // Конструкторы и деструктор

        Vector(const Vector& v) // конструктор копирования
            : Size(v.size())
            , Capacity(Size)
            , data(new int[Capacity]) 
        {
            for(int i = 0; i < Size; i++)
            {
                data[i] = v[i];
            }
        }
        Vector(size_t size_, int defaultValue)
            : Size(size_)
            , Capacity(Size)
            , data(new int[Size])
        {
            for(size_t i = 0; i < Size; i++)
            {
                data[i] = defaultValue;
            }
        }
        Vector()
            : Size(0)
            , Capacity(Size)
            , data(new int[Size]) {}

        ~Vector() // деструктор
        {
            delete[] data;
        }
        // Методы

        size_t size() const{
            return Size;
        }

        size_t capacity() const{
            return Capacity;
        }

        void push_back(int value)
        {
            if(Size < Capacity)
            {
                data[Size] = value;
                ++Size;
                return;
            }

            // проверяем крайний случай -- если изначально был вектор размера 0 и вместимость тоже была 0
            int* newData = new int[Capacity > 0 ? Capacity * 2 : 1];
            copyMemory(data, newData);
            delete[] data;
            Capacity = (Capacity > 0 ? Capacity * 2 : 1);
            data = newData;
            data[Size] = value;
            ++Size;
        }
        void print()
        {
            for(int i = 0; i < Size; i++)
            {
                std::cout << data[i] << ' ';
            }
            std::cout << std::endl;
        }


        void resize(size_t newSize)
        {
            return resize(newSize, 0);
        }

        void resize(size_t newSize, int defaultValue)
        {
            if(newSize <= Size)
            {
                int* newData = new int[newSize];
                Size = newSize;
                copyMemory(data, newData);
                delete[] data;
                data = newData;
                Capacity = newSize;
                return;
            }

            if(newSize > Size)
            {
                int* newData = new int[newSize];
                copyMemory(data, newData);
                delete[] data;
                data = newData;
                for(int i = Size; i < newSize; i++)
                {
                    data[i] = defaultValue;
                }
                Size = newSize;
                Capacity = newSize;
                return;
            }
        }
        void pop_back()
        {
            Size--;
            if(Size <= Capacity / 4 + 1)
            {
                int* newData = new int[Capacity / 2];
                copyMemory(data, newData);
                delete[] data;
                data = newData;
                Capacity /= 2;
            }
        }

        // Определение опертаоров

        int operator [](size_t index) const // клянемся, что не будем менять внутри ничего => можно использовать для константных объектов
        // const_cast< "type" >( "pointer" ) меняет константность
        {
            return const_cast<Vector*>(this)->operator[](index);
            // this: const Vector* --> Vector*, поэтому можем вызвать неконстантный метод,
            // который вернет ссылку, но так как наша константная функция возвращает копию, то все ок 
        }
        int& operator [](size_t index)
        {
            return data[index];
        }

};

// переопределили оператор "<<"" для нашего класса "Vector"
std::ostream& operator << (std::ostream& s, const Vector& v)
{
    s << "Size: " << v.size() << " Capacity: " << v.capacity() << std::endl;
    for(int i = 0; i < (int(v.size()) >= 5 ? 5 : v.size()); i++)
    {
        s << v[i] << ' ';
    }
    return s;
}

int main()
{
    Vector v1;
    v1.push_back(1);
    v1.push_back(2);
    //std::cout << v1[0] << ' ' << v1[1] << std::endl;
    v1.print();
    v1.pop_back();
    v1.resize(10, 2);
    v1.print();
    v1.resize(1);
    std::cout << v1;
    return 0;
}