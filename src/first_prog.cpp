// Using SDL, SDL OpenGL and standard IO
#include <vector>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include "init.h"
// Module for space geometry
#include "geometry.h"
// Module for generating and rendering forms
#include "forms.h"
#include "sphere.h"
#include "cuboid.h"
#include "wall.h"
#include "floor.h"
#include "scene.h"


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

        // Scene object declaration  

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


        Wall *right = new Wall(Point(floor_length / 2, floor_depth / 2, (-floor_width / 2) + wall_thickness),
                               Vector(0, 0, 1),
                               Vector(0, 1, 0),
                               floor_width - 2 * wall_thickness, wall_height, wall_thickness, wall_color);


        std::vector<Wall *> walls = {back, front, left, right};

        double off_x = -floor_length / 2;
        double off_z = -floor_width / 2;
        double off_y = floor_depth / 2;
        Vector u = Vector(floor_length / 5, wall_height, floor_width / 5);

        // Labyrinth

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
        #ifdef __linux__
            img2GLuint(texMarble, "images/bille_2.jpg");
            img2GLuint(texField, "images/plateau_2.jpg");
            img2GLuint(texGrey, "images/gris.jpg");
            img2GLuint(texBackground, "images/fond.jpg");
        #elif _WIN32
            img2GLuint(texMarble, "images\\bille_2.jpg");
            img2GLuint(texField, "images\\plateau_2.jpg");
            img2GLuint(texGrey, "images\\gris.jpg");
            img2GLuint(texBackground, "images\\fond.jpg");
        #endif
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
        // While application is running
        while (!quit)
        {
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
                            case SDLK_l:
                                angle += 1;
                                break;
                            case SDLK_m:
                                angle -= 1;
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
