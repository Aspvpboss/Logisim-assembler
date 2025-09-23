#include "quit.h"
#include "alloc.h"



void free_file_manager(File_Manager *manager){

    for(int i = 0; i < manager->amount_inputs; i++){

        for(int x = 0; x < manager->inputs[i].num_lines; x++)
            s_free(manager->inputs[i].raw_text[x]);

        s_free(manager->inputs[i].raw_text);
        s_free(manager->inputs[i].path);
        if(manager->inputs[i].file)
            fclose(manager->inputs[i].file);
    }

    s_free(manager->inputs);
    s_free(manager->output.path);
    s_free(manager->output.raw_text);
    if(manager->output.file)
        fclose(manager->output.file);

}


void free_tokenized_line(Token_Line *tl){

    for(int i = 0; i < tl->amount_tokens; i++){
        s_free(tl->tk[i].text);
    }

    
    s_free(tl->tk);
    s_free(tl->path);

}

void free_tokenized_file(Token_File *tf){

    for(int i = 0; i < tf->amount_lines; i++){
        free_tokenized_line(tf->tk_line[i]);
        s_free(tf->tk_line[i]);
    }
    s_free(tf->tk_line);
    s_free(tf->path);
    
}

void free_tok_file_manager(Token_File_Manager *manager){

    if(manager->amount_files == 0){
        return;
    }

    for(int i = 0; i < manager->amount_files; i++){
        free_tokenized_file(manager->tk_files[i]);
        s_free(manager->tk_files[i]);
    }
    
    s_free(manager->tk_files);
}


void quit(Appstate *state){

    free_file_manager(&state->manager);

    free_tok_file_manager(&state->tk_manager);
    
    size_t allocations = get_allocations();
    if(allocations){

        printf("\n\nMemory Leak - %lld allocations leaked\n", allocations);

    } else{

        printf("\n\nMemory successfully freed\n");

    }

}