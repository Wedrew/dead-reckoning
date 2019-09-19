#ifndef CIRCLE_H
#define CIRCLE_H

#include <SDL2/SDL.h>

namespace zero {

class Circle {
private:
    double radius;
    int diameter;

public:
    Circle();
    Circle(double radius);

    void setRadius(double radius);

    double getRadius() const;
    double getArea() const;
    double getDiameter() const;
    double getCircumference() const;


};




}

#endif