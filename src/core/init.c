#include "init_functions.h"





int parse_command_args(Appstate *state, int argc, char *argv[], ErrorData *result){

    File_Manager *manager = &state->manager;
    Assembler_Configs *configs = &state->configs;
    manager->amount_inputs = 0;
    manager->output.path = NULL;

    configs->debug_info = NULL;
    configs->amount_debug = 0;
    configs->output_type = NO_OUTPUT;

    int function_ret = 0;

    if(argc <= 1){
        Set_ErrorData(result, 4, 0, NULL, NULL);
        return 1;
    }


    for(int i = 1; i < argc; i++){

        function_ret = parse_output_file(manager, argv, argc, &i, result);
        if(function_ret == 1)
            continue;
        if(function_ret == -1)
            return 1;
        


        function_ret = parse_output_types(configs, argv, i, result);
        if(function_ret == 1)
            continue;
        if(function_ret == -1)
            return 1;


        function_ret = parse_input_files(manager, argv, i);
        if(function_ret == 1)
            continue;



        Set_ErrorData(result, 1, 0, argv[i], NULL);
        return 1;
    }

 

    if(!manager->amount_inputs){
        Set_ErrorData(result, 7, 0, NULL, NULL);
        return 1;
    }

    if(manager->output.path == NULL){
        Set_ErrorData(result, 3, 0, NULL, NULL);
        return 1;
    }

    if(configs->output_type == NO_OUTPUT){
        Set_ErrorData(result, 6, 0, NULL, NULL);
        return 1;
    }

    return 0;
}




uint16_t get_lines_file(FILE *file){

    char file_line[500];
    uint16_t num_lines = 0;
    while(fgets(file_line, sizeof(file_line), file)){
        num_lines++;    
    }

    rewind(file);

    return num_lines;
}

int open_files(File_Manager *manager, ErrorData *result){

    File_Info *output = &manager->output;
    File_Info *inputs = manager->inputs;
    int amount_inputs = manager->amount_inputs;

    output->file = NULL; 
    output->file = fopen(output->path, "w"); 
    if(output->file == NULL){
        Set_ErrorData(result, 1, 0, NULL, NULL);
        return 1;
    }
    output->num_lines = 0;


    for(int i = 0; i < amount_inputs; i++){
        inputs[i].file = NULL;
        inputs[i].file = fopen(inputs[i].path, "r");
        if(inputs[i].file == NULL){
            Set_ErrorData(result, 2, 0, inputs[i].path, NULL);
            return 1;            
        }

        inputs[i].num_lines = get_lines_file(inputs[i].file);
    }

    return 0;
}



int read_files(File_Manager *manager){

    char file_line[255];

    for(int i = 0; i < manager->amount_inputs; i++){

        char file_name[255];
        manager->inputs[i].num_lines += 2;
        manager->inputs[i].raw_text = t_malloc(sizeof(char*) * (manager->inputs[i].num_lines));


        snprintf(file_name, sizeof(file_name), ".startfile \"%s\"", manager->inputs[i].path);
        manager->inputs[i].raw_text[0] = t_strdup(file_name);


        for(int x = 1; x < manager->inputs[i].num_lines - 1; x++){

            fgets(file_line, sizeof(file_line), manager->inputs[i].file);
            file_line[strcspn(file_line, "\n")] = '\0';
            manager->inputs[i].raw_text[x] = t_strdup(file_line);

        }

        snprintf(file_name, sizeof(file_name), ".endfile \"%s\"", manager->inputs[i].path);
        manager->inputs[i].raw_text[manager->inputs[i].num_lines - 1] = t_strdup(file_name);
    }

    return 0;
}


int initialize(Appstate *state, int argc, char **argv){

    ErrorData result;
    result.string = NULL;

    state->manager.inputs = NULL;
    state->manager.output.raw_text = NULL;


    if(parse_command_args(state, argc, argv, &result)){
        LogError(ASSEMBLE_ARGS_ERROR, &result);
        return 1;
    }
    

    if(open_files(&state->manager, &result)){
        LogError(FILE_ERROR, &result);
        return 1;
    }
    

    read_files(&state->manager);



    return 0;
}

