#include <stdio.h>
#include <stdlib.h>

#include "drawcontext.h"
#include "error.h"
#include "canvas.h"

int addCanvas(DRAW_CONTEXT * pDc, int width, int height)
{
    CANVAS * pCanvas = (CANVAS *)malloc(sizeof(CANVAS));
    if (NULL == pCanvas) return E_OOM;

    initCanvas(pCanvas, width, height);

    CANVAS_NODE * pCanvasNode = (CANVAS_NODE *) malloc(sizeof(CANVAS_NODE));
    if (NULL == pCanvasNode) return E_OOM;
    pCanvasNode->pCanvas = pCanvas;

    pCanvasNode->pNext = pDc->pCanvasStack;
    pDc->pCanvasStack = pCanvasNode;
}

int initDc(DRAW_CONTEXT * pDc)
{
    if (NULL == pDc) return E_BAD_ARG;

    pDc->pCanvasStack = NULL;

    return E_OK;
}

int freeDc(DRAW_CONTEXT * pDc)
{
    if (NULL == pDc) return E_BAD_ARG;

    while (pDc->pCanvasStack)
    {
        CANVAS_NODE * pNode = pDc->pCanvasStack->pNext;
        free(pDc->pCanvasStack);
        pDc->pCanvasStack = pNode;
    }
}

int printDc(DRAW_CONTEXT * pDc, FILE * fp)
{
    CANVAS_NODE * pCanvasNode = pDc->pCanvasStack;
    while (pCanvasNode)
    {
        printCanvas(pCanvasNode->pCanvas, fp);
        pCanvasNode = pCanvasNode->pNext;
    }
}

int drawLine(DRAW_CONTEXT * pDc, int x1, int y1, int x2, int y2)
{
    if (NULL == pDc || NULL == pDc->pCanvasStack) return E_BAD_ARG;

    return drawCanvasLine(pDc->pCanvasStack->pCanvas, x1, y1, x2, y2);
}

int drawRect(DRAW_CONTEXT * pDc, int x1, int y1, int x2, int y2)
{
    if (NULL == pDc || NULL == pDc->pCanvasStack) return E_BAD_ARG;

    return drawCanvasRect(pDc->pCanvasStack->pCanvas, x1, y1, x2, y2);
}

int fill(DRAW_CONTEXT * pDc, int x, int y, COLOUR c)
{
    if (NULL == pDc || NULL == pDc->pCanvasStack) return E_BAD_ARG;

    return fillCanvas(pDc->pCanvasStack->pCanvas, x, y, c);
}
