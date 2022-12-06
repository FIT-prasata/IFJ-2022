#include "../stack.h"
#include "test_utils.h"

#define T_STACK_INIT                   \
    Token_stack_t test_token_stack;    \
    token_stack_init(&test_token_stack);

#define T_STACK_FREE                   \
    token_stack_clear(&test_token_stack);

#define C_STACK_INIT                   \
    Char_stack_t test_char_stack;      \
    char_stack_init(&test_char_stack);

#define C_STACK_FREE                   \
    char_stack_clear(&test_char_stack);

// Token stack tests

TEST(T_token_stack_init)
Token_stack_t test_token_stack;
int r;
ASSERT_TRUE((r = token_stack_init(&test_token_stack)) != INTERNAL_ERR)
T_STACK_FREE
ENDTEST

TEST(T_token_stack_init_fail)
int r;
ASSERT_TRUE((r = token_stack_init(NULL)) == INTERNAL_ERR)
ENDTEST

TEST(T_token_stack_get_head_fail)
T_STACK_INIT
ASSERT_TRUE(token_stack_get_head(&test_token_stack) == NO_TYPE)
T_STACK_FREE
ENDTEST

TEST(T_token_stack_get_head_null_stack)
ASSERT_TRUE(token_stack_get_head(NULL) == INTERNAL_ERR)
ENDTEST

TEST(T_token_stack_push)
T_STACK_INIT
Token_t *test_token = malloc(sizeof(Token_t));
test_token->type = T_ID;
ASSERT_TRUE(token_stack_push(&test_token_stack, test_token) != INTERNAL_ERR)
ASSERT_TRUE(token_stack_get_head(&test_token_stack) == T_ID)
T_STACK_FREE
ENDTEST

TEST(T_token_stack_multi_push)
T_STACK_INIT
Token_t *test_token = malloc(sizeof(Token_t));
test_token->type = T_ID;
Token_t *test_token2 = malloc(sizeof(Token_t));
test_token2->type = T_MUL;
Token_t *test_token3 = malloc(sizeof(Token_t));
test_token3->type = T_ID;
Token_t *test_token4 = malloc(sizeof(Token_t));
test_token4->type = T_RBR;
ASSERT_TRUE(token_stack_push(&test_token_stack, test_token) != INTERNAL_ERR)
ASSERT_TRUE(token_stack_push(&test_token_stack, test_token2) != INTERNAL_ERR)
ASSERT_TRUE(token_stack_push(&test_token_stack, test_token3) != INTERNAL_ERR)
ASSERT_TRUE(token_stack_push(&test_token_stack, test_token4) != INTERNAL_ERR)
ASSERT_TRUE(token_stack_get_head(&test_token_stack) == T_RBR)
T_STACK_FREE
ENDTEST

TEST(T_token_stack_push_no_type)
T_STACK_INIT
Token_t *test_token = malloc(sizeof(Token_t));
test_token->type = NO_TYPE;
ASSERT_TRUE(token_stack_push(&test_token_stack, test_token) == INTERNAL_ERR)
T_STACK_FREE
ENDTEST

TEST(T_token_stack_push_null_token)
T_STACK_INIT
ASSERT_TRUE(token_stack_push(&test_token_stack, NULL) == INTERNAL_ERR)
T_STACK_FREE
ENDTEST

TEST(T_token_stack_push_null_stack)
Token_t *test_token = malloc(sizeof(Token_t));
test_token->type = T_ID;
ASSERT_TRUE(token_stack_push(NULL, test_token) == INTERNAL_ERR)
ENDTEST

TEST(T_token_stack_pop)
T_STACK_INIT
Token_t *test_token = malloc(sizeof(Token_t));
test_token->type = T_ID;
Token_t *test_token2 = malloc(sizeof(Token_t));
test_token2->type = T_MUL;
ASSERT_TRUE(token_stack_push(&test_token_stack, test_token) != INTERNAL_ERR)
ASSERT_TRUE(token_stack_push(&test_token_stack, test_token2) != INTERNAL_ERR)
ASSERT_TRUE(token_stack_pop(&test_token_stack) == T_MUL)
ASSERT_TRUE(token_stack_get_head(&test_token_stack) == T_ID)
T_STACK_FREE
ENDTEST

TEST(T_token_stack_pop_null_stack)
ASSERT_TRUE(token_stack_pop(NULL) == INTERNAL_ERR)
ENDTEST

TEST(T_token_stack_pop_empty_stack)
T_STACK_INIT
ASSERT_TRUE(token_stack_pop(&test_token_stack) == TOKEN_EMPTY_STACK)
T_STACK_FREE
ENDTEST

TEST(T_token_stack_complex_test)
T_STACK_INIT
Token_t *test_token = malloc(sizeof(Token_t));
test_token->type = T_ID;
Token_t *test_token2 = malloc(sizeof(Token_t));
test_token2->type = T_MUL;
Token_t *test_token3 = malloc(sizeof(Token_t));
test_token3->type = T_ID;
Token_t *test_token4 = malloc(sizeof(Token_t));
test_token4->type = T_ADD;
Token_t *test_token5 = malloc(sizeof(Token_t));
test_token5->type = T_ID;
ASSERT_TRUE(token_stack_push(&test_token_stack, test_token) != INTERNAL_ERR)
ASSERT_TRUE(token_stack_push(&test_token_stack, test_token2) != INTERNAL_ERR)
ASSERT_TRUE(token_stack_pop(&test_token_stack) != INTERNAL_ERR)
ASSERT_TRUE(token_stack_push(&test_token_stack, test_token3) != INTERNAL_ERR)
ASSERT_TRUE(token_stack_pop(&test_token_stack) != INTERNAL_ERR)
ASSERT_TRUE(token_stack_push(&test_token_stack, test_token4) != INTERNAL_ERR)
ASSERT_TRUE(token_stack_push(&test_token_stack, test_token5) != INTERNAL_ERR)
ASSERT_TRUE(token_stack_pop(&test_token_stack) != INTERNAL_ERR)
ASSERT_TRUE(token_stack_get_head(&test_token_stack) == T_ADD)
T_STACK_FREE
ENDTEST


// Char stack tests

TEST(T_char_stack_init)
Char_stack_t test_char_stack;
int r;
ASSERT_TRUE((r = char_stack_init(&test_char_stack)) != INTERNAL_ERR)
C_STACK_FREE
ENDTEST

TEST(T_char_stack_init_fail)
int r;
ASSERT_TRUE((r = char_stack_init(NULL)) == INTERNAL_ERR)
ENDTEST

TEST(T_char_stack_get_head_fail)
C_STACK_INIT
ASSERT_TRUE(char_stack_get_head(&test_char_stack) == CHAR_STACK_BOTTOM)
C_STACK_FREE
ENDTEST

TEST(T_char_stack_get_head_null_stack)
ASSERT_TRUE(char_stack_get_head(NULL) == INTERNAL_ERR)
ENDTEST

TEST(T_char_stack_push)
C_STACK_INIT
ASSERT_TRUE(char_stack_push(&test_char_stack, EXPR_EQ) == OK)
ASSERT_TRUE(char_stack_get_head(&test_char_stack) == EXPR_EQ)
C_STACK_FREE
ENDTEST

TEST(T_char_stack_multi_push)
C_STACK_INIT
ASSERT_TRUE(char_stack_push(&test_char_stack, EXPR_EQ) == OK)
ASSERT_TRUE(char_stack_push(&test_char_stack, EXPR_NEQ) == OK)
ASSERT_TRUE(char_stack_push(&test_char_stack, EXPR_LT) == OK)
ASSERT_TRUE(char_stack_push(&test_char_stack, EXPR_GT) == OK)
ASSERT_TRUE(char_stack_get_head(&test_char_stack) == EXPR_GT)
C_STACK_FREE
ENDTEST

TEST(T_char_stack_push_null_stack)
ASSERT_TRUE(char_stack_push(NULL, EXPR_EQ) == INTERNAL_ERR)
ENDTEST

TEST(T_char_stack_pop)
C_STACK_INIT
ASSERT_TRUE(char_stack_push(&test_char_stack, EXPR_EQ) == OK)
ASSERT_TRUE(char_stack_push(&test_char_stack, EXPR_NEQ) == OK)
ASSERT_TRUE(char_stack_pop(&test_char_stack) == EXPR_NEQ)
ASSERT_TRUE(char_stack_get_head(&test_char_stack) == EXPR_EQ)
C_STACK_FREE
ENDTEST

TEST(T_char_stack_pop_null_stack)
ASSERT_TRUE(char_stack_pop(NULL) == CHAR_STACK_POP_ERR)
ENDTEST

TEST(T_char_stack_pop_empty_stack)
C_STACK_INIT
ASSERT_TRUE(char_stack_pop(&test_char_stack) == CHAR_STACK_POP_ERR)
C_STACK_FREE
ENDTEST

TEST(T_char_stack_complex_test)
C_STACK_INIT
ASSERT_TRUE(char_stack_push(&test_char_stack, EXPR_ID) == OK)
ASSERT_TRUE(char_stack_push(&test_char_stack, EXPR_MUL) == OK)
ASSERT_TRUE(char_stack_pop(&test_char_stack) == EXPR_MUL)
ASSERT_TRUE(char_stack_push(&test_char_stack, EXPR_ID) == OK)
ASSERT_TRUE(char_stack_pop(&test_char_stack) == EXPR_ID)
ASSERT_TRUE(char_stack_push(&test_char_stack, EXPR_ADD) == OK)
ASSERT_TRUE(char_stack_push(&test_char_stack, EXPR_ID) == OK)
ASSERT_TRUE(char_stack_pop(&test_char_stack) == EXPR_ID)
ASSERT_TRUE(char_stack_get_head(&test_char_stack) == EXPR_ADD)
C_STACK_FREE
ENDTEST

TEST(T_char_stack_get_closest_terminal)
C_STACK_INIT
ASSERT_TRUE(char_stack_push(&test_char_stack, 'E') == OK)
ASSERT_TRUE(char_stack_push(&test_char_stack, EXPR_ID) == OK)
ASSERT_TRUE(char_stack_push(&test_char_stack, 'E') == OK)
ASSERT_TRUE(char_stack_push(&test_char_stack, EXPR_MUL) == OK)
ASSERT_TRUE(char_stack_push(&test_char_stack, 'E') == OK)
ASSERT_TRUE(char_stack_get_closest_terminal(&test_char_stack) == EXPR_MUL)
C_STACK_FREE
ENDTEST

TEST(T_char_stack_get_closest_terminal_stack_bottom)
C_STACK_INIT
ASSERT_TRUE(char_stack_push(&test_char_stack, 'E') == OK)
ASSERT_TRUE(char_stack_push(&test_char_stack, 'E') == OK)
ASSERT_TRUE(char_stack_get_closest_terminal(&test_char_stack) == CHAR_STACK_BOTTOM)
C_STACK_FREE
ENDTEST

TEST(T_char_stack_get_closest_terminal_null_stack)
ASSERT_TRUE(char_stack_get_closest_terminal(NULL) == INTERNAL_ERR)
ENDTEST

TEST(T_char_stack_push_shift)
C_STACK_INIT
ASSERT_TRUE(char_stack_push(&test_char_stack, 'E') == OK)
ASSERT_TRUE(char_stack_push(&test_char_stack, EXPR_ADD) == OK)
ASSERT_TRUE(char_stack_push(&test_char_stack, 'E') == OK)
ASSERT_TRUE(char_stack_push_shift(&test_char_stack) == OK)
ASSERT_TRUE(char_stack_get_closest_terminal(&test_char_stack) == EXPR_ADD)
ASSERT_TRUE(char_stack_pop(&test_char_stack) == 'E')
ASSERT_TRUE(char_stack_get_head(&test_char_stack) == '[')
C_STACK_FREE
ENDTEST

TEST(T_char_stack_push_shift_top_terminal)
C_STACK_INIT
ASSERT_TRUE(char_stack_push(&test_char_stack, 'E') == OK)
ASSERT_TRUE(char_stack_push(&test_char_stack, EXPR_ADD) == OK)
ASSERT_TRUE(char_stack_push_shift(&test_char_stack) == OK)
ASSERT_TRUE(char_stack_get_closest_terminal(&test_char_stack) == EXPR_ADD)
ASSERT_TRUE(char_stack_get_head(&test_char_stack) == '[')
C_STACK_FREE
ENDTEST

TEST(T_char_stack_push_shift_stack_bottom)
C_STACK_INIT
ASSERT_TRUE(char_stack_push(&test_char_stack, 'E') == OK)
ASSERT_TRUE(char_stack_push_shift(&test_char_stack) == OK)
ASSERT_TRUE(char_stack_get_closest_terminal(&test_char_stack) == CHAR_STACK_BOTTOM)
ASSERT_TRUE(char_stack_pop(&test_char_stack) == 'E')
ASSERT_TRUE(char_stack_get_head(&test_char_stack) == '[')
C_STACK_FREE
ENDTEST

TEST(T_char_stack_push_shift_null_stack)
ASSERT_TRUE(char_stack_push_shift(NULL) == INTERNAL_ERR)
ENDTEST

int run_stack_tests() {
    int errors = 0;
    printf("Running token stack tests...\n");
    errors += T_token_stack_init();
    errors += T_token_stack_init_fail();
    errors += T_token_stack_get_head_fail();
    errors += T_token_stack_get_head_null_stack();
    errors += T_token_stack_push();
    errors += T_token_stack_multi_push();
    errors += T_token_stack_push_no_type();
    errors += T_token_stack_push_null_token();
    errors += T_token_stack_push_null_stack();
    errors += T_token_stack_pop();
    errors += T_token_stack_pop_null_stack();
    errors += T_token_stack_pop_empty_stack();
    errors += T_token_stack_complex_test();
    printf("\nRunning char stack tests...\n");
    errors += T_char_stack_init();
    errors += T_char_stack_init_fail();
    errors += T_char_stack_get_head_fail();
    errors += T_char_stack_get_head_null_stack();
    errors += T_char_stack_push();
    errors += T_char_stack_multi_push();
    errors += T_char_stack_push_null_stack();
    errors += T_char_stack_pop();
    errors += T_char_stack_pop_null_stack();
    errors += T_char_stack_pop_empty_stack();
    errors += T_char_stack_complex_test();
    errors += T_char_stack_get_closest_terminal();
    errors += T_char_stack_get_closest_terminal_stack_bottom();
    errors += T_char_stack_get_closest_terminal_null_stack();
    errors += T_char_stack_push_shift();
    errors += T_char_stack_push_shift_top_terminal();
    errors += T_char_stack_push_shift_stack_bottom();
    errors += T_char_stack_push_shift_null_stack();
    return errors;
}
