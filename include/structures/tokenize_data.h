#pragma once

enum Token_Type{

    TOKEN_NONE,
    TOKEN_OPCODE,
    TOKEN_DIRECT_REGISTER,
    TOKEN_INDIRECT_REGISTER,
    TOKEN_INDEX_REGISTER,

    TOKEN_LABEL,
    TOKEN_ASCII_ARRAY,
    TOKEN_BYTE_ARRAY,
    TOKEN_GLOBAL,
    TOKEN_INCLUDE,

    TOKEN_START_STRING,
    TOKEN_END_STRING,

    TOKEN_START_ARRAY,
    TOKEN_END_ARRAY,

    TOKEN_START_ADDRESSING,
    TOKEN_END_ADDRESSING,

    TOKEN_START_FILE,
    TOKEN_END_FILE,

    TOKEN_IMMEDIATE,
    TOKEN_EIGHT_ADDRESS,
    TOKEN_SIXTEEN_ADDRESS,
    TOKEN_AT_DIRECTIVE,

};

typedef struct{

    char *text;
    enum Token_Type type;

} Token;

typedef struct{

    int amount_tokens;
    Token *tk;
    char *path;
    int original_line;

} Token_Line;


typedef struct{

    Token_Line **tk_line;
    int amount_lines;
    char *path;

} Token_File;



typedef struct{

    Token_File **tk_files;
    int amount_files;
    
} Token_File_Manager;
