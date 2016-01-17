#include <stdio.h>
#include <stdlib.h>

#include "error.h"
#include "drawcontext.h"
#include "commands.h"

int procLine(FILE * fpInput, DRAW_CONTEXT * pDc)
{
    CMD_ID cmd;
    int err = readCmdId(fpInput, &cmd);
    if (E_OK != err) return err;

    if (CMD_CREATE_CANVAS.id == cmd.id){
        CMD_CREATE_CANVAS_ARGS args;
        err = parseCreateCanvasArgs(fpInput, &args);
        if (E_OK != err) return err;
        addCanvas(pDc, args.width, args.height);
    } else if (CMD_LINE.id == cmd.id){
        CMD_LINE_ARGS args;
        err = parseLineArgs(fpInput, &args);
        if (E_OK != err) return err;
        drawLine(pDc, args.x1, args.y1, args.x2, args.y2);
    } else if (CMD_RECT.id == cmd.id){
        CMD_RECT_ARGS args;
        err = parseRectArgs(fpInput, &args);
        if (E_OK != err) return err;
        drawRect(pDc, args.x1, args.y1, args.x2, args.y2);
    } else if (CMD_FILL.id == cmd.id){
        CMD_FILL_ARGS args;
        err = parseFillArgs(fpInput, &args);
        if (E_OK != err) return err;
        fill(pDc, args.x, args.y, args.colour);
    } else {
        return E_BAD_ARG;
    }

    return E_OK;
}

int procInput(const char * szInputFile, DRAW_CONTEXT * pDc)
{
    FILE * fpInput = fopen(szInputFile, "r");
    if (NULL == fpInput) {
        return E_FAIL_OPEN_FILE;
    }

    // Process all the commands and create the canvases
    while (procLine(fpInput, pDc) == E_OK);

    fclose(fpInput);
    return E_OK;
}

int main(int argc, char *argv[])
{
    const char * sz_inputFile = argv[1];
    const char * sz_outputFile = argv[2];

    DRAW_CONTEXT dc;
    initDc(&dc);
    procInput(sz_inputFile, &dc);
    printDc(&dc, stdout);

    return E_OK;
}
