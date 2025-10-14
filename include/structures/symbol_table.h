#pragma once
#include <stdbool.h>

typedef enum{

    SYMBOL_LABEL,
    SYMBOL_MACRO,

} Symbol_Type;


typedef struct{

    void *data;
    char *text;
    bool export;
    Symbol_Type type;

} Symbol;


typedef struct{

    Symbol **symbols;
    uint16_t amount_symbols;
    char *file;

} Symbol_Table;


typedef struct{

    Symbol_Table **tables;
    uint16_t amount_tables;

} Symbol_Table_Manager;

