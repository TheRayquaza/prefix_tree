#pragma once

#include "../structure/ptree.h"
#include <stdio.h>
#include <err.h>
#include <string.h>

char ** read_file(const char * filename, size_t * nb_strings);

void write_file(const char * filename, ptree * root);

