#include "appstate.h"
#include "symbol_table.h"
#include "tokenize_data.h"
#include "error.h"

#include <stdbool.h>
#include <string.h>
#include <stdlib.h>


const char* token_type_to_string(enum Token_Type type) {

    switch (type) {
        case TOKEN_NONE: return "TOKEN_NONE";

        case TOKEN_OP_ADD: return "TOKEN_OP_ADD";
        case TOKEN_OP_SUB: return "TOKEN_OP_SUB";
        case TOKEN_OP_CMP: return "TOKEN_OP_CMP";
        case TOKEN_OP_LRS: return "TOKEN_OP_LRS";
        case TOKEN_OP_OR: return "TOKEN_OP_OR";
        case TOKEN_OP_XOR: return "TOKEN_OP_XOR";
        case TOKEN_OP_NAND: return "TOKEN_OP_NAND";

        case TOKEN_OP_JMP: return "TOKEN_OP_JMP";
        case TOKEN_OP_JIF: return "TOKEN_OP_JIF";
        case TOKEN_OP_CAL: return "TOKEN_OP_CAL";
        case TOKEN_OP_CIF: return "TOKEN_OP_CIF";
        case TOKEN_OP_HLT: return "TOKEN_OP_HLT";
        case TOKEN_OP_RET: return "TOKEN_OP_RET";

        case TOKEN_OP_LDI: return "TOKEN_OP_LDI";
        case TOKEN_OP_RTR: return "TOKEN_OP_RTR";
        case TOKEN_OP_RPC: return "TOKEN_OP_RPC";
        case TOKEN_OP_PCR: return "TOKEN_OP_PCR";
        case TOKEN_OP_STR: return "TOKEN_OP_STR";
        case TOKEN_OP_LOD: return "TOKEN_OP_LOD";
        case TOKEN_OP_STR_INDIRECT: return "TOKEN_OP_STR_INDIRECT";
        case TOKEN_OP_LOD_INDIRECT: return "TOKEN_OP_LOD_INDIRECT";

        case TOKEN_OP_SND: return "TOKEN_OP_SND";
        case TOKEN_OP_SDI: return "TOKEN_OP_SDI";
        case TOKEN_OP_WRE: return "TOKEN_OP_WRE";
        case TOKEN_OP_REC: return "TOKEN_OP_REC";

        case TOKEN_COMP_CARRY: return "TOKEN_COMP_CARRY";
        case TOKEN_COMP_ZERO: return "TOKEN_COMP_ZERO";
        case TOKEN_COMP_NOT_ZERO: return "TOKEN_COMP_NOT_ZERO";
        case TOKEN_COMP_GREATER: return "TOKEN_COMP_GREATER";
        case TOKEN_COMP_LESS: return "TOKEN_COMP_LESS";
        case TOKEN_COMP_GREATER_EQ: return "TOKEN_COMP_GREATER_EQ";
        case TOKEN_COMP_LESS_EQ: return "TOKEN_COMP_LESS_EQ";
        case TOKEN_COMP_ODD: return "TOKEN_COMP_ODD";

        case TOKEN_REGISTER: return "TOKEN_REGISTER";
        case TOKEN_REG_POINTER: return "TOKEN_REG_POINTER";

        case TOKEN_LABEL: return "TOKEN_LABEL";
        case TOKEN_LABEL_COLON: return "TOKEN_LABEL_COLON";

        case TOKEN_STRING_START: return "TOKEN_STRING_START";
        case TOKEN_STRING: return "TOKEN_STRING";
        case TOKEN_STRING_END: return "TOKEN_STRING_END";

        case TOKEN_MACRO_START: return "TOKEN_MACRO_START";
        case TOKEN_MACRO_MUL: return "TOKEN_MACRO_MUL";
        case TOKEN_MACRO_ARGS: return "TOKEN_MACRO_ARGS";
        case TOKEN_MACRO_END: return "TOKEN_MACRO_END";

        case TOKEN_MACRO_INLINE: return "TOKEN_MACRO_INLINE";
        case TOKEN_MACRO_SINGLE: return "TOKEN_MACRO_SINGLE";

        case TOKEN_IMMEDIATE: return "TOKEN_IMMEDIATE";

        case TOKEN_AT_DIR: return "TOKEN_AT_DIR";
        case TOKEN_GLOBAL_DIR: return "TOKEN_GLOBAL_DIR";
        case TOKEN_INCLUDE_DIR: return "TOKEN_INCLUDE_DIR";
        case TOKEN_START_FILE_DIR: return "TOKEN_START_FILE_DIR";
        case TOKEN_END_FILE_DIR: return "TOKEN_END_FILE_DIR";

        default: return "TOKEN_UNKNOWN";
    }

    return NULL;
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


enum Token_Type check_special_type(char *str, size_t str_len){

    if(strcmp(str, ".macro") == 0)
        return TOKEN_MACRO_START;
    if(strcmp(str, ".macroend") == 0)
        return TOKEN_MACRO_END;
    if(strcmp(str, ".inline_macro") == 0)
        return TOKEN_MACRO_INLINE;

    if(str_len == 1 && str[0] == ':')
        return TOKEN_LABEL_COLON;
    if(str_len == 1 && str[0] == '"')
        return TOKEN_STRING_START;

    return TOKEN_NONE;
}


enum Token_Type check_directives(char *str){

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


enum Token_Type check_opcode(char *str){

    if(strcasecmp(str, "add") == 0)
        return TOKEN_OP_ADD;
    if(strcasecmp(str, "sub") == 0)
        return TOKEN_OP_SUB;
    if(strcasecmp(str, "cmp") == 0)
        return TOKEN_OP_CMP;
    if(strcasecmp(str, "lrs") == 0)
        return TOKEN_OP_LRS;
    if(strcasecmp(str, "or") == 0)
        return TOKEN_OP_OR;
    if(strcasecmp(str, "xor") == 0)
        return TOKEN_OP_XOR;
    if(strcasecmp(str, "nand") == 0)
        return TOKEN_OP_NAND;


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

    result = (check_register(str, str_len));
    if(result)
        return result;

    result = check_special_type(str, str_len);
    if(result)
        return result;

    result = check_directives(str);
    if(result)
        return result;

    result = check_opcode(str);
    if(result)
        return result;

    result = check_comparison_operators(str);
    if(result)
        return result;



    return TOKEN_NONE;
}


int lex_token_line(Token_Line *token_line, ErrorData *error){

    Token *current_token = NULL;
    Token *previous_token = NULL;

    bool string_opened = 0;
    bool macro_opened = 0;
    uint16_t macro_args = 0;

    for(uint8_t i = 0; i < token_line->amount_tokens; i++){

        current_token = &token_line->tk[i];
        current_token->type = lex_token(current_token);



        if(string_opened && current_token->type == TOKEN_STRING_START){
            string_opened = 0;
            current_token->type = TOKEN_STRING_END;
        }

        if(!string_opened && current_token->type == TOKEN_STRING_START)
            string_opened = 1;

        
            


        if(!previous_token || i == 0){
            previous_token = current_token;
            continue;
        }

        switch(current_token->type){

            case(TOKEN_MACRO_START):

                macro_opened = 1;

                break;

            case(TOKEN_LABEL_COLON):

                if(!previous_token->type)
                    previous_token->type = TOKEN_LABEL;

                break;

            case(TOKEN_NONE):

                if(previous_token->type == TOKEN_STRING_START)
                    current_token->type = TOKEN_STRING;

                if(previous_token->type == TOKEN_MACRO_START)
                    previous_token->type = TOKEN_MACRO_MUL;


                if(previous_token->type == TOKEN_MACRO_INLINE)
                    current_token->type = TOKEN_MACRO_SINGLE;
                
                if(macro_opened && current_token->type == TOKEN_NONE){
                    current_token->type = TOKEN_MACRO_ARGS;
                    macro_args++;
                }

                break;

            default:

                break;
        }

        previous_token = current_token;
    }
    


    return 0;
}





int lexical_analysis(Appstate *state){

    ErrorData error;
    error.code = 0;
    error.string = NULL;

    Token_Line *current = state->tk_manager.tk_files[0]->head;


    while(current){

        lex_token_line(current, &error);

        for(int i = 0; i < current->amount_tokens; i++){
            printf("%s - %s\n", current->tk[i].text, token_type_to_string(current->tk[i].type));
        }

        current = current->next;
        printf("\n");
    }


    
    return 0;
}
