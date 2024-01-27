#include <ctype.h>
#include <string.h>

#include "raylib.h"

#include "game_function.h"
#include "snake.h"
#include "apple.h"
#include "defaults.h"
#include "high_score.h"


static char initials[MAX_INITIALS + 1] = "\0";
static int letterCount = 0;

bool still_alive(void)
{
    Rectangle head = get_snake_head();
    bool alive = (head.x - (head.width / 2.0)) < 0;
    alive |= (head.x + (head.width * 2)) > GetScreenWidth();
    alive |= (head.y - (head.height / 2.0)) < (top_boarder  
                                                + get_snake_head().height);
    alive |= (head.y + (head.height * 2)) > GetScreenHeight();
    alive |= is_on_snake(head, true);

    return !alive;
}

bool got_new_high_score(void)
{
    return (int)(get_snake_len() - 1) > high_score;
}

void draw_new_leader_prompt(Font font, int framesCounter)
{
    int fontsize = font.baseSize * 0.5;
    int padding = font.glyphPadding * 0.5;

    int base_x = (int)(GetScreenWidth() / 2.0f);
    int width = 100;
    int height = 50;
    Rectangle textBox = { 
        base_x - (width / 2.0f), 
        (GetScreenHeight() * 0.175f) - (height / 2.0f), 
        width, 
        height 
    };
    char *add_leader = "Add your initials for the leaderboard!";
    Vector2 loc = MeasureTextEx(font, add_leader, 
                        fontsize, padding);      

    DrawTextEx(font, add_leader, 
        (Vector2) { 
            base_x - (loc.x / 2.0), 
            GetScreenHeight() * 0.075f
        }, fontsize, padding, GRAY);

    DrawTextEx(font, initials, 
                (Vector2) { (int)textBox.x + 5, (int)textBox.y + 8 }, 
                font.baseSize, font.glyphPadding, RAYWHITE);

    if (letterCount < MAX_INITIALS)
    {
        // Draw blinking underscore char
        if (((framesCounter/15)%2) == 0) 
        {
            loc = MeasureTextEx(font, initials, font.baseSize, font.glyphPadding);
            DrawTextEx(
                font,
                "_", 
                (Vector2) {
                    textBox.x + 8 + loc.x,
                    textBox.y + 12
                }, font.baseSize, font.glyphPadding, RAYWHITE);
        }

        const char* input_chars_str = TextFormat("INPUT CHARS: %i/%i", 
                                                 letterCount, MAX_INITIALS);
        loc = MeasureTextEx(font, input_chars_str, 
                                    fontsize, padding);

        DrawTextEx(font, input_chars_str, 
                (Vector2) {
                    base_x - (loc.x / 2.0f), 
                    (textBox.y + textBox.height) * 1.05f 
                }, fontsize, padding, DARKGRAY);
    }
    else
    {
        const char* backspace_text = "Press BACKSPACE to delete chars...";
        loc = MeasureTextEx(font, backspace_text, 
                            fontsize, padding);
        DrawTextEx(font, backspace_text, 
            (Vector2) {
                base_x - (loc.x / 2.0f),
                (textBox.y + textBox.height) * 1.05f
            }, fontsize, padding, GRAY);
    }
        
}

void add_to_leaderboard(int score)
{ 
    // Get char pressed (unicode character) on the queue
    int key = GetCharPressed();

    // Check if more characters have been pressed on the same frame
    while (key > 0)
    {
        // NOTE: Only allow keys in range [32..125] and no spaces
        if ((key >= 32) && (key <= 125) && (letterCount < MAX_INITIALS) && 
            key != KEY_SPACE)
        {
            initials[letterCount] = toupper((char)key);
            initials[letterCount+1] = '\0'; // Add null terminator at the end of the string.
            letterCount++;
        }

        key = GetCharPressed();  // Check next character in the queue
    }

    if (IsKeyPressed(KEY_BACKSPACE))
    {
        letterCount--;
        if (letterCount < 0) 
            letterCount = 0;
        initials[letterCount] = '\0';
    }

    if (IsKeyPressed(KEY_ENTER))
    {
        editing = false;
        // If no initials are set, set them to the default
        if(strcmp(initials, "") == 0)
            strcpy(initials, DEFAULT_INITIALS);

        add_high_score(score, initials);

        // Reset the initials
        memset(initials, 0, MAX_INITIALS + 1);
        letterCount = 0;
        // Save the leaderboard
        save_high_scores_list();
    }
}

/// Draw the column headers of the leaderboard
/// @param font The font to use
/// @param base_x The location on the screen to base the x positions from
/// @param base_y The location on the screen to base the y positions from
/// @param col_size How wide each column should be 
void draw_column_headers(Font font, int base_x, int base_y, int col_size)
{
    int row_x = base_x - (col_size * 1.5f);
    DrawTextEx(
        font,
        "Rank", 
        (Vector2) { row_x, base_y }, 
        font_size, font.glyphPadding, RAYWHITE);

    DrawTextEx(
        font,
        "Player", 
        (Vector2) { row_x + col_size, base_y },
        font_size, font.glyphPadding, RAYWHITE);

    DrawTextEx(
        font,
        "Score", 
        (Vector2) { row_x + (2.2 * col_size), base_y }, 
        font_size, font.glyphPadding, RAYWHITE);

}

/// Draw an individual row of the leaderboard
/// @param font The font to use
/// @param base_x The location on the screen to base the x positions from
/// @param base_y The location on the screen to base the y positions from
/// @param col_size How wide each column should be 
/// @param rank What rank is the current row for
/// @param hs The HIGH_SCORE that will be put in this row
void draw_leaderboard_row(Font font, int base_x, int base_y, int col_size, 
                            int rank, HIGH_SCORE hs)
{
    int row_x = base_x - (col_size * 1.5f);
    DrawTextEx(
        font,
        TextFormat("%d.", rank), 
        (Vector2) { row_x, base_y },
        font_size, font.glyphPadding, RAYWHITE);

    DrawTextEx(
        font,
        hs.initials, 
        (Vector2) { row_x + col_size, base_y },
        font_size, font.glyphPadding, RAYWHITE);

    // Right justify the scores
    Vector2 size = MeasureTextEx(font, TextFormat("%d",hs.score), 
                                 font_size, font.glyphPadding);
    Vector2 col = MeasureTextEx(font, "Score", 
                                font_size, font.glyphPadding);
    DrawTextEx(
        font,
        TextFormat("%d", hs.score), 
        (Vector2) { row_x + ((2.2 * col_size) + col.x - size.x), base_y },
        font_size, font.glyphPadding, RAYWHITE);
}

void draw_leaderboard(Font font)
{
    int base_x = (int)(GetScreenWidth() / 2.0);
    int base_y = (int)(GetScreenHeight() * 0.45);

    // G's are arbitrary
    const char* column = "GGGGGG";
    Vector2 column_size = MeasureTextEx(font, column, 
                                        font.baseSize, font.glyphPadding);

    Vector2 loc = MeasureTextEx(font, "Leaderboard", 
                                font.baseSize,
                                font.glyphPadding);
    DrawTextEx(
        font,
        "Leaderboard", 
        (Vector2) {
            base_x - loc.x / 2.0f, 
            base_y 
        }, font.baseSize, font.glyphPadding, RAYWHITE);

    base_y += font.baseSize;
    draw_column_headers(font, base_x, base_y, column_size.x);

    HIGH_SCORE *high_scores = get_high_score_list();
    for(int x = 0; x < NUM_HIGH_SCORES; x++)
    {
        draw_leaderboard_row(font, base_x, base_y + (font_size * (x + 1)), 
                    column_size.x, x + 1, high_scores[x]);
    }
    
}

// NOTE: For anyone good enough to make the length of the snake take up 
// basically the whole screen, this will cause issues.
void update_apple(void)
{
    do
    {
        move_apple();
    } while(is_on_snake(get_apple(), false));
}

void draw_score(Font font)
{
    int x_boarder = 5;
    int y_boarder = 5;
    int fontsize = font.baseSize * 0.5;
    int padding = font.glyphPadding * 0.5;
    DrawTextEx(font, TextFormat("Score: %d", (int)get_snake_len() - 1),
        (Vector2) { x_boarder, y_boarder },
        fontsize, padding, RAYWHITE);

    const char* hscore_str = TextFormat("High Score: %d", high_score);
    Vector2 hscore_size = MeasureTextEx(font, hscore_str, 
                                        fontsize, padding);
    DrawTextEx(font, hscore_str, 
        (Vector2) {
            GetScreenWidth() - (hscore_size.x + x_boarder), 
            y_boarder 
        }, fontsize, padding, RAYWHITE);
}

void draw_new_high_score(Font font)
{
    int y_boarder = 5;
    int fontsize = font.baseSize * 0.5;
    int padding = font.glyphPadding * 0.5;

    const char* str = "New High Score!";
    Vector2 size = MeasureTextEx(font, str, fontsize, padding);
    DrawTextEx(font, str, 
        (Vector2) {
            (GetScreenWidth() / 2.0) - (size.x / 2.0), 
            y_boarder 
        }, fontsize, padding, RAYWHITE);
}

void display_gameover(Font font)
{
    char* gameOver = "Game Over";
    int fontsize = font.baseSize * 1.5;
    int padding = font.glyphPadding;
    Vector2 GUI_Text_size = MeasureTextEx(font, gameOver, 
                                          fontsize, padding);

    int base_x = (int)(GetScreenWidth() / 2.0);
    int base_y = (int)(GetScreenHeight() * 0.33);
    DrawTextEx(font, gameOver, 
        (Vector2) { base_x - (GUI_Text_size.x / 2.0), base_y },
        fontsize, font.glyphPadding, RAYWHITE);
    draw_leaderboard(font);
}

void display_status(Font font, char* status, int ypos)
{
    if(ypos <= 0)
        ypos = GetScreenHeight() / 2.0;

    Vector2 GUI_Text_size = MeasureTextEx(font, status, 
                                          font.baseSize * 0.5, 
                                          font.glyphPadding * 0.5);

    Rectangle bg = {
        (GetScreenWidth() / 2.0) - ((GUI_Text_size.x / 2.0)),
        (ypos - font.baseSize) + 
            (font.baseSize * (1 - text_scale)),
        GUI_Text_size.x,
        GUI_Text_size.y * text_scale
    };
    // Give background to text
    DrawRectangleRec(bg, BLACK);
    DrawTextEx(font, status, 
        (Vector2) {
            (GetScreenWidth() / 2.0) - (GUI_Text_size.x / 2.0), 
            ypos - ((GUI_Text_size.y * 2) * text_scale)
        }, font.baseSize * 0.5, font.glyphPadding * 0.5, RAYWHITE);

}