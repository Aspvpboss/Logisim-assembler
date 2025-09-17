#include "error.h"
#include <string.h>

void LogError(ErrorCode error, int code){

    char error_string[100];

    switch(error){

        case(ASSEMBLE_ARGS_ERROR):

            
            if(code == 1){
                strcpy(error_string, "invalid command arg");
            }
            if(code == 2){
                strcpy(error_string, "invalid output arg");
            }
            if(code == 3){
                strcpy(error_string, "no output file");
            }
            if(code == 4){
                strcpy(error_string, "no command args");
            }
            if(code == 5){
                strcpy(error_string, "duplicate output type flags");
            }
            if(code == 6){
                strcpy(error_string, "no output type flag");
            }

            printf("Command prompt error: %s\n", error_string);
            break;

        case(FILE_ERROR):

            if(code == 1){
                strcpy(error_string, "failed to open output file");
            }
            if(code == 2){
                strcpy(error_string, "failed to open an input file");
            }            

            printf("File error: %s\n", error_string);
            break;

        default:

            break;

    }

}