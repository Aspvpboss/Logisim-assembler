#include "error.h"
#include "quit.h"
#include <string.h>


void LogError(ErrorCode error, ErrorData *data){

    switch(error){

        case(ASSEMBLE_ARGS_ERROR):

            switch(data->code){

                case(1):
                    printf("Command prompt error: invalid command arg '%s'\n", data->string);
                    break;

                case(2):
                    printf("Command prompt error: invalid output arg '%s'\n", data->string);
                    break;

                case(3):
                    printf("Command prompt error: no output file given\n");
                    break;

                case(4):
                    printf("Command prompt error: no command args given\n");
                    break;

                case(5):
                    printf("Command prompt error: duplicate output type flags '%s'\n", data->string);
                    break;

                case(6):
                    printf("Command prompt error: no output type flag given\n");
                    break;

                case(7):
                    printf("Command prompt error: no input file given\n");
                    break;

            }

            break;

        case(FILE_ERROR):

            switch(data->code){
            
                case(1):
                    printf("File error: failed to open output file '%s'\n", data->string);
                    break;
            
                case(2):
                    printf("File error: failed to open an input file '%s'\n", data->string);
                    break;
            
                case(3):
                    printf("File error: an input file is empty\n");
                    break;

            }

            break;

        default:

            break;

    }


    t_free(data->string);    
}

