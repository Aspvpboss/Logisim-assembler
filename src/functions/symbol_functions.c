#include "symbol_functions.h"
#include "macro_data.h"
#include <string.h>
#include <MemTrack.h>


int append_symbols(Token *previous, Token *current, Symbol_Table *symbols, Token_Line *token_line, ErrorData *result){

    Symbol_Type type = SYMBOL_NONE;
    char *text = NULL;

    if(current->type == TOKEN_LABEL_COLON && previous->type == TOKEN_LABEL){

        type = SYMBOL_LABEL;
        text = previous->text;

    } else if(current->type == TOKEN_MACRO_MUL && previous->type == TOKEN_MACRO_START){

        type = SYMBOL_MACRO_MUL;
        text = current->text;

    } else if(current->type == TOKEN_MACRO_SINGLE && previous->type == TOKEN_MACRO_INLINE){

        type = SYMBOL_MACRO_SINGLE;
        text = current->text;

    }

    if(type == SYMBOL_NONE)
        return 0;

    Symbol *existing_symbol = find_symbol_by_name(text, symbols);

    if(existing_symbol){
        Set_ErrorData(
            result, 8, token_line->original_line, text, token_line->file);
        return 1;
    }

    symbols->amount_symbols++;
    symbols->symbols = t_realloc(symbols->symbols, sizeof(Symbol) * symbols->amount_symbols);
    Symbol *symbol = &symbols->symbols[symbols->amount_symbols - 1];

    symbol->type = type;
    symbol->at_line = token_line;
    symbol->is_exported = 0;
    symbol->is_imported = 0;


    if(type == SYMBOL_LABEL){

        symbol->text = t_strdup(text);
        symbol->data = NULL;

    } else if(type == SYMBOL_MACRO_MUL){

        symbol->text = t_strdup(text);
        symbol->data = t_malloc(sizeof(Mul_Macro_Data));

    } else if(type == SYMBOL_MACRO_SINGLE){

        symbol->text = t_strdup(text);
        symbol->data = t_malloc(sizeof(Single_Macro_Data));

    }



    return 0;
}



Symbol* find_symbol_by_name(const char *str, Symbol_Table *table){

    for(int i = 0; i < table->amount_symbols; i++){
        if(strcmp(str, table->symbols[i].text) == 0){
            return &table->symbols[i];
        }
    }

    return NULL;
}




Symbol_Table* find_symbol_name_by_name(const char *str, Symbol_Table_Manager *table){

    for(int i = 0; i < table->amount_tables; i++){
        if(strcmp(str, table->tables[i].file) == 0){
            return &table->tables[i];
        }
    }

    return NULL;
}



void find_glob_symbol(Token_Line *current, Symbol_Table *symbols){

    if(current->amount_tokens != 2)
        return;

    if(current->tk[0].type != TOKEN_GLOBAL_DIR || current->tk[1].type != TOKEN_NONE)
        return;

    Symbol *glob_symbol = NULL;
    glob_symbol = find_symbol_by_name(current->tk[1].text, symbols);

    if(!glob_symbol)
        return;
    
    current->tk[1].type = TOKEN_SYMBOL_EXPORTED;
    glob_symbol->is_exported = 1;
    
    return;
}


void init_symbol_manager(Symbol_Table_Manager *symbols, Token_File_Manager *manager){

    symbols->tables = t_malloc(sizeof(Symbol_Table) * manager->amount_files);
    symbols->amount_tables = manager->amount_files;

    for(int i = 0; i < symbols->amount_tables; i++){

        symbols->tables[i].file = t_strdup(manager->tk_files[i]->file);
        symbols->tables[i].symbols = NULL;
        symbols->tables[i].amount_symbols = 0;

    }

}