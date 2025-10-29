#include "error.h"
#include "quit.h"
#include <string.h>


void LogError(ErrorCode general_error, ErrorData *result){

    fputs("\n", stderr);

    switch(general_error){

        case(ASSEMBLE_ARGS_ERROR):

            switch(result->specific_code){

                case(1):
                    fprintf(stderr, "Command prompt error: invalid command arg '%s'\n", 
                            result->string);
                    break;

                case(2):
                    fprintf(stderr, "Command prompt error: invalid output arg '%s'\n", 
                            result->string);
                    break;

                case(3):
                    fprintf(stderr, "Command prompt error: no output file given\n");
                    break;

                case(4):
                    fprintf(stderr, "Command prompt error: no command args given\n");
                    break;

                case(5):
                    fprintf(stderr, "Command prompt error: duplicate output type flags '%s'\n", 
                            result->string);
                    break;

                case(6):
                    fprintf(stderr, "Command prompt error: no output type flag given\n");
                    break;

                case(7):
                    fprintf(stderr, "Command prompt error: no input file given\n");
                    break;


                default: break;
            }

            break;

        case(FILE_ERROR):

            switch(result->specific_code){
            
                case(1):
                    fprintf(stderr, "File error: failed to open output file '%s'\n", 
                            result->string);
                    break;
            
                case(2):
                    fprintf(stderr, "File error: failed to open an input file '%s'\n", 
                            result->string);
                    break;
            
                case(3):
                    fprintf(stderr, "File error: an input file '%s' is empty\n", result->string);
                    break;


                default: break;
            }

            break;

        case(MACRO_ERROR):

            switch(result->specific_code){

                case(1):
                    fprintf(stderr, "Macro error: inline_macros should be defined with one macro, at line '%d' in file '%s'\n",
                            result->integer_data, result->file_name);
                    break;

                case(2):
                    fprintf(stderr, "Macro error: duplicate macro args detected, at line '%d' in file '%s'\n",
                            result->integer_data, result->file_name);
                    break;


                default: break;

            }

            break;

        case(LINKER_ERROR):

            switch(result->specific_code){

                case(1):
                    fprintf(stderr, "Linker error: .include couldn't find '%s' as a file, at line '%d' in file '%s'\nmake sure to assemble all files you want to include\n", 
                            result->string, result->integer_data, result->file_name);
                    break;
                case(2):
                    fprintf(stderr, "Linker error: '%s' has already been included once, at line '%d' in file '%s'\nyou cannot include a file more than once\n",
                            result->string, result->integer_data, result->file_name);
                    break;
                case(3):
                    fprintf(stderr, "Linker error: .extern couldn't find '%s' as a file, at line '%d' in file '%s'\nmake sure to assemble all files you want to extern\n",
                            result->string, result->integer_data, result->file_name);
                    break;
                case(4):
                    fprintf(stderr, "Linker error: must include '%s' before using .extern on it, at line '%d' in file '%s'\n\n",
                            result->string, result->integer_data, result->file_name);
                    break;
                case(5):
                    fprintf(stderr, "Linker error: '%s' cannot include itself, at line '%d' in file '%s'\n\n",
                            result->string, result->integer_data, result->file_name);
                    break;
                case(6):
                    fprintf(stderr, "Linker error: tried to include duplicate symbol into '%s', at line '%d' in file '%s'\n\nDid you .include more than once?",
                            result->string, result->integer_data, result->file_name);
                    break;
                case(7):
                    fprintf(stderr, "Linker error: tried to extern duplicate symbol into '%s', at line '%d' in file '%s'\n\nDid you .extern more than once?",
                            result->string, result->integer_data, result->file_name);
                    break;
                case(8):
                    fprintf(stderr, "Linker error: duplicate symbol '%s', at line '%d' in file '%s'\n\n",
                            result->string, result->integer_data, result->file_name);
                    break;     
                case(9):
                    fprintf(stderr, "Linker error: cannot include root file '%s', at line '%d' in file '%s'\n\n",
                            result->string, result->integer_data, result->file_name);
                    break;     
                                               

                default: break;

            }


        default: break;

    }

    fputs("\n", stderr);

    t_free(result->string); 
    t_free(result->file_name);

}


void Set_ErrorData(ErrorData *result, uint8_t code, uint32_t integer_data, const char *string_data, const char *file_name){

    result->specific_code = code;
    result->integer_data = integer_data;
    result->string = NULL;
    result->file_name = NULL;
    if(string_data)
        result->string = t_strdup(string_data);
    if(file_name)
        result->file_name = t_strdup(file_name);

}