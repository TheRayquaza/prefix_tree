#include "descriptors.h"

#define MAX(x, y) (((x) > (y)) ? (x) : (y))

// Count the number of words in the given prefix tree
size_t count_words(ptree * root)
{
    size_t count = root->is_word;

    for (size_t i = 0; i < root->nb_children; i++)
        count += count_words(root->children[i]);

    return count;
}


// Get the longest word length
static size_t __longest_word_length(ptree * root, size_t current)
{
    size_t longest = root->is_word ? current : 0;
    for (size_t i = 0; i < root->nb_children; i++)
        longest = MAX(longest, 
                __longest_word_length(root->children[i], current+1));
    return longest;
}

size_t longest_word_length(ptree * root)
{
    return __longest_word_length(root, 0);
}


// Calculate the average length of the word of a given prefix tree
static double __average_length(ptree * root, double * nb_words, double current)
{
    double length = root->is_word ? current : 0;
    if (root->is_word)
        (*nb_words)++;
    for (size_t i = 0; i < root->nb_children; i++)
        length += __average_length(root->children[i], nb_words, current+1);

    return length;
    
}

double average_length(ptree * root)
{
    double nb_words, length = __average_length(root, &nb_words, 0);
    return (nb_words == 0) ? 0.0 : length/nb_words;
}


// Word list of a prefix tree
static void __word_list(ptree * root, char *** list, size_t * nb_words, 
        char * current)
{
    char * s = append_new(current, root->c);

    if (root->is_word)
    {
        char ** copy = calloc(*nb_words+1, sizeof(char*));

        for (size_t i = 0; i < *nb_words; i++)
            copy[i] = (*list)[i];

        (*nb_words)++;
        free(*list);
        copy[*nb_words-1] = s;
        *list = copy;
    }

    for (size_t i = 0; i < root->nb_children; i++)
        __word_list(root->children[i], list, nb_words, s);

    if (!root->is_word)
        free(s);
}

char ** word_list(ptree * root, size_t * nb_words)
{
    char ** list = malloc(0);
    *nb_words = 0;
    __word_list(root, &list, nb_words, "");
    list = realloc(list, (*nb_words + 1) * sizeof(char*));
    list[*nb_words] = NULL;

    return list;
}
