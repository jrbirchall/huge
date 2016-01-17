#ifndef FILE_COLOUR_H
#define FILE_COLOUR_H

/*
Primitive COLOUR structure
which represents a colour
by a character.

Used to draw.
*/
typedef struct _COLOUR
{
    char colour;
} COLOUR;

/*
The colour of a line.
*/
static const COLOUR LINE_COLOUR = {.colour = 'x'};

/*
The colour of an empty PIXEL.
*/
static const COLOUR EMPTY_COLOUR = {.colour = ' '};

#endif
