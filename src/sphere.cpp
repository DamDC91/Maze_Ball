#include <GL/glu.h>
#include "sphere.h"


Sphere::Sphere(double r, Point org, Color cl)
{
    radius = r;
    anim.setPos(org);
    col = cl;
}


void Sphere::update(double delta_t)
{
    // Complete this part

}


void Sphere::render()
{
    GLUquadric *quad;

    quad = gluNewQuadric();

    // Complete this part
    Form::render();
    gluSphere(quad, this->radius, 100, 20);

    gluDeleteQuadric(quad);
}
