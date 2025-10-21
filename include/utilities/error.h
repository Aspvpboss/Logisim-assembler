#pragma once

#include <stdio.h>
#include <stdint.h>

typedef enum{

    NO_ERROR,
    ASSEMBLE_ARGS_ERROR,
    FILE_ERROR,
    MACRO_ERROR,
    LINKER_ERROR

} ErrorCode;


typedef struct{

    uint8_t specific_code;
    uint32_t integer_data;
    char *string;
    char *file_name;

} ErrorData;


void Set_ErrorData(ErrorData *result, uint8_t code, uint32_t integer_data, const char *string_data, const char *file_name);
void LogError(ErrorCode general_error, ErrorData *result);

