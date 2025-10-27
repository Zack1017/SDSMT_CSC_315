//
// Created by kchri on 8/15/2024.
//
class Rectangle: public Shape {

public:
    Rectangle(int newx, int newy, int newwidth, int newheight);
    int getWidth();
    int getHeight();
    void setWidth(int newwidth);
    void setHeight(int newheight);
    void draw();

private:
    int width;
    int height;
};
