#pragma once

enum Output_Type{
    
    NO_OUTPUT,
    BINARY_OUTPUT,
    HEX_OUTPUT

};


enum Debug_Info{

    SYMBOL_INFO,
    DUMP_FILE_PREMACRO,
    DUMP_FILE_MACRO

};


typedef struct{

    enum Output_Type output_type;
    enum Debug_Info *debug_info;
    int amount_debug;

} Assembler_Configs;