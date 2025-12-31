#include <iostream>
#include "turtle.hpp"
using namespace std;

int main() {

    Turtle turtle(1000, 1000);

    turtle.setPenColor(0,0,0);
    turtle.drawCircle(50, 50, 10);
    turtle.drawCircle(0, 0, 10);
    turtle.reset();
    turtle.forward(50);
    turtle.drawCircle(50, 50, 10);

    turtle.saveBMP("image.bmp");

    return 0;
}
