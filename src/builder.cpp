#include "builder.h"

#include <stdio.h>
#include "utils.h"

void Object::apply_forces(std::vector<Object *> /*objects*/) {
    comp.acc = vector_sum(comp.acc, {0, g});
}
void Object::update(std::vector<Object *> objects, std::vector<Wall> walls, double DT) {
    apply_forces(objects);
    comp = update_pfd(comp, walls, DT);
    comp.acc = {0, 0}; // L'acceleration est compute chaque frame
}
void Object::draw(SDL_Renderer *renderer) {
    SDL_RenderCircle(renderer, comp.pos.x, comp.pos.y, comp.radius, comp.radius / 5, SDL_WHITE);
}

void FixedObject::apply_forces(std::vector<Object *> /*objects*/) {
    comp.acc = {0, 0};
    comp.vel = {0, 0};
}
void FixedObject::draw(SDL_Renderer *renderer) {
    SDL_RenderFilledCircle(renderer, comp.pos.x, comp.pos.y, 10, SDL_BLUE);
}

void Spring::init(Object *obj1, Object *obj2) {
    this->obj1 = obj1;
    this->obj2 = obj2;
}
void Spring::apply_forces(std::vector<Object *> /*objects*/) {
    if(obj1 == NULL || obj2 == NULL) return;
    Vector2D dist = vector_sub(obj2->comp.pos, obj1->comp.pos);
    double length = dist.get_norm();
    if (length > 1e-3) {
        Vector2D dir = vector_normalise(dist);
        double displacement = length - l0;
        Vector2D spring_force = vector_scalar(dir, k * displacement);

        obj1->comp.acc = vector_sum(obj1->comp.acc, vector_scalar(spring_force, 1.0 / obj1->comp.mass));
        obj2->comp.acc = vector_sum(obj2->comp.acc, vector_scalar(spring_force, - 1.0 / obj2->comp.mass));
    }
}
void Spring::draw(SDL_Renderer *renderer) {
    if(obj1 == NULL || obj2 == NULL) return;
    Vector2D dist = vector_sub(obj1->comp.pos, obj2->comp.pos);
    SDL_RenderVector(renderer, dist, obj2->comp.pos.x, obj2->comp.pos.y, SDL_WHITE);
}

void Particle::apply_forces(std::vector<Object *> objects) {
    for(Object *obj : objects) {
        if(obj == this) continue;
        Particle* part = dynamic_cast<Particle*>(obj);
        if(part != NULL) {
            Vector2D dist = vector_sub(comp.pos, obj->comp.pos);
            
            Vector2D uni = vector_normalise(dist);
            if(dist.get_norm() < 1e-1) continue;
            
            float coef = part->charge * this->charge / (comp.mass * 4 * M_PI * EPSILON_0 * dist.get_norm() * dist.get_norm());
            Vector2D elec_acc = vector_scalar(uni, coef);
            comp.acc = vector_sum(comp.acc, elec_acc);
        }
    }
    Object::apply_forces(objects);
}
void Particle::draw(SDL_Renderer *renderer) {
    SDL_RenderCircle(renderer, comp.pos.x, comp.pos.y, comp.radius, comp.radius / 5, charge > 0 ? SDL_YELLOW : SDL_RED);
}

void add_box(std::vector<Wall> *walls, double x, double y, double width, double height) {
    //Box
    walls->push_back((Wall) {.pos = {x - width / 2, y}, .norm = {1, 0}}); //Left
    walls->push_back((Wall) {.pos = {x + width / 2, y}, .norm = {-1, 0}}); //Right
    walls->push_back((Wall) {.pos = {x, y - height / 2}, .norm = {0, 1}}); //Up
    walls->push_back((Wall) {.pos = {x, y + height / 2}, .norm = {0, -1}}); //Bottom
}