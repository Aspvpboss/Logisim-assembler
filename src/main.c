#include "init.h"

int main(int argc, char **argv){

    Appstate state;

    if(initialize(&state, argc, argv)){
        return 1;
    }




    printf("output\n%s\n", state.manager.output.path);

    printf("\ninputs\n");

    for(int i = 0; i < state.manager.amount_inputs; i++){
        printf("%s\n", state.manager.inputs[i].path);
    }

    if(state.configs.output_type == BINARY_OUTPUT){
        printf("\nbinary output\n");
    }
    if(state.configs.output_type == HEX_OUTPUT){
        printf("\nhex output\n");
    }

    return 0;
}

