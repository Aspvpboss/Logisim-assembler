#pragma once

enum Token_Type{

    TOKEN_NONE,
    TOKEN_OPCODE,
    TOKEN_DIRECT_REG,
    TOKEN_INDIRECT_REG,
    TOKEN_INDEX_BASE_REG,
    TOKEN_INDEX_OFFSET_REG,

    TOKEN_LABEL,
    TOKEN_LABEL_COLON,
    TOKEN_ASCII_ARRAY,
    TOKEN_BYTE_ARRAY,


    TOKEN_START_STRING,
    TOKEN_END_STRING,
    TOKEN_START_ARRAY,
    TOKEN_END_ARRAY,
    TOKEN_START_ADDRESSING,
    TOKEN_END_ADDRESSING,


    TOKEN_IMMEDIATE,
    TOKEN_EIGHT_DEC,
    TOKEN_EIGHT_HEX,
    TOKEN_EIGHT_BIN,
    TOKEN_SIXTEEN_DEC,
    TOKEN_SIXTEEN_HEX,
    TOKEN_SIXTEEN_BIN,
    
    TOKEN_AT_DIR,
    TOKEN_GLOBAL_DIR,
    TOKEN_INCLUDE_DIR,
    TOKEN_START_FILE_DIR,
    TOKEN_END_FILE_DIR

};

typedef struct{

    char *text;
    enum Token_Type type;
    size_t text_len;

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
