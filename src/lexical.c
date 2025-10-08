#include "appstate.h"
#include "symbol_table.h"
#include "tokenize_data.h"
#include "error.h"

#include <stdbool.h>
#include <string.h>
#include <stdlib.h>


void print_TokenType(enum Token_Type type){
    switch(type){

        case(TOKEN_NONE):
            printf("NONE\n");
            break;
        case(TOKEN_IMMEDIATE):
            printf("immediate\n");
            break;
        case(TOKEN_REGISTER):
            printf("REGISTER\n");
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

    if(addr_value >= 0 && addr_value < 256){

        return TOKEN_IMMEDIATE;

    }
    
    return TOKEN_NONE;
}


int check_register(char *str, size_t str_len){

    if(str_len != 2 || str[0] != 'r')
        return 0;

    if(str[0] == 'r' && str_len == 2){
        int reg_addr = str[1] - '0';
        if(reg_addr <= 7 && reg_addr >= 0){
            return 1;
        }
    }

    return 0;
}


enum Token_Type check_special_type(char *str, size_t str_len){

    if(strcmp(str, ".macro"))
        return TOKEN_MACRO_START;
    if(strcmp(str, ".macroend"))
        return TOKEN_MACRO_END;
    if(strcmp(str, ".inline_macro"))
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

    if(check_register(str, str_len))
        return TOKEN_REGISTER;

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

        if(!string_opened && current_token->type == TOKEN_STRING_START)
            string_opened = 1;

        if(string_opened && current_token->type == TOKEN_STRING_END)
            string_opened = 0;


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

            case(TOKEN_STRING_END):

                if(!previous_token->type)
                    previous_token->type = TOKEN_STRING;

                break;

            case(TOKEN_NONE):

                if(previous_token->type == TOKEN_MACRO_START)
                    previous_token->type = TOKEN_MACRO_MUL;


                if(previous_token->type == TOKEN_MACRO_INLINE)
                    current_token->type = TOKEN_MACRO_SINGLE;

                break;

            default:

                break;
        }


        if(string_opened){
            error->string = t_strdup(token_line->path);
            error->data = token_line->original_line;
            return 1;
        }


        previous_token = current_token;
    }

    return 0;
}





int lexical_analysis(Appstate *state){

    ErrorData error;
    error.code = 0;
    error.string = NULL;

    Token_Line *token_line = state->tk_manager.tk_files[0]->tail;

    if(lex_token_line(token_line, &error)){
        LogError(LEXICAL_ERROR, &error);
        return 1;
    }




    return 0;
}
