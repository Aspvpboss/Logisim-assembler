#include "appstate.h"
#include "tokenize_data.h"

#include "print_functions.h"

#include "quit.h"
#include "error.h"



Token_Line* copy_Token_Line(const Token_Line *line){

    if(!line)
        return NULL;

    Token_Line *new_line = t_malloc(sizeof(Token_Line));

    *new_line = *line;
    new_line->next = NULL;
    new_line->file = t_strdup(new_line->file);
    
    new_line->tk = t_malloc(sizeof(Token) * new_line->amount_tokens);

    for(int i = 0; i < new_line->amount_tokens; i++){

        new_line->tk[i] = line->tk[i];
        new_line->tk[i].text = t_strdup(line->tk[i].text);

    }



    return new_line;
}



void copy_exported_symbols(Symbol_Table *dest, Symbol_Table *src){

    Symbol *src_symbol = src->symbols;
    Symbol *dest_symbol = dest->symbols;

    for(int i = 0; i < src->amount_symbols; i++){
        
        if(!src_symbol[i].is_exported)
            continue;

        dest->amount_symbols++;
        dest_symbol = t_realloc(dest_symbol, sizeof(Symbol) * dest->amount_symbols);
        Symbol *new_symbol = &dest_symbol[dest->amount_symbols - 1];
        *new_symbol = src_symbol[i];
        new_symbol->is_imported = 1;
        new_symbol->is_exported = 0;

    }

    dest->symbols = dest_symbol;
}





int solve_includes_extern(Token_Line *head, ErrorData *result){

    Token_Line *current = head;

    while(current){



    }


    return 0;
}



int linker(Appstate *state){

    Symbol_Table *tables = state->symbol_manager.tables;

    print_symbols(&state->symbol_manager);
    
    copy_exported_symbols(&tables[0], &tables[1]);
    
    print_symbols(&state->symbol_manager);



    return 0;
}