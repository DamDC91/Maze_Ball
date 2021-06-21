#pragma once

#include "forms.h"
#include "cube_face.h"
#include "geometry.h"
#include "cuboid.h"

class Wall : public Cuboid
{
private:

public:
    Wall(Point c_origin, Vector c_face_dir1, Vector c_face_dir2,Vector c_face_dir3, Color cl);
    bool collisionSphere(Sphere &sphere, Vector const &floor_normal);
};