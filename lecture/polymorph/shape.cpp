//
// Created by kchri on 8/15/2024.
//
#include "Shape.h"

// Constructor
Shape::Shape(int newx, int newy) {
    moveTo(newx, newy);
}

// Accessors for x & y
int Shape::getX() { return x; }
int Shape::getY() { return y; }
void Shape::setX(int newx) { x = newx; }
void Shape::setY(int newy) { y = newy; }

// Move the shape position
void Shape::moveTo(int newx, int newy) {
    setX(newx);
    setY(newy);
}
void Shape::rMoveTo(int deltax, int deltay) {
    moveTo(getX() + deltax, getY() + deltay);
}

// Abstract draw method
void Shape::draw() {
}
