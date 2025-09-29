#include "appstate.h"
#include "symbol_table.h"
#include "tokenize_data.h"
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>


void print_TokenType(enum Token_Type type){
    switch(type){

        case(TOKEN_NONE):
            printf("NONE\n");
            break;
        case(TOKEN_EIGHT_BIN):
            printf("EIGHT_BIN\n");
            break;
        case(TOKEN_EIGHT_DEC):
            printf("EIGHT_DEC\n");
            break;
        case(TOKEN_EIGHT_HEX):
            printf("EIGHT_HEX\n");
            break;
        case(TOKEN_SIXTEEN_BIN):
            printf("SIXTEEN_BIN\n");
            break;
        case(TOKEN_SIXTEEN_DEC):
            printf("SIXTEEN_DEC\n");
            break;
        case(TOKEN_SIXTEEN_HEX):
            printf("SIXTEEN_HEX\n");
            break;
        case(TOKEN_DIRECT_REG):
            printf("DIRECT REGISTER\n");
            break;
        default:
            printf("not an option\n");
            break;
    }
}


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

    if(addr_value > -128 && addr_value < 256){

        switch(base){
            case(2):
                return TOKEN_EIGHT_BIN;
            case(10):
                return TOKEN_EIGHT_DEC;
            case(16):
                return TOKEN_EIGHT_HEX;
            default:
                break;
        }

    }

    if(addr_value >= 0 && addr_value < 65536){

        switch(base){
            case(2):
                return TOKEN_SIXTEEN_BIN;
            case(10):
                return TOKEN_SIXTEEN_DEC;
            case(16):
                return TOKEN_SIXTEEN_HEX;
            default:
                break;
        }

    }
    
    return TOKEN_NONE;
}


int check_register(char *str, size_t str_len){

    if(str[0] == 'r' && str_len == 2){
        int reg_addr = str[1] - '0';
        if(reg_addr <= 7 && reg_addr >= 0){
            return TOKEN_DIRECT_REG;
        }
    }

    return 0;
}


enum Token_Type check_special_type(char *str, size_t str_len){

    if(str_len == 1){
        switch(str[0]){

            case('#'):
                return TOKEN_IMMEDIATE;
            case('"'):
                return TOKEN_START_STRING;
            case('['):
                return TOKEN_START_ADDRESSING;
            case(']'):
                return TOKEN_END_ADDRESSING;
            case('{'):
                return TOKEN_START_ARRAY;
            case('}'):
                return TOKEN_END_ARRAY;
            case(':'):
                return TOKEN_LABEL_COLON;

            default:
                return TOKEN_NONE;
        }
    }

    return TOKEN_NONE;
}


enum Token_Type check_directives(char *str, size_t str_len){

    if(strcmp(str, ".include") == 0)
        return TOKEN_INCLUDE_DIR;

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


enum Token_Type check_label_type(char *str, size_t str_len){

    if(strcmp(str, ".byte") == 0)
        return TOKEN_BYTE_ARRAY;

    if(strcmp(str, ".ascii") == 0)
        return TOKEN_ASCII_ARRAY;

    if(strcmp(str, ".macro"))
        return TOKEN_MACRO_START;
    
    if(strcmp(str, ".macroend"))
        return TOKEN_MACRO_END;

    return TOKEN_NONE;
}

enum Token_Type check_opcode(char *str, size_t str_len){

    if(strcasecmp(str, "add") == 0)
        return TOKEN_OP_ADD;
    if(strcasecmp(str, "sub") == 0)
        return TOKEN_OP_SUB;
    if(strcasecmp(str, "cmp") == 0)
        return TOKEN_OP_CMP;
    if(strcasecmp(str, "ars") == 0)
        return TOKEN_OP_ARS;
    if(strcasecmp(str, "lrs") == 0)
        return TOKEN_OP_LRS;
    if(strcasecmp(str, "lls") == 0)
        return TOKEN_OP_LLS;
    if(strcasecmp(str, "mul") == 0)
        return TOKEN_OP_MUL;
    if(strcasecmp(str, "div") == 0)
        return TOKEN_OP_DIV;
    if(strcasecmp(str, "and") == 0)
        return TOKEN_OP_AND;
    if(strcasecmp(str, "or") == 0)
        return TOKEN_OP_OR;
    if(strcasecmp(str, "xor") == 0)
        return TOKEN_OP_XOR;
    if(strcasecmp(str, "not") == 0)
        return TOKEN_OP_NOT;
    if(strcasecmp(str, "nand") == 0)
        return TOKEN_OP_NAND;
    if(strcasecmp(str, "nor") == 0)
        return TOKEN_OP_NOR;
    if(strcasecmp(str, "xnor") == 0)
        return TOKEN_OP_XNOR;

    if(strcasecmp(str, "MOV") == 0)
        return TOKEN_OP_MOV;
    if(strcasecmp(str, "PUSH") == 0)
        return TOKEN_OP_PUSH;
    if(strcasecmp(str, "POP") == 0)
        return TOKEN_OP_POP;
    if(strcasecmp(str, "JMP") == 0)
        return TOKEN_OP_JMP;
    if(strcasecmp(str, "JIF") == 0)
        return TOKEN_OP_JIF;
    if(strcasecmp(str, "CAL") == 0)
        return TOKEN_OP_CAL;
    if(strcasecmp(str, "CIF") == 0)
        return TOKEN_OP_CIF;
    if(strcasecmp(str, "HLT") == 0)
        return TOKEN_OP_HLT;


    return TOKEN_NONE;
}


enum Token_Type check_comparison_operators(char *str, size_t str_len){

    if(strcasecmp(str, ">"))
        return TOKEN_COMP_ULS;

    return TOKEN_NONE;
}


enum Token_Type lex_token(Token *token){

    char *str = token->text;
    size_t str_len = token->text_len;
    enum Token_Type result;

    if(!str_len){
        return TOKEN_NONE;
    }


    result = check_immediate_type(str, str_len);
    if(result)
        return result;

    if(check_register(str, str_len))
        return TOKEN_DIRECT_REG;

    result = check_special_type(str, str_len);
    if(result)
        return result;

    result = check_directives(str, str_len);
    if(result)
        return result;

    result = check_label_type(str, str_len);
    if(result)
        return result;

    result = check_opcode(str, str_len);
    if(result)
        return result;



    return TOKEN_NONE;
}





int lexical_analysis(Appstate *state){
    
    Token test;
    test.text = t_strdup("0xff");

    enum Token_Type result = lex_token(&test);

    print_TokenType(result);

    t_free(test.text);

    return 0;
}
