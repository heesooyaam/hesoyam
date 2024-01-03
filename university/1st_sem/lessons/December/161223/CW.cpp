#include <cmath>
#include <sstream>
#include <vector>
#include <memory>
#include <cassert>
#include <iostream>

/*
 * В данном задании необходимо реализовать несколько классов, моделирующих некоторые свойства определенных геометрических
 * фигур.
 * - IShape2D -- базовый интерфейс, который должны реализовать все классы фигур. Содержит объявления методов
 *  GetPerimeter() и GetArea()
 * - Rectangle -- прямоугольник. Принимает в конструкторе длину и ширину. Кроме методов, объявленных в IShape2D, также
 *  имеет метод для вычисления радиуса описанной окружности GetCircumscribedCircleRadius()
 * - Square -- квадрат. Принимает в конструкторе длину стороны. Кроме методов, объявленных в IShape2D, также
 *  имеет метод для вычисления радиуса описанной окружности GetCircumscribedCircleRadius()
 * - Circle -- окружность. Принимает в конструкторе радиус.
 * Также нужно реализовать функцию PrintProperties(std::stringstream& ss, const IShape2D* shape), которая для данной
 * фигуры формирует запись в лог, пишущийся в поток ss. В лог для данной фигуры должны записаться периметр и площадь, а также
 * радиус описанной окружности, если он определен для неё.
 */
const double PI = acos(-1.0);
class IShape2D 
{
public:
    virtual ~IShape2D() = default;
    double GetPerimeter() const
    {
        return perimeter_;
    }
    double GetArea() const
    {
        return area_;
    }
    virtual void PrintProperties(std::stringstream& ss) const = 0;
protected:
    double area_;
    double perimeter_;
};

class Rectangle : public IShape2D 
{
protected:
    double CircumscribedCircleRadius_;
    void MakeRectangle(double length, double width)
    {
        area_ = length * width;
        perimeter_ = (length + width) * 2;
        CircumscribedCircleRadius_ = sqrt(length * length + width * width) / 2;
    }
public:
    Rectangle() = default;
    ~Rectangle() = default; 
    Rectangle(double length, double width)
    {
        MakeRectangle(length, width);
    }
    double GetCircumscribedCircleRadius() const
    {
        return CircumscribedCircleRadius_;
    }
    void PrintProperties(std::stringstream& ss) const override final
    {
        ss << "A shape with P = " << perimeter_ << "; S = " << area_ << "; R = " << CircumscribedCircleRadius_ << '\n';
    }

};

class Square : public Rectangle 
{
public:
    Square() = default;
    Square(double length)
    {
        MakeRectangle(length, length);
    }

};

class Circle : public IShape2D 
{
public:
    Circle() = default;
    Circle(double R)
    {
        area_ = PI * R * R;
        perimeter_ = 2 * PI * R;
    }
    ~Circle() = default;
    void PrintProperties(std::stringstream& ss) const override final
    {
        ss << "A shape with P = " << perimeter_ << "; S = " << area_ << '\n';
    }
};

void PrintProperties(std::stringstream& ss, const IShape2D* shape) {
    shape->PrintProperties(ss);
}

int main() {
    // Код, помогающий в отладке
    std::vector<std::unique_ptr<IShape2D>> shapes;

    shapes.push_back(std::make_unique<Circle>(10));
    shapes.push_back(std::make_unique<Circle>(20));
    shapes.push_back(std::make_unique<Rectangle>(5, 10));
    shapes.push_back(std::make_unique<Rectangle>(1, 10));
    shapes.push_back(std::make_unique<Square>(5));

    std::stringstream ss;
    for (auto& shape : shapes) {
        PrintProperties(ss, shape.get());
    }

    std::cout << ss.str();
    std::string expectedOutput = R"(A shape with P = 62.8319; S = 314.159
A shape with P = 125.664; S = 1256.64
A shape with P = 30; S = 50; R = 5.59017
A shape with P = 22; S = 10; R = 5.02494
A shape with P = 20; S = 25; R = 3.53553
)";
    // Если проверка не проходит из-за точности чисел с точкой, то нестрашно
    assert(ss.str() == expectedOutput);
}
