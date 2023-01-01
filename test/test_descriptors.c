#include "test_header.h"

Test(descriptors, count_words, .init = setup, .fini = teardown)
{
    cr_expect(count_words(lexicons1) == 11);
    cr_expect(count_words(lexicons2) == 0);
    cr_expect(count_words(lexicons3) == 0);
}

Test(descriptors, longest_word_length, .init = setup, .fini = teardown)
{
    cr_expect(longest_word_length(lexicons1) == 6);
    cr_expect(longest_word_length(lexicons2) == 0);
    cr_expect(longest_word_length(lexicons3) == 0);
}

static int equal_double(double x, double y, double delta)
{
    if (x - delta < y && x + delta > y)
        return 1;
    return 0;
}

Test(descriptors, average_length, .init = setup, .fini = teardown)
{
    cr_expect(equal_double(average_length(lexicons1), 4.63, 0.01));
    cr_expect(equal_double(average_length(lexicons2), 0,0.01));
    cr_expect(equal_double(average_length(lexicons3), 0, 0.01));
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

Test(descriptors, word_list, .init = setup, .fini = teardown)
{
    char * s1[] = {"case", "cast", "castle", "circle", "city", "come", "could", 
        "fame", "famous", "fan", "fancy"};
    char ** s2 = word_list(lexicons1);
    size_t i = 0;
    for (; s2[i] != NULL; i++);
    cr_expect(are_array_equal(s1, s2, 11, i));
    for (i = 0; s2[i] != NULL; i++)
        free(s2[i]);
    free(s2[i]);
    free(s2);

    

}
