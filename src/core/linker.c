#include "appstate.h"
#include "tokenize_data.h"

#include "print_functions.h"
#include "linker_functions.h"

#include "quit.h"
#include "error.h"






int include_new_file(Token_Line *current, Token_File_Manager *token_manager, ErrorData *result){

    Token_File *include_file = find_token_file_name(current->file, token_manager);

    if(!include_file){
        //error stuff
        return 1;
    }

    Token_Line *include_current = include_file->head;
    Token_Line *original_next = current->next;

    Token_Line *new_tail = current;

    while(include_current){

        new_tail->next = copy_Token_Line(include_current);

        include_current = include_current->next;
        new_tail = new_tail->next;
    }

    new_tail->next = original_next;


    return 0;
}


int resolve_includes_extern(Token_Line *start, Symbol_Table_Manager *sym_manager, Token_File_Manager *token_manager, ErrorData *result){

    Token_Line *current = start;

    while(current){

        

        current = current->next;
    }


    return 0;
}



int linker(Appstate *state){

    // Symbol_Table *tables = state->symbol_manager.tables;

    // print_symbols(&state->symbol_manager);
    
    // copy_exported_symbols(&tables[0], &tables[1]);
    
    // print_symbols(&state->symbol_manager);



    return 0;
}