//
// Created by kchri on 8/15/2024.
//
#include "Shape.h"
#include "Rectangle.h"
#include <iostream>

// Constructor
Rectangle::Rectangle(int newx, int newy, int newwidth, int newheight): Shape(newx, newy) {
    setWidth(newwidth);
    setHeight(newheight);
}

// Accessors for width and height
int Rectangle::getWidth() { return width; }
int Rectangle::getHeight() { return height; }
void Rectangle::setWidth(int newwidth) { width = newwidth; }
void Rectangle::setHeight(int newheight) { height = newheight; }

// draw the rectangle
void Rectangle::draw() {
    std::cout << "Drawing a Rectangle at:(" << getX() << "," << getY() <<
         "), width " << getWidth() << ", height " << getHeight() << std::endl;
}