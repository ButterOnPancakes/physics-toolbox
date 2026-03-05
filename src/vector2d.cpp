#include "vector2d.h"

Vector2D vector_scalar(Vector2D vector, double scalar) {
    struct vector2d_s vec;
    vec.x = vector.x * scalar; vec.y = vector.y * scalar;
    return vec;
}
Vector2D vector_sum(Vector2D vec1, Vector2D vec2) {
    struct vector2d_s vec;
    vec.x = vec1.x + vec2.x; vec.y = vec1.y + vec2.y;
    return vec;
}
Vector2D vector_sub(Vector2D vec1, Vector2D vec2) {
    struct vector2d_s vec;
    vec.x = vec1.x - vec2.x; vec.y = vec1.y - vec2.y;
    return vec;
}

Vector2D vector_normalise(Vector2D vec) {
    double norm = vec.get_norm();
    return vector_scalar(vec, 1 / norm);
}

double vector_dot(Vector2D vec1, Vector2D vec2) {
    return vec1.x * vec2.x + vec1.y * vec2.y;
}

Vector2D vector_project(Vector2D vec, Vector2D on) {
    double tnorm = on.get_norm();
    if(tnorm < 1e-3) return (Vector2D) {0, 0};
    return vector_scalar(on, vector_dot(vec, on) / (tnorm * tnorm));
}

Vector2D vector_rotate(Vector2D vec, double angle) {
    Vector2D rotated = {
        cos(angle) * vec.x - sin(angle) * vec.y,
        sin(angle) * vec.x + cos(angle) * vec.y
    };
    return rotated;
}

Vector2D vector_flip(Vector2D vec, Vector2D surface_vector) {
    Vector2D proj = vector_project(vec, surface_vector);
    return vector_sub(vec, vector_scalar(proj, 2));
}