#include "init.h"
#include "quit.h"

int main(int argc, char **argv){

    Appstate state;

    if(initialize(&state, argc, argv)){
        return 1;
    }

    File_Manager *manager = &state.manager;

    for(int i = 0; i < manager->amount_inputs; i++){

        for(int x = 0; x < manager->inputs[i].num_lines; x++){

            printf("%s\n", manager->inputs[i].raw_text[x]);

        }
    }
    

    quit(&state);

    return 0;
}

