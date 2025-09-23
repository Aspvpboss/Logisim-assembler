#pragma once

#include <stdio.h>

typedef enum{

    NO_ERROR,
    ASSEMBLE_ARGS_ERROR,
    FILE_ERROR

} ErrorCode;


typedef struct{

    int code;
    char *string;

} ErrorData;


void LogError(ErrorCode error, ErrorData *data);

