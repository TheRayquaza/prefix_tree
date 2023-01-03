#include "basics.h"

void display_string_list(char ** s)
{
    printf("[");
    for (size_t i = 0; s[i]; i++)
        printf("%s ", s[i]);
    printf("]\n");
}

void free_string_list(char ** s)
{
    for (size_t i = 0; s[i]; i++)
        free(s[i]);
    free(s);
}

char * concat_str(const char * s1, const char * s2)
{
    size_t len1 = strlen(s1);
    size_t len2 = strlen(s2);
    size_t i = 0, j = 0;
    char * s = calloc(len1 + len2 + 1, sizeof(char));

    for (i = 0; i < len1; i++)
        s[i] = s1[i];
    for (j = 0; j < len2; j++)
        s[j+len1] = s2[j];
    s[len1+len2] = 0;

    return s;
}

char * append_new(const char * s, char c) 
{
    size_t len = strlen(s);
    char * r = calloc(len+2, sizeof(char));
    for (size_t i = 0; i < len; i++)
        r[i] = s[i];
    r[len] = c;
    r[len+1] = 0;

    return r;
}

char * remove_last_new(const char * s)
{
    char * new_s = calloc(strlen(s), sizeof(char));
    for (size_t i = 0; i < strlen(s); i++)
        new_s[i] = s[i];
    return new_s;
}

int string_contains_char(const char * s, char c) 
{
    for (; *s; s++)
        if (*s == c) 
            return 1;
    return 0;
}
