#pragma once

#include <stdio.h>

typedef struct{

    char **raw_text;
    FILE *file;
    uint16_t num_lines;
    char *path;

} File_Info;

typedef struct{

    uint16_t amount_inputs;
    File_Info *inputs;
    File_Info output;

} File_Manager;