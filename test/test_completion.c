#include "test_header.h"

Test(completion, search_word, .init = setup, .fini = teardown)
{
    cr_expect(search_word(lexicons1, "fabulous") == 0);
    cr_expect(search_word(lexicons1, "famous") == 1);
     
}

static int are_array_equal(char ** s1, char ** s2, size_t nb_1, size_t nb_2)
{
    if (nb_1 != nb_2)
        return 0;
    for (size_t i = 0; i < nb_1; i++)
        if (strcmp(s1[i], s2[i]) != 0)
            return 0;
    return 1;
}

Test(completion, completion, .init = setup, .fini = teardown)
{
    char ** s = completion(lexicons1, "fan");
    char * strings[] = {"fan", "fancy"};
    
    size_t i = 0;
    for (; s[i] != NULL; i++);
    cr_expect(are_array_equal(s, strings, i, 2)); 
    for (i = 0; s[i] != NULL; i++)
        free(s[i]);
    free(s[i]);
    free(s);
}
