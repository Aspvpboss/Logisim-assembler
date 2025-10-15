#include "appstate.h"
#include "symbol_table.h"
#include "tokenize_data.h"
#include "error.h"
#include "print_functions.h"
#include "lexical_functions.h"

#include <stdbool.h>
#include <string.h>
#include <stdlib.h>



void append_symbols(Token *previous, Token *current, Symbol_Table *symbols){

    Symbol_Type type = SYMBOL_NONE;

    if(current->type == TOKEN_LABEL_COLON && previous->type == TOKEN_LABEL){

        type = SYMBOL_LABEL;

    } else if(current->type == TOKEN_MACRO_MUL && previous->type == TOKEN_MACRO_START){

        type = SYMBOL_MACRO_MUL;

    } else if(current->type == TOKEN_MACRO_SINGLE && previous->type == TOKEN_MACRO_INLINE){

        type = SYMBOL_MACRO_SINGLE;

    }

    if(type == SYMBOL_NONE)
        return;

    symbols->amount_symbols++;

    // symbols->symbols = t_realloc(symbols->symbols, sizeof(Symbol) * symbols->amount_symbols);
    // symbols->symbols[symbols->amount_symbols - 1].type = type;
    // symbols->symbols[symbols->amount_symbols - 1].text = t_strdup()
    // symbols->symbols[symbols->amount_symbols - 1].

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


int lex_token_line(Token_Line *token_line, Symbol_Table *symbols){

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



        previous_token = current_token;
    }
    
    return 0;
}

int lex_file(Token_File *file, Symbol_Table *symbols){

    Token_Line *current = file->head;

    while(current){

        lex_token_line(current, symbols);
        current = current->next;
        printf("\n");

    }    

    return 0;
}


void init_symbol_manager(Symbol_Table_Manager *symbols, Token_File_Manager *manager){

    symbols->tables = t_malloc(sizeof(Symbol_Table) * manager->amount_files);
    symbols->amount_tables = manager->amount_files;

    for(int i = 0; i < symbols->amount_tables; i++){

        symbols->tables[i].file = t_strdup(manager->tk_files[i]->path);
        symbols->tables[i].symbols = NULL;
        symbols->tables[i].amount_symbols = 0;

    }

}


int lexical_analysis(Appstate *state){

    Token_File_Manager *manager = &state->tk_manager;
    Symbol_Table_Manager *symbols = &state->symbol_manager;

    init_symbol_manager(symbols, manager);



    for(int i = 0; i < state->tk_manager.amount_files; i++){
        lex_file(manager->tk_files[i], &symbols->tables[i]);
    }    

    
    print_file_lex(manager);


    return 0;
}
