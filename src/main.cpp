#include <SDL3/SDL.h>

#include "shapes.h"
#include "vector2d.h"
#include "physics.h"
#include "builder.h"
#include "utils.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
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
    add_box(&walls, window_width / 2., window_height / 2., window_width - 50, window_height - 50);

    Particle* ball = new Particle();
    ball->comp.mass = MASS_PROTON;
    ball->comp.pos = {(double) window_width / 2, (double) window_height / 2};
    ball->charge = CHARGE;
    objects.push_back(ball);

    Particle* ball2 = new Particle();
    ball2->comp.mass = MASS_ELECTRON;
    ball2->comp.pos = {(double) window_width / 2 + 100, (double) window_height / 2 + 100};
    ball2->comp.vel = {6, -6};
    ball2->charge = -CHARGE;
    objects.push_back(ball2);

    /*Spring* spring = new Spring();
    spring->comp.pos = {(double) window_width / 2, (double) 40};
    spring->k = 1;
    spring->l0 = 0;
    spring->init(ball);
    objects.push_back(spring);*/

    bool running = true;
    while(running) {
        float x, y;
        SDL_GetMouseState(&x, &y);
        //ball2->comp.pos.x = x; ball2->comp.pos.y = y;
        //spring->comp.pos.x = x; spring->comp.pos.y = y;

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
                }
            }
        }

        for(Object* obj : objects) obj->update(objects, walls);
        
        SDL_RenderBackground(renderer, SDL_BLACK);
        
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
    }
	
    for(Object* obj : objects) delete obj;
    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}