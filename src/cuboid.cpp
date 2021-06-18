#include "GL/glu.h"
#include "cuboid.h"
#include "cube_face.h"
#include "forms.h"

#include <iostream>

Cuboid::Cuboid(Point c_origin, Vector c_face_dir1, Vector c_face_dir2, Vector c_face_dir3, Color cl) : origin(c_origin), color(cl)
{
    width = c_face_dir1.norm();
    heigth = c_face_dir2.norm();
    depth = c_face_dir3.norm();

    face_dir1 = 1.0 / c_face_dir1.norm() * c_face_dir1;
    face_dir2 = 1.0 / c_face_dir2.norm() * c_face_dir2;
    face_dir3 = 1.0 / c_face_dir3.norm() * c_face_dir3;

    center = Point(origin.x + width / 2, origin.y + heigth / 2, origin.z + depth / 2);

    Point org = origin;

    faces[Front] = new CubeFace(face_dir1, face_dir2, org, width, heigth, color);

    faces[Left] = new CubeFace(face_dir2, face_dir3, org, heigth, depth, color);

    faces[Bot] = new CubeFace(face_dir3, face_dir1, org, depth, width, color);

    org.translate(width * face_dir1 + heigth * face_dir2 + depth * face_dir3);

    faces[Top] = new CubeFace(-1 * face_dir3, -1 * face_dir1, org, depth, width, color);

    faces[Right] = new CubeFace(-1 * face_dir3, -1 * face_dir2, org, depth, heigth, color);

    faces[Back] = new CubeFace(-1 * face_dir1, -1 * face_dir2, org, width, heigth, color);
}

void Cuboid::update(double delta_t)
{
}

void Cuboid::render()
{
    for (int i = 0; i < 6; i++)
    {
        glPushMatrix();
        faces[i]->render();
        glPopMatrix();
    }
}