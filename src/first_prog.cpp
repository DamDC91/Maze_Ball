// Using SDL, SDL OpenGL and standard IO
#include <vector>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_opengl.h>
#include <GL/glu.h>

// Module for space geometry
#include "geometry.h"
// Module for generating and rendering forms
#include "forms.h"
#include "sphere.h"
#include "cuboid.h"
#include "wall.h"
#include "floor.h"

#include "scene.h"
/***************************************************************************/
/* Constants and functions declarations                                    */
/***************************************************************************/
// Screen dimension constants
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

/***************************************************************************/
/* Functions implementations                                               */
/***************************************************************************/
bool init(SDL_Window **window, SDL_GLContext *context)
{
    // Initialization flag
    bool success = true;

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "SDL could not initialize! SDL Error: " << SDL_GetError() << std::endl;
        success = false;
    }
    else
    {
        // Use OpenGL 2.1
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

        // Create window
        *window = SDL_CreateWindow("TP intro OpenGL / SDL 2", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                   SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
        if (*window == NULL)
        {
            std::cout << "Window could not be created! SDL Error: " << SDL_GetError() << std::endl;
            success = false;
        }
        else
        {
            // Create context
            *context = SDL_GL_CreateContext(*window);
            if (*context == NULL)
            {
                std::cout << "OpenGL context could not be created! SDL Error: " << SDL_GetError() << std::endl;
                success = false;
            }
            else
            {
                // Use Vsync
                if (SDL_GL_SetSwapInterval(1) < 0)
                {
                    std::cout << "Warning: Unable to set VSync! SDL Error: " << SDL_GetError() << std::endl;
                }

                // Initialize OpenGL
                if (!initGL())
                {
                    std::cout << "Unable to initialize OpenGL!" << std::endl;
                    success = false;
                }
            }
        }
    }

    return success;
}

bool initGL()
{
    bool success = true;
    GLenum error = GL_NO_ERROR;

    // Initialize Projection Matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Set the viewport : use all the window to display the rendered scene
    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

    // Fix aspect ratio and depth clipping planes
    gluPerspective(40.0, (GLdouble) SCREEN_WIDTH / SCREEN_HEIGHT, 1.0, 100.0);

    // Initialize Modelview Matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Initialize clear color : black with no transparency
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    // Activate Z-Buffer
    glEnable(GL_DEPTH_TEST);
    //glPolygonMode(GL_FRONT_AND_BACK,GL_LINE); // TO DISPLAY IN WIREFRAME MODE

    // Lighting basic configuration and activation
    const GLfloat light_ambient[] = {0.3f, 0.3f, 0.3f, 1.0f};
    const GLfloat light_diffuse[] = {1.0f, 1.0f, 1.0f, 1.0f};
    const GLfloat light_specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
    const GLfloat light_position[] = {2.0f, 5.0f, 5.0f, 0.0f};

    const GLfloat mat_ambient[] = {0.7f, 0.7f, 0.7f, 1.0f};
    const GLfloat mat_diffuse[] = {0.8f, 0.8f, 0.8f, 1.0f};
    const GLfloat mat_specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
    const GLfloat high_shininess[] = {100.0f};

    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);

    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);

    // Check for error
    error = glGetError();
    if (error != GL_NO_ERROR)
    {
        std::cout << "Error initializing OpenGL!  " << gluErrorString(error) << std::endl;
        success = false;
    }

    return success;
}

void close(SDL_Window **window)
{
    //Destroy window
    SDL_DestroyWindow(*window);
    *window = NULL;

    //Quit SDL subsystems
    SDL_Quit();
}

void img2GLuint(GLuint &textureID, const char * imgFile)
{
    SDL_Surface *imgsurf = IMG_Load(imgFile);
    if (imgsurf == nullptr)
    {
        printf("Failed to load texture image!\n");
        return;
    }
    // work out what format to tell glTexImage2D to use...
    int mode;
    if (imgsurf->format->BytesPerPixel == 3)
    { // RGB 24bit
        mode = GL_RGB;
    }
    else if (imgsurf->format->BytesPerPixel == 4)
    { // RGBA 32bit
        mode = GL_RGBA;
    }
    else
    {
        SDL_FreeSurface(imgsurf);
        return;
    }
    // create one texture name
    glGenTextures(1, &textureID);

    // tell opengl to use the generated texture name
    glBindTexture(GL_TEXTURE_2D, textureID);

    // this reads from the sdl imgsurf and puts it into an opengl texture
    glTexImage2D(GL_TEXTURE_2D, 0, mode, imgsurf->w, imgsurf->h, 0, mode, GL_UNSIGNED_BYTE, imgsurf->pixels);

    // these affect how this texture is drawn later on...
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // clean up
    SDL_FreeSurface(imgsurf);
}

/***************************************************************************/
/* MAIN Function                                                           */
/***************************************************************************/
int main(int argc, char *args[])
{
    // The window we'll be rendering to
    SDL_Window *gWindow = NULL;

    // OpenGL context
    SDL_GLContext gContext;

    // Start up SDL and create window
    if (!init(&gWindow, &gContext))
    {
        std::cout << "Failed to initialize!" << std::endl;
    }
    else
    {
        // Main loop flag
        bool quit = false;
        Uint32 current_time, previous_time, elapsed_time;

        // Event handler
        SDL_Event event;

        // Camera position
        Point camera_position(0, 0.0, 8.0);

        double floor_length = 5;
        double floor_width = 5;
        double floor_depth = 0.5;
        double wall_thickness = 0.1; // thickness
        double wall_height = 0.3; // height
        Color wall_color = WHITE;
        Color floor_color = WHITE;
        Color marble_color = WHITE;

        Floor *floor = new Floor(Point(-floor_length / 2, -floor_depth / 2, floor_width / 2),
                                 Vector(1, 0, 0),
                                 Vector(0, 0, -1),
                                 floor_length, floor_width, floor_depth, floor_color);

        // walls normals are pointing toward the center of the floor
        Wall *back = new Wall(Point(-floor_length / 2, floor_depth / 2, -floor_width / 2),
                              Vector(1, 0, 0),
                              Vector(0, 1, 0),
                              floor_length, wall_height, wall_thickness, wall_color);

        Wall *front = new Wall(Point(floor_length / 2, floor_depth / 2, floor_width / 2),
                               Vector(-1, 0, 0),
                               Vector(0, 1, 0),
                               floor_length, wall_height, wall_thickness, wall_color);

        Wall *left = new Wall(Point(-floor_length / 2, floor_depth / 2, (floor_width / 2) - wall_thickness),
                              Vector(0, 0, -1),
                              Vector(0, 1, 0),
                              floor_width - 2 * wall_thickness, wall_height, wall_thickness, wall_color);

//        Wall *left = new Wall(Point(-floor_length / 2, floor_depth / 2, floor_width / 2),
//                              Vector(0, 0, -1),
//                              Vector(0, 1, 0),
//                              floor_width, wall_height, wall_thickness, wall_color);

        Wall *right = new Wall(Point(floor_length / 2, floor_depth / 2, (-floor_width / 2) + wall_thickness),
                               Vector(0, 0, 1),
                               Vector(0, 1, 0),
                               floor_width - 2 * wall_thickness, wall_height, wall_thickness, wall_color);

//        Wall *right = new Wall(Point(floor_length / 2, floor_depth / 2, -floor_width / 2),
//                               Vector(0, 0, 1),
//                               Vector(0, 1, 0),
//                               floor_width, wall_height, wall_thickness, wall_color);

        std::vector<Wall *> walls = {back, front, left, right};

        double off_x = -floor_length / 2;
        double off_z = -floor_width / 2;
        double off_y = floor_depth / 2;
        Vector u = Vector(floor_length / 5, wall_height, floor_width / 5);

        Wall *maze1 = new Wall(Point(0 * u.x + off_x, 0 * u.y + off_y, 1 * u.z + off_z),
                               Vector(1, 0, 0),
                               Vector(0, 1, 0),
                               1 * u.x, wall_height, wall_thickness, wall_color);
        walls.push_back(maze1);

        Wall *maze2 = new Wall(Point(1 * u.x + off_x, 0 * u.y + off_y, 2 * u.z + off_z),
                               Vector(1, 0, 0),
                               Vector(0, 1, 0),
                               1 * u.x, wall_height, wall_thickness, wall_color);
        walls.push_back(maze2);

        Wall *maze3 = new Wall(Point(2 * u.x + off_x, 0 * u.y + off_y, 1 * u.z + off_z),
                               Vector(1, 0, 0),
                               Vector(0, 1, 0),
                               1 * u.x, wall_height, wall_thickness, wall_color);
        walls.push_back(maze3);

        Wall *maze4 = new Wall(Point(3 * u.x + off_x, 0 * u.y + off_y, 2 * u.z + off_z),
                               Vector(1, 0, 0),
                               Vector(0, 1, 0),
                               1 * u.x, wall_height, wall_thickness, wall_color);
        walls.push_back(maze4);

        Wall *maze5 = new Wall(Point(1 * u.x + off_x, 0 * u.y + off_y, 3 * u.z + off_z),
                               Vector(0, 0, 1),
                               Vector(0, 1, 0),
                               2 * u.z, wall_height, wall_thickness, wall_color);
        walls.push_back(maze5);

        Wall *maze6 = new Wall(Point(3 * u.x + off_x, 0 * u.y + off_y, 2 * u.z + off_z),
                               Vector(0, 0, 1),
                               Vector(0, 1, 0),
                               2 * u.z, wall_height, wall_thickness, wall_color);
        walls.push_back(maze6);

        Wall *maze7 = new Wall(Point(4 * u.x + off_x, 0 * u.y + off_y, 3 * u.z + off_z),
                               Vector(0, 0, 1),
                               Vector(0, 1, 0),
                               2 * u.z, wall_height, wall_thickness, wall_color);
        walls.push_back(maze7);

        Wall *maze8 = new Wall(Point(4 * u.x + off_x, 0 * u.y + off_y, 0 * u.z + off_z),
                               Vector(0, 0, 1),
                               Vector(0, 1, 0),
                               2 * u.z, wall_height, wall_thickness, wall_color);
        walls.push_back(maze8);

        Wall *maze9 = new Wall(Point(2 * u.x + off_x, 0 * u.y + off_y, 0 * u.z + off_z),
                               Vector(0, 0, 1),
                               Vector(0, 1, 0),
                               4 * u.z, wall_height, wall_thickness, wall_color);
        walls.push_back(maze9);

        double radius = 0.2;
        Sphere *sphere = new Sphere(radius, Point(u.x / 2 + off_x, off_y + radius, u.z / 2 + off_z), marble_color);

        Scene scene;
        scene.setFloor(floor);
        scene.SetWalls(walls);
        scene.setSpheres(std::vector<Sphere *>{sphere});

        float angle = 0.0;


        // Texture //////////////////////////////////////////////////////////
        GLuint texMarble, texField, texGrey, texBackground;
        img2GLuint(texMarble, "../images/bille_2.jpg");
        img2GLuint(texField, "../images/terrain.jpg");
        img2GLuint(texGrey, "../images/gris.jpg");
        img2GLuint(texBackground, "../images/fond.jpg");
        // Textures ready to be enable (private member of each form) ///////

        floor->setTexture(texGrey);
        floor->setTexture(texField, Cuboid::Front);
        sphere->setTexture(texMarble);
        for (auto & wall : walls)
        {
            wall->setTexture(texGrey);
        }

        // Get first "current time"
        previous_time = SDL_GetTicks();
        unsigned int time = SDL_GetTicks();
        unsigned int last_time = 0;
        // While application is running
        while (!quit)
        {
            time = SDL_GetTicks();
            //  angle += 0.04;

            // Handle events on queue
            while (SDL_PollEvent(&event) != 0)
            {
                int x = 0, y = 0;
                SDL_Keycode key_pressed = event.key.keysym.sym;

                switch (event.type)
                {
                    // User requests quit
                    case SDL_QUIT:
                        quit = true;
                        break;
                    case SDL_KEYDOWN:
                        // Handle key pressed with current mouse position
                        SDL_GetMouseState(&x, &y);

                        switch (key_pressed)
                        {
                            // Quit the program when 'q' or Escape keys are pressed
                            case SDLK_q:
                            case SDLK_ESCAPE:
                                quit = true;
                                break;
                            case SDLK_o:
                                camera_position.y += 0.3;
                                break;
                            case SDLK_p:
                                camera_position.y -= 0.3;
                                break;
                            case SDLK_UP:
                                scene.decAlpha();
                                break;
                            case SDLK_DOWN:
                                scene.incAlpha();
                                break;
                            case SDLK_LEFT:
                                scene.incBeta();
                                break;
                            case SDLK_RIGHT:
                                scene.decBeta();
                                break;

                            default:
                                break;
                        }
                        break;
                    default:
                        break;
                }
            }

            // Update the scene
            current_time = SDL_GetTicks(); // get the elapsed time from SDL initialization (ms)
            elapsed_time = current_time - previous_time;
            if (elapsed_time > ANIM_DELAY)
            {
                previous_time = current_time;

                scene.update(1e-3 * elapsed_time); // International system units : seconds
            }

            if (1e-3 * time >= last_time + 1)
            {
                last_time = 1e-3 * time;
                std::cout << last_time << " s" << std::endl;
            }

            // Render the scene
            scene.render(camera_position, angle);

            // Update window screen
            SDL_GL_SwapWindow(gWindow);
        }
    }

    // Free resources and close SDL
    close(&gWindow);

    return 0;
}
