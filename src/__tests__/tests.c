#include "t_dynamic_string.c"

int main(void) {
    int errors = 0;
    errors += run_d_string_tests();
    printf("Total errors: %d \n", errors);
    return errors != 0;
}