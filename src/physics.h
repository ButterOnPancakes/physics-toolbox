#ifndef PHYSICS_H
#define PHYSICS_H

#include "vector2d.h"
#include <vector>

typedef struct {
    Vector2D pos;
    Vector2D vel;
    Vector2D acc;
    
    double radius;

    double mass;
} PhysicsComponent;

typedef struct {
    Vector2D pos;
    Vector2D norm;
} Wall;

PhysicsComponent update_pfd(PhysicsComponent comp, std::vector<Wall> walls, double DT);

#endif