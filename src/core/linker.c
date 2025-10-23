#include "appstate.h"
#include "tokenize_data.h"

#include "print_functions.h"
#include "linker_functions.h"

#include "quit.h"
#include "error.h"




int check_proper_include(Token_Line *current){

    if(current->amount_tokens != 4)
        return 0;

    if(current->tk[0].type != TOKEN_INCLUDE_DIR)
        return 0;
    if(current->tk[1].type != TOKEN_STRING_START)
        return 0;
    if(current->tk[2].type != TOKEN_STRING)
        return 0;
    if(current->tk[3].type != TOKEN_STRING_END)
        return 0;

    return 1;
}


int include_new_file(Token_Line *current, Token_File_Manager *token_manager, ErrorData *result){

    Token_File *include_file = find_token_file_name(current->tk[2].text, token_manager);

    if(!include_file){
        Set_ErrorData(result, 1, current->original_line, current->tk[2].text, current->file);
        return 1;
    }

    if(include_file->included){
        Set_ErrorData(result, 2, current->original_line, current->tk[2].text, current->file);
        return 1;
    }

    Token_Line *old_next = current->next;
    current->next = include_file->head;
    include_file->tail->next = old_next;
    include_file->included = 1;

    return 0;
}



int resolve_includes_extern(Token_Line *start, Symbol_Table_Manager *sym_manager, Token_File_Manager *token_manager, ErrorData *result){

    Token_Line *current = start;
    
    while(current){

        if(check_proper_include(current)){

            if(include_new_file(current, token_manager, result))
                return 1;

            print_dump_file(token_manager);
        }
        


        current = current->next;
    }


    return 0;
}





int linker(Appstate *state){

    ErrorData result = {0};

    Token_Line *start = state->tk_manager.tk_files[0]->head;

    if(resolve_includes_extern(start, &state->symbol_manager, &state->tk_manager, &result)){
        LogError(LINKER_ERROR, &result);
        return 1;
    }


    return 0;
}