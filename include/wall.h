#pragma once

#include "forms.h"
#include "cube_face.h"
#include "geometry.h"

class Wall : public Cuboid
{
private:

public:
    Wall(Point c_origin, Vector c_face_dir1, Vector c_face_dir2,Vector c_face_dir3, Color cl);
    bool collisionSphere(Point sph_pos, double radius, Vector floor_normal);
};