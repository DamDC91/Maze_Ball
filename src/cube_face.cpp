#include <GL/glu.h>
#include "sphere.h"
#include "cube_face.h"


CubeFace::CubeFace(Vector v1, Vector v2, Vector n, Point org, double l, double w, Color cl)
{
    vdir1 = 1.0 / v1.norm() * v1;
    vdir2 = 1.0 / v2.norm() * v2;
    normal = 1.0 / n.norm() * n;
    anim.setPos(org);
    length = l;
    width = w;
    col = cl;
}

void CubeFace::update(double delta_t)
{
    // Complete this part
    //  this->anim.setTheta(this->anim.getTheta() + 0.3);
    //  this->anim.setPhi(this->anim.getPhi() + 0.3);
}

void CubeFace::render()
{
    Point p1 = Point();
    Point p2 = p1, p3, p4 = p1;
    p2.translate(length * vdir1);
    p3 = p2;
    p3.translate(width * vdir2);
    p4.translate(width * vdir2);

    Form::render();

    glBegin(GL_QUADS);
    {
        glVertex3d(p1.x, p1.y, p1.z);
        glVertex3d(p2.x, p2.y, p2.z);
        glVertex3d(p3.x, p3.y, p3.z);
        glVertex3d(p4.x, p4.y, p4.z);
    }
    glEnd();
}

bool CubeFace::collisionSphere(Sphere &sphere, Vector floor_normal)
{
    Vector horizontal; // horizontal face direction
    Vector vertical; // vertical face direction

    if (floor_normal * this->vdir1 < 1e-6)
    { // vdir1 orthogonal to the floor <-> vdir1 = horizontal direction
        horizontal = this->vdir1;
        vertical = this->vdir2;
    }
    else
    {
        horizontal = this->vdir2;
        vertical = this->vdir1;
    }

    Point face_h1 = this->anim.getPos();
    Point face_h2 = {face_h1.x + horizontal.x, face_h1.y + horizontal.y, face_h1.z + horizontal.z};

    Vector h1_to_sph = Vector(face_h1, sphere.getAnim().getPos());
    Vector h2_to_sph = Vector(face_h2, sphere.getAnim().getPos());

    // algebraic distance from the origin of the face to the sphere, along the horizontal axis of the wall
    double d_horizontal = h1_to_sph * horizontal;
    double d_wall = h1_to_sph * this->getNormal(); // algebraic distance to the wall
    double d_h1_to_sph = (h1_to_sph ^ vertical).norm() * (1.0 / vertical.norm());
    double d_h2_to_sph = (h2_to_sph ^ vertical).norm() * (1.0 / vertical.norm());

    bool collides_face = std::abs(d_wall) <= sphere.getRadius() && (d_horizontal > 0 && d_horizontal <= this->length);
    bool collides_h1 = std::abs(d_h1_to_sph) <= sphere.getRadius();
    bool collides_h2 = std::abs(d_h2_to_sph) <= sphere.getRadius();


    Vector correction;

    if (collides_face)
    {
        correction = std::abs(sphere.getRadius() - d_wall) * this->getNormal();
    }
    
    if (collides_h1)
    {
        correction = std::abs(sphere.getRadius() - d_h1_to_sph) * h1_to_sph;
    }

    if (collides_h2)
    {
        correction = std::abs(sphere.getRadius() - d_h2_to_sph) * h2_to_sph;
    }

    if (collides_face || collides_h1 || collides_h2)
    {
        // correction of the position of sphere
        Point new_pos = sphere.getAnim().getPos();
        new_pos.translate(correction);
        sphere.getAnim().setPos(new_pos);

        // modifying sphere speed
        Vector speed = sphere.getAnim().getSpeed();
        sphere.getAnim().setSpeed(speed - 2 * (speed * this->getNormal()) * this->getNormal() * 0.90);

        return true;
    }

    return false;
}
