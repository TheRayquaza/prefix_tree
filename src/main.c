#include "structure/ptree.h"
#include "descriptors/descriptors.h"
#include "completion/completion.h"
#include "err.h"

int main(int argc, char *argv[])
{
    if (argc != 2)
        errx(EXIT_FAILURE, "Wrong format !");
    
    ptree * root = build_tree(argv[1]);

    //printf("number of words : %lu\n", count_words(root)); 
    //printf("longest word length : %lu\n", longest_word_length(root));
    //printf("average length %lf\n", average_length(root));
    
    //printf("searching for word : famous %i\n", search_word(root, "famous"));
    //printf("searching for words : fabulous %i\n", search_word(root, "fabulous"));

    printf("Completion for fan : \n");
    size_t nb_words;
    char ** list = completion(root, "fan", &nb_words);
    printf("[");
    for (size_t i = 0; i < nb_words; i++)
    {
        printf("%s ", list[i]);
        free(list[i]);
    }
    free(list);
    printf("]\n");

    printf("Completion for ci : \n");
    list = completion(root, "ci", &nb_words);
    printf("[");
    for (size_t i = 0; i < nb_words; i++)
    {
        printf("%s ", list[i]);
        free(list[i]);
    }
    free(list);
    printf("]\n");

    destroy_ptree(root);

    return 0;
}
