#include "init_functions.h"




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




int parse_output_file(File_Manager *manager, char **argv, int argc, int *i, ErrorData *result){


    if(strcmp(argv[*i], "-o") == 0 && *i + 1 < argc){

        if(!validate_paths(argv[*i + 1], ".txt")){
            Set_ErrorData(result, 2, 0, argv[*i + 1], NULL);
            return -1;
        }

        manager->output.path = t_strdup(argv[*i + 1]);
        manager->output.file = NULL;
        manager->output.num_lines = 0;
        (*i)++;

        return 1;
    }


    return 0;
}



int parse_output_types(Assembler_Configs *configs, char **argv, int i, ErrorData *result){

    if(strcmp(argv[i], "-B") == 0){

        if(configs->output_type != NO_OUTPUT){
            Set_ErrorData(result, 5, 0, argv[i], NULL);
            return -1;
        }

        configs->output_type = BINARY_OUTPUT;
        return 1;
    }

    if(strcmp(argv[i], "-H") == 0){

        if(configs->output_type != NO_OUTPUT){
            Set_ErrorData(result, 5, 0, argv[i], NULL);
            return -1;
        }

        configs->output_type = HEX_OUTPUT;
        return 1;
    }

    return 0;
}


int parse_input_files(File_Manager *manager, char **argv, int i){

    if(validate_paths(argv[i], ".asm")){

        manager->amount_inputs++;

        manager->inputs = t_realloc(manager->inputs, sizeof(File_Info) * manager->amount_inputs);
        manager->inputs[manager->amount_inputs - 1].path = t_strdup(argv[i]);
        manager->inputs[manager->amount_inputs - 1].file = NULL;
        manager->inputs[manager->amount_inputs - 1].raw_text = NULL;
        manager->inputs[manager->amount_inputs - 1].num_lines = 0;

        
        return 1;
    }

    return 0;
}


int parse_debug_flags(Assembler_Configs *configs, char *_arg){

    //int amount_debug = configs->amount_debug;

    if(strcmp(_arg, "-all_debug") == 0){

    }
    if(strcmp(_arg, "-symbol_info") == 0){

    }
    if(strcmp(_arg, "-premacro_dump") == 0){

    }
    if(strcmp(_arg, "-postmacro_dump") == 0){

    }

    return 0;
}