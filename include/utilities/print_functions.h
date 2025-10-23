#pragma once

#include <stdio.h>
#include <stdint.h>
#include "tokenize_data.h"
#include "macro_data.h"
#include "symbol_table.h"


void print_token_files(Token_File_Manager *manager);
void print_file_lex(Token_File_Manager *manager);
void print_symbols(Symbol_Table_Manager *manager);
void print_dump_file(Token_File_Manager *manager);