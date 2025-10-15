#include "quit.h"


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

}


void free_tokenized_line(Token_Line *tl){

    for(int i = 0; i < tl->amount_tokens; i++){
        t_free(tl->tk[i].text);
    }

    
    t_free(tl->tk);
    t_free(tl->path);

}

void free_tokenized_file(Token_File *tf){

    Token_Line *current = tf->head;
    Token_Line *next = NULL;

    while(current){
        
        next = current->next;
        free_tokenized_line(current);
        t_free(current->path);
        t_free(current);
        current = next;

    }

    tf->head = NULL;
    tf->tail = NULL;

    t_free(tf->path);
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


void quit(Appstate *state){

    free_file_manager(&state->manager);

    free_tok_file_manager(&state->tk_manager);

    if(check_memory_leak())
        print_tracking_info();

}