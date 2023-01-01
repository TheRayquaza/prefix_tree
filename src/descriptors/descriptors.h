#pragma once

#include "../structure/ptree.h"
#include <stdio.h>

size_t count_words(ptree * root);

size_t longest_word_length(ptree * root);

double average_length(ptree * root);

char ** word_list(ptree * root);
