#pragma once

#include "forms.h"
#include "cube_face.h"
#include "geometry.h"

class Cuboid : public Form
{
protected:
    double length, width, depth;
    CubeFace *faces[6];
    Vector vdir1, vdir2;

public:
    enum Face
    {
        Front = 0,
        Right = 1,
        Back = 2,
        Left = 3,
        Top = 4,
        Bottom = 5
    };

    explicit Cuboid(Vector v1 = Vector(1, 0, 0), Vector v2 = Vector(0, 0, 1),
                    Point org = Point(), double l = 1.0, double w = 1.0, double d = 1.0,
                    Color cl = Color());

    void update(double delta_t) override;

    void render() override;

    Vector getNormal() { return vdir1 ^ vdir2; }

    void setTexture(GLuint textureId, int i);

    void setTexture(GLuint textureId) override;
};