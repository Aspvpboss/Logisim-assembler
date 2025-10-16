#pragma once

#include "appstate.h"
#include "tokenize.h"
#include "symbol_table.h"

void quit(Appstate *state);
void free_tokenized_file(Token_File *tf);
void free_tokenized_line(Token_Line *tl);