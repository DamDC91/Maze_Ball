#pragma once

#include "forms.h"
#include "cube_face.h"
#include "geometry.h"

class Cuboid : public Form
{
private:
    enum Face
    {
        Front = 0,
        Right = 1,
        Back = 2,
        Left = 3,
        Top = 4,
        Bottom = 5
    };
    Point center;
    Point origin;
    double width, heigth, depth;
    CubeFace *faces[6];
    Vector face_dir1, face_dir2, face_dir3;
    Color color;

public:
    Cuboid(Point c_origin, Vector c_face_dir1, Vector c_face_dir2,Vector c_face_dir3, Color cl);
    void update(double delta_t);
    void render();
};