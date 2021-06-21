#pragma once

#include "forms.h"


// A particular Form
class Sphere : public Form
{
private:
    // The sphere center is aligned with the coordinate system origin
    // => no center required here, information is stored in the anim object
    double radius;
public:
    Sphere(double r = 1.0, Point org = Point(), Color cl = Color());

    Sphere(double r = 1.0, Color cl = Color()) : Sphere(r, Point(), cl) {};

    double getRadius() const { return radius; }

    void setRadius(double r) { radius = r; }

    void update(double delta_t);

    void render();

    void update(double delta_t, double alpha, double beta);
};
