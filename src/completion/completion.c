#include "completion.h"


// Search a word into the prefix tree
static int __search_word(ptree * root, const char * s, size_t i)
{
    if (s[i] == root->c) 
        return 0;
    else if (!s[i])
        return root->is_word;
    else
        for (size_t j = 0; j < root->nb_children; j++)
            if (__search_word(root->children[j], s, i+1))
                return 1;
    return 0;
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
    if (s[i] == 0)
        return root;
    else
        for (size_t j = 0; j < root->nb_children; j++)
            if (s[i] == root->children[j]->c) 
                return __get_valid_root(root->children[i], s, i+1);
    return NULL;
}

char ** completion(ptree * root, const char * s)
{
    ptree * valid_trie = __get_valid_root(root, s, 0);
    if (valid_trie)
        return word_list(valid_trie);
    else
        return calloc(1, sizeof(char *));
}
