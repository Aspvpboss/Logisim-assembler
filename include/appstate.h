#pragma once

#include <MemTrack.h>
#include <stdint.h>
#include "file_manager.h"
#include "tokenize_data.h"
#include "assembler_configs.h"
#include "symbol_table.h"


typedef struct{

    File_Manager manager;
    Assembler_Configs configs;
    Token_File_Manager tk_manager;
    Symbol_Table_Manager symbol_manager;

} Appstate;


