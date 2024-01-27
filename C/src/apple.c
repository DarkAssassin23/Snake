#include "raylib.h"

#include "defaults.h"
#include "apple.h"

static Apple apple;

void init_apple(int size)
{
    apple.size = size;
    move_apple();
}

void move_apple(void)
{
    int offset = apple.size * 2;

    int x = GetRandomValue(offset, GetScreenWidth() - offset);
    int y = GetRandomValue(top_boarder + (offset * 1.5),
                            GetScreenHeight() - offset);

    // Ensure each apple lines up with the snake
    apple.pos.x = x - (x % offset);
    apple.pos.y = y - (y % offset);
}

Rectangle get_apple(void)
{
    return (Rectangle){
        apple.pos.x,
        apple.pos.y,
        apple.size,
        apple.size
    };
}

void draw_apple(void)
{
    DrawRectangle(apple.pos.x, apple.pos.y, apple.size, apple.size, RED);
}