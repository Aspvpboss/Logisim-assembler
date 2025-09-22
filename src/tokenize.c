#include "tokenize.h"
#include "appstate.h"
#include "error.h"

int check_special(const char c){
    
    switch(c){

        case('"'):
            return 1;
        case('['):
            return 1;
        case(']'):
            return 1;
        case('{'):
            return 1;
        case('}'):
            return 1;
        case('#'):
            return 1;

    }

    return 0;
}

 
Token_Line* tokenize_line(const char *raw_line, const char *file_name, int original_line, ErrorData *result){

    Token_Line *tok_line = malloc(sizeof(Token_Line));
    tok_line->amount_tokens = 0;
    tok_line->tk = NULL;
    tok_line->path = strdup(file_name);
    tok_line->original_line = original_line;

    char *line = strdup(raw_line);
    size_t line_len = strlen(raw_line);

    bool in_quotes = 0;
    bool comment = 0;

    for(int i = 0; i <= line_len; i++){

        if(comment){
            line[i] = '\0';
            continue;
        }

        if(line[i]  == ';'){
            line[i] = '\0';
            comment = 1;
            continue;
        }


        if(line[i] == '"'){
            in_quotes = !in_quotes;
            continue;
        }
        if(in_quotes)
            continue;


        if(isspace(line[i]) || line[i] == ','){
            line[i] = '\0';
        }
    }



    bool previous_char = 0;
    int amount_tokens = 0;

    for(int i = 0; i <= line_len; i++){

        if(check_special(line[i])){

            amount_tokens++;
            tok_line->tk = realloc(tok_line->tk, sizeof(Token) * amount_tokens);
            tok_line->tk[amount_tokens - 1].text = malloc(sizeof(char) * 2);
            tok_line->tk[amount_tokens - 1].text[0] = line[i];
            tok_line->tk[amount_tokens - 1].text[1] = '\0';
            line[i] = '\0';
            previous_char = 0;
            continue;

        }

        if(line[i] != '\0' && !previous_char){

            amount_tokens++;
            tok_line->tk = realloc(tok_line->tk, sizeof(Token) * amount_tokens);
            
            int num_char = 0;
            tok_line->tk[amount_tokens - 1].text = NULL;

            for(int x = i; line[x] != '\0'; x++){

                if(!check_special(line[x])){
                    num_char++;
                    continue;            
                }
            }

            tok_line->tk[amount_tokens - 1].text = malloc(sizeof(char) * (num_char + 1));
            strncpy(tok_line->tk[amount_tokens - 1].text, &line[i], num_char);
            tok_line->tk[amount_tokens - 1].text[num_char] = '\0';

            previous_char = 1;
            continue;
        }

        if(line[i] == '\0'){
            previous_char = 0;
        }
    }

    free(line);

    tok_line->amount_tokens = amount_tokens;
    if(amount_tokens == 0){

        free(tok_line);
        return NULL;
    }

    return tok_line;
}


Token_File* tokenize_file(File_Info *file, ErrorData *error){

    Token_File *tok_file = malloc(sizeof(Token_File));
    tok_file->path = strdup(file->path);

    Token_Line *tok_line;
    tok_file->tk_line = NULL;
    int amount_lines = 0;

    for(int i = 0; i < file->num_lines; i++){

        tok_line = tokenize_line(file->raw_text[i], file->path, i + 1, error);

        if(tok_line == NULL){
            continue;
        }

        amount_lines++;
        tok_file->tk_line = realloc(tok_file->tk_line, sizeof(Token_Line*) * amount_lines);
        tok_file->tk_line[amount_lines - 1] = tok_line;
    }

    tok_file->amount_lines = amount_lines;

    if(tok_file->amount_lines <= 2){
        error->code = 3;
        free(tok_file);
        return NULL;
    }

    return tok_file;   
}



void print_tk_files(Token_File_Manager *tk_manager){

    for(int f = 0; f < tk_manager->amount_files; f++){

        printf("\n\n");

        for(int i = 0; i < tk_manager->tk_files[f]->amount_lines; i++){

            for(int x = 0; x < tk_manager->tk_files[f]->tk_line[i]->amount_tokens; x++){
                printf("%s ", tk_manager->tk_files[f]->tk_line[i]->tk[x].text);
            }
            printf("\n");
        }

    }
}


int tokenize(void *appstate){

    ErrorData result;
    result.string = NULL;
    Appstate *state = (Appstate*)appstate;
    File_Manager *manager = &state->manager;
    Token_File_Manager *tk_manager = &state->tk_manager;

    tk_manager->tk_files = NULL;    
    Token_File *tk_file = NULL;
    int amount_files = 0;

    
    for(int i = 0; i < manager->amount_inputs; i++){

        tk_file = tokenize_file(&manager->inputs[i], &result);

        if(tk_file == NULL){
            LogError(FILE_ERROR, NULL);
            return 1;
        }

        amount_files++;
        tk_manager->tk_files = realloc(tk_manager->tk_files, sizeof(Token_File) * amount_files);
        tk_manager->tk_files[amount_files - 1] = tk_file;

    }

    tk_manager->amount_files = amount_files;
    

    print_tk_files(tk_manager);

    return 0;
}


