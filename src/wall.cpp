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
        // check if face is parallel to the floor
        if (face->getVdir1() * floor_normal > 1e-6 || face->getVdir2() * floor_normal > 1e-6)
        {
            if (face->collisionSphere(sphere.getAnim().getPos(), sphere.getRadius(), floor_normal))
            {
                Vector speed = sphere.getAnim().getSpeed();
                sphere.getAnim().setSpeed(speed - 2*(speed*face->getNormal())*face->getNormal());
                return true;
            }
        }
    }
    return false;
}