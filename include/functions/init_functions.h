#pragma once


#include "appstate.h"
#include "error.h"

#include <string.h>
#include <ctype.h>
/*

    all parse functions
    return 0 for nothing
    return 1 to continue in for loop
    return -1 for error

*/
int parse_output_file(File_Manager *manager, char **argv, int argc, int *i, ErrorData *result);
int parse_output_types(Assembler_Configs *configs, char **argv, int i, ErrorData *result);
int parse_input_files(File_Manager *manager, char **argv, int i);