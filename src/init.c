#include "init.h"
#include "error.h"



int validate_paths(const char *file_path, const char *file_type){

    size_t len_path = strlen(file_path);
    size_t len_type = strlen(file_type);

    if(len_path < len_type){
        return 0;
    }

    if(strcmp(file_path + len_path - len_type, file_type) != 0){
        return 0;
    }


    for(int i = 0; file_path[i] != '\0'; i++){

        if(!isgraph((unsigned char)file_path[i])){
            return 0;
        }

    }

    return 1;
}



int parse_command_args(Appstate *state, int argc, char *argv[], int *result){

    File_Manager *manager = &state->manager;
    Assembler_Configs *configs = &state->configs;

    int amount_inputs = 0;
    manager->output.path = NULL;

    if(argc <= 1){
        *result = 4;
        return 1;
    }

    for(int i = 1; i < argc; i++){

        if(strcmp(argv[i], "-o") == 0 && i + 1 < argc){

            if(!validate_paths(argv[i + 1], ".txt")){
                *result = 2;
                return 1;
            }

            manager->output.path = strdup(argv[i + 1]);

            i++;

            continue;
        }

        if(strcmp(argv[i], "-B") == 0){
            if(configs->output_type != NO_OUTPUT){
                *result = 5;
                return 1;
            }
            configs->output_type = BINARY_OUTPUT;
            continue;
        }

        if(strcmp(argv[i], "-H") == 0){
            if(configs->output_type != NO_OUTPUT){
                *result = 5;
                return 1;
            }
            configs->output_type = HEX_OUTPUT;
            continue;
        }

        if(validate_paths(argv[i], ".asm")){

            amount_inputs++;

            manager->inputs = realloc(manager->inputs, sizeof(File_Info) * amount_inputs);

            manager->inputs[amount_inputs - 1].path = strdup(argv[i]);
            
            continue;
        }

        *result = 1;
        return 1;

    }

    manager->amount_inputs = amount_inputs;

    if(manager->output.path == NULL){
        *result = 3;
        return 1;
    }

    if(configs->output_type == NO_OUTPUT){
        *result = 6;
        return 1;
    }

    return 0;
}

int get_lines_file(FILE *file){
    
}

int open_files(File_Manager *manager, int *result){

    File_Info *output = &manager->output;
    File_Info *inputs = manager->inputs;
    int amount_inputs = manager->amount_inputs;

    return 0;
}


int initialize(Appstate *state, int argc, char **argv){

    int result = 0;

    state->manager.inputs = NULL;
    state->configs.output_type = NO_OUTPUT;

    if(parse_command_args(state, argc, argv, &result)){
        LogError(ASSEMBLE_ARGS_ERROR, result);
        return 1;
    }

    if(open_files(&state->manager, &result)){
        LogError(FILE_ERROR, result);
        return 1;
    }
    
    return 0;
}

