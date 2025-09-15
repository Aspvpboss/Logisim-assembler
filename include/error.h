#pragma once

#include <stdio.h>

typedef enum{

    NO_ERROR,
    ASSEMBLE_ARGS_ERROR,
    FILE_ERROR

} ErrorCode;


void LogError(ErrorCode error, int code);