#include <cmath>
#include <SDL2/SDL_opengl.h>
#include <GL/glu.h>
#include "forms.h"
#include "cube_face.h"

#include <iostream>

Cube_face::Cube_face(Vector v1, Vector v2, Point org, double l, double w, Color cl)
{
    vdir1 = 1.0 / v1.norm() * v1;
    vdir2 = 1.0 / v2.norm() * v2;
    anim.setPos(org);
    length = l;
    width = w;
    col = cl;
}

void Cube_face::update(double delta_t)
{
    // Complete this part
  //  this->anim.setTheta(this->anim.getTheta() + 0.3);
  //  this->anim.setPhi(this->anim.getPhi() + 0.3);
}

void Cube_face::render()
{

    Point p1 = Point();
    Point p2 = p1, p3, p4 = p1;
    p2.translate(length * vdir1);
    p3 = p2;
    p3.translate(width * vdir2);
    p4.translate(width * vdir2);

    Form::render();

    glBegin(GL_QUADS);
    {
        glVertex3d(p1.x, p1.y, p1.z);
        glVertex3d(p2.x, p2.y, p2.z);
        glVertex3d(p3.x, p3.y, p3.z);
        glVertex3d(p4.x, p4.y, p4.z);
    }
    glEnd();
}
