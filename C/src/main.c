#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#include "raylib.h"

#include "defaults.h"
#include "config_utils.h"
#include "snake.h"
#include "apple.h"
#include "game_function.h"
#include "high_score.h"

int MAX_WIDTH = 0;
int MAX_HEIGHT = 0;
int MIN_WIDTH = 0;
int MIN_HEIGHT = 0;

int num_threads = DEFAULT_THREADS;
int font_size = 20;
int high_score = 0;
float text_scale = 1.1f;

int top_boarder = 0;
int running = false;
int editing = true;

bool gameOver = false;

int main(int argc, char** argv) 
{
    // Initialize global screen resolution
    // InitWindow needed to start the GLFW context in order to get monitor dims
    InitWindow(DEFAULT_WIDTH, DEFAULT_HEIGHT, "Snake"); 
    MAX_WIDTH = fmax(DEFAULT_WIDTH, GetMonitorWidth(0));
    MAX_HEIGHT = fmax(DEFAULT_HEIGHT, GetMonitorHeight(0));
    MIN_WIDTH = fmin(DEFAULT_WIDTH, GetMonitorWidth(0));
    MIN_HEIGHT = fmin(DEFAULT_HEIGHT, GetMonitorHeight(0));
    CloseWindow();
    
    int screenWidth = MIN_WIDTH;
    int screenHeight = MIN_HEIGHT;
    int resolution = DEFAULT_RES;
    int fps = DEFAULT_FPS;

    FILE* cfg = fopen("config.txt", "r");
    if(cfg != NULL)
    {
        Config_Screen_Properties csp = parse_config(cfg);
        screenHeight = csp.height;
        screenWidth = csp.width;
        resolution = csp.resolution + (csp.resolution % 2);
        fps = csp.speed;
        num_threads = csp.threads;
    }
    fclose(cfg);
    load_high_scores_list();
    print_high_scores_list();
    high_score = get_top_score();

    top_boarder = (int)(font_size * text_scale);


    InitWindow(screenWidth, screenHeight, "Snake"); 
    if(screenWidth == MAX_WIDTH && screenHeight == MAX_HEIGHT)
        ToggleFullscreen(); 

    Font mono_font = LoadFont("resources/mono_font.ttf");
    bool paused = false;
    int frameCounter = 0;

    SetTargetFPS(fps);

    // Initialize the snake and the apple
    if(!init_snake(resolution, YELLOW))
    {
        perror("init_snake");
        return -1;
    }
    init_apple(resolution);
    while(is_on_snake(get_apple(), false))
        move_apple();

    while (!WindowShouldClose()) 
    {
        frameCounter++;
        // Reset
        if((IsKeyDown(KEY_LEFT_CONTROL) || 
            IsKeyDown(KEY_RIGHT_CONTROL)) &&
            IsKeyPressed(KEY_N))
        {
            free_snake();
            if(!init_snake(resolution, YELLOW))
            {
                perror("init_snake");
                return -1;
            }
            update_apple();
            paused = false;
            gameOver = false;
            running = false;
            editing = true;
            frameCounter = 0;
        }
        if(CheckCollisionRecs(get_apple(), get_snake_head()))
        {
            update_apple();
            grow_snake();
        }

        if(!still_alive())
        {
            paused = true;
            gameOver = true;
        }

        if(got_new_high_score())
            high_score = (int)(get_snake_len() - 1);

        move_snake();

        // Only pause the game if it is not over and is running
        if(IsKeyPressed(KEY_SPACE) && (!gameOver && running))
            paused = !paused;

        if(!paused)
            update_snake();

        if(gameOver && is_high_score(get_snake_len() - 1) && editing)
            add_to_leaderboard(get_snake_len() - 1);

        BeginDrawing();
        ClearBackground(BLACK);

        // Display the score and top boarder
        draw_score(mono_font);
        DrawRectangle(0, top_boarder, GetScreenWidth(), resolution, RAYWHITE);

        if(gameOver) 
        {
            display_gameover(mono_font);
            
            // If the user got a score high enough to be on the leaderboard
            // and they haven't typed their initials, prompt them to enter 
            // their initials for the leaderboard
            if(is_high_score(get_snake_len() - 1) && editing)
                draw_new_leader_prompt(mono_font, frameCounter);
            else
                display_status(mono_font, 
                        "Press Ctrl+N to start a new game or ESC to exit",
                        (GetScreenHeight() * 0.25));
        }
        else 
        {
            draw_snake();
            draw_apple();
        }

        if(high_score > get_top_score())
            draw_new_high_score(mono_font);
        
        if(paused && !gameOver) 
            display_status(mono_font, "Paused", 0);
        else if(!running && !gameOver) 
            display_status(mono_font, "Press an arrow key to begin", 0);

        EndDrawing();
    }

    // Free our memory
    free_snake();
    UnloadFont(mono_font);

    CloseWindow();

    return 0;
}

