#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <direct.h>

#define SUCCESS 0
#define FAILURE 1

// Helper macro to run commands in Git Bash
#define BASH_CMD(cmd) "bash -c \"" cmd "\""

void exit_testing(const char *test_name){

    printf("Failure - %s\n", test_name);

    abort();

}


void test(const char *cmd, bool wanted_result, const char *test_name){

    printf("\n[-]-----Running: %s-----[-]\n", test_name);

    int result = system(cmd);

    if(result){

        if(!wanted_result)
            exit_testing(test_name);

        printf("--------------------------\n\nSuccess - %s\n\n--------------------------\n", test_name);
        return;

    }
        
    if(wanted_result)
        exit_testing(test_name);
    
    printf("--------------------------\nSuccess - %s\n\n--------------------------\n", test_name);
    return;
}

int main(){


    printf("Running validation tests...\n\n");

    // -------No command args-------
    test(BASH_CMD("./rca.exe"), FAILURE, "No command args");

    // -------No output file-------
    test(BASH_CMD("./rca.exe empty.asm"), FAILURE, "No output file");

    // -------Invalid command arg-------
    test(BASH_CMD("./rca.exe empty.asm -o"), FAILURE, "Invalid command arg");

    // -------No output type flag-------
    test(BASH_CMD("./rca.exe empty.asm -o out.txt"), FAILURE, "No output type flag");

    // -------Duplicate output type flags-------
    test(BASH_CMD("./rca.exe empty.asm -o out.txt -B -B"), FAILURE, "Duplicate output type flags");

    // -------Empty file-------
    test(BASH_CMD("./rca.exe empty.asm -o out.txt -B"), FAILURE, "Empty file");

    // -------Failed to find input file-------
    test(BASH_CMD("./rca.exe nothing.asm -o out.txt -B"), FAILURE, "Failed to find input file");

    // -------Invalid output file type-------
    test(BASH_CMD("./rca.exe empty.asm -o out.asm -B"), FAILURE, "Invalid output file type");

    // -------Inline macro error-------
    test(BASH_CMD("./rca.exe inline_macro.asm -o out.txt -B"), FAILURE, "Inline macro error");

    // -------Multi macro error-------
    test(BASH_CMD("./rca.exe multi_macro.asm -o out.txt -B"), FAILURE, "Multi macro error");

    // -------Cannot find .include file-------
    test(BASH_CMD("./rca.exe no_find_include.asm -o out.txt -B"), FAILURE, "Cannot find .include file");

    // -------Double .include file-------
    test(BASH_CMD("./rca.exe multi_include.asm a.asm -o out.txt -B"), FAILURE, "Double .include file");


    printf("\n\nValidation Test succesful!\n");

    return 0;
}