#pragma once


typedef enum{

    SYMBOL_LABEL,
    SYMBOL_MACRO,
    SYMBOL_EXPORT_LABEL,
    SYMBOL_EXPORT_MACRO

} Symbol_Type;


typedef struct{

    void *data;
    char *text;
    Symbol_Type type;

} Symbol;


typedef struct{

    Symbol **symbols;
    int amount_symbols;
    char *file;

} Symbol_Table;


typedef struct{

    Symbol_Table **tables;
    int amount_tables;

} Symbol_Table_Manager;

