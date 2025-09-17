#include "appstate.h"

typedef enum{

    NONE,
    OPCODE,
    DIRECT_REGISTER,
    INDIRECT_REGISTER,
    INDEX_REGISTER,
    LABEL,
    ASCII_ARRAY,
    INT_ARRAY,
    FUNCTION,
    GLOBAL,
    INCLUDE,
    IMMEDIATE,
    AT_DIRECTIVE

} Token_Type;


typedef struct{

    struct Token{

        char *text;
        Token_Type type;

    } *token;

    char *file;
    int original_line;

} Token_Line;


int tokenize(Appstate state);