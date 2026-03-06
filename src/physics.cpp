#include "physics.h"

#include "vector2d.h"

#include <vector>
#include <stdio.h>

int max_width = 1280;
int max_height = 720;

double MAX_VEL = 200;

void collide_wall(PhysicsComponent *comp, PhysicsComponent *newcomp, Wall wall) {
    double dot = vector_dot(wall.norm, comp->vel);
    if(dot < 0) {
        newcomp->pos = comp->pos; //Annule le mvmt
        
        newcomp->vel = vector_flip(newcomp->vel, wall.norm);
        //printf("Collisions : %f\n", reaction.get_norm());
    }
}

void update_pfd(PhysicsComponent *comp, std::vector<Wall> walls) {
    //printf("Position / Velocity / Accel 2 : %f / %f / %f\n", comp->pos.y, comp->vel.get_norm(), comp->acc.get_norm());
    
    Vector2D new_vel = vector_sum(comp->vel, comp->acc);
    if(new_vel.get_norm() > MAX_VEL) {
        new_vel = vector_scalar(vector_normalise(new_vel), MAX_VEL);
    }
    PhysicsComponent newcomp = {
        .pos = vector_sum(comp->pos, new_vel),
        .vel = new_vel,
        .acc = comp->acc,
        .radius = comp->radius,
        .mass = comp->mass,
    };

    for(int i = 0; i < (int)walls.size(); i++) {
        Vector2D dir = vector_sub(newcomp.pos, walls[i].pos);

        //One-way walls
        if(vector_dot(dir, walls[i].norm) < 0) collide_wall(comp, &newcomp, walls[i]);
    }

    *comp = newcomp;
    
    //printf("Position / Velocity / Accel 2 : %f / %f / %f\n", comp->pos.y, comp->vel.get_norm(), comp->acc.get_norm());
}