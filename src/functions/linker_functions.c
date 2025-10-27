#include "linker_functions.h"
#include "symbol_functions.h"
#include "error.h"
#include <MemTrack.h>

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



int copy_exported_symbols(Symbol_Table *dest, Symbol_Table *src, ErrorData *result){

    Symbol *src_symbol = src->symbols;
    Symbol *dest_symbol = dest->symbols;

    for(int i = 0; i < src->amount_symbols; i++){
        
        if(!src_symbol[i].is_exported)
            continue;

        if(find_symbol_by_name(src_symbol[i].text, dest)){
            Set_ErrorData(result, 0, src_symbol[i].at_line->original_line, dest->file, src_symbol[i].at_line->file);
            return 1;
        }

        dest->amount_symbols++;
        dest_symbol = t_realloc(dest_symbol, sizeof(Symbol) * dest->amount_symbols);
        Symbol *new_symbol = &dest_symbol[dest->amount_symbols - 1];
        *new_symbol = src_symbol[i];
        new_symbol->is_imported = 1;
        new_symbol->is_exported = 0;

    }

    dest->symbols = dest_symbol;
    
    return 0;
}



Token_File *find_token_file_name(const char *str, Token_File_Manager *token_manager){

    for(int i = 0; i < token_manager->amount_files; i++){

        if(strcmp(token_manager->tk_files[i]->file, str) == 0){
            return token_manager->tk_files[i];
        }

    }

    return NULL;
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

    while(current && !check_file_end(current)){

        find_glob_symbol(current, table);
        current = current->next;

    }

}
