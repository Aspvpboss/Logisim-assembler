#include "appstate.h"
#include "tokenize_data.h"

#include "print_functions.h"
#include "linker_functions.h"
#include "symbol_functions.h"

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

int check_file_end(Token_Line *start){

    if(start->amount_tokens != 4)
        return 0;
    Token *tokens = start->tk;

    if(tokens[0].type != TOKEN_END_FILE_DIR)
        return 0;

    if(strcmp(start->file, tokens[2].text) != 0)
        return 0;

    return 1;
}

void update_glob_symbols(Token_Line *start, Symbol_Table *table){

    if(!start || !table)
        return;

    Token_Line *current = start;

    while(current && !check_file_end(start)){

        find_glob_symbol(current, table);
        current = current->next;

    }

}



int resolve_includes_extern(Token_Line *start, Symbol_Table_Manager *sym_manager, Token_File_Manager *token_manager, ErrorData *result){

    Token_Line *current = start;
    
    while(current){

        if(check_proper_include(current)){

            if(include_new_file(current, token_manager, result))
                return 1;

        }

        if(current->next && current->tk[0].type == TOKEN_END_FILE_DIR){

            copy_exported_symbols((Symbol_Table*)current->next->symbol_table, (Symbol_Table*)current->symbol_table);
            update_glob_symbols(current->next, (Symbol_Table*)current->next->symbol_table);

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

    print_dump_file(&state->tk_manager);
    // print_file_lex(&state->tk_manager);
    print_symbols(&state->symbol_manager);

    return 0;
}