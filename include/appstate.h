#pragma once

#include "file_manager.h"
#include "assembler_configs.h"

typedef struct{

    File_Manager manager;
    Assembler_Configs configs;

} Appstate;