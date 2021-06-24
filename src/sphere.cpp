#include <GL/glu.h>
#include <animation.h>
#include <sphere.h>
#include <matrix.h>
#include <cmath>


Sphere::Sphere(double r, Point org, Color cl)
{
    radius = r;
    anim = Animation(0.0, 0.0, Vector(0.0, 0.0, 0.0), Vector(0.0, 0.0, 0.0), org);
    col = cl;
}

Sphere::Sphere(double r, Color cl) : Sphere(r, Point(), cl) {}


void Sphere::update(double delta_t)
{
    // Complete this part

}

void Sphere::update(double delta_t, double alpha, double beta)
{
    Vector g(0, -9.81, 0);

    Vector newG = rotate_x(g, -alpha * M_PI / 180.0);
    newG = rotate_z(newG, -beta * M_PI / 180.0);


    Vector newG2 = (newG * Vector(1, 0, 0)) * Vector(1, 0, 0);
    newG2 = newG2 + (newG * Vector(0, 0, 1)) * Vector(0, 0, 1);

    this->anim.setAccel(newG2);


    this->anim.setSpeed(this->anim.getSpeed() + delta_t * this->anim.getAccel());
    Point P = this->anim.getPos();
    Vector V = delta_t * this->anim.getSpeed();
    P.x = P.x + V.x;
    P.y = P.y + V.y;
    P.z = P.z + V.z;
    this->anim.setPos(P);


    //angular speed
    double angular_speed = this->anim.getSpeed().norm() / this->radius; // rad / s
    double delta_angle = delta_t * angular_speed; // rad

    // axe of rotation
    Vector axe = this->anim.getSpeed() ^Vector(0, 1, 0);
    axe = 1.0 / axe.norm() * axe;

    double theta = this->anim.getTheta() * M_PI / 180.0; // rad
    double phi = this->anim.getPhi() * M_PI / 180.0;     //rad

    std::cout << "theta " << this->anim.getTheta() << std::endl;
    std::cout << "phi " << this->anim.getPhi() << std::endl;

    //conversion in cartesian
    //Vector s = Vector(sin(theta)*cos(phi), sin(theta)*sin(phi), cos(theta));

    Vector s = Vector(cos(phi), sin(phi) * cos(theta), sin(phi) * sin(theta));

    //rotation
    s = rotate_u(s, axe, delta_angle);
    if (s.is_valid())
    {
        //conversion in spheric
        theta = acos(s.z);
        phi = atan2(s.y, s.x);

        this->anim.setPhi(phi * 180.0 / M_PI);
        this->anim.setTheta(theta * 180.0 / M_PI * 180.0 / M_PI);
    }

}


void Sphere::render()
{
    GLUquadric *quad;

    quad = gluNewQuadric();

    Form::render(); // Position the form and assign its color

    // Mise en route de la texture associee
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture_id);
    gluQuadricTexture(quad, texture_id);
    gluQuadricNormals(quad, GLU_SMOOTH);


    gluSphere(quad, this->radius, 20, 20);

    gluDeleteQuadric(quad);

    // Ne plus appliquer la texture pour la suite
    glDisable(GL_TEXTURE_2D);
}
