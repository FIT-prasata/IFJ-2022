#include "../stack.h"
#include "test_utils.h"


#define STACK_INIT                     \
    Token_stack_t test_token_stack;   \
    token_stack_init(&test_token_stack);

#define STACK_FREE                      \
    token_stack_clear(&test_token_stack);

TEST(T_token_stack_init)
Token_stack_t test_token_stack;
int r;
ASSERT_TRUE((r = token_stack_init(&test_token_stack)) != INTERNAL_ERR)
STACK_FREE
ENDTEST

TEST(T_token_stack_init_fail)
int r;
ASSERT_TRUE((r = token_stack_init(NULL)) == INTERNAL_ERR)
ENDTEST

TEST(T_token_stack_get_head_fail)
STACK_INIT
ASSERT_TRUE(token_stack_get_head(&test_token_stack) == NO_TYPE)
STACK_FREE
ENDTEST

TEST(T_token_stack_get_head_null_stack)
ASSERT_TRUE(token_stack_get_head(NULL) == INTERNAL_ERR)
ENDTEST

TEST(T_token_stack_push)
STACK_INIT
Token_t *test_token = malloc(sizeof(Token_t));
test_token->type = T_ID;
ASSERT_TRUE(token_stack_push(&test_token_stack, test_token) != INTERNAL_ERR)
ASSERT_TRUE(token_stack_get_head(&test_token_stack) == T_ID)
STACK_FREE
ENDTEST

TEST(T_token_stack_multi_push)
STACK_INIT
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
STACK_FREE
ENDTEST

TEST(T_token_stack_push_no_type)
STACK_INIT
Token_t *test_token = malloc(sizeof(Token_t));
test_token->type = NO_TYPE;
ASSERT_TRUE(token_stack_push(&test_token_stack, test_token) == INTERNAL_ERR)
STACK_FREE
ENDTEST

TEST(T_token_stack_push_null_token)
STACK_INIT
ASSERT_TRUE(token_stack_push(&test_token_stack, NULL) == INTERNAL_ERR)
STACK_FREE
ENDTEST

TEST(T_token_stack_push_null_stack)
Token_t *test_token = malloc(sizeof(Token_t));
test_token->type = T_ID;
ASSERT_TRUE(token_stack_push(NULL, test_token) == INTERNAL_ERR)
ENDTEST

TEST(T_token_stack_pop)
STACK_INIT
Token_t *test_token = malloc(sizeof(Token_t));
test_token->type = T_ID;
Token_t *test_token2 = malloc(sizeof(Token_t));
test_token2->type = T_MUL;
ASSERT_TRUE(token_stack_push(&test_token_stack, test_token) != INTERNAL_ERR)
ASSERT_TRUE(token_stack_push(&test_token_stack, test_token2) != INTERNAL_ERR)
ASSERT_TRUE(token_stack_pop(&test_token_stack) == T_MUL)
ASSERT_TRUE(token_stack_get_head(&test_token_stack) == T_ID)
STACK_FREE
ENDTEST

TEST(T_token_stack_pop_null_stack)
ASSERT_TRUE(token_stack_pop(NULL) == INTERNAL_ERR)
ENDTEST

int run_stack_tests() {
    int errors = 0;
    printf("Running stack tests...\n");
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
    return errors;
}
