#include "print_functions.h"


const char* token_type_to_string(enum Token_Type type) {

    switch(type){

        case TOKEN_NONE: return "TOKEN_NONE";

        case TOKEN_OP_ADD: return "TOKEN_OP_ADD";
        case TOKEN_OP_SUB: return "TOKEN_OP_SUB";
        case TOKEN_OP_INC: return "TOKEN_OP_INC";
        case TOKEN_OP_LRS: return "TOKEN_OP_LRS";
        case TOKEN_OP_OR: return "TOKEN_OP_OR";
        case TOKEN_OP_XOR: return "TOKEN_OP_XOR";
        case TOKEN_OP_NAND: return "TOKEN_OP_NAND";

        case TOKEN_OP_JMP: return "TOKEN_OP_JMP";
        case TOKEN_OP_JIF: return "TOKEN_OP_JIF";
        case TOKEN_OP_CAL: return "TOKEN_OP_CAL";
        case TOKEN_OP_CIF: return "TOKEN_OP_CIF";
        case TOKEN_OP_HLT: return "TOKEN_OP_HLT";
        case TOKEN_OP_RET: return "TOKEN_OP_RET";

        case TOKEN_OP_LDI: return "TOKEN_OP_LDI";
        case TOKEN_OP_RTR: return "TOKEN_OP_RTR";
        case TOKEN_OP_RPC: return "TOKEN_OP_RPC";
        case TOKEN_OP_PCR: return "TOKEN_OP_PCR";
        case TOKEN_OP_STR: return "TOKEN_OP_STR";
        case TOKEN_OP_LOD: return "TOKEN_OP_LOD";
        case TOKEN_OP_STR_INDIRECT: return "TOKEN_OP_STR_INDIRECT";
        case TOKEN_OP_LOD_INDIRECT: return "TOKEN_OP_LOD_INDIRECT";

        case TOKEN_OP_SND: return "TOKEN_OP_SND";
        case TOKEN_OP_SDI: return "TOKEN_OP_SDI";
        case TOKEN_OP_WRE: return "TOKEN_OP_WRE";
        case TOKEN_OP_REC: return "TOKEN_OP_REC";

        case TOKEN_COMP_CARRY: return "TOKEN_COMP_CARRY";
        case TOKEN_COMP_ZERO: return "TOKEN_COMP_ZERO";
        case TOKEN_COMP_NOT_ZERO: return "TOKEN_COMP_NOT_ZERO";
        case TOKEN_COMP_GREATER: return "TOKEN_COMP_GREATER";
        case TOKEN_COMP_LESS: return "TOKEN_COMP_LESS";
        case TOKEN_COMP_GREATER_EQ: return "TOKEN_COMP_GREATER_EQ";
        case TOKEN_COMP_LESS_EQ: return "TOKEN_COMP_LESS_EQ";
        case TOKEN_COMP_ODD: return "TOKEN_COMP_ODD";

        case TOKEN_REGISTER: return "TOKEN_REGISTER";
        case TOKEN_REG_POINTER: return "TOKEN_REG_POINTER";

        case TOKEN_LABEL: return "TOKEN_LABEL";
        case TOKEN_LABEL_COLON: return "TOKEN_LABEL_COLON";

        case TOKEN_STRING_START: return "TOKEN_STRING_START";
        case TOKEN_STRING: return "TOKEN_STRING";
        case TOKEN_STRING_END: return "TOKEN_STRING_END";

        case TOKEN_START_BRACKET: return "TOKEN_START_BRACKET";
        case TOKEN_END_BRACKET: return "TOKEN_END_BRACKET";

        case TOKEN_MACRO_START: return "TOKEN_MACRO_START";
        case TOKEN_MACRO_MUL: return "TOKEN_MACRO_MUL";
        case TOKEN_MACRO_ARGS: return "TOKEN_MACRO_ARGS";
        case TOKEN_MACRO_END: return "TOKEN_MACRO_END";

        case TOKEN_MACRO_INLINE: return "TOKEN_MACRO_INLINE";
        case TOKEN_MACRO_SINGLE: return "TOKEN_MACRO_SINGLE";

        case TOKEN_IMMEDIATE: return "TOKEN_IMMEDIATE";

        case TOKEN_AT_DIR: return "TOKEN_AT_DIR";
        case TOKEN_GLOBAL_DIR: return "TOKEN_GLOBAL_DIR";
        case TOKEN_INCLUDE_DIR: return "TOKEN_INCLUDE_DIR";
        case TOKEN_START_FILE_DIR: return "TOKEN_START_FILE_DIR";
        case TOKEN_END_FILE_DIR: return "TOKEN_END_FILE_DIR";

        default: return "TOKEN_UNKNOWN";
    }

    return NULL;
}


void print_token_files(Token_File_Manager *manager){

    for(int f = 0; f < manager->amount_files; f++){

        printf("\n\n");

        Token_Line *token_line = manager->tk_files[f]->head;

        while(token_line){

            for(int x = 0; x < token_line->amount_tokens; x++){
                printf("%s ", token_line->tk[x].text);
            }
            printf("- line %d\n", token_line->original_line);

            token_line = token_line->next;
        }

    }
}


void print_file_lex(Token_File_Manager *manager){

    for(int i = 0; i < manager->amount_files; i++){

        Token_Line *current = manager->tk_files[i]->head;

        while(current){

            for(int i = 0; i < current->amount_tokens; i++){
                printf("%s - %s\n", current->tk[i].text, token_type_to_string(current->tk[i].type));
            }

            current = current->next;
            printf("\n");
        }

    }

}