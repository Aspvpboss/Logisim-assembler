#pragma once
#include "tokenize_data.h"
#include "symbol_table.h"


Token_Line* copy_Token_Line(const Token_Line *line);
void copy_exported_symbols(Symbol_Table *dest, Symbol_Table *src);
Token_File *find_token_file_name(const char *str, Token_File_Manager *token_manager);