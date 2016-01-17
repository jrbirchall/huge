#include <stdlib.h>
#include <stdio.h>
#include "canvas.h"
#include "error.h"

int initCanvas(CANVAS * pCanvas, int width, int height)
{
    if (NULL == pCanvas) return E_BAD_ARG;
    pCanvas->width = width;
    pCanvas->height = height;
    pCanvas->pPixels = (PIXEL *)calloc(width * height, sizeof(PIXEL));
    if (NULL == pCanvas->pPixels) return E_OOM;

    return E_OK;
}

int freeCanvas(CANVAS * pCanvas)
{
    if (NULL == pCanvas) return E_BAD_ARG;
    free(pCanvas->pPixels);

    return E_OK;
}

int setPixel(CANVAS * pCanvas, int x, int y, COLOUR c)
{
    if (NULL == pCanvas || NULL == pCanvas->pPixels) return E_BAD_ARG;

    pCanvas->pPixels[x + pCanvas->width * y].colour.colour = c.colour;

    return E_OK;
}

int getPixel(CANVAS * pCanvas, int x, int y, COLOUR * c)
{
    if (NULL == pCanvas || NULL == pCanvas->pPixels || NULL == c) return E_BAD_ARG;
    if (x < 0 || x > pCanvas->width) return E_BAD_ARG;
    if (y < 0 || y > pCanvas->height) return E_BAD_ARG;

    c->colour = pCanvas->pPixels[x + pCanvas->width * y].colour.colour;

    return E_OK;
}

int printCanvas(CANVAS * pCanvas, FILE * fp)
{
    int x,y;
    for (x =0; x < pCanvas->width + 2; x++)
        fputc('-', fp);
    fputc('\n', fp);

    for (y = 0; y < pCanvas->height; y++)
    {
        fputc('|', fp);
        for (x = 0; x < pCanvas->width; x++){
            COLOUR c;
            getPixel(pCanvas, x, y, &c);
            if (c.colour == '\0') c.colour = EMPTY_COLOUR.colour;
            fputc(c.colour, fp);
        }
        fputc('|', fp);
        fputc('\n', fp);
    }
    for (x =0; x < pCanvas->width + 2; x++)
        fputc('-', fp);
    fputc('\n', fp);

    return E_OK;
}

/*
Draw Line using Bresenham's Algorithm.
*/
int drawCanvasLine(CANVAS * pCanvas, int x1, int y1, int x2, int y2)
{
    if (NULL == pCanvas || NULL == pCanvas->pPixels) return E_BAD_ARG;
    if (x1 < 0 || x1 >= pCanvas->width) return E_BAD_ARG;
    if (y1 < 0 || y1 >= pCanvas->height) return E_BAD_ARG;
    if (x2 < 0 || x2 >= pCanvas->width) return E_BAD_ARG;
    if (y2 < 0 || y2 >= pCanvas->height) return E_BAD_ARG;

    int dx = abs(x2-x1), sx = x1<x2 ? 1 : -1;
    int dy = abs(y2-y1), sy = y1<y2 ? 1 : -1;
    int err = (dx>dy ? dx : -dy)/2, e2;

    for (;;)
    {
        setPixel(pCanvas, x1, y1, LINE_COLOUR);
        if (x1 == x2 && y1 == y2) break;
        e2 = err;
        if (e2 > -dx){ err -= dy; x1 += sx; }
        if (e2 < dy){ err += dx; y1 += sy; }
    }

    return E_OK;
}

int drawCanvasRect(CANVAS * pCanvas, int x1, int y1, int x2, int y2)
{
    if (NULL == pCanvas || NULL == pCanvas->pPixels) return E_BAD_ARG;
    if (x1 < 0 || x1 >= pCanvas->width) return E_BAD_ARG;
    if (y1 < 0 || y1 >= pCanvas->height) return E_BAD_ARG;
    if (x2 < 0 || x2 >= pCanvas->width) return E_BAD_ARG;
    if (y2 < 0 || y2 >= pCanvas->height) return E_BAD_ARG;

    drawCanvasLine(pCanvas, x1, y1, x1, y2);
    drawCanvasLine(pCanvas, x1, y2, x2, y2);
    drawCanvasLine(pCanvas, x2, y2, x2, y1);
    drawCanvasLine(pCanvas, x2, y1, x1, y1);

    return E_OK;
}

typedef struct _POINT_NODE
{
    int x;
    int y;
    int processed;
    struct _POINT_NODE * pNext;
} POINT_NODE;

int fillCanvas(CANVAS * pCanvas, int x, int y, COLOUR replacement_colour)
{
    if (NULL == pCanvas || NULL == pCanvas->pPixels) return E_BAD_ARG;
    if (x < 0 || x >= pCanvas->width) return E_BAD_ARG;
    if (y < 0 || y >= pCanvas->height) return E_BAD_ARG;


    POINT_NODE * pPoint = (POINT_NODE *)malloc(sizeof(POINT_NODE));
    if (NULL == pPoint) return E_OOM;
    pPoint->x = x;
    pPoint->y = y;
    pPoint->pNext = NULL;

    COLOUR target_colour;
    int e_getPixel = getPixel(pCanvas, x, y, &target_colour);
    if (E_OK != e_getPixel) return e_getPixel;

    while (pPoint)
    {
        POINT_NODE * pCurrPoint = pPoint;

        int x = pCurrPoint->x;
        int y = pCurrPoint->y;
        pPoint = pCurrPoint->pNext;
        free(pCurrPoint);

        COLOUR px_colour;
        int e_getPixel = getPixel(pCanvas, x, y, &px_colour);
        if (E_OK != e_getPixel) return e_getPixel;

        if (px_colour.colour == target_colour.colour)
        {
            int e_setPixel = setPixel(pCanvas, x, y, replacement_colour);
            if (E_OK != e_setPixel) return e_setPixel;

            // Check West
            if (x > 0){
                POINT_NODE * pNewPoint = (POINT_NODE *)malloc(sizeof(POINT_NODE));
                if (NULL == pNewPoint) return E_OOM;
                pNewPoint->x = x - 1;
                pNewPoint->y = y;

                if (pPoint) pNewPoint->pNext = pPoint;
                pPoint = pNewPoint;
            }

            // Check East
            if (x < pCanvas->width - 1)
            {
                POINT_NODE * pNewPoint = (POINT_NODE *)malloc(sizeof(POINT_NODE));
                if (NULL == pNewPoint) return E_OOM;
                pNewPoint->x = x + 1;
                pNewPoint->y = y;

                if (pPoint) pNewPoint->pNext = pPoint;
                pPoint = pNewPoint;
            }

            // Check North
            if (y < pCanvas->height - 1)
            {
                POINT_NODE * pNewPoint = (POINT_NODE *)malloc(sizeof(POINT_NODE));
                if (NULL == pNewPoint) return E_OOM;
                pNewPoint->x = x;
                pNewPoint->y = y + 1;

                if (pPoint) pNewPoint->pNext = pPoint;
                pPoint = pNewPoint;
            }

            // Check South
            if (y > 0)
            {
                POINT_NODE * pNewPoint = (POINT_NODE *)malloc(sizeof(POINT_NODE));
                if (NULL == pNewPoint) return E_OOM;
                pNewPoint->x = x;
                pNewPoint->y = y - 1;

                if (pPoint) pNewPoint->pNext = pPoint;
                pPoint = pNewPoint;
            }
        }
    }
    return E_OK;
}

