#include "GL/glu.h"
#include "cuboid.h"
#include "cube_face.h"
#include "forms.h"

Cuboid::Cuboid(Vector v1, Vector v2, Point org, double l, double w, double d, Color cl)
{
    this->vdir1 = v1 * (1.0 / v1.norm());
    this->vdir2 = v2 * (1.0 / v2.norm());

    this->length = l;
    this->width = w;
    this->depth = d;

    this->origin = org;
    this->col = cl;

    Vector vdir3 = vdir1 ^vdir2;

    this->faces[Back] = new CubeFace(vdir2, vdir1, org, w, l, cl);
    this->faces[Left] = new CubeFace(vdir3, vdir2, org, d, w, cl);
    this->faces[Bottom] = new CubeFace(vdir1, vdir3, org, l, d, cl);

    org.translate(l * vdir1 + w * vdir2 + d * vdir3);

    this->faces[Front] = new CubeFace(-vdir1, -vdir2, org, l, w, cl);
    this->faces[Right] = new CubeFace(-vdir2, -vdir3, org, w, d, cl);
    this->faces[Top] = new CubeFace(-vdir3, -vdir1, org, d, l, cl);
}

void Cuboid::update(double delta_t) {}

void Cuboid::render()
{
    for (auto &face : faces)
    {
        glPushMatrix();
        face->render();
        glPopMatrix();
    }
}

void Cuboid::setTexture(GLuint textureId, int i)
{
    this->faces[i]->setTexture(textureId);
}

void Cuboid::setTexture(GLuint textureId)
{
    for (auto &face : this->faces)
    {
        face->setTexture(textureId);
    }
}
