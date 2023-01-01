#include "structure/ptree.h"
#include "descriptors/descriptors.h"
#include "completion/completion.h"
#include "err.h"

int main(int argc, char *argv[])
{
    if (argc != 2)
        errx(EXIT_FAILURE, "Wrong format !");
    
    ptree * root = build_tree(argv[1]);
    display_ptree(root);
    char ** list = word_list(root), ** tmp;
    tmp = list;
    printf("Word list : \n");
    while (list)
    {
        printf("%s\n", *list);
        free(*list);
        list++;
    }
    free(*list);
    free(tmp);

    destroy_ptree(root);

    return 0;
}
