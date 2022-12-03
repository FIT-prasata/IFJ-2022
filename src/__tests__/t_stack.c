#include "../stack.h"
#include "test_utils.h"

TEST(T_token_stack_init)
Token_stack_t *test_token_stack;
int r;
ASSERT_TRUE((r = token_stack_init(test_token_stack)) != INTERNAL_ERR)
ENDTEST

int run_stack_tests() {
    int errors = 0;
    printf("Running stack tests...\n");
    errors += T_token_stack_init();
    return errors;
}
