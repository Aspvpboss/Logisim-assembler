#pragma once

#include "macro_data.h"
#include "tokenize_data.h"
#include "symbol_table.h"
#include "error.h"

int lex_all_macros(Symbol_Table *symbols, ErrorData *error);