#ifndef FILE_COMMANDS_H
#define FILE_COMMANDS_H

#include <stdio.h>
#include "colour.h"

/*
Instructions are broken down into a
command identifier (CMD_ID) and a command-specific
set of paramters space delimited and terminated
by a newline.
*/

/*
Drawing command identifiers.
*/
typedef struct _CMD_ID
{
    char id;
} CMD_ID;

static const CMD_ID BAD_CMD_ID = {.id = '\0'};
static const CMD_ID CMD_CREATE_CANVAS = {.id = 'C'};
static const CMD_ID CMD_LINE = {.id = 'L'};
static const CMD_ID CMD_RECT = {.id = 'R'};
static const CMD_ID CMD_FILL = {.id = 'B'};

// Arguments.
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

/*
Read a CmdID from the file stream fp and put it in the output parameter pArgs.  

Returns E_OK if everything goes well.
*/
int readCmdId(FILE * fp, CMD_ID * pArgs);

/*
Read a list of arguments from fp and put them into pArgs.
Returns E_OK if everything goes well.
*/
int parseCreateCanvasArgs(FILE * fp, CMD_CREATE_CANVAS_ARGS * pArgs);

/*
Read a list of arguments from fp and put them into pArgs.
Returns E_OK if everything goes well.
*/
int parseLineArgs(FILE * fp, CMD_LINE_ARGS * pArgs);

/*
Read a list of arguments from fp and put them into pArgs.
Returns E_OK if everything goes well.
*/
int parseRectArgs(FILE * fp, CMD_RECT_ARGS * pArgs);

/*
Read a list of arguments from fp and put them into pArgs.
Returns E_OK if everything goes well.
*/
int parseFillArgs(FILE * fp, CMD_FILL_ARGS * pArgs);

#endif /* FILE_COMMANDS_H */
