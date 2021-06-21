#include "scene.h"
#include "GL/glu.h"

#include <iostream>

Scene::Scene()
{
    floor = nullptr;
}

void Scene::render(const Point &cam_pos, float angle) const
{
    // Clear color buffer and Z-Buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Initialize Modelview Matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Set the camera position and parameters
    gluLookAt(cam_pos.x, cam_pos.y, cam_pos.z, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    // Isometric view
    glRotated(-45, 0, 1, 0);
    glRotated(30, 1, 0, -1);

    glRotated(angle, 0, 1, 0);

    // X, Y and Z axis
    glPushMatrix(); // Preserve the camera viewing point for further forms
    // Render the coordinates system
    glBegin(GL_LINES);
    {
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex3i(0, 0, 0);
        glVertex3i(1, 0, 0);
        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex3i(0, 0, 0);
        glVertex3i(0, 1, 0);
        glColor3f(0.0f, 0.0f, 1.0f);
        glVertex3i(0, 0, 0);
        glVertex3i(0, 0, 1);
    }
    glEnd();
    glPopMatrix(); // Restore the camera viewing point for next object


    floor->render();
    for(size_t i=0;i<this->walls.size();i++)
    {
        this->walls[i]->render();
    }
    for(size_t i=0;i<this->spheres.size();i++)
    {
        this->spheres[i]->render();
    }
}

void Scene::update(double delta_t)
{
    this->floor->update(delta_t);
    for(size_t i=0;i<this->walls.size();i++)
    {
        this->walls[i]->update(delta_t);
    }
    for(size_t i=0;i<this->spheres.size();i++)
    {
        this->spheres[i]->update(delta_t);
    }
}