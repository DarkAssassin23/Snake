#pragma once

#include <stdbool.h>

#include "raylib.h"

/// Check if the snake is still alive. Meaning still in bounds and not on
/// top of itself
/// @return True if still alive
bool still_alive(void);

/// Check if there is a new high score
/// @return If there has been a new high score
bool got_new_high_score(void);

/// Draw a textbox to the screen for the user to input their initials
/// @param font The font to use
/// @param framesCounter The current frame count
void draw_new_leader_prompt(Font font, int framesCounter);

/// Add the new players initials and score to the high scores list
/// @param score The score associated with the player
void add_to_leaderboard(int score);

/// Draw the leaderboard to the screen
/// @param font The font to use
void draw_leaderboard(Font font);

/// Update the position of the apple on the screen
void update_apple(void);

/// Draw the current score, and high score, to the screen
/// @param font The font to use
void draw_score(Font font);

/// Draw the notification of a new high score has been achieved
/// @param font The font to use
void draw_new_high_score(Font font);

/// Display the 'Game Over' dialog to the screen
/// @param font The font to use
void display_gameover(Font font);

/// Display the given status message, centered, to the screen
/// @param font The font to use
/// @param status The status message to display to the screen
/// @param ypos The y position on the screen to display the text
void display_status(Font font, char* status, int ypos);