#pragma once
#include "raylib.h"

typedef struct Apple
{
    Vector2 pos;
    int size;
} Apple;

/// Initialize a new apple
/// @param size The size of the apple
void init_apple(int size);

/// Move the apple to a new location on the screen
void move_apple(void);

/// Get the apple
/// @return The apple as a rectangle
Rectangle get_apple(void);

/// Draw the apple to the screen
void draw_apple(void);