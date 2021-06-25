#ifndef INIT_H_INCLUDED
#define INIT_H_INCLUDED

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_opengl.h>
#include <GL/glu.h>

#include "forms.h"


const int SCREEN_WIDTH = 640 * 2;
const int SCREEN_HEIGHT = 480 * 2;

// Max number of forms : static allocation
const int MAX_FORMS_NUMBER = 10;

// Animation actualization delay (in ms) => 100 updates per second
const Uint32 ANIM_DELAY = 10;

// Starts up SDL, creates window, and initializes OpenGL
bool init(SDL_Window **window, SDL_GLContext *context);

// Initializes matrices and clear color
bool initGL();

// Updating forms for animation
void update(Form *formlist[MAX_FORMS_NUMBER], double delta_t);

// Renders scene to the screen
void render(Form *formlist[MAX_FORMS_NUMBER], const Point &cam_pos);

// Frees media and shuts down SDL
void close(SDL_Window **window);

//Loading texture
void img2GLuint(GLuint &textureID, const char *imgFile);

#endif