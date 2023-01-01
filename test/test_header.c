#include "test_header.h"

void setup(void)
{
    lexicons1 = build_tree("../lexicons/lexicons1");
    lexicons2 = build_tree("../lexicons/lexicons2");
    lexicons3 = build_tree("../lexicons/lexicons3");
}

void teardown(void)
{
    destroy_ptree(lexicons1);
    destroy_ptree(lexicons2);
    destroy_ptree(lexicons3);
}
