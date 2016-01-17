#ifndef FILE_COMMANDS_H
#define FILE_COMMANDS_H

#include <stdio.h>
#include "colour.h"

typedef struct _CMD_ID
{
    char id;
} CMD_ID;
static const CMD_ID BAD_CMD_ID = {.id = '\0'};
static const CMD_ID CMD_CREATE_CANVAS = {.id = 'C'};
static const CMD_ID CMD_LINE = {.id = 'L'};
static const CMD_ID CMD_RECT = {.id = 'R'};
static const CMD_ID CMD_FILL = {.id = 'B'};

typedef struct _CMD_CREATE_CANVAS_ARGS
{
    int width;
    int height;
} CMD_CREATE_CANVAS_ARGS;

typedef struct _CMD_LINE_ARGS
{
    int x1;
    int y1;
    int x2;
    int y2;
} CMD_LINE_ARGS;

typedef struct _CMD_RECT_ARGS
{
    int x1;
    int y1;
    int x2;
    int y2;
} CMD_RECT_ARGS;

typedef struct _CMD_FILL_ARGS
{
    int x;
    int y;
    COLOUR colour;
} CMD_FILL_ARGS;

int readCmdId(FILE * fp, CMD_ID * pArgs);
int parseCreateCanvasArgs(FILE * fp, CMD_CREATE_CANVAS_ARGS * pArgs);
int parseLineArgs(FILE * fp, CMD_LINE_ARGS * pArgs);
int parseRectArgs(FILE * fp, CMD_RECT_ARGS * pArgs);
int parseFillArgs(FILE * fp, CMD_FILL_ARGS * pArgs);

#endif /* FILE_COMMANDS_H */
