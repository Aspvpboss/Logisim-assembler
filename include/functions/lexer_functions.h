#pragma once

#include "tokenize_data.h"
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>


enum Token_Type check_immediate_type(char *str, size_t str_len);
enum Token_Type check_register(char *str, size_t str_len);
enum Token_Type check_io(char *str, size_t str_len);
enum Token_Type check_special_type(char *str, size_t str_len);
enum Token_Type check_directives(char *str);
enum Token_Type check_opcode(char *str);
enum Token_Type check_comparison_operators(char *str);