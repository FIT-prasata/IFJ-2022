#include "../expr.h"
#include "test_utils.h"

TEST(T_expr_get_next_move_complex)
ptable_symbol_t stack = EXPR_STACK_BOTTOM;
ptable_symbol_t input = EXPR_STACK_BOTTOM;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_ERROR);
input = EXPR_ID;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_SHIFT);
input = EXPR_ADD;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_SHIFT);
input = EXPR_SUB;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_SHIFT);
input = EXPR_MUL;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_SHIFT);
input = EXPR_DIV;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_SHIFT);
input = EXPR_DOT;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_SHIFT);
input = EXPR_EQ;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_SHIFT);
input = EXPR_NEQ;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_SHIFT);
input = EXPR_LT;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_SHIFT);
input = EXPR_GT;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_SHIFT);
input = EXPR_LE;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_SHIFT);
input = EXPR_GE;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_SHIFT);
input = EXPR_LBR;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_SHIFT);
input = EXPR_RBR;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_ERROR);
stack = EXPR_ID;
input = EXPR_STACK_BOTTOM;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_REDUCE);
input = EXPR_ID;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_ERROR);
input = EXPR_ADD;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_REDUCE);
input = EXPR_SUB;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_REDUCE);
input = EXPR_MUL;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_REDUCE);
input = EXPR_DIV;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_REDUCE);
input = EXPR_DOT;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_REDUCE);
input = EXPR_EQ;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_REDUCE);
input = EXPR_NEQ;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_REDUCE);
input = EXPR_LT;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_REDUCE);
input = EXPR_GT;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_REDUCE);
input = EXPR_LE;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_REDUCE);
input = EXPR_GE;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_REDUCE);
input = EXPR_LBR;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_ERROR);
input = EXPR_RBR;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_REDUCE);
stack = EXPR_ADD;
input = EXPR_STACK_BOTTOM;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_REDUCE);
input = EXPR_ID;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_SHIFT);
input = EXPR_ADD;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_REDUCE);
input = EXPR_SUB;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_REDUCE);
input = EXPR_MUL;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_SHIFT);
input = EXPR_DIV;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_SHIFT);
input = EXPR_DOT;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_REDUCE);
input = EXPR_EQ;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_REDUCE);
input = EXPR_NEQ;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_REDUCE);
input = EXPR_LT;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_REDUCE);
input = EXPR_GT;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_REDUCE);
input = EXPR_LE;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_REDUCE);
input = EXPR_GE;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_REDUCE);
input = EXPR_LBR;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_SHIFT);
input = EXPR_RBR;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_REDUCE);
stack = EXPR_SUB;
input = EXPR_STACK_BOTTOM;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_REDUCE);
input = EXPR_ID;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_SHIFT);
input = EXPR_ADD;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_REDUCE);
input = EXPR_SUB;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_REDUCE);
input = EXPR_MUL;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_SHIFT);
input = EXPR_DIV;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_SHIFT);
input = EXPR_DOT;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_REDUCE);
input = EXPR_EQ;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_REDUCE);
input = EXPR_NEQ;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_REDUCE);
input = EXPR_LT;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_REDUCE);
input = EXPR_GT;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_REDUCE);
input = EXPR_LE;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_REDUCE);
input = EXPR_GE;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_REDUCE);
input = EXPR_LBR;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_SHIFT);
input = EXPR_RBR;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_REDUCE);
stack = EXPR_MUL;
input = EXPR_STACK_BOTTOM;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_REDUCE);
input = EXPR_ID;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_SHIFT);
input = EXPR_ADD;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_REDUCE);
input = EXPR_SUB;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_REDUCE);
input = EXPR_MUL;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_REDUCE);
input = EXPR_DIV;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_REDUCE);
input = EXPR_DOT;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_REDUCE);
input = EXPR_EQ;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_REDUCE);
input = EXPR_NEQ;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_REDUCE);
input = EXPR_LT;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_REDUCE);
input = EXPR_GT;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_REDUCE);
input = EXPR_LE;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_REDUCE);
input = EXPR_GE;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_REDUCE);
input = EXPR_LBR;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_SHIFT);
input = EXPR_RBR;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_REDUCE);
stack = EXPR_DIV;
input = EXPR_STACK_BOTTOM;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_REDUCE);
input = EXPR_ID;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_SHIFT);
input = EXPR_ADD;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_REDUCE);
input = EXPR_SUB;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_REDUCE);
input = EXPR_MUL;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_REDUCE);
input = EXPR_DIV;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_REDUCE);
input = EXPR_DOT;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_REDUCE);
input = EXPR_EQ;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_REDUCE);
input = EXPR_NEQ;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_REDUCE);
input = EXPR_LT;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_REDUCE);
input = EXPR_GT;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_REDUCE);
input = EXPR_LE;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_REDUCE);
input = EXPR_GE;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_REDUCE);
input = EXPR_LBR;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_SHIFT);
input = EXPR_RBR;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_REDUCE);
stack = EXPR_DOT;
input = EXPR_STACK_BOTTOM;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_REDUCE);
input = EXPR_ID;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_SHIFT);
input = EXPR_ADD;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_REDUCE);
input = EXPR_SUB;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_REDUCE);
input = EXPR_MUL;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_SHIFT);
input = EXPR_DIV;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_SHIFT);
input = EXPR_DOT;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_REDUCE);
input = EXPR_EQ;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_REDUCE);
input = EXPR_NEQ;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_REDUCE);
input = EXPR_LT;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_REDUCE);
input = EXPR_GT;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_REDUCE);
input = EXPR_LE;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_REDUCE);
input = EXPR_GE;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_REDUCE);
input = EXPR_LBR;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_SHIFT);
input = EXPR_RBR;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_REDUCE);
stack = EXPR_EQ;
input = EXPR_STACK_BOTTOM;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_REDUCE);
input = EXPR_ID;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_SHIFT);
input = EXPR_ADD;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_SHIFT);
input = EXPR_SUB;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_SHIFT);
input = EXPR_MUL;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_SHIFT);
input = EXPR_DIV;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_SHIFT);
input = EXPR_DOT;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_SHIFT);
input = EXPR_EQ;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_ERROR);
input = EXPR_NEQ;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_ERROR);
input = EXPR_LT;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_ERROR);
input = EXPR_GT;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_ERROR);
input = EXPR_LE;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_ERROR);
input = EXPR_GE;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_ERROR);
input = EXPR_LBR;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_SHIFT);
input = EXPR_RBR;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_REDUCE);
stack = EXPR_NEQ;
input = EXPR_STACK_BOTTOM;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_REDUCE);
input = EXPR_ID;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_SHIFT);
input = EXPR_ADD;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_SHIFT);
input = EXPR_SUB;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_SHIFT);
input = EXPR_MUL;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_SHIFT);
input = EXPR_DIV;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_SHIFT);
input = EXPR_DOT;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_SHIFT);
input = EXPR_EQ;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_ERROR);
input = EXPR_NEQ;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_ERROR);
input = EXPR_LT;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_ERROR);
input = EXPR_GT;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_ERROR);
input = EXPR_LE;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_ERROR);
input = EXPR_GE;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_ERROR);
input = EXPR_LBR;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_SHIFT);
input = EXPR_RBR;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_REDUCE);
stack = EXPR_LT;
input = EXPR_STACK_BOTTOM;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_REDUCE);
input = EXPR_ID;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_SHIFT);
input = EXPR_ADD;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_SHIFT);
input = EXPR_SUB;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_SHIFT);
input = EXPR_MUL;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_SHIFT);
input = EXPR_DIV;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_SHIFT);
input = EXPR_DOT;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_SHIFT);
input = EXPR_EQ;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_ERROR);
input = EXPR_NEQ;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_ERROR);
input = EXPR_LT;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_ERROR);
input = EXPR_GT;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_ERROR);
input = EXPR_LE;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_ERROR);
input = EXPR_GE;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_ERROR);
input = EXPR_LBR;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_SHIFT);
input = EXPR_RBR;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_REDUCE);
stack = EXPR_GT;
input = EXPR_STACK_BOTTOM;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_REDUCE);
input = EXPR_ID;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_SHIFT);
input = EXPR_ADD;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_SHIFT);
input = EXPR_SUB;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_SHIFT);
input = EXPR_MUL;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_SHIFT);
input = EXPR_DIV;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_SHIFT);
input = EXPR_DOT;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_SHIFT);
input = EXPR_EQ;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_ERROR);
input = EXPR_NEQ;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_ERROR);
input = EXPR_LT;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_ERROR);
input = EXPR_GT;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_ERROR);
input = EXPR_LE;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_ERROR);
input = EXPR_GE;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_ERROR);
input = EXPR_LBR;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_SHIFT);
input = EXPR_RBR;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_REDUCE);
stack = EXPR_LE;
input = EXPR_STACK_BOTTOM;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_REDUCE);
input = EXPR_ID;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_SHIFT);
input = EXPR_ADD;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_SHIFT);
input = EXPR_SUB;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_SHIFT);
input = EXPR_MUL;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_SHIFT);
input = EXPR_DIV;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_SHIFT);
input = EXPR_DOT;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_SHIFT);
input = EXPR_EQ;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_ERROR);
input = EXPR_NEQ;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_ERROR);
input = EXPR_LT;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_ERROR);
input = EXPR_GT;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_ERROR);
input = EXPR_LE;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_ERROR);
input = EXPR_GE;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_ERROR);
input = EXPR_LBR;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_SHIFT);
input = EXPR_RBR;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_REDUCE);
stack = EXPR_GE;
input = EXPR_STACK_BOTTOM;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_REDUCE);
input = EXPR_ID;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_SHIFT);
input = EXPR_ADD;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_SHIFT);
input = EXPR_SUB;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_SHIFT);
input = EXPR_MUL;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_SHIFT);
input = EXPR_DIV;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_SHIFT);
input = EXPR_DOT;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_SHIFT);
input = EXPR_EQ;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_ERROR);
input = EXPR_NEQ;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_ERROR);
input = EXPR_LT;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_ERROR);
input = EXPR_GT;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_ERROR);
input = EXPR_LE;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_ERROR);
input = EXPR_GE;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_ERROR);
input = EXPR_LBR;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_SHIFT);
input = EXPR_RBR;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_REDUCE);
stack = EXPR_LBR;
input = EXPR_STACK_BOTTOM;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_ERROR);
input = EXPR_ID;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_SHIFT);
input = EXPR_ADD;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_SHIFT);
input = EXPR_SUB;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_SHIFT);
input = EXPR_MUL;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_SHIFT);
input = EXPR_DIV;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_SHIFT);
input = EXPR_DOT;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_SHIFT);
input = EXPR_EQ;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_SHIFT);
input = EXPR_NEQ;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_SHIFT);
input = EXPR_LT;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_SHIFT);
input = EXPR_GT;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_SHIFT);
input = EXPR_LE;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_SHIFT);
input = EXPR_GE;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_SHIFT);
input = EXPR_LBR;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_SHIFT);
input = EXPR_RBR;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_SPECIAL_SHIFT);
stack = EXPR_RBR;
input = EXPR_STACK_BOTTOM;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_REDUCE);
input = EXPR_ID;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_ERROR);
input = EXPR_ADD;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_REDUCE);
input = EXPR_SUB;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_REDUCE);
input = EXPR_MUL;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_REDUCE);
input = EXPR_DIV;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_REDUCE);
input = EXPR_DOT;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_REDUCE);
input = EXPR_EQ;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_REDUCE);
input = EXPR_NEQ;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_REDUCE);
input = EXPR_LT;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_REDUCE);
input = EXPR_GT;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_REDUCE);
input = EXPR_LE;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_REDUCE);
input = EXPR_GE;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_REDUCE);
input = EXPR_LBR;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_ERROR);
input = EXPR_RBR;
ASSERT_TRUE(ptable_get_next_move(stack, input) == EXPR_REDUCE);
ENDTEST

int run_expr_tests() {
    int errors = 0;
    printf("Running expression parser tests...\n");
    errors += T_expr_get_next_move_complex();
    return errors;
}
