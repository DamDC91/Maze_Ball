#pragma once

#include "forms.h"
#include "cube_face.h"
#include "geometry.h"
#include "cuboid.h"

class Floor : public Cuboid
{
public:
    Floor(Point c_origin, Vector c_face_dir1, Vector c_face_dir2, Vector c_face_dir3, Vector c_normal, Color cl);

    Floor(Point org, Vector v1, Vector v2, double l, double w, double d, Color cl) :
            Cuboid(v1, v2, org, l, w, d, cl) {};

    // bool collisionSphere(Point sph_pos, double radius, Vector floor_normal); TODO
};