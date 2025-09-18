#pragma once

#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "file_manager.h"
#include "assembler_configs.h"

typedef struct{

    File_Manager manager;
    Assembler_Configs configs;

} Appstate;