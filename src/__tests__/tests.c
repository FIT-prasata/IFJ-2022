#include "t_dynamic_string.c"
#include "t_symtable.c"
#include "t_lex_analyzer.c"
#include "t_stack.c"

// GLOBAL line number - same variable asi in main.c, but main.c is not compiled into tests
int line_num = 1;

int main(void) {
    int errors = 0;
    printf("\n");
    errors += run_d_string_tests();
    printf("\n");
    errors += run_symtable_tests();
    printf("\n");
    errors += run_lex_analyzer_tests();
    printf("\n");
    errors += run_stack_tests();
    printf("\n");
    printf("Total errors: %d \n", errors);
    return errors != 0;
}