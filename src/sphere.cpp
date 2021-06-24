#include <GL/glu.h>
#include "sphere.h"
#include <matrix.h>
#include <cmath>


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

void Sphere::update(double delta_t, double alpha, double beta)
{
    Vector g(0, -9.81, 0);

    Vector newG = rotate_x(g, -alpha * M_PI / 180.0);
    newG = rotate_z(newG, -beta * M_PI / 180.0);


    Vector newG2 = (newG * Vector(1, 0, 0)) * Vector(1, 0, 0);
    newG2 = newG2 + (newG * Vector(0, 0, 1)) * Vector(0, 0, 1);

    this->anim.setAccel(newG2);


    this->anim.setSpeed(this->anim.getSpeed() + delta_t * this->anim.getAccel());
    Point P = this->anim.getPos();
    Vector V = delta_t * this->anim.getSpeed();
    P.x = P.x + V.x;
    P.y = P.y + V.y;
    P.z = P.z + V.z;
    this->anim.setPos(P);
}


void Sphere::render()
{
    GLUquadric *quad;

    quad = gluNewQuadric();

    // Complete this part
    Form::render(); // Position the form and assign its color

    // Mise en route de la texture associee
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture_id);
    gluQuadricTexture(quad, texture_id);
    gluQuadricNormals(quad, GLU_SMOOTH);

    gluSphere(quad, this->radius, 100, 20);

    gluDeleteQuadric(quad);

    // Ne plus appliquer la texture pour la suite
    glDisable(GL_TEXTURE_2D);
}
