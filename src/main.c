#include "structure/ptree.h"
#include "descriptors/descriptors.h"
#include "completion/completion.h"
#include "basics/basics.h"

#include <err.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
        errx(EXIT_FAILURE, "Wrong format, expecting at least one lexicon !");
    
    printf("Building lexicon from %s ...\n", argv[1]);
    ptree * root = build_tree(argv[1]);

    char current_word[512];

    while(!string_contains_char(current_word, 27))
    {
        fscanf(stdin, "%s", current_word);
        system("clear");
        display_completion(root, current_word);
    }
    
    destroy_ptree(root);

    return 0;
}
