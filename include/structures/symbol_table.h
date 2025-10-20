#pragma once
#include <stdbool.h>
#include <stdint.h>
#include "tokenize_data.h"

typedef enum{

    SYMBOL_NONE,
    SYMBOL_LABEL,
    SYMBOL_MACRO_MUL,
    SYMBOL_MACRO_SINGLE

} Symbol_Type;


typedef struct{

    void *data;
    char *text;
    bool is_exported;
    bool is_imported;
    Symbol_Type type;
    Token_Line *at_line;

} Symbol;


typedef struct{

    Symbol *symbols;
    uint16_t amount_symbols;
    char *file;

} Symbol_Table;


typedef struct{

    Symbol_Table *tables;
    uint16_t amount_tables;

} Symbol_Table_Manager;

