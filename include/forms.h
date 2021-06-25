#ifndef FORMS_H_INCLUDED
#define FORMS_H_INCLUDED

#include "geometry.h"
#include "animation.h"
#include <GL/glu.h>


class Color
{
public:
    float r, g, b;

    explicit Color(float rr = 1.0f, float gg = 1.0f, float bb = 1.0f)
    {
        r = rr;
        g = gg;
        b = bb;
    }
};

// Constant Colors
const Color RED(1.0f, 0.0f, 0.0f);
const Color BLUE(0.0f, 0.0f, 1.0f);
const Color GREEN(0.0f, 1.0f, 0.0f);
const Color YELLOW(1.0f, 1.0f, 0.0f);
const Color WHITE(1.0f, 1.0f, 1.0f);
const Color GREY_D(0.5f, 0.5f, 0.5f);
const Color GREY_L(0.6f, 0.6f, 0.6f);
const Color ORANGE(1.0f, 0.65f, 0.0f);


// Generic class to render and animate an object
class Form
{
protected:
    Color col;
    Animation anim;
    GLuint texture_id{};
public:
    Animation &getAnim() { return anim; }

    void setAnim(Animation ani) { this->anim = ani; }

    // This method should update the anim object with the corresponding physical model
    // It has to be done in each inherited class, otherwise all forms will have the same movements !
    // Virtual method for dynamic function call
    // Pure virtual to ensure all objects have their physics implemented
    virtual void update(double delta_t)=0;

    // Virtual method : Form is a generic type, only setting color and reference position
    virtual void render();

    virtual void setTexture(GLuint textureID) { this->texture_id = textureID; }
    void setColor(Color color) { this->col = color; }
};

#endif // FORMS_H_INCLUDED
