#ifndef SPHERE_H_INCLUDED
#define SPHERE_H_INCLUDED

#include "forms.h"

// A particular Form
class Sphere : public Form
{
private:
    // The sphere center is aligned with the coordinate system origin
    // => no center required here, information is stored in the anim object
    double radius;
public:
    explicit Sphere(double r = 1.0, Point org = Point(), Color cl = Color());

    explicit Sphere(double r = 1.0, Color cl = Color());

    double getRadius() const { return radius; }

    void setRadius(double r) { radius = r; }

    void update(double delta_t) override;

    void render() override;

    void update(double delta_t, double alpha, double beta);
};

#endif //SPHERE_H_INCLUDED
