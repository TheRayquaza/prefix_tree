#pragma once

#include <stdio.h>
#include <err.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>

typedef struct ptree
{
    char c;
    struct ptree ** children;
    size_t nb_children;
    int is_word;
} ptree;

ptree * create_ptree(char c);

void destroy_ptree(ptree * t);

void add_word(ptree * root, const char * s);

ptree * build_tree(const char * filename);

void display_ptree(ptree * root);
