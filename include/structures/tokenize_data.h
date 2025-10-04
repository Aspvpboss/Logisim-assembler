#pragma once



enum Token_Type{

    TOKEN_NONE,

    TOKEN_OP_ADD,
    TOKEN_OP_SUB,
    TOKEN_OP_MUL,
    TOKEN_OP_DIV,
    TOKEN_OP_CMP,
    TOKEN_OP_LRS,
    TOKEN_OP_ARS,
    TOKEN_OP_LLS,
    TOKEN_OP_AND,
    TOKEN_OP_OR,
    TOKEN_OP_XOR,
    TOKEN_OP_NOT,
    TOKEN_OP_NOR,
    TOKEN_OP_NAND,
    TOKEN_OP_XNOR,

    TOKEN_OP_MOV,
    TOKEN_OP_PUSH,
    TOKEN_OP_POP,
    TOKEN_OP_JMP,
    TOKEN_OP_JIF,
    TOKEN_OP_CAL,
    TOKEN_OP_CIF,
    TOKEN_OP_HLT,

    TOKEN_COMP_OVER,
    TOKEN_COMP_CARRY,
    TOKEN_COMP_NEGATIVE,
    TOKEN_COMP_ZERO,
    TOKEN_COMP_NEQ,
    TOKEN_COMP_EQ,
    TOKEN_COMP_UGR,
    TOKEN_COMP_ULS,
    TOKEN_COMP_UGRE,
    TOKEN_COMP_ULSE,
    TOKEN_COMP_SGR,
    TOKEN_COMP_SLS,
    TOKEN_COMP_SGRE,
    TOKEN_COMP_SLSE,

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
    TOKEN_MACRO_START,
    TOKEN_MACRO_END,

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

typedef struct Token_Line{

    int amount_tokens;
    Token *tk;
    char *path;
    int original_line;
    struct Token_Line *next;

} Token_Line;


typedef struct{

    Token_Line *head;
    Token_Line *tail;
    int amount_lines;
    char *path;

} Token_File;


typedef struct{

    Token_File **tk_files;
    int amount_files;
    
} Token_File_Manager;


