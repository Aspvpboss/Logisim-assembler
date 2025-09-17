#include "quit.h"




void quit(Appstate *state){

    File_Manager *manager = &state->manager;


    for (int i = 0; i < manager->amount_inputs; i++) {
        for (int x = 0; x < manager->inputs[i].num_lines; x++) {
            free(manager->inputs[i].raw_text[x]);
        }
        free(manager->inputs[i].raw_text);
        free(manager->inputs[i].path);
    }
    free(manager->inputs);
    free(manager->output.path);

}