#include "converter.h"

char ** read_file(const char * filename, size_t * nb_strings)
{
    FILE * f = fopen(filename, "r");
    if (!f)
        errx(EXIT_FAILURE, "Unable to open %s", filename);

    char s[256];    
    char ** content = malloc(0);
    *nb_strings = 0;


    while (fscanf(f, "%s\n", s) != EOF)
    {
        (*nb_strings)++;
        content = realloc(content, (*nb_strings)*sizeof(char*));
        content[*nb_strings-1] = calloc(strlen(s), sizeof(char));
        strcpy(content[*nb_strings-1], s);
    }

    fclose(f);
    return content;
}



static void __write_file(FILE * f, ptree * trie, char * current)
{
    char * s;

    if (trie->is_word)
        fprintf(f, "%s\n", current);

    for (size_t i = 0; i < trie->nb_children; i++)
    {
        s = calloc(strlen(current)+1, sizeof(char));
        sprintf(s, "%s%c", current, trie->c);
        __write_file(f, trie->children[i], s);
        free(s);
    }
}

void write_file(const char * filename, ptree * root)
{
    FILE * f = fopen(filename, "w");

    if (!f)
        errx(EXIT_FAILURE, "Unbale to open %s", filename);

    __write_file(f, root, ""); 

    fclose(f);
}
