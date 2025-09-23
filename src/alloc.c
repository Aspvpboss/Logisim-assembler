#include <stdlib.h>
#include <string.h>

static size_t allocations = 0;

size_t get_allocations(){
    return allocations;
}

void s_free(void *memory){

    if(memory){
        free(memory);
        allocations--;
    }
    
}


void* s_malloc(size_t size){
    void *mem = NULL;
    mem = malloc(size);

    if(mem)
        allocations++;

    return mem;
}


void* s_realloc(void *mem, size_t size){

    void *new_mem = NULL;
    
    new_mem = realloc(mem, size);

    if(new_mem && !mem)
        allocations++;

    return new_mem;

}

char* s_strdup(const char* src){
    size_t src_len = strlen(src);
    char *dup = NULL;

    dup = s_malloc(sizeof(char) * (src_len + 1));
    strcpy(dup, src);
    dup[src_len] = '\0';

    return dup;
}