#pragma once
#include "symbol_table.h"
#include "tokenize_data.h"

void init_symbol_manager(Symbol_Table_Manager *symbols, Token_File_Manager *manager);
void append_symbols(Token *previous, Token *current, Symbol_Table *symbols, Token_Line *token_line);
Symbol* find_symbol_by_name(const char *str, Symbol_Table *table);
Symbol_Table* find_symbol_name_by_name(const char *str, Symbol_Table_Manager *table);