#include <stdio.h>
#include <stdlib.h>

#include "commands.h"
#include "error.h"

int readCmdId(FILE * fp, CMD_ID * pId)
{
    if (NULL == fp) return E_BAD_ARG;
    if (feof(fp)) return E_EOF;

    pId->id = fgetc(fp);
    if (feof(fp)) return E_BAD_ARG;

    // Skip the command terminator.  If it's not there, raise an error.
    char delim = fgetc(fp);
    if (feof(fp) || !(delim  == ' ' || delim == '\n'))
        return E_BAD_ARG;

    return E_OK;
}

int parseCreateCanvasArgs(FILE * fp, CMD_CREATE_CANVAS_ARGS * pArgs)
{
    if (fscanf(fp, "%d %d\n", &(pArgs->width), &(pArgs->height)) < 2)
        return E_BAD_ARG;
    return E_OK;
}

int parseLineArgs(FILE * fp, CMD_LINE_ARGS * pArgs)
{
    if (fscanf(fp, "%d %d %d %d\n", &(pArgs->x1), &(pArgs->y1), &(pArgs->x2), &(pArgs->y2)) < 4)
        return E_BAD_ARG;

    // So, irritatingly, these numbers are supposed to be 1-indexed, and not 0 indexed as would be expected.
    // I decrement one here to make it conform.

    pArgs->x1--; pArgs->x2--; pArgs->y1--; pArgs->y2--;

    return E_OK;
}

int parseRectArgs(FILE * fp, CMD_RECT_ARGS * pArgs)
{
    if (fscanf(fp, "%d %d %d %d\n", &(pArgs->x1), &(pArgs->y1), &(pArgs->x2), &(pArgs->y2)) < 4)
        return E_BAD_ARG;

    // So, irritatingly, these numbers are supposed to be 1-indexed, and not 0 indexed as would be expected.
    // I decrement one here to make it conform.

    pArgs->x1--; pArgs->x2--; pArgs->y1--; pArgs->y2--;

    return E_OK;
}

int parseFillArgs(FILE * fp, CMD_FILL_ARGS * pArgs)
{
    if (fscanf(fp, "%d %d %c\n", &(pArgs->x), &(pArgs->y), &(pArgs->colour)) < 3)
        return E_BAD_ARG;

    // So, irritatingly, these numbers are supposed to be 1-indexed, and not 0 indexed as would be expected.
    // I decrement one here to make it conform.

    pArgs->x--; pArgs->y--; 

    return E_OK;
}
