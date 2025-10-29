#pragma once

#include <stdint.h>
#include <stdbool.h>


enum Token_Type{

    TOKEN_NONE,

    TOKEN_OP_ADD,
    TOKEN_OP_SUB,
    TOKEN_OP_INC,
    TOKEN_OP_LRS,
    TOKEN_OP_OR,
    TOKEN_OP_XOR,
    TOKEN_OP_NAND,

    TOKEN_OP_JMP,
    TOKEN_OP_JIF,
    TOKEN_OP_CAL,
    TOKEN_OP_CIF,
    TOKEN_OP_HLT,
    TOKEN_OP_RET,

    TOKEN_OP_LDI,
    TOKEN_OP_RTR,
    TOKEN_OP_RPC,
    TOKEN_OP_PCR,
    TOKEN_OP_STR,
    TOKEN_OP_LOD,
    TOKEN_OP_STR_INDIRECT,
    TOKEN_OP_LOD_INDIRECT,
    TOKEN_OP_SND,
    TOKEN_OP_SDI,
    TOKEN_OP_WRE,
    TOKEN_OP_REC,


    TOKEN_START_BRACKET,
    TOKEN_END_BRACKET,



    TOKEN_COMP_CARRY,
    TOKEN_COMP_ZERO,
    TOKEN_COMP_NOT_ZERO,
    TOKEN_COMP_GREATER,
    TOKEN_COMP_LESS,
    TOKEN_COMP_GREATER_EQ,
    TOKEN_COMP_LESS_EQ,
    TOKEN_COMP_ODD,

    TOKEN_IO,
    TOKEN_REGISTER,
    TOKEN_REG_POINTER,

    TOKEN_LABEL,
    TOKEN_LABEL_REF,
    TOKEN_LABEL_COLON,

    TOKEN_STRING_START,
    TOKEN_STRING,
    TOKEN_STRING_END,

    TOKEN_MACRO_START,
    TOKEN_MACRO_MUL,
    TOKEN_MACRO_MUL_REF,
    TOKEN_MACRO_ARGS,
    TOKEN_MACRO_END,

    TOKEN_MACRO_INLINE,
    TOKEN_MACRO_SINGLE,
    TOKEN_MACRO_SINGLE_REF,

    TOKEN_IMMEDIATE,
    
    
    TOKEN_GLOBAL_DIR,
    TOKEN_INCLUDE_DIR,
    TOKEN_EXTERN_DIR,
    TOKEN_SYMBOL_EXPORTED,

    TOKEN_AT_DIR,
    TOKEN_START_FILE_DIR,
    TOKEN_END_FILE_DIR

};

typedef struct{

    char *text;
    enum Token_Type type;
    size_t text_len;

} Token;

typedef struct Token_Line{

    uint8_t amount_tokens;
    Token *tk;
    char *file;
    uint16_t original_line;
    struct Token_Line *next;
    void *symbol_table;

} Token_Line;


typedef struct{

    Token_Line *head;
    Token_Line *tail;
    uint16_t amount_lines;
    char *file;
    bool is_included;
    bool is_root;
    void *symbol_table;

} Token_File;


typedef struct{

    Token_File **tk_files;
    uint16_t amount_files;
    
} Token_File_Manager;


