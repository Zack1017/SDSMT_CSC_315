//
// Created by kchri on 8/15/2022.
//
#include "Shape.h"
#include "Circle.h"
#include <iostream>

// constructor
Circle::Circle(int newx, int newy, int newradius): Shape(newx, newy) {
    setRadius(newradius);
}

// accessors for the radius
int Circle::getRadius() { return radius; }
void Circle::setRadius(int newradius) { radius = newradius; }

// draw the circle
void Circle::draw() {
    std::cout << "Drawing a Circle at:(" << getX() << "," << getY() <<
         "), radius " << getRadius() << std::endl;
}