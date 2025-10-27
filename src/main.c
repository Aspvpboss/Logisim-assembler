#include "init.h"
#include "tokenize.h"
#include "lexer.h"
#include "linker.h"

#include "quit.h"

/*

    current line count is 2116
    before finishing linking
    bruh

    this is just including src and include files

*/


int main(int argc, char **argv){

    Appstate state = {0};

    if(initialize(&state, argc, argv)){
        quit(&state);
        return 1;
    }

    printf("\n\ninit usage - %lld\n", check_memory_usage());

    if(tokenize(&state)){
        quit(&state);
        return 1;
    }

    free_file_manager(&state.manager);


    if(lexical_analysis(&state)){
        quit(&state);
        return 1;        
    }

    
    if(linker(&state)){
        quit(&state);
        return 1;            
    }

    quit(&state);

    

    return 0;
}
