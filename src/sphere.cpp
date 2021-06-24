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

    double theta = this->anim.getTheta(); // rad
    double phi = this->anim.getPhi();     //rad

   // std::cout << "theta " << this->anim.getTheta() << std::endl;
   // std::cout << "phi " << this->anim.getPhi() << std::endl;

    //conversion in cartesian
    Vector s = Vector(sin(theta)*sin(phi), cos(theta), sin(theta)*cos(phi));

    glPushMatrix();
    glTranslated(this->anim.getPos().x, this->anim.getPos().y, this->anim.getPos().z);
    glBegin(GL_LINES);
    {
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex3i(2*s.x, 2*s.y, 2*s.z);
    }
    glEnd();
    glPopMatrix();

    //rotation
   // std::cout <<"s :" << s << std::endl;
    s=rotate_u(s,axe,-delta_angle);
    //std::cout <<"s :" << s << std::endl;
    if (s.is_valid())
    {
        //conversion in spheric
        theta = acos(s.y);
        
        std::cout << s.x<<"/"<<s.z << "         y : "<<s.y << std::endl;
       // if (abs(s.x) < 1e-9)
       //     s.x = 0.0;
   
        phi = atan2(s.x,s.z);
        //phi=atan(s.y/s.x);
        if (phi < 0)
            phi = phi + 2* M_PI;

        this->anim.setPhi(phi);
        this->anim.setTheta(theta);
        std::cout << "Phi : [" << phi << "]       theta : [" << theta << "]"<< std::endl<<std::endl; 
    }

}


void Sphere::render()
{
    ////// Debugging rotation /////
    /* 
    double theta = this->anim.getTheta(); // rad
    double phi = this->anim.getPhi();     // rad

    //conversion in cartesian
    Vector s = Vector(sin(theta)*sin(phi), cos(theta), sin(theta)*cos(phi));

    glPushMatrix();
    glTranslated(this->anim.getPos().x, this->anim.getPos().y, this->anim.getPos().z);
    glBegin(GL_LINES);
    {
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex3f(0, 0, 0);
        glVertex3f(0.5*s.x, 0.5*s.y, 0.5*s.z);


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
    glPopMatrix();
    */

    GLUquadric *quad;

    quad = gluNewQuadric();

    Form::render(); // Position the form and assign its color

    // Mise en route de la texture associee
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture_id);
    gluQuadricTexture(quad, texture_id);
    gluQuadricNormals(quad, GLU_SMOOTH);


    gluSphere(quad, this->radius, 100, 20);

    gluDeleteQuadric(quad);

    // Ne plus appliquer la texture pour la suite
    glDisable(GL_TEXTURE_2D);
}
