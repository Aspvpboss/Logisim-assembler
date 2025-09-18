#include "tokenize.h"

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

    }

    return 0;
}


Token_Line* process_line(const char *raw_line, const char *file_name, int original_line, int *result){

    Token_Line *tok_line = malloc(sizeof(Token_Line));
    tok_line->amount_tokens = 0;
    tok_line->tk = NULL;
    tok_line->file = strdup(file_name);
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
                    tok_line->tk[amount_tokens - 1].text = realloc(tok_line->tk[amount_tokens - 1].text, sizeof(char) * num_char); 
                    tok_line->tk[amount_tokens - 1].text[num_char - 1] = line[x];   
                    continue;            
                }
                num_char++;
                tok_line->tk[amount_tokens - 1].text = realloc(tok_line->tk[amount_tokens - 1].text, sizeof(char) * num_char); 
                tok_line->tk[amount_tokens - 1].text[num_char - 1] = '\0';   
            }

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

Token_Line* tokenize_line(const char *raw_line, const char *file_name, int original_line, int *result){

    Token_Line *tok_line = process_line(raw_line, file_name, original_line, result);

    return tok_line;
}


int tokenize(Appstate *state){
    int result = 0;
    char test_line[] = " ";
    Token_Line *tok_line = tokenize_line(test_line, "burger.asm", 30, &result);

    if(tok_line == NULL){
        printf("empty string\n");
    }

    return 0;
}
