#ifndef SCENE_H_INCLUDED
#define SCENE_H_INCLUDED

#include <utility>
#include <vector>

#include "floor.h"
#include "wall.h"
#include "sphere.h"


class Scene
{
private:
    double alpha, beta, inc;
    std::vector<Wall *> walls;
    Floor *floor;
    std::vector<Sphere *> spheres;

public:

    Scene();

    void SetWalls(std::vector<Wall *> newWalls) { this->walls = std::move(newWalls); };

    void setFloor(Floor *newFloor) { this->floor = newFloor; };

    void setSpheres(std::vector<Sphere *> newSpheres) { this->spheres = std::move(newSpheres); };

    void addWall(Wall *wall) { this->walls.push_back(wall); };

    void addSphere(Sphere *sphere) { this->spheres.push_back(sphere); };

    void incAlpha() { alpha += inc; };

    void decAlpha() { alpha -= inc; };

    void incBeta() { beta += inc; };

    void decBeta() { beta -= inc; };

    void render(const Point &cam_pos, float angle = 0.0) const;

    void update(double delta_t);

};

#endif//SCENE_H_INCLUDED