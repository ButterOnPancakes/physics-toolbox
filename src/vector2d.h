#ifndef VECTOR2D_H
#define VECTOR2D_H

#include "math.h"

typedef struct vector2d_s {
    double x, y;

    double get_norm() {
        return sqrt(x * x + y * y);
    }
} Vector2D;

Vector2D vector_scalar(Vector2D vector, double scalar);
Vector2D vector_sum(Vector2D vec1, Vector2D vec2);
Vector2D vector_sub(Vector2D vec1, Vector2D vec2);

Vector2D vector_normalise(Vector2D vec);

double vector_dot(Vector2D vec1, Vector2D vec2);
Vector2D vector_project(Vector2D vec, Vector2D on);

// Angle in radiant
Vector2D vector_rotate(Vector2D vec, double angle);

// Return a symetric vector
Vector2D vector_flip(Vector2D vec, Vector2D surface_vector);

#endif