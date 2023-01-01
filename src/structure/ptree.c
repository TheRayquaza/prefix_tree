#include "ptree.h"

// Create a prefix tree with a character
ptree * create_ptree(char c) 
{
    ptree * t = calloc(1, sizeof(ptree));

    t->c = c;
    t->children = calloc(0, sizeof(ptree*));
    t->nb_children = 0;
    t->is_word = 0;

    return t;
}

// Destroy the prefix tree
void destroy_ptree(ptree * t)
{
    for (size_t i = 0; i < t->nb_children; i++)
        destroy_ptree(t->children[i]);
    free(t->children);
    free(t);
}

// Add a word into the prefix tree
static void __insert_ptree(ptree * root, ptree * inserted)
{
    root->children = realloc(root->children, (root->nb_children+1)*sizeof(ptree*));
    ptree * tmp;

    size_t i = 0;
    while (i < root->nb_children && root->children[i]->c < inserted->c) 
        i++;

    root->children[root->nb_children] = inserted;
    size_t j = root->nb_children;
    while (i != j)
    {
        tmp = root->children[j-1];
        root->children[j-1] = root->children[j];
        root->children[j] = tmp;
        j--;
    }
    (root->nb_children)++;
}

static ptree * __contain_ptree(ptree ** children , size_t nb_children, char c) 
{
    for (size_t i = 0; i < nb_children; i++)
        if (children[i]->c == c) 
            return children[i];
    return NULL;
}

void add_word(ptree * root, const char * s)
{
    if (*s == 0)
        return;
    else if (*s != 0 && *(s+1) == 0)
    {
        root->is_word = 1;
        root->c = *s;
    }
    else
    {
        ptree * tmp = __contain_ptree(root->children, root->nb_children, *s);
        if (tmp == NULL)
        {
            tmp = create_ptree(*s);
            __insert_ptree(root, tmp);
        }
        add_word(tmp, s+1);
    }
}

static char ** __read_file(const char * filename, size_t * nb_strings)
{
    FILE * f = fopen(filename, "r");
    if (!f)
        errx(EXIT_FAILURE, "Unable to open %s", filename);

    char s[256];    
    char ** content = malloc(0);
    size_t len;
    *nb_strings = 0;


    while (fscanf(f, "%s\n", s) != EOF)
    {
        (*nb_strings)++;
        len = strlen(s);
        content = realloc(content, (*nb_strings)*sizeof(char*));
        content[*nb_strings-1] = calloc(len+1, sizeof(char));
        for (size_t i = 0; i < len; i++)
            content[*nb_strings-1][i] = s[i];
        content[*nb_strings-1][len] = 0;
    }

    fclose(f);
    return content;
}


// Build a tree based on a lexicon
ptree * build_tree(const char * filename)
{
    size_t nb_strings;
    char ** content = __read_file(filename, &nb_strings);
    ptree * root = create_ptree(0);

    for (size_t i = 0; i < nb_strings; i++)
    {
        add_word(root, content[i]); 
        free(content[i]);
    }
    free(content);

    return root;
}


// Display a prefix tree


static void __display_tree(ptree * root, size_t depth)
{
    for (size_t i = 0; i < depth; i++)
        printf(" ");
    printf("|-%c\n",root->c);
    for (size_t i = 0; i < root->nb_children; i++)
        __display_tree(root->children[i], depth+1);
}

void display_ptree(ptree * root)
{
    printf("---  TREE :\n");
    __display_tree(root, 0);
}
