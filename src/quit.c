#include "quit.h"


void free_manager(File_Manager *manager){

    for (int i = 0; i < manager->amount_inputs; i++) {
        for (int x = 0; x < manager->inputs[i].num_lines; x++) {
            free(manager->inputs[i].raw_text[x]);
        }
        free(manager->inputs[i].raw_text);
        free(manager->inputs[i].path);
        fclose(manager->inputs[i].file);
    }
    free(manager->inputs);
    free(manager->output.path);
    fclose(manager->output.file);

    if(manager->output.raw_text)
        free(manager->output.raw_text);

}


void free_tokenized_line(Token_Line *tl){

    for(int i = 0; i < tl->amount_tokens; i++){
        free(tl->tk[i].text);
    }
    free(tl->tk);
    free(tl->file);
}

void free_tokenized_file(Token_File *tf){
    for(int i = 0; i < tf->amount_lines; i++){
        free_tokenized_line(&tf->tk_line[i]);
    }
    free(tf->tk_line);
}



void quit(Appstate *state){

    free_manager(&state->manager);



}