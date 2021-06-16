#include <cmath>
#include <SDL2/SDL_opengl.h>
#include <GL/glu.h>
#include "forms.h"
#include "sphere.h"

#include <iostream>

Sphere::Sphere(double r, Color cl)
{
    radius = r;
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
    Form::render();
    gluSphere(quad,this->radius,100,20);

    // Complete this part

    gluDeleteQuadric(quad);
}
