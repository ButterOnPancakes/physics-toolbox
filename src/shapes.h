#ifndef SHAPES_H
#define SHAPES_H

#include <SDL3/SDL.h>

#include "vector2d.h"

#define SDL_WHITE ((SDL_Color) {255, 255, 255, 255})
#define SDL_RED ((SDL_Color) {255, 0, 0, 255})
#define SDL_GREEN ((SDL_Color) {0, 255, 0, 255})
#define SDL_BLUE ((SDL_Color) {0, 0, 255, 255})
#define SDL_YELLOW ((SDL_Color) {255, 255, 0, 255})
#define SDL_ORANGE ((SDL_Color) {255, 128, 0, 255})
#define SDL_BLACK ((SDL_Color) {0, 0, 0, 255})

#define SDL_DEFAULT_COLOR  ((SDL_Color) {0, 0, 0, 255})

void SDL_RenderBackground(SDL_Renderer *renderer, SDL_Color color);

void SDL_RenderCircle(SDL_Renderer *renderer, double x, double y, double radius, double thickness, SDL_Color color);
void SDL_RenderFilledCircle(SDL_Renderer *renderer, int x, int y, int radius, SDL_Color color);

void SDL_RenderVector(SDL_Renderer *renderer, Vector2D vec, double x, double y, SDL_Color color);

#endif