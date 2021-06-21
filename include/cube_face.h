#pragma once

#include "forms.h"
#include "sphere.h"


// A face of a cube
class CubeFace : public Form
{
private:
    Vector vdir1, vdir2, normal;
    double length, width;
public:
    CubeFace(Vector v1 = Vector(1, 0, 0), Vector v2 = Vector(0, 0, 1), Vector n=Vector(0,1,0),
             Point org = Point(), double l = 1.0, double w = 1.0,
             Color cl = Color());

    Vector getVdir1() const { return vdir1; };
    Vector getVdir2() const { return vdir2; };
    Vector getNormal() const {return normal; };

    void update(double delta_t);

    void render();

    bool collisionSphere(Point sph_pos, double radius, Vector floor_normal);
    bool collisionSphere(Sphere sphere, Vector floor_normal);
};
