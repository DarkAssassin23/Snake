#pragma once
#include <stdbool.h>
#include "raylib.h"

typedef struct Segment
{
    void *next;
    Vector2 pos;
} Segment;

typedef struct Snake
{
    Segment *head;
    Segment *tail;
    size_t length;
    int xspeed, yspeed, segment_size;
    Color color;
} Snake;

/// Initialize a new Snake
/// @param segment_size How big each segment of the snake should be
/// @param color The color the snake should be
bool init_snake(int segment_size, Color color);

/// Draw the snake to the screen
void draw_snake(void);

/// Update the Snakes speed given a direction
void move_snake(void);

/// Update the position of each of the segments of the snake
void update_snake(void);

/// Return the head of the snake as a rectangle
Rectangle get_snake_head(void);

/// Get the length of the snake
size_t get_snake_len(void);

/// Check to see if the apple is on the snake
/// @param rec Rectangle to check if it is on the snake
/// @param self_check Are we checking if the snake is on itself
/// @return true if the given rectangle is on the snake
bool is_on_snake(Rectangle rec, bool self_check);

void print_snake(void);

/// Increases the length of the snake
void grow_snake(void);

/// Free the memory used by the snake
void free_snake(void);