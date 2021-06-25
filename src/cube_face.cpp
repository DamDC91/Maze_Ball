#include <GL/glu.h>
#include "sphere.h"
#include "cube_face.h"


CubeFace::CubeFace(Vector v1, Vector v2, Point org, double l, double w, Color cl)
{
    vdir1 = 1.0 / v1.norm() * v1;
    vdir2 = 1.0 / v2.norm() * v2;
    anim.setPos(org);
    length = l;
    width = w;
    col = cl;
}

void CubeFace::update(double delta_t)
{
    // Nothing to do here
}

void CubeFace::render()
{
    Point p1 = Point();
    Point p2 = p1, p3, p4 = p1;
    p2.translate(length * vdir1);
    p3 = p2;
    p3.translate(width * vdir2);
    p4.translate(width * vdir2);

    // Autorisation de la texture choisie a la creation de la face (cf main())
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture_id);

    Form::render();

    glBegin(GL_QUADS);
    {
        glTexCoord2f(0.0f, 0.0f);
        glVertex3d(p1.x, p1.y, p1.z);
        glTexCoord2f(1.0f, 0.0f);
        glVertex3d(p2.x, p2.y, p2.z);
        glTexCoord2f(1.0f, 1.0f);
        glVertex3d(p3.x, p3.y, p3.z);
        glTexCoord2f(0.0f, 1.0f);
        glVertex3d(p4.x, p4.y, p4.z);
    }
    glEnd();

    // Ne plus appliquer la texture pour la suite
    glDisable(GL_TEXTURE_2D);
}

bool CubeFace::collisionSphere(Sphere &sphere, Vector floor_normal)
{
    Vector horizontal; // horizontal face direction
    Vector vertical; // vertical face direction

    if (std::abs(floor_normal * this->vdir1) < 1e-6)
    { // vdir1 orthogonal to the floor <-> vdir1 = horizontal direction
        horizontal = this->vdir1 * this->length;
        vertical = this->vdir2 * this->width;
    }
    else
    {
        horizontal = this->vdir2 * this->width;
        vertical = this->vdir1 * this->length;
    }

    Point face_h1 = this->anim.getPos();
    Point face_h2 = Point(face_h1.x + horizontal.x, face_h1.y + horizontal.y, face_h1.z + horizontal.z);

    Vector h1_to_sph = Vector(face_h1, sphere.getAnim().getPos());
    Vector h2_to_sph = Vector(face_h2, sphere.getAnim().getPos());

    // algebraic distance from the origin of the face to the sphere, along the horizontal axis of the wall
    double d_horizontal = h1_to_sph * horizontal * (1.0 / horizontal.norm());
    double d_wall = h1_to_sph * this->getNormal(); // algebraic distance to the wall
    double d_h1_to_sph = (vertical ^ h1_to_sph).norm() * (1.0 / vertical.norm());
    double d_h2_to_sph = (vertical ^ h2_to_sph).norm() * (1.0 / vertical.norm());

    bool collides_face =
            std::abs(d_wall) <= sphere.getRadius() && (d_horizontal > 0 && d_horizontal <= horizontal.norm());
    bool collides_h1 = std::abs(d_h1_to_sph) <= sphere.getRadius();
    bool collides_h2 = std::abs(d_h2_to_sph) <= sphere.getRadius();

    Vector correction;

    if (collides_face)
    {
        correction = std::abs(sphere.getRadius() - d_wall) * this->getNormal();
    }
    else
    {
        if (collides_h1)
        {
            Vector vc1 = h1_to_sph * Vector(1, 0, 0) * Vector(1, 0, 0) + h1_to_sph * Vector(0, 0, 1) * Vector(0, 0, 1);
            correction = std::abs(sphere.getRadius() - d_h1_to_sph) * vc1;
        }

        if (collides_h2)
        {
            Vector vc2 = h2_to_sph * Vector(1, 0, 0) * Vector(1, 0, 0) + h2_to_sph * Vector(0, 0, 1) * Vector(0, 0, 1);
            correction = std::abs(sphere.getRadius() - d_h2_to_sph) * vc2;
        }
    }

    if (collides_face || collides_h1 || collides_h2)
    {
        // correction of the position of sphere
        Point new_pos = sphere.getAnim().getPos();
        new_pos.translate(correction);
        sphere.getAnim().setPos(new_pos);

        // modifying sphere speed
        Vector vI = sphere.getAnim().getSpeed();
        Vector vS;
        double A = 1;

        Vector normal;
        if (collides_face)
        {
            normal = this->getNormal();
            double K = 0.65;
            // F = cos(incident angle)
            double F = std::abs(this->getNormal() * (vI * (1.0 / vI.norm())));
            // (K - 1) * cos(incident angle) + 1
            // no attenuation when the incident angle equals 90 degrees.
            A = (K - 1) * F + 1;
        }
        else if (collides_h1)
        {
            normal = this->getNormal() - (horizontal * (1.0 / horizontal.norm()));
            normal = normal * (1.0 / normal.norm());
        }
        else
        {
            normal = this->getNormal() + (horizontal * (1.0 / horizontal.norm()));
            normal = normal * (1.0 / normal.norm());
        }

        vS = vI - 2 * (vI * normal) * normal;
        vS = vS * A;

        sphere.getAnim().setSpeed(vS);

        return true;
    }

    return false;
}
