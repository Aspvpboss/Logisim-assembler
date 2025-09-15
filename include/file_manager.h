#pragma once

#include <stdio.h>

typedef struct{

    FILE *file;
    int num_lines;
    const char *path;

} File_Info;

typedef struct{

    int amount_inputs;
    File_Info *inputs;
    File_Info output;

} File_Manager;