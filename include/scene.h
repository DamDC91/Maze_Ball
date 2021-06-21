#ifndef SCENE_H_INCLUDED
#define SCENE_H_INCLUDED

#include <floor.h>
#include <wall.h>
#include <sphere.h>
#include <vector>


class Scene 
{
private:

    std::vector<Wall*> walls;
    Floor *floor;
    std::vector<Sphere*> spheres;

public:
    Scene();
    void SetWalls(std::vector<Wall*> walls) { this->walls = walls; };
    void setFloor(Floor* floor) { this->floor = floor; };
    void setSpheres(std::vector<Sphere*> spheres) { this->spheres = spheres; };

    void addWall(Wall* wall) { this->walls.push_back(wall); };
    void addSphere(Sphere* sphere) { this->spheres.push_back(sphere); };

    void render(const Point &cam_pos, float angle = 0.0) const;
    void update(double delta_t);
};

#endif