#ifndef FILE_DRAWCONTEXT_H
#define FILE_DRAWCONTEXT_H

#include <stdio.h>
#include "canvas.h"

typedef struct _CANVAS_NODE
{
    CANVAS * pCanvas;
    struct _CANVAS_NODE * pNext;
} CANVAS_NODE;

typedef struct _DRAW_CONTEXT
{
    CANVAS_NODE * pCanvasStack;
} DRAW_CONTEXT;

int initDc(DRAW_CONTEXT * pDC);
int addCanvas(DRAW_CONTEXT * pDc, int width, int height);
int printDc(DRAW_CONTEXT * pDc, FILE * fp);
int drawLine(DRAW_CONTEXT * pDc, int x1, int y1, int x2, int y2);
int drawRect(DRAW_CONTEXT * pDc, int x1, int y1, int x2, int y2);
int fill(DRAW_CONTEXT * pDc, int x, int y, COLOUR c);

#endif /* FILE_DRAWCONTEXT_H */
