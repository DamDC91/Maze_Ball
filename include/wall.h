#pragma once

#include "forms.h"
#include "cube_face.h"
#include "geometry.h"
#include "cuboid.h"

class Wall : public Cuboid
{
private:

public:
    Wall(Point c_origin, Vector c_face_dir1, Vector c_face_dir2, Vector c_face_dir3, Color cl);

    Wall(Point org, Vector v1, Vector v2, double l, double w, double d, Color cl) :
            Cuboid(v1, v2, org, l, w, d, cl) {};

    bool collisionSphere(Sphere &sphere, Vector const &floor_normal);
};