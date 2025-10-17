#pragma once
#include "tokenize_data.h"
#include <stdint.h>

typedef struct{

    char **args;
    uint8_t amount_args;

} Mul_Macro_Data;

typedef struct{

    char *macro;

} Single_Macro_Data;

