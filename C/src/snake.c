#include <stdio.h>
#include <stdlib.h>

#include "raylib.h"

#include "snake.h"
#include "defaults.h"

#define GROWTH_AMOUNT 5

static Snake s;

/// Add a new segment to the end of the snake
/// @param pos The position to add the segment
/// @return If the new segment was added successfully
static bool add_segment(Vector2 pos)
{
    Segment *segment = malloc(sizeof(Segment));
    if(segment == NULL)
        return false;

    segment->pos = pos;

    if(s.tail == NULL)
    {
        s.tail = segment;
        s.head = segment;
        segment->next = NULL;
    }
    else
    {
        segment->next = s.tail;
        s.tail = segment;
    }
    s.length++;
    return true;
}

bool init_snake(int segment_size, Color color)
{
    s.head = NULL;
    s.tail = NULL;
    s.length = s.xspeed = s.yspeed = 0;
    s.segment_size = segment_size;
    s.color = color;

    int x = (int)(GetScreenWidth() / 2.0);
    int y = (int)(GetScreenHeight() / 2.0);
    return add_segment((Vector2){x, y});
}


void draw_snake(void)
{
    Segment *segment = s.tail;
    for(int x = 0; x < s.length; x++)
    {
        DrawRectangle(segment->pos.x, segment->pos.y, 
                      s.segment_size, s.segment_size, 
                      s.color);
        segment = segment->next;
    }
}

void move_snake(void)
{
    if(IsKeyPressed(KEY_DOWN) && s.yspeed == 0)
    {
        s.yspeed += s.segment_size;
        s.xspeed = 0;
    }
    if(IsKeyPressed(KEY_UP)  && s.yspeed == 0)
    {
        s.yspeed -= s.segment_size;
        s.xspeed = 0;
    }
    if(IsKeyPressed(KEY_RIGHT) && s.xspeed == 0)
    {
        s.yspeed = 0;
        s.xspeed += s.segment_size;
    }
    if(IsKeyPressed(KEY_LEFT) && s.xspeed == 0)
    {
        s.yspeed = 0;
        s.xspeed -= s.segment_size;
    }
    running = s.yspeed + s.xspeed;
}

void update_snake(void)
{
    if(s.head == NULL || s.tail == NULL)
        return;

    Segment *prev = s.tail;
    Segment *segment = s.tail;
    for(int x = 0; x < s.length; x++)
    {
        prev->pos = segment->pos;
        prev = segment;
        segment = segment->next;
    }

    s.head->pos.x += s.xspeed;
    s.head->pos.y += s.yspeed;
}

Rectangle get_snake_head(void)
{
    return (Rectangle){
        s.head->pos.x,
        s.head->pos.y,
        s.segment_size,
        s.segment_size
    };
}

size_t get_snake_len(void)
{
    return s.length;
}

bool is_on_snake(Rectangle rec, bool self_check)
{
    Segment *current = s.tail;
    Rectangle tailSegment = {
        current->pos.x,
        current->pos.y,
        s.segment_size,
        s.segment_size
    };

    for(int x = 0; x < s.length - self_check; x++)
    {
        Rectangle segment = {
            current->pos.x,
            current->pos.y,
            s.segment_size,
            s.segment_size
        };

        // Need to also check if the current segment is on the tail
        // since otherwise this will always return true after the
        // snake grows
        if(CheckCollisionRecs(rec, segment) && 
            !CheckCollisionRecs(tailSegment, segment))
            return true;

        current = current->next;
    }
    return false;
}

void print_snake(void)
{
    Segment *current = s.tail;
    int index = 0;

    while(current != NULL)
    {
        printf("%d - (x,y): (%d, %d)\n",
                index, (int)current->pos.x, (int)current->pos.y);
        current = current->next;
        index++;
    }
}

void grow_snake(void)
{
    for(int x = 0; x < GROWTH_AMOUNT; x++)
    {
        if(!add_segment(s.tail->pos))
            return;
    }
}

void free_snake(void)
{
    Segment *next = s.tail;

    while(s.tail != NULL)
    {
        next = s.tail->next;
        free(s.tail);
        s.tail = next;
    }
}