#include "GL/glu.h"
#include "cuboid.h"
#include "cube_face.h"
#include "wall.h"

#include <iostream>

Wall::Wall(Point c_origin, Vector c_face_dir1, Vector c_face_dir2,Vector c_face_dir3, Color cl) : Cuboid::Cuboid(c_origin, c_face_dir1, c_face_dir2, c_face_dir3, cl)
{
    
}

bool Wall::collisionSphere(Point sph_pos, double radius, Vector floor_normal)
{
    for(int i =0; i<6;i++)
    {
        if( faces[i]->getVdir1()*floor_normal > 1e-6 || faces[i]->getVdir2()*floor_normal > 1e-6)
        {
            if (faces[i]->collisionSphere(sph_pos,radius,floor_normal))
                return true;
        }
    }
    return false;
}