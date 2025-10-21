#include "tokenize.h"
#include "error.h"
#include "quit.h"
#include "print_functions.h"

#include <stdbool.h>
#include <string.h>
#include <ctype.h>

int check_special(const char c){
    
    switch(c){

        case('"'):
            return 1;
        case('['):
            return 1;
        case(']'):
            return 1;
        case(':'):
            return 1;

    }

    return 0;
}

 
Token_Line* tokenize_line(const char *raw_line, char *file_name, uint16_t original_line){

    Token_Line *tok_line = t_malloc(sizeof(Token_Line));
    tok_line->amount_tokens = 0;
    tok_line->tk = NULL;
    tok_line->file = file_name;
    tok_line->original_line = original_line;

    char *line = t_strdup(raw_line);
    size_t line_len = strlen(raw_line);

    bool in_quotes = 0;
    bool comment = 0;

    for(size_t i = 0; i <= line_len; i++){

        if(comment){
            line[i] = '\0';
            continue;
        }

        if(line[i]  == ';'){
            line[i] = '\0';
            comment = 1;
            continue;
        }

        if(strncmp(line + i, "//", 2) == 0){
            line[i] = '\0';
            line[i + 1] = '\0';
            comment = 1;
            i++;
            continue;            
        }


        if(line[i] == '"'){
            in_quotes = !in_quotes;
            continue;
        }

        if(in_quotes)
            continue;


        if(isspace(line[i]) || line[i] == ',' || line[i] == '#'){
            line[i] = '\0';
        }
    }



    bool previous_char = 0;
    int amount_tokens = 0;

    for(size_t i = 0; i <= line_len; i++){

        if(check_special(line[i])){

            amount_tokens++;
            tok_line->tk = t_realloc(tok_line->tk, sizeof(Token) * amount_tokens);
            tok_line->tk[amount_tokens - 1].text = t_malloc(sizeof(char) * 2);
            tok_line->tk[amount_tokens - 1].text[0] = line[i];
            tok_line->tk[amount_tokens - 1].text[1] = '\0';
            line[i] = '\0';
            tok_line->tk[amount_tokens - 1].text_len = strlen(tok_line->tk[amount_tokens - 1].text);
            previous_char = 0;
            continue;

        }

        if(line[i] != '\0' && !previous_char){

            amount_tokens++;
            tok_line->tk = t_realloc(tok_line->tk, sizeof(Token) * amount_tokens);
            
            int num_char = 0;
            tok_line->tk[amount_tokens - 1].text = NULL;
            tok_line->tk[amount_tokens - 1].type = TOKEN_NONE;

            for(int x = i; line[x] != '\0'; x++){

                if(!check_special(line[x])){
                    num_char++;
                    continue;            
                }
            }

            tok_line->tk[amount_tokens - 1].text = t_malloc(sizeof(char) * (num_char + 1));
            strncpy(tok_line->tk[amount_tokens - 1].text, &line[i], num_char);
            tok_line->tk[amount_tokens - 1].text[num_char] = '\0';

            tok_line->tk[amount_tokens - 1].text_len = strlen(tok_line->tk[amount_tokens - 1].text);

            previous_char = 1;
            continue;
        }

        if(line[i] == '\0'){
            previous_char = 0;
        }
    }

    t_free(line);

    tok_line->amount_tokens = amount_tokens;

    if(amount_tokens == 0){

        free_tokenized_line(tok_line);
        t_free(tok_line);
        return NULL;
    }


    

    return tok_line;
}


Token_File* tokenize_file(File_Info *file, ErrorData *result){

    Token_File *token_file = t_malloc(sizeof(Token_File));
    token_file->file = t_strdup(file->path);

    Token_Line *token_line = NULL;
    token_file->head = NULL;
    uint16_t amount_lines = 0;

    for(int i = 0; i < file->num_lines; i++){

        token_line = tokenize_line(file->raw_text[i], file->path, i);

        if(token_line == NULL){
            continue;
        }

        if(token_file->head == NULL){

            token_line->next = NULL;
            token_file->head = token_line;
            token_file->tail = token_line;

        } else{

            token_file->tail->next = token_line;
            token_file->tail = token_line;
            token_line->next = NULL;

        }

        amount_lines++;

    }

    token_file->amount_lines = amount_lines;

    if(token_file->amount_lines <= 2){
        result->specific_code = 3;   
        free_tokenized_file(token_file);
        t_free(token_file);
        return NULL;
    }

    return token_file;   
}






int tokenize(void *appstate){


    ErrorData result;
    result.string = NULL;
    Appstate *state = (Appstate*)appstate;
    File_Manager *manager = &state->manager;
    Token_File_Manager *tk_manager = &state->tk_manager;

    tk_manager->tk_files = NULL;    
    Token_File *tk_file = NULL;
    uint16_t amount_files = 0;

    
    for(int i = 0; i < manager->amount_inputs; i++){

        tk_file = tokenize_file(&manager->inputs[i], &result);

        if(tk_file == NULL){
            LogError(FILE_ERROR, &result);
            return 1;
        }

        amount_files++;
        tk_manager->tk_files = t_realloc(tk_manager->tk_files, sizeof(Token_File*) * amount_files);
        tk_manager->tk_files[amount_files - 1] = tk_file;

    }

    tk_manager->amount_files = amount_files;
    


    //print_tk_files(tk_manager);

    return 0;
}


