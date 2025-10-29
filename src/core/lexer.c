#include "appstate.h"
#include "error.h"

#include "symbol_table.h"
#include "tokenize_data.h"
#include "macro_data.h"

#include "print_functions.h"
#include "lexer_functions.h"
#include "symbol_functions.h"
#include "macro_functions.h"


#include <stdbool.h>
#include <string.h>
#include <stdlib.h>



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

    result = check_register(str, str_len);
    if(result)
        return result;

    result = check_io(str, str_len);
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




int lex_token_line(Token_Line *token_line, Symbol_Table *symbols, ErrorData *result){

    Token *current_token = NULL;
    Token *previous_token = NULL;

    bool string_opened = 0;

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

            case(TOKEN_LABEL_COLON):

                if(!previous_token->type)
                    previous_token->type = TOKEN_LABEL;

                break;

            case(TOKEN_NONE):

                if(previous_token->type == TOKEN_STRING_START){

                    current_token->type = TOKEN_STRING;

                } else if(previous_token->type == TOKEN_MACRO_START){

                    current_token->type = TOKEN_MACRO_MUL;

                } else if(previous_token->type == TOKEN_MACRO_INLINE){

                    current_token->type = TOKEN_MACRO_SINGLE;

                }

                break;

            default:

                break;
        }

        if(append_symbols(previous_token, current_token, symbols, token_line, result))
            return 1;

        previous_token = current_token;
    }
    
    return 0;
}






int find_symbol_references(Token_Line *current, Symbol_Table *symbols){

    Symbol *symbol = NULL;

    for(int i = 0; i < current->amount_tokens; i++){

        if(current->tk[i].type != TOKEN_NONE)
            continue;

        symbol = find_symbol_by_name(current->tk[i].text, symbols);

        if(!symbol)
            continue;

        switch(symbol->type){

            case SYMBOL_LABEL:

                current->tk[i].type = TOKEN_LABEL_REF;

                break;

            case SYMBOL_MACRO_MUL:

                current->tk[i].type = TOKEN_MACRO_MUL_REF;

                break;

            case SYMBOL_MACRO_SINGLE:

                current->tk[i].type = TOKEN_MACRO_SINGLE_REF;

                break;

            default:

                break;
        }
        

    }

    return 0;
}





int lex_file(Token_File *file, Symbol_Table *symbols, ErrorData *result){

    Token_Line *current = file->head;

    while(current){

        current->symbol_table = symbols;
        if(lex_token_line(current, symbols, result))
            return 1;
        current = current->next;

    }    

    current = file->head;

    while(current){

        find_glob_symbol(current, symbols);
        find_symbol_references(current, symbols);
        
        current = current->next;

    }    

    if(lex_all_macros(symbols, result))
        return 1;

    return 0;
}




int lexical_analysis(Appstate *state){

    ErrorData result = {0};
    result.string = NULL;

    Token_File_Manager *manager = &state->tk_manager;
    Symbol_Table_Manager *symbols = &state->symbol_manager;

    init_symbol_manager(symbols, manager);

    for(int i = 0; i < state->tk_manager.amount_files; i++){

        manager->tk_files[i]->symbol_table = &symbols->tables[i];

        if(lex_file(manager->tk_files[i], &symbols->tables[i], &result)){

            if(result.specific_code == 8){

                LogError(LINKER_ERROR, &result);

            } else{

                LogError(MACRO_ERROR, &result);

            }

            
            return 1;
        }

    }    
    
    return 0;
}
