#pragma once

#define DEFAULT_WIDTH 640
#define DEFAULT_HEIGHT 480

#define DEFAULT_RES 10
#define MAX_RES 2 // Note: Lower means smaller squares and more of them

#define DEFAULT_FPS 30
#define DEFAULT_THREADS 1

extern int MAX_WIDTH;
extern int MAX_HEIGHT;
extern int MIN_WIDTH;
extern int MIN_HEIGHT;

extern int running;
extern int editing;
extern int top_boarder;
extern int font_size;
extern float text_scale;