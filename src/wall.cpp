#include "GL/glu.h"
#include "cuboid.h"
#include "cube_face.h"
#include "wall.h"

#include <iostream>

Wall::Wall(Point c_origin, Vector c_face_dir1, Vector c_face_dir2, Vector c_face_dir3, Color cl) : Cuboid::Cuboid(
        c_origin, c_face_dir1, c_face_dir2, c_face_dir3, cl)
{

}

bool Wall::collisionSphere(Sphere &sphere, Vector const &floor_normal)
{
    for (auto &face : this->faces)
    {
        face->setColor(BLUE);
        // check if face is parallel to the floor
        if (std::abs(face->getVdir1() * floor_normal) > 1e-3 || std::abs(face->getVdir2() * floor_normal) > 1e-3)
        {
            if (face->collisionSphere(sphere, floor_normal))
            {
                face->setColor(GREEN);
                return true;
            }
        }
    }
    return false;
}