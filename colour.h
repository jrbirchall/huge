#ifndef FILE_COLOUR_H
#define FILE_COLOUR_H

typedef struct _COLOUR
{
    char colour;
} COLOUR;
static const COLOUR LINE_COLOUR = {.colour = 'x'};
static const COLOUR EMPTY_COLOUR = {.colour = ' '};

#endif
