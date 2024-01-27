#pragma once

#include <stdbool.h>

#define NUM_HIGH_SCORES 10
#define MAX_INITIALS 3
#define DEFAULT_INITIALS ("JDH")

/// @struct HIGH_SCORE
/// Struct to contain the score and initials of a high score
typedef struct HIGH_SCORE
{
    int score;
    char initials[MAX_INITIALS + 1];
} HIGH_SCORE;

extern int high_score;

/// Load the high scores from the high scores file
void load_high_scores_list(void);

/// Save the high scores to the high scores file
void save_high_scores_list(void);

/// Add a new high score to the high scores list
//void add_high_score(HIGH_SCORE hs);
void add_high_score(int score, char* initials);

/// Get the highest score in the high scores list
/// @return The highest score in the high scores list
int get_top_score(void);

/// Check to see if the given score is high enough to be a high score
/// @param score The score to check if it is a high score
/// @return If the given score is a high score
bool is_high_score(int score);

/// Get the list of all the high scores
/// @return List of all the high scores
HIGH_SCORE* get_high_score_list(void);

/// Print all the high scores to the console
void print_high_scores_list(void);