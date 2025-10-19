#pragma once

enum Output_Type{
    
    NO_OUTPUT,
    BINARY_OUTPUT,
    HEX_OUTPUT

};

typedef struct{

    enum Output_Type output_type;

} Assembler_Configs;