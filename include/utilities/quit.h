#pragma once

#include "appstate.h"
#include "tokenize.h"
#include "symbol_table.h"
#include "macro_data.h"

void quit(void *appstate);
void free_tokenized_file(Token_File *tf);
void free_tokenized_line(Token_Line *tl);
void free_file_manager(File_Manager *manager);