#include "lexer_functions.h"



enum Token_Type check_immediate_type(char *str, size_t str_len){

    if(str_len < 1)
        return TOKEN_NONE;

    int base = 10;
    int offset = 0;
    char *endptr;
    long int addr_value;

    if(str_len >= 3){

        if(strncmp(str, "0x", 2) == 0){
            base = 16;
            offset = 2;
        }
        if(strncmp(str, "0b", 2) == 0){
            base = 2;
            offset = 2;
        }

    }

    
    addr_value = strtol(str + offset, &endptr, base);

    if(str + offset == endptr || *endptr != '\0'){

        return TOKEN_NONE;

    }

    if(addr_value >= 0 && addr_value < 256){

        return TOKEN_IMMEDIATE;

    }
    
    return TOKEN_NONE;
}


enum Token_Type check_register(char *str, size_t str_len){

    if(str_len == 4 && str[0] == '[' && str[1] == 'r' && str[3] == ']'){
        int reg_addr = str[1] - '0';
        if(reg_addr <= 7 && reg_addr >= 0){
            return TOKEN_REG_POINTER;
        }
    }

    if(str_len == 2 && str[0] == 'r'){
        int reg_addr = str[1] - '0';
        if(reg_addr <= 7 && reg_addr >= 0){
            return TOKEN_REGISTER;
        }
    }

    return TOKEN_NONE;
}


enum Token_Type check_io(char *str, size_t str_len){

    if(str_len == 3 && (strncmp(str, "io", 2) == 0)){

        int reg_addr = str[2] - '0';
        if(reg_addr <= 7 && reg_addr >= 0){
            return TOKEN_IO;
        }
    }

    return TOKEN_NONE;
}


enum Token_Type check_special_type(char *str, size_t str_len){

    if(strcmp(str, ".macrostart") == 0)
        return TOKEN_MACRO_START;
    if(strcmp(str, ".macroend") == 0)
        return TOKEN_MACRO_END;
    if(strcmp(str, ".inline_macro") == 0)
        return TOKEN_MACRO_INLINE;

    switch(str[0]){

        case(':'):
            return TOKEN_LABEL_COLON;
        case('"'):
            return TOKEN_STRING_START;
        case('['):
            return TOKEN_START_BRACKET;
        case(']'):
            return TOKEN_END_BRACKET;

    }

    return TOKEN_NONE;
}


enum Token_Type check_directives(char *str){

    if(strcmp(str, ".include") == 0)
        return TOKEN_INCLUDE_DIR;

    if(strcmp(str, ".extern") == 0)
        return TOKEN_EXTERN_DIR;

    if(strcmp(str, ".at") == 0)
        return TOKEN_AT_DIR;

    if(strcmp(str, ".startfile") == 0)
        return TOKEN_START_FILE_DIR;

    if(strcmp(str, ".endfile") == 0)
        return TOKEN_END_FILE_DIR;
    
    if(strcmp(str, ".glob") == 0)
        return TOKEN_GLOBAL_DIR;


    return TOKEN_NONE;
}


enum Token_Type check_opcode(char *str){

    if (strcasecmp(str, "add") == 0) return TOKEN_OP_ADD;
    if (strcasecmp(str, "sub") == 0) return TOKEN_OP_SUB;
    if (strcasecmp(str, "inc") == 0) return TOKEN_OP_INC;
    if (strcasecmp(str, "lrs") == 0) return TOKEN_OP_LRS;
    if (strcasecmp(str, "or")  == 0) return TOKEN_OP_OR;
    if (strcasecmp(str, "xor") == 0) return TOKEN_OP_XOR;
    if (strcasecmp(str, "nand") == 0) return TOKEN_OP_NAND;

    if (strcasecmp(str, "ldi") == 0) return TOKEN_OP_LDI;
    if (strcasecmp(str, "rtr") == 0) return TOKEN_OP_RTR;
    if (strcasecmp(str, "rpc") == 0) return TOKEN_OP_RPC;
    if (strcasecmp(str, "pcr") == 0) return TOKEN_OP_PCR;
    if (strcasecmp(str, "str") == 0) return TOKEN_OP_STR;
    if (strcasecmp(str, "lod") == 0) return TOKEN_OP_LOD;

    if (strcasecmp(str, "jmp") == 0) return TOKEN_OP_JMP;
    if (strcasecmp(str, "jif") == 0) return TOKEN_OP_JIF;
    if (strcasecmp(str, "cal") == 0) return TOKEN_OP_CAL;
    if (strcasecmp(str, "cif") == 0) return TOKEN_OP_CIF;
    if (strcasecmp(str, "ret") == 0) return TOKEN_OP_RET;
    if (strcasecmp(str, "hlt") == 0) return TOKEN_OP_HLT;

    if (strcasecmp(str, "snd") == 0) return TOKEN_OP_SND;
    if (strcasecmp(str, "sdi") == 0) return TOKEN_OP_SDI;
    if (strcasecmp(str, "rec") == 0) return TOKEN_OP_REC;
    if (strcasecmp(str, "wre") == 0) return TOKEN_OP_WRE;

    return TOKEN_NONE;

}


enum Token_Type check_comparison_operators(char *str){

    if(strcmp(str, ">") == 0)
        return TOKEN_COMP_GREATER;
    if(strcmp(str, ">=") == 0)
        return TOKEN_COMP_GREATER_EQ;
    if(strcmp(str, "<") == 0)
        return TOKEN_COMP_LESS;
    if(strcmp(str, "<=") == 0)
        return TOKEN_COMP_LESS_EQ;
    if(strcmp(str, "==") == 0)
        return TOKEN_COMP_ZERO;
    if(strcmp(str, "!=") == 0)
        return TOKEN_COMP_NOT_ZERO;
    if(strcmp(str, "odd") == 0)
        return TOKEN_COMP_ODD;
    if(strcmp(str, "carry") == 0)
        return TOKEN_COMP_CARRY;

    return TOKEN_NONE;
}