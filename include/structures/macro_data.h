#pragma once
#include "tokenize_data.h"
#include <stdint.h>

typedef struct{

    char *name;
    char **args;
    uint8_t amount_args;
    Token_Line *head;

} Mul_Macro_Data;

typedef struct{

    char *name;
    char *macro;

} Single_Macro_Data;

