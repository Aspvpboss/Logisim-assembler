#pragma once
#include "tokenize_data.h"
#include "symbol_table.h"
#include "error.h"


Token_Line* copy_Token_Line(const Token_Line *line);
int copy_exported_symbols(Symbol_Table *dest, Symbol_Table *src, ErrorData *result);
Token_File *find_token_file_name(const char *str, Token_File_Manager *token_manager);
void update_glob_symbols(Token_Line *start, Symbol_Table *table);