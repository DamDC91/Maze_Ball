#include "scene.h"
#include "GL/glu.h"

Scene::Scene() : alpha(0.0), beta(0.0), inc(0.4)
{
    floor = nullptr;
}

void Scene::render(const Point &cam_pos, float angle) const
{
    // Clear color buffer and Z-Buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.12, 0.12, 0.12, 0.0);

    // Initialize Modelview Matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Set the camera position and parameters
    gluLookAt(cam_pos.x, cam_pos.y, cam_pos.z, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    glRotated(20,1,0,0);
    glRotated(angle, 0, 1, 0);

    glPushMatrix();
    glBegin(GL_LINES);
    {
        glColor3f(1.0f, 0.0f, 0.5f);
        glVertex3f(-2.5, 0, -2.5);
        glVertex3f(-2.5, 0, 2.5);

        glVertex3f(-2.5, 0, 2.5);
        glVertex3f(2.5, 0, 2.5);

        glVertex3f(2.5, 0, 2.5);
        glVertex3f(2.5, 0, -2.5);

        glVertex3f(2.5, 0, -2.5);
        glVertex3f(-2.5, 0, -2.5);  
    }
    glEnd();
    glPopMatrix();
    

    glPushMatrix();
    glRotated(alpha, 1, 0, 0);
    glRotated(beta, 0, 0, 1);

    floor->render();

    for (auto wall : this->walls)
    {
        for (auto sphere : this->spheres)
        {
            wall->collisionSphere(*sphere, this->floor->getNormal());
        }
    }

    for (auto wall : this->walls)
    {
        wall->render();
    }
    for (auto sphere : this->spheres)
    {
        sphere->render();
    }
    glPopMatrix();
}

void Scene::update(double delta_t)
{
    this->floor->update(delta_t);
    for (auto &wall : this->walls)
    {
        wall->update(delta_t);
    }
    for (auto &sphere : this->spheres)
    {
        sphere->update(delta_t, this->alpha, this->beta);
    }
}
