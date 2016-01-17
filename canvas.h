#ifndef FILE_CANVAS_H
#define FILE_CANVAS_H

#include <stdio.h>
#include "colour.h"

typedef struct _PIXEL
{
    COLOUR colour;
} PIXEL;

typedef struct _CANVAS
{
    int width;
    int height;
    PIXEL * pPixels;
} CANVAS;

int initCanvas(CANVAS * pCanvas, int width, int height);
int drawCanvasLine(CANVAS * pCanvas, int x1, int y1, int x2, int y2);
int drawCanvasRect(CANVAS * pCanvas, int x1, int y1, int x2, int y2);
int fillCanvas(CANVAS * pCanvas, int x, int y, COLOUR c);
int freeCanvas(CANVAS * pCanvas);
int printCanvas(CANVAS * pCanvas, FILE * fp);

#endif /* !FILE_CANVAS_H */
