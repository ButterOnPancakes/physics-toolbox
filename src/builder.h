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
            .radius = 10,
            .mass = 0.1,
        };

        virtual ~Object() {}

        virtual void apply_forces(std::vector<Object *> objects);
        void update(std::vector<Object *> objects, std::vector<Wall> walls, double DT);
        virtual void draw(SDL_Renderer *renderer);
};

class FixedObject : public Object {
    public:
        
        void apply_forces(std::vector<Object *> objects) override;
        void draw(SDL_Renderer *renderer) override;
};

class Spring : public Object {
    public:
        Object* obj1;
        Object* obj2;
        double l0;
        double k;

        void init(Object *obj1, Object *obj2);
        void apply_forces(std::vector<Object *> objects) override;
        void draw(SDL_Renderer *renderer) override;
};

class Particle : public Object {
    public:
        double charge;
        
        void apply_forces(std::vector<Object *> objects) override;
        void draw(SDL_Renderer *renderer) override;
};

void add_box(std::vector<Wall> *walls, double x, double y, double width, double height);

#endif