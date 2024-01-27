#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "config_utils.h"
#include "defaults.h"

char* trim_leading_whitespace(char *str)
{
    // Trim leading space
    while(isspace((unsigned char)*str)) str++;

    if(*str == 0)
        return str;

    return str;
}

Config_Screen_Properties parse_config(FILE* config)
{
    Config_Screen_Properties csp = { 
        DEFAULT_WIDTH,
        DEFAULT_HEIGHT,
        DEFAULT_RES,
        DEFAULT_FPS,
        DEFAULT_THREADS
     };
    char* line = NULL;
    size_t len = 0;
    ssize_t nread;
    while((nread = getline(&line, &len, config)) != -1)
    {
        // Ignore # (comments) and new lines
        if(line[0] == '#' || line[0] == '\n' || line[0] == '\r')
            continue;
        len = strlen(line);
        // Strip the new line
        if(line[len - 1] == '\n')
            line[len - 1] = '\0';

        char* result = trim_leading_whitespace(line);

        // Get the key and the value
        char *value = strchr(result, ' ') + 1;
        char key[(value - result)];
        strncpy(key, result, sizeof(key) - 1);
        key[sizeof(key) - 1] = '\0';

        if(strcmp(key, "width") == 0)
        {
            int width = strtol(value, NULL, 10);
            if(width <= -1 || width >= MAX_WIDTH)
                csp.width = MAX_WIDTH;
            else if(width == 0)
                csp.width = MIN_WIDTH;
            else
                csp.width = width;
        }
        else if(strcmp(key, "height") == 0)
        {
            int height = strtol(value, NULL, 10);
            if(height <= -1 || height >= MAX_HEIGHT)
                csp.height = MAX_HEIGHT;
            else if(height == 0)
                csp.height = MIN_HEIGHT;
            else
                csp.height = height;
        }
        else if(strcmp(key, "resolution") == 0)
        {
            int resolution = strtol(value, NULL, 10);
            if(resolution == 0)
                csp.resolution = DEFAULT_RES;
            // Remember, lower number means higher resolution
            else if(resolution <= MAX_RES)
                csp.resolution = MAX_RES;
            else
                csp.resolution = resolution;
        }
        else if(strcmp(key, "speed") == 0)
        {
            int speed = strtol(value, NULL, 10);
            if(speed <= 0)
                csp.speed = DEFAULT_FPS;
            else
                csp.speed = speed;
        }
        else if(strcmp(key, "threads") == 0)
        {
            int threads = strtol(value, NULL, 10);
            if(threads <= 0)
                csp.threads = DEFAULT_THREADS;
            else
                csp.threads = threads;
        }
    }
    free(line);
    return csp;
}