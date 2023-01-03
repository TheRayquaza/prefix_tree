#pragma once

#include "../descriptors/descriptors.h"
#include "../basics/basics.h"

int search_word(ptree * root, const char * s);

char ** completion(ptree * root, const char * s, size_t * nb_words);

void display_completion(ptree * root, const char * s);
