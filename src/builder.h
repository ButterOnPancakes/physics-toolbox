#ifndef BUILDER_H
#define BUILDER_H

#include "physics.h"
#include "vector2d.h"
#include "shapes.h"

#include <vector>
#include <SDL3/SDL.h>

class Object {
    public:
        PhysicsComponent comp = {
            .pos = {},
            .vel = {0, 0},
            .acc = {0, 0},
            .radius = 20,
            .mass = 100,
        };

        virtual ~Object() {}

        virtual void update(std::vector<Object *> objects, std::vector<Wall> walls);
        virtual void draw(SDL_Renderer *renderer);
};

class Spring : public Object {
    public:
        Object* moving;
        double l0;
        double k;

        void init(Object *obj);
        void update(std::vector<Object *> objects, std::vector<Wall> walls) override;
        void draw(SDL_Renderer *renderer) override;
};

class Particle : public Object {
    public:
        double charge;
        
        void update(std::vector<Object *> objects, std::vector<Wall> walls) override;
        void draw(SDL_Renderer *renderer) override;
};

void add_box(std::vector<Wall> *walls, double x, double y, double width, double height);

#endif