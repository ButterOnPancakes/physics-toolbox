#include "shapes.h"

#include <SDL3/SDL.h>

void set_draw_color(SDL_Renderer *renderer, SDL_Color color) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
}
void reset_draw_color(SDL_Renderer *renderer) {
    set_draw_color(renderer, SDL_DEFAULT_COLOR);
}

void SDL_RenderBackground(SDL_Renderer *renderer, SDL_Color color) {
    set_draw_color(renderer, color);
    SDL_RenderClear(renderer);
    reset_draw_color(renderer);
}

void SDL_RenderCircle(SDL_Renderer *renderer, double x, double y, double radius, double thickness, SDL_Color color) {
    set_draw_color(renderer, color);
    double minDist = (radius - thickness) * (radius - thickness);
    double maxDist = radius * radius;
    for (int w = 0; w < radius * 2; w++) {
        for (int h = 0; h < radius * 2; h++) {
            int dx = radius - w;
            int dy = radius - h;
            if (minDist <= (dx*dx + dy*dy) && (dx*dx + dy*dy) <= maxDist) {
                SDL_RenderPoint(renderer, x + dx, y + dy);
            }
        }
    }
    reset_draw_color(renderer);
}

void SDL_RenderFilledCircle(SDL_Renderer *renderer, int x, int y, int radius, SDL_Color color) {
    set_draw_color(renderer, color);
    for (int w = 0; w < radius * 2; w++) {
        for (int h = 0; h < radius * 2; h++) {
            int dx = radius - w;
            int dy = radius - h;
            if ((dx*dx + dy*dy) <= (radius * radius)) {
                SDL_RenderPoint(renderer, x + dx, y + dy);
            }
        }
    }
    reset_draw_color(renderer);
}

void SDL_RenderVector(SDL_Renderer *renderer, Vector2D vec, double x, double y, SDL_Color color) {
    set_draw_color(renderer, color);
    SDL_RenderLine(renderer, x, y, x + vec.x, y + vec.y);
    reset_draw_color(renderer);
}