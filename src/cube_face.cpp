#include <GL/glu.h>
#include "sphere.h"
#include "cube_face.h"


CubeFace::CubeFace(Vector v1, Vector v2, Vector n, Point org, double l, double w, Color cl)
{
    vdir1 = 1.0 / v1.norm() * v1;
    vdir2 = 1.0 / v2.norm() * v2;
    normal = 1.0 /n.norm() * n;
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

bool CubeFace::collisionSphere(Sphere sphere, Vector floor_normal)
{
    return collisionSphere(sphere.getAnim().getPos(), sphere.getRadius(), floor_normal);
}

bool CubeFace::collisionSphere(Point sph_pos, double radius, Vector floor_normal)
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

    Vector h1_to_sph = Vector(face_h1, sph_pos);
    Vector h2_to_sph = Vector(face_h2, sph_pos);
    Vector face_normal = horizontal ^vertical; // normalized because vdir1 and vdir2 are normalized

    double a = h1_to_sph * horizontal; // algebraic distance
    bool collides_face = std::abs(h1_to_sph * face_normal) <= radius && (a > 0 && a <= this->length);
    bool collides_h1 = (h1_to_sph ^ vertical).norm() * (1.0 / vertical.norm()) <= radius;
    bool collides_h2 = (h2_to_sph ^ vertical).norm() * (1.0 / vertical.norm()) <= radius;

    return collides_face || collides_h1 || collides_h2;
}
