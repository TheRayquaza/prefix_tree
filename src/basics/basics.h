#pragma once 


#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



void display_string_list(char ** s);

void free_string_list(char ** s);

char * concat_str(const char * s1, const char * s2);

char * append_new(const char * s, char c);

char * remove_last_new(const char * s);

int string_contains_char(const char * s, char c);
