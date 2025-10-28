#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#define SUCCESS 1
#define FAILURE 0


void exit_testing(const char *test_name){

    printf("Failure - %s\n", test_name);

    abort();

}


void test_valuation(const char *test_name, const char *cmd, bool wanted_result){

    if(system(cmd)){

        if(!wanted_result)
            exit_testing(test_name);

        printf("Success - %s\n", test_name);
        return;

    }
        
    if(wanted_result)
        exit_testing(test_name);
    
    printf("Success - %s\n", test_name);
    return;
}

int main(){

    

    

    return 0;
}