#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

#include "raylib.h"

#include "high_score.h"
#include "config_utils.h"

static HIGH_SCORE high_scores_list[NUM_HIGH_SCORES];
static const char* high_scores_file = "high_scores.txt";

/// Initialize the high score list
void init_high_score_list(void)
{
    for(int x = 0; x < NUM_HIGH_SCORES; x++)
    {
        strcpy(high_scores_list[x].initials, DEFAULT_INITIALS);
        high_scores_list[x].score = 0;
    }
}

/// Compare function for qsort()
int cmpscores(const void* p1, const void* p2)
{
    const HIGH_SCORE *s1 = p1, *s2 = p2;
    return s2->score - s1->score;
}

/// Sort the high scores list
void sort_scores()
{
    qsort(high_scores_list, NUM_HIGH_SCORES, sizeof(HIGH_SCORE), cmpscores);
}

/// Make sure the high score list is in order
void order_scores(void)
{
    bool in_order = true;
    for(int x = 1; x < NUM_HIGH_SCORES; x++)
    {
        if(high_scores_list[x-1].score < high_scores_list[x].score)
        {
            in_order = false;
            break;
        }
    }

    if(!in_order)
        sort_scores();
}

void load_high_scores_list(void)
{
    init_high_score_list();
    FILE *f = fopen(high_scores_file, "r");
    if(f == NULL)
    {
        perror("fopen");
        return;
    }

    char* line = NULL;
    size_t len = 0;
    ssize_t nread;
    int loaded_scores = 0;
    while((nread = getline(&line, &len, f)) != -1 && loaded_scores < NUM_HIGH_SCORES)
    {
        len = strlen(line);
        // Strip the new line if it exists
        line[len - 1] = (line[len - 1] == '\n') ? '\0' : line[len - 1];

        char* mid = strchr(line, ',');
        // Make sure mid is not NULL
        if(mid == NULL)
            continue;
        mid++;

        high_scores_list[loaded_scores].score = strtol(mid, NULL, 10);

        // Make sure it is a valid score. If not, go to the next one
        if(high_scores_list[loaded_scores].score % 5 != 0 ||
            high_scores_list[loaded_scores].score <= 0)
            continue;

        char* initial = strtok(line, ",");
        initial = trim_leading_whitespace(initial);
        // Make sure there is a name, if initial equals mid, then they both point
        // to the same thing and there is no name
        if(strcmp(initial, mid) == 0)
            strcpy(initial, DEFAULT_INITIALS);

        size_t to_copy = fmin(MAX_INITIALS, strlen(initial));
        strncpy(high_scores_list[loaded_scores].initials, 
                TextToUpper(initial), to_copy);
        high_scores_list[loaded_scores].initials[to_copy] = '\0';

        loaded_scores++;
    }
    free(line);
    fclose(f);

    order_scores();
}

void save_high_scores_list(void)
{
    order_scores();
    FILE *f = fopen(high_scores_file, "w");
    if(f == NULL)
    {
        perror("fopen");
        return;
    }

    for(int x = 0; x < NUM_HIGH_SCORES; x++)
    {
        // We don't care about saving scores of 0 (aka. placeholders)
        if(high_scores_list[x].score <= 0)
            break;
        fprintf(f, "%s,%d\n", 
            high_scores_list[x].initials, high_scores_list[x].score);
    }
    fclose(f);
}

void add_high_score(int score, char* initials)
{

    // Find where the new high score ranks on the leaderboard
    int index = NUM_HIGH_SCORES;
    for(int x = 0; x < NUM_HIGH_SCORES; x++)
    {
        if(high_scores_list[x].score < score)
        {
            index = x;
            break;
        }
    }
    // If the index is equal to the number of high scores it is not
    // high enough so there is nothing to do
    if(index == NUM_HIGH_SCORES)
        return;

    // Create a new HIGH_SCORE struct from the parameters
    HIGH_SCORE hs;
    hs.score = score;
    size_t to_copy = fmin(MAX_INITIALS, strlen(initials));
    strncpy(hs.initials, initials, to_copy);
    hs.initials[to_copy] = '\0';

    // Shift the scores below the index down one, and remove 
    // the lowest score
    if(index != (NUM_HIGH_SCORES - 1))
        memcpy(&high_scores_list[index + 1],
                &high_scores_list[index],
                sizeof(HIGH_SCORE) * ((NUM_HIGH_SCORES - 1) - index));

    // Set the new high score to its place in the array
    high_scores_list[index] = hs;
}

int get_top_score(void)
{
    return high_scores_list[0].score;
}

bool is_high_score(int score)
{
    return score > high_scores_list[NUM_HIGH_SCORES - 1].score;
}

HIGH_SCORE* get_high_score_list(void)
{
    return high_scores_list;
}

void print_high_scores_list(void)
{
    for(int x = 0; x < NUM_HIGH_SCORES; x++)
    {
        char *fmt = (x >= 9) ? " " : "  ";
        printf("%d.%sInitials: %s, Score: %d\n", (x + 1), fmt, 
                high_scores_list[x].initials, high_scores_list[x].score);
    }
}