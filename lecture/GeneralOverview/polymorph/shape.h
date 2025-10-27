//
// Created by kchri on 8/15/2024.
//

class Shape {

public:
    Shape(int newx, int newy);
    ~Shape() = default;
    int getX();
    int getY();
    void setX(int newx);
    void setY(int newy);
    void moveTo(int newx, int newy);
    void rMoveTo(int deltax, int deltay);
    virtual void draw();

private:
    int x;
    int y;
};