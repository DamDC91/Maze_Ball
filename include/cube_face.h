#ifndef CUBEFACE_H_INCLUDED
#define CUBEFACE_H_INCLUDED

#include "forms.h"
#include "sphere.h"


// A face of a cube
class CubeFace : public Form
{
private:
    Vector vdir1, vdir2;
    double length, width;

public:
    explicit CubeFace(Vector v1 = Vector(1, 0, 0), Vector v2 = Vector(0, 0, 1),
                      Point org = Point(), double l = 1.0, double w = 1.0,
                      Color cl = Color());

    Vector getVdir1() const { return vdir1; };

    Vector getVdir2() const { return vdir2; };

    Vector getNormal() const { return vdir1 ^ vdir2; };

    void update(double delta_t) override;

    void render() override;

    bool collisionSphere(Sphere &sphere, Vector floor_normal);

};
#endif