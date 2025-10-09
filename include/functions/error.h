#pragma once

#include <stdio.h>
#include <stdint.h>

typedef enum{

    NO_ERROR,
    ASSEMBLE_ARGS_ERROR,
    FILE_ERROR,
    LEXICAL_ERROR

} ErrorCode;


typedef struct{

    uint8_t code;
    uint32_t data;
    char *string;

} ErrorData;


void LogError(ErrorCode error, ErrorData *data);

