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

    printf("\n\ntokenize usage - %lld\n", check_memory_usage());

    if(lexical_analysis(&state)){
        quit(&state);
        return 1;        
    }

    printf("\n\nlexical analysis usage - %lld\n", check_memory_usage());
    
    if(linker(&state)){
        quit(&state);
        return 1;            
    }

    printf("\n\nlinker usage - %lld\n", check_memory_usage());

    quit(&state);

    

    return 0;
}
