#ifndef FILE_CANVAS_H
#define FILE_CANVAS_H

#include <stdio.h>
#include "colour.h"

/*
Primitive PIXEL structure.  Holds only a colour.
*/
typedef struct _PIXEL
{
    COLOUR colour;
} PIXEL;

/* 
Primitive CANVAS structure.  

Holds a drawing stream of PIXELS
in pPixels of size width * height.
*/
typedef struct _CANVAS
{
    int width;
    int height;
    PIXEL * pPixels;
} CANVAS;

/*
Initialises a Canvas structure and gets it ready to be drawn.  Once initialised, 
the structure must be freed.
*/
int initCanvas(CANVAS * pCanvas, int width, int height);

/*
Draw a line on pCanvas between (x1, y1) and (x2, y2).
*/
int drawCanvasLine(CANVAS * pCanvas, int x1, int y1, int x2, int y2);

/*
Draw a rectangle on pCanvas bounded by (x1, y1) and (x2, y2)
*/
int drawCanvasRect(CANVAS * pCanvas, int x1, int y1, int x2, int y2);

/*
Use a seed-fill to fill an area seeded at (x,y) with colour c.
*/
int fillCanvas(CANVAS * pCanvas, int x, int y, COLOUR c);

/*
Free the memory allocated for pCanvas.
*/
int freeCanvas(CANVAS * pCanvas);

/*
Print pCanvas to the File fp.
*/
int printCanvas(CANVAS * pCanvas, FILE * fp);

#endif /* !FILE_CANVAS_H */
