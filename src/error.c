#include "error.h"

void LogError(ErrorCode error, int code){

    switch(error){

        case(ASSEMBLE_ARGS_ERROR):

            /*
                0x1 - invalid command arg
                0x2 - invalid output arg
                0x3 - no output file
                0x4 - no command args
                0x5 - duplicate output type flags
                0x6 - no output type flag
            */
            printf("Command prompt error: %#x\n", code);
            break;

        case(FILE_ERROR):

            /*
            
            */
            printf("File error: %#x\n", code);
            break;

        default:

            break;

    }

}