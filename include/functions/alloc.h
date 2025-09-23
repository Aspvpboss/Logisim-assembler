#pragma once

#include <stddef.h>

size_t get_allocations();
void s_free(void *memory);
void* s_malloc(size_t size);
void* s_realloc(void *mem, size_t size);
char* s_strdup(const char* src);