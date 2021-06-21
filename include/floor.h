#pragma once

#include "forms.h"
#include "cube_face.h"
#include "geometry.h"

class Floor : public Cuboid
{
private:
    Vector normal;

public:
    Floor(Point c_origin, Vector c_face_dir1, Vector c_face_dir2,Vector c_face_dir3, Vector c_normal, Color cl);
    // bool collisionSphere(Point sph_pos, double radius, Vector floor_normal); TODO
};