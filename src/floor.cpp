#include "GL/glu.h"
#include "cuboid.h"
#include "cube_face.h"
#include "floor.h"

#include <iostream>

Floor::Floor(Point c_origin, Vector c_face_dir1, Vector c_face_dir2,Vector c_face_dir3, Vector c_normal, Color cl) : Cuboid::Cuboid(c_origin, c_face_dir1, c_face_dir2, c_face_dir3, cl), normal(c_normal)
{
    
}
