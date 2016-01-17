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

    if (CMD_CREATE_CANVAS.id == cmd.id)
    {
        CMD_CREATE_CANVAS_ARGS args;
        err = parseCreateCanvasArgs(fpInput, &args);
        if (E_OK != err) return err;
        addCanvas(pDc, args.width, args.height);
    }
    else if (CMD_LINE.id == cmd.id)
    {
        CMD_LINE_ARGS args;
        err = parseLineArgs(fpInput, &args);
        if (E_OK != err) return err;
        drawLine(pDc, args.x1, args.y1, args.x2, args.y2);
    }
    else if (CMD_RECT.id == cmd.id)
    {
        CMD_RECT_ARGS args;
        err = parseRectArgs(fpInput, &args);
        if (E_OK != err) return err;
        drawRect(pDc, args.x1, args.y1, args.x2, args.y2);
    }
    else if (CMD_FILL.id == cmd.id)
    {
        CMD_FILL_ARGS args;
        err = parseFillArgs(fpInput, &args);
        if (E_OK != err) return err;
        fill(pDc, args.x, args.y, args.colour);
    }
    else
    {
        return E_BAD_ARG;
    }

    return E_OK;
}

int proc(FILE *fpInput, FILE *fpOutput)
{
    DRAW_CONTEXT dc;
    initDc(&dc);

    // Process all the commands and create the canvases
    while (procLine(fpInput, &dc) == E_OK)
    {
        // The problem format requires that
        // output be generated incrementally.
        printDc(&dc, fpOutput);
    }

    return E_OK;
}

int main(int argc, char *argv[])
{
    const char * sz_inputFile = argv[1];
    const char * sz_outputFile = argv[2];

    int exit_code = E_OK;
    FILE *fpInput = stdin, *fpOutput = stdout;

    if (argc > 1)
    {
        fpInput = fopen(sz_inputFile, "r");
        if (NULL == fpInput) goto cleanup;
    }

    if (argc > 2)
    {
        fpOutput = fopen(sz_outputFile, "w");
        if (NULL == fpOutput) goto cleanup;
    }

    proc(fpInput, fpOutput);

cleanup:
    if (fpInput)
        fclose(fpInput);
    if (fpOutput)
        fclose(fpOutput);

    return exit_code;
}
