#include "completion.h"


// Search a word into the prefix tree
static int __search_word(ptree * root, const char * s, size_t i)
{
    for (size_t j = 0; j < root->nb_children; j++)
        if (root->c == s[i] &&  __search_word(root->children[j], s, i+1))
            return 1;
    return s[i+1] == 0 && root->is_word;
}

int search_word(ptree * root, const char * s)
{
    for (size_t i = 0; i < root->nb_children; i++)
        if (__search_word(root->children[i], s, 0))
            return 1;
    return 0;
}

// Get the completion words
static ptree * __get_valid_root(ptree * root, const char * s, size_t i)
{
    for (size_t j = 0; j < root->nb_children; j++)
        if (s[i] == root->children[j]->c)
            return __get_valid_root(root->children[j], s, i+1);
    return (s[i] == 0) ? root : NULL;
}

char ** completion(ptree * root, const char * s, size_t * nb_words)
{
    ptree * valid_trie = __get_valid_root(root, s, 0);

    if (valid_trie)
    {
        char ** list = word_list(valid_trie, nb_words), * tmp;

        for (size_t i = 0; i < *nb_words; i++)
        {
            tmp = concat_str(s, list[i]+1);
            free(list[i]);
            list[i] = tmp;
        }
        return list;
    }
    else
    {
        *nb_words = 0;
        return calloc(0, sizeof(char *));
    }
}

void display_completion(ptree * root, const char * s)
{
    size_t nb_words;
    char ** completion_list = completion(root, s, &nb_words);
    printf("\t-> Displaying all possibilities\n");
    for (size_t i = 0; i < nb_words; i++)
        printf("%lu) %s\n", i, completion_list[i]);
    printf("\t-> Number of words %lu \n", nb_words);
}
