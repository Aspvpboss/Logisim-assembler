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



int parse_command_args(Appstate *state, int argc, char *argv[], ErrorData *error){

    File_Manager *manager = &state->manager;
    Assembler_Configs *configs = &state->configs;

    int amount_inputs = 0;
    manager->output.path = NULL;

    if(argc <= 1){
        error->code = 4;
        return 1;
    }

    for(int i = 1; i < argc; i++){

        if(strcmp(argv[i], "-o") == 0 && i + 1 < argc){

            if(!validate_paths(argv[i + 1], ".txt")){
                error->code = 2;
                return 1;
            }

            manager->output.path = strdup(argv[i + 1]);

            i++;

            continue;
        }

        if(strcmp(argv[i], "-B") == 0){
            if(configs->output_type != NO_OUTPUT){
                error->code = 5;
                error->string = strdup(argv[i]);
                return 1;
            }
            configs->output_type = BINARY_OUTPUT;
            continue;
        }

        if(strcmp(argv[i], "-H") == 0){
            if(configs->output_type != NO_OUTPUT){
                error->code = 5;
                error->string = strdup(argv[i]);
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

        error->code = 1;
        error->string = strdup(argv[i]);
        return 1;

    }

    manager->amount_inputs = amount_inputs;

    if(manager->output.path == NULL){
        error->code = 3;
        return 1;
    }

    if(configs->output_type == NO_OUTPUT){
        error->code = 6;
        return 1;
    }

    return 0;
}




int get_lines_file(FILE *file){

    char file_line[500];
    int num_lines = 0;
    while(fgets(file_line, sizeof(file_line), file)){
        num_lines++;    
    }

    rewind(file);

    return num_lines;
}

int open_files(File_Manager *manager, ErrorData *error){

    File_Info *output = &manager->output;
    File_Info *inputs = manager->inputs;
    int amount_inputs = manager->amount_inputs;

    output->file = fopen(output->path, "w");
    if(output->file == NULL){
        error->code = 1;
        return 1;
    }
    output->num_lines = 0;


    for(int i = 0; i < amount_inputs; i++){
        inputs[i].file = fopen(inputs[i].path, "r");
        if(inputs[i].file == NULL){
            error->code = 2;
            error->string = strdup(inputs[i].path);
            return 1;            
        }

        inputs[i].num_lines = get_lines_file(inputs[i].file);
    }

    return 0;
}



int read_files(File_Manager *manager, ErrorData *result){

    char file_line[255];

    for(int i = 0; i < manager->amount_inputs; i++){

        char file_name[255];
        manager->inputs[i].num_lines += 2;
        manager->inputs[i].raw_text = malloc(sizeof(char*) * (manager->inputs[i].num_lines));


        snprintf(file_name, sizeof(file_name), ".startfile %s", manager->inputs[i].path);
        manager->inputs[i].raw_text[0] = strdup(file_name);


        for(int x = 1; x < manager->inputs[i].num_lines; x++){

            fgets(file_line, sizeof(file_line), manager->inputs[i].file);
            file_line[strcspn(file_line, "\n")] = '\0';
            manager->inputs[i].raw_text[x] = strdup(file_line);

        }

        snprintf(file_name, sizeof(file_name), ".endfile %s", manager->inputs[i].path);
        manager->inputs[i].raw_text[manager->inputs[i].num_lines - 1] = strdup(file_name);
    }

    return 0;
}


int initialize(Appstate *state, int argc, char **argv){

    ErrorData result;
    result.string = NULL;

    state->manager.inputs = NULL;
    state->manager.output.raw_text = NULL;
    state->configs.output_type = NO_OUTPUT;


    if(parse_command_args(state, argc, argv, &result)){
        LogError(ASSEMBLE_ARGS_ERROR, &result);
        return 1;
    }

    if(open_files(&state->manager, &result)){
        LogError(FILE_ERROR, &result);
        return 1;
    }

    if(read_files(&state->manager, &result)){
        LogError(FILE_ERROR, &result);
        return 1;        
    }


    return 0;
}

