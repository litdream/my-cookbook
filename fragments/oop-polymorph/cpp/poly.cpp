#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

using std::cout;
using std::endl;

class Shape {
public:
    virtual double area() const = 0;
    virtual ~Shape() {}   // virtual destructor
};

class Circle : public Shape {
private:
    double radius;
public:
    Circle(double r) : radius(r) {}

    double area() const override {
        // M_PI is a common C++ standard library constant for pi
        return M_PI * radius * radius;
    }
    double getRadius() const { return radius; }
};

class Square : public Shape {
private:
    double side;
public:
    Square(double s) : side(s) {}

    double area() const override {
        return side * side;
    }
    double getSide() const { return side; }
};

int main() {
    cout << std::fixed << std::setprecision(2);
    cout << "C++ Virtual Function Polymorphism Demonstration\n\n";


    Circle circle_obj(7.0);
    Square square_obj(5.0);

    cout << "--- Direct Area Calculation ---\n";
    cout << "Circle (Radius " << circle_obj.getRadius()
         << ") Area: " << circle_obj.area() << endl;
    cout << "Square (Side " << square_obj.getSide() << ") Area: "
         << square_obj.area() << endl;

    std::vector<Shape*> shapes;
    shapes.push_back(new Circle(7.0));
    shapes.push_back(new Square(5.0));
    shapes.push_back(new Circle(3.0));

    double total_area = 0.0;
    int i = 0;
    for (Shape* shape : shapes) {
        double current_area = shape->area();
        cout << "Shape " << ++i << ": Area = " << current_area << endl;
        total_area += current_area;
    }

    cout << "-----------------------------\n";
    cout << "Total Area of all shapes: " << total_area << endl;

    // --- 5. Clean up Memory ---
    for (Shape* shape : shapes) {
        delete shape;
    }
    
    return 0;
}
