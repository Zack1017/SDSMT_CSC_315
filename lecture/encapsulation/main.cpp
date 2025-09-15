/*
 * C++ program to explain
 * encapsulation
 *
 * ckarlsso 11/27/2024
 */
#include <iostream>

// Declaring class
class Circle {
    // Access modifier
private:
    // Data Member
    double area;
    double radius;

public:
    // Default constructor and destructor
    Circle() = default;
    ~Circle() = default;
    void getRadius() {
        std::cout << "Enter radius: ";
        std::cin >> radius;
    }
    void findArea() {
        area = 3.14 * radius * radius;
        std::cout << "Area of circle=" << area;
    }
};
int main() {
    // Creating instance(object) of class
    Circle cir{};
    cir.getRadius();    // Calling public function
    cir.findArea();     // Calling public function
}
