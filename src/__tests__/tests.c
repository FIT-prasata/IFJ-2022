#include "t_dynamic_string.c"
#include "t_lex_analyzer.c"

int main(void) {
    int errors = 0;
    errors += run_d_string_tests();
    //errors += run_lex_analyzer_tests();
    printf("Total errors: %d \n", errors);
    return errors != 0;
}