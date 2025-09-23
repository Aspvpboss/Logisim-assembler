#pragma once

#include <stdio.h>

typedef struct{

    char **raw_text;
    FILE *file;
    int num_lines;
    char *path;

} File_Info;

typedef struct{

    int amount_inputs;
    File_Info *inputs;
    File_Info output;

} File_Manager;