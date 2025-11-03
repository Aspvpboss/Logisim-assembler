#include "quit.h"
#include "print_functions.h"
#include "assert.h"



void free_file_manager(File_Manager *manager){

    for(int i = 0; i < manager->amount_inputs; i++){

        for(int x = 0; x < manager->inputs[i].num_lines; x++)
            t_free(manager->inputs[i].raw_text[x]);

        t_free(manager->inputs[i].raw_text);
        t_free(manager->inputs[i].path);
        if(manager->inputs[i].file)
            fclose(manager->inputs[i].file);
    }

    t_free(manager->inputs);
    t_free(manager->output.path);
    t_free(manager->output.raw_text);
    if(manager->output.file)
        fclose(manager->output.file);
    manager->output.file = NULL;
    manager->amount_inputs = 0;

}


void free_tokenized_line(Token_Line *tl){

    for(int i = 0; i < tl->amount_tokens; i++){
        t_free(tl->tk[i].text);
    }

    t_free(tl->tk);
}

void free_tokenized_file(Token_File *tf){


    t_free(tf->file);

    if(tf->is_included)
        return;


    Token_Line *current = tf->head;
    Token_Line *next = NULL;

    while(current){
        
        next = current->next;
        free_tokenized_line(current);
        t_free(current);
        current = next;

    }

    tf->head = NULL;
    tf->tail = NULL;
    
}

void free_tok_file_manager(Token_File_Manager *manager){

    if(manager->amount_files == 0){
        return;
    }

    for(int i = 0; i < manager->amount_files; i++){
        free_tokenized_file(manager->tk_files[i]);
        t_free(manager->tk_files[i]);
    }
    
    t_free(manager->tk_files);
}


void free_symbol(Symbol *sym){

    if(sym->is_imported)
        return;

    t_free(sym->text);

    switch(sym->type){

        case SYMBOL_LABEL:
            break;

        case SYMBOL_MACRO_MUL:{

            Mul_Macro_Data *sym_data = (Mul_Macro_Data*)sym->data;
            for(int i = 0; i < sym_data->amount_args; i++){
                t_free(sym_data->args[i]);
            }
            t_free(sym_data->args);

            break;
        }

        
        case SYMBOL_MACRO_SINGLE: {

            Single_Macro_Data *sym_data = (Single_Macro_Data*)sym->data;

            t_free(sym_data->macro);

            break;
        }


        default:

            break;

    }

    t_free(sym->data);

}


void free_symbol_table(Symbol_Table *table){

    t_free(table->file);

    for(int i = 0; i < table->amount_symbols; i++){

        free_symbol(&table->symbols[i]);

    }

    t_free(table->symbols);

}

void free_symbol_table_manager(Symbol_Table_Manager *manager){

    for(int i = 0; i < manager->amount_tables; i++){

        free_symbol_table(&manager->tables[i]);

    }

    t_free(manager->tables);

}


void quit(void *appstate){

    Appstate *state = (Appstate*)appstate; 

    free_file_manager(&state->manager);

    free_tok_file_manager(&state->tk_manager);

    free_symbol_table_manager(&state->symbol_manager);

    if(check_memory_leak())
        print_tracking_info();


    free_tracking_info();

    printf("No crash!\n\n");

}
