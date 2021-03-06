#include <SDL2/SDL_opengl.h>

#include "forms.h"


void Form::update(double delta_t)
{
    // Nothing to do here, animation update is done in child class method
}


void Form::render()
{
    // Point of view for rendering
    // Common for all Forms
    Point org = anim.getPos();
    glTranslated(org.x, org.y, org.z);
    glRotated(this->anim.getPhi()*180.0/M_PI, 0, 1,0);
    glRotated(this->anim.getTheta()*180.0/M_PI, 1,0,0);
    glColor3f(col.r, col.g, col.b);
}
