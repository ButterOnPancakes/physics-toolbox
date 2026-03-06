#include <SDL3/SDL.h>

#include "shapes.h"
#include "vector2d.h"
#include "physics.h"
#include "builder.h"
#include "utils.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <vector>

using namespace std;

int window_width = 1280;
int window_height = 720;

int main() {
    if(!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS)) {
        printf("Video not initialised\n");
        return EXIT_FAILURE;
    }
    
    SDL_Window *window = SDL_CreateWindow("Simple Physics Simulation", window_width, window_height, 0);
    if(!window) {
        printf("Window could not be created\n");
        return EXIT_FAILURE;
    }
    SDL_Renderer *renderer = SDL_CreateRenderer(window, NULL);
    if(!renderer) {
        printf("Renderer could not be created\n");
        return EXIT_FAILURE;
    }

    vector<Object*> objects;
    vector<Wall> walls;
    //add_box(&walls, window_width / 2., window_height / 2., window_width - 50, window_height - 50);

    /*Particle* proton = new Particle();
    proton->comp.mass = MASS_PROTON;
    proton->comp.pos = {(double) window_width / 2, (double) window_height / 2};
    proton->charge = CHARGE;
    objects.push_back(proton);

    Particle* electron = new Particle();
    electron->comp.mass = MASS_ELECTRON;
    electron->comp.pos = {(double) window_width / 2 + 100, (double) window_height / 2 + 100};
    electron->comp.vel = {6, -6};
    electron->charge = -CHARGE;
    objects.push_back(electron);*/

    int space = 5;
    int amount = (window_width) / (double) space - 1;

    Object* start = new Object();
    start->comp.pos = {0, (double) window_height / 2};
    objects.push_back(start);

    for(int i = 1; i < amount; i++) {
        Object* obj = new Object();
        obj->comp.radius = 5;
        obj->comp.pos = {(double) i * space, (double) window_height / 2};
        objects.push_back(obj);
    }
    int size = objects.size();

    FixedObject* end = new FixedObject();
    end->comp.pos = {(double) size * space, (double) window_height / 2};
    objects.push_back(end);

    for(int i=0; i < size; i++) {
        Spring* spring = new Spring();
        spring->k = 250;
        spring->l0 = 0;
        spring->init(objects[i], objects[i+1]);
        objects.push_back(spring);
    }

    double time = 0;
    bool running = true;
    bool pause = false;
    while(running) {
        SDL_Event event;
        while(SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_EVENT_QUIT: {
                    running = false;
                    break;
                }
                case SDL_EVENT_KEY_UP: {
                    if(event.key.scancode == SDL_SCANCODE_ESCAPE) {
                        running = false;
                        break;
                    }
                    if(event.key.scancode == SDL_SCANCODE_SPACE) {
                        pause = !pause;
                        break;
                    }
                }
            }
        }
        if(!pause) {
            for(Object* obj : objects) obj->update(objects, walls);

            float x, y;
            SDL_GetMouseState(&x, &y);
            start->comp.pos.x = 0;
            start->comp.vel.x = 0;
            //start->comp.pos.y = window_height / 2 + 100 * sin(5 * time);
            //end->comp.pos.x = window_width - 100 + 10 * sin(3 * time);
            end->comp.pos.y = window_height / 2 - 100 * sin(3.2 * time);
        }

        //Drawing things
        SDL_RenderBackground(renderer, SDL_BLACK);
        SDL_RenderFilledRectangle(renderer, window_width - 100, 50, 50, 50, pause ? SDL_RED : SDL_GREEN);
        
        for(Object* obj : objects) obj->draw(renderer);

        double scalar = 800;
        for(Wall w : walls) {
            Vector2D perp = vector_rotate(w.norm, M_PI/2);
            Vector2D pos = vector_sub(w.pos, vector_scalar(perp, scalar));
            SDL_RenderVector(renderer, vector_scalar(w.norm, 20), w.pos.x, w.pos.y, SDL_GREEN);
            SDL_RenderVector(renderer, vector_scalar(perp, 2 * scalar), pos.x, pos.y, SDL_GREEN);
        }
        
        SDL_RenderPresent(renderer);

        SDL_Delay(16.67);
        if(!pause) time += 16.67 * 1e-3;
    }
	
    for(Object* obj : objects) delete obj;
    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}