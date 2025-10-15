#pragma once
#include <stdbool.h>

typedef enum{

    SYMBOL_NONE,
    SYMBOL_LABEL,
    SYMBOL_MACRO_MUL,
    SYMBOL_MACRO_SINGLE

} Symbol_Type;


typedef struct{

    void *data;
    char *text;
    bool is_glob;
    Symbol_Type type;

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

