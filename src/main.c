
#include "init.h"
#include "tokenize.h"
#include "lexical.h"
#include "quit.h"

int main(int argc, char **argv){

    Appstate state = {0};

    if(initialize(&state, argc, argv)){
        quit(&state);
        return 1;
    }

    if(tokenize(&state)){
        quit(&state);
        return 1;
    }

    // if(lexical_analysis(&state)){
    //     quit(&state);
    //     return 1;        
    // }

    quit(&state);

    return 0;
}




// File_Manager *manager = &state.manager;

// for(int i = 0; i < manager->amount_inputs; i++){

//     for(int x = 0; x < manager->inputs[i].num_lines; x++){

//         printf("%s\n", manager->inputs[i].raw_text[x]);

//     }
// }