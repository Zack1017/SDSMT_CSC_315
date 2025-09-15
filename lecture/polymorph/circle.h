//
// Created by kchri on 8/15/2024.
//
class Circle: public Shape {

public:
    Circle(int newx, int newy, int newradius);
    int getRadius();
    void setRadius(int newradius);
    void draw();

private:
    int radius;
};
