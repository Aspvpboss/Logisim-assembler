#include "macro_functions.h"
#include "MemTrack.h"


int is_macro_argument(char *str, Mul_Macro_Data *data){

    for(int i = 0; i < data->amount_args; i++){
        if(strcmp(str, data->args[i]) == 0)
            return 1;
    }

    return 0;
}




//make this function returns 1 if duplicate args
int lex_mul_macros(Token_Line *symbol_line, Symbol *current_symbol){

    Mul_Macro_Data *data = (Mul_Macro_Data*)current_symbol->data;
    data->args = NULL;
    data->amount_args = 0;

    if(symbol_line->amount_tokens < 2)
        return 0;


    uint8_t duplicate_args = 0;

    for(int i = 2; i < symbol_line->amount_tokens; i++){

        Token *current_token = &symbol_line->tk[i];

        if(current_token->type != TOKEN_NONE)
            continue;

        //dup arg
        if(is_macro_argument(current_token->text, data)){
            duplicate_args = 1;
            continue;
        }
            


        current_token->type = TOKEN_MACRO_ARGS;

        data->amount_args++;
        data->args = t_realloc(data->args, sizeof(char*) * data->amount_args);
        data->args[data->amount_args - 1] = t_strdup(current_token->text);

    }    



    Token_Line *current_line = symbol_line;
    while(current_line && current_line->tk[0].type != TOKEN_MACRO_END){

        Token *tokens = current_line->tk;

        for(int i = 0; i < current_line->amount_tokens; i++){

            if(!is_macro_argument(tokens[i].text, data))
                continue;

            tokens[i].type = TOKEN_MACRO_ARGS;

        }

        current_line = current_line->next;
    }

    return duplicate_args;
}




int lex_single_macros(Token_Line *symbol_line, Symbol *current_symbol){

    Single_Macro_Data* data = (Single_Macro_Data*) current_symbol->data;
    data->macro = NULL;

    if(symbol_line->amount_tokens != 3)
        return 1;

    symbol_line->tk[2].type = TOKEN_MACRO_ARGS;
    data->macro = t_strdup(symbol_line->tk[2].text);

    return 0;
}




int lex_all_macros(Symbol_Table *symbols, ErrorData *result){


    for(int i = 0; i < symbols->amount_symbols; i++){

        Symbol *current_symbol = &symbols->symbols[i];

        if(current_symbol->type == SYMBOL_NONE || current_symbol->type == SYMBOL_LABEL)
            continue;

        Token_Line *symbol_line = current_symbol->at_line;

        if(current_symbol->type == SYMBOL_MACRO_SINGLE){

            if(lex_single_macros(symbol_line, current_symbol)){
                Set_ErrorData(result, 1, current_symbol->at_line->original_line, NULL, current_symbol->at_line->file);
                return 1;
            }

        } else{

            if(lex_mul_macros(symbol_line, current_symbol)){
                Set_ErrorData(result, 2, current_symbol->at_line->original_line, NULL, current_symbol->at_line->file);
                return 1;
            }

        }
            
    }

    return 0;
}
