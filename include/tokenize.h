#pragma once
#include "appstate.h"

enum Token_Type{

    NONE,
    OPCODE,
    DIRECT_REGISTER,
    INDIRECT_REGISTER,
    INDEX_REGISTER,

    LABEL,
    ASCII_ARRAY,
    BYTE_ARRAY,
    GLOBAL,
    INCLUDE,

    START_STRING,
    END_STRING,

    START_ARRAY,
    END_ARRAY,

    START_ADDRESSING,
    END_ADDRESSING,

    START_FILE,
    END_FILE,

    IMMEDIATE,
    EIGHT_ADDRESS,
    SIXTEEN_ADDRESS,
    AT_DIRECTIVE,

};

typedef struct{

    char *text;
    enum Token_Type type;

} Token;

typedef struct{

    int amount_tokens;
    Token *tk;
    char *file;
    int original_line;

} Token_Line;


typedef struct{

    Token_Line *tk_line;
    int amount_lines;
    char *path;

} Token_File;



typedef struct{


    
} Token_File_Manager;


int tokenize(Appstate *state);