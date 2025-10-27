/*
 * C++ program to explain Polymorphism
 *
 * ckarlsso 11/27/2024
 */
#include "Shape.h"
#include "Rectangle.h"
#include "Circle.h"

int main() {
    /* Create an array of the shapes */
    Shape *scribble[2];
    scribble[0] = new Rectangle(10, 20, 5, 6);
    scribble[1] = new Circle(15, 25, 8);

    // Iterate through the array and handle shapes polymorphically
    for (int i = 0; i < 2; i++) {
        scribble[i]->draw();
        scribble[i]->rMoveTo(100, 100);
        scribble[i]->draw();
    }

    // Call a rectangle specific function
    Rectangle *arec = new Rectangle(0, 0, 15, 15);
    arec->setWidth(30);
    arec->draw();
    return 0;
}