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

TEST(T_expr_shift)
Char_stack_t test_char_stack;      
char_stack_init(&test_char_stack);
char_stack_push(&test_char_stack, 'E');
char_stack_push(&test_char_stack, EXPR_ADD);
char_stack_push(&test_char_stack, 'E');
ASSERT_TRUE(expr_shift(&test_char_stack, EXPR_ID) == OK)
ASSERT_TRUE(char_stack_pop(&test_char_stack) == EXPR_ID)
ASSERT_TRUE(char_stack_pop(&test_char_stack) == 'E')
ASSERT_TRUE(char_stack_pop(&test_char_stack) == '[')
ASSERT_TRUE(char_stack_pop(&test_char_stack) == EXPR_ADD)
ASSERT_TRUE(char_stack_pop(&test_char_stack) == 'E')
ASSERT_TRUE(char_stack_pop(&test_char_stack) == CHAR_STACK_POP_ERR)
char_stack_clear(&test_char_stack);
ENDTEST

TEST(T_expr_shift_stack_bottom)
Char_stack_t test_char_stack;
char_stack_init(&test_char_stack);
ASSERT_TRUE(expr_shift(&test_char_stack, EXPR_ID) == OK)
ASSERT_TRUE(char_stack_pop(&test_char_stack) == EXPR_ID)
ASSERT_TRUE(char_stack_pop(&test_char_stack) == '[')
ASSERT_TRUE(char_stack_pop(&test_char_stack) == CHAR_STACK_POP_ERR)
char_stack_clear(&test_char_stack);
ENDTEST

TEST(T_expr_shift_null_stack)
ASSERT_TRUE(expr_shift(NULL, EXPR_ID) == INTERNAL_ERR)
ENDTEST

TEST(T_expr_is_valid_rule)
DString_t d_string;
d_string_init(&d_string);
d_string_add_char(&d_string, 'E');
d_string_add_char(&d_string, EXPR_ADD);
d_string_add_char(&d_string, 'E');
ASSERT_TRUE(is_valid_rule(&d_string) == OK)
d_string_clear(&d_string);
d_string_add_char(&d_string, 'E');
d_string_add_char(&d_string, EXPR_SUB);
d_string_add_char(&d_string, 'E');
ASSERT_TRUE(is_valid_rule(&d_string) == OK)
d_string_clear(&d_string);
d_string_add_char(&d_string, 'E');
d_string_add_char(&d_string, EXPR_MUL);
d_string_add_char(&d_string, 'E');
ASSERT_TRUE(is_valid_rule(&d_string) == OK)
d_string_clear(&d_string);
d_string_add_char(&d_string, 'E');
d_string_add_char(&d_string, EXPR_DIV);
d_string_add_char(&d_string, 'E');
ASSERT_TRUE(is_valid_rule(&d_string) == OK)
d_string_clear(&d_string);
d_string_add_char(&d_string, 'E');
d_string_add_char(&d_string, EXPR_DOT);
d_string_add_char(&d_string, 'E');
ASSERT_TRUE(is_valid_rule(&d_string) == OK)
d_string_clear(&d_string);
d_string_add_char(&d_string, 'E');
d_string_add_char(&d_string, EXPR_EQ);
d_string_add_char(&d_string, 'E');
ASSERT_TRUE(is_valid_rule(&d_string) == OK)
d_string_clear(&d_string);
d_string_add_char(&d_string, 'E');
d_string_add_char(&d_string, EXPR_NEQ);
d_string_add_char(&d_string, 'E');
ASSERT_TRUE(is_valid_rule(&d_string) == OK)
d_string_clear(&d_string);
d_string_add_char(&d_string, 'E');
d_string_add_char(&d_string, EXPR_LT);
d_string_add_char(&d_string, 'E');
ASSERT_TRUE(is_valid_rule(&d_string) == OK)
d_string_clear(&d_string);
d_string_add_char(&d_string, 'E');
d_string_add_char(&d_string, EXPR_GT);
d_string_add_char(&d_string, 'E');
ASSERT_TRUE(is_valid_rule(&d_string) == OK)
d_string_clear(&d_string);
d_string_add_char(&d_string, 'E');
d_string_add_char(&d_string, EXPR_LE);
d_string_add_char(&d_string, 'E');
ASSERT_TRUE(is_valid_rule(&d_string) == OK)
d_string_clear(&d_string);
d_string_add_char(&d_string, 'E');
d_string_add_char(&d_string, EXPR_GE);
d_string_add_char(&d_string, 'E');
ASSERT_TRUE(is_valid_rule(&d_string) == OK)
d_string_clear(&d_string);
d_string_add_char(&d_string, EXPR_LBR);
d_string_add_char(&d_string, 'E');
d_string_add_char(&d_string, EXPR_RBR);
ASSERT_TRUE(is_valid_rule(&d_string) == OK)
d_string_clear(&d_string);
d_string_add_char(&d_string, EXPR_ID);
ASSERT_TRUE(is_valid_rule(&d_string) == OK)
d_string_clear(&d_string);
ENDTEST

TEST(T_expr_reduce)
Char_stack_t test_char_stack;
char_stack_init(&test_char_stack);
char_stack_push(&test_char_stack, 'E');
char_stack_push(&test_char_stack, EXPR_ADD);
char_stack_push(&test_char_stack, 'E');
ASSERT_TRUE(expr_reduce(&test_char_stack) == OK)
ASSERT_TRUE(char_stack_pop(&test_char_stack) == 'E')
ASSERT_TRUE(char_stack_pop(&test_char_stack) == CHAR_STACK_POP_ERR)
char_stack_clear(&test_char_stack);
char_stack_push(&test_char_stack, 'E');
char_stack_push(&test_char_stack, EXPR_SUB);
char_stack_push(&test_char_stack, 'E');
ASSERT_TRUE(expr_reduce(&test_char_stack) == OK)
ASSERT_TRUE(char_stack_pop(&test_char_stack) == 'E')
ASSERT_TRUE(char_stack_pop(&test_char_stack) == CHAR_STACK_POP_ERR)
char_stack_clear(&test_char_stack);
char_stack_push(&test_char_stack, 'E');
char_stack_push(&test_char_stack, EXPR_MUL);
char_stack_push(&test_char_stack, 'E');
ASSERT_TRUE(expr_reduce(&test_char_stack) == OK)
ASSERT_TRUE(char_stack_pop(&test_char_stack) == 'E')
ASSERT_TRUE(char_stack_pop(&test_char_stack) == CHAR_STACK_POP_ERR)
char_stack_clear(&test_char_stack);
char_stack_push(&test_char_stack, 'E');
char_stack_push(&test_char_stack, EXPR_DIV);
char_stack_push(&test_char_stack, 'E');
ASSERT_TRUE(expr_reduce(&test_char_stack) == OK)
ASSERT_TRUE(char_stack_pop(&test_char_stack) == 'E')
ASSERT_TRUE(char_stack_pop(&test_char_stack) == CHAR_STACK_POP_ERR)
char_stack_clear(&test_char_stack);
char_stack_push(&test_char_stack, 'E');
char_stack_push(&test_char_stack, EXPR_DOT);
char_stack_push(&test_char_stack, 'E');
ASSERT_TRUE(expr_reduce(&test_char_stack) == OK)
ASSERT_TRUE(char_stack_pop(&test_char_stack) == 'E')
ASSERT_TRUE(char_stack_pop(&test_char_stack) == CHAR_STACK_POP_ERR)
char_stack_clear(&test_char_stack);
char_stack_push(&test_char_stack, 'E');
char_stack_push(&test_char_stack, EXPR_EQ);
char_stack_push(&test_char_stack, 'E');
ASSERT_TRUE(expr_reduce(&test_char_stack) == OK)
ASSERT_TRUE(char_stack_pop(&test_char_stack) == 'E')
ASSERT_TRUE(char_stack_pop(&test_char_stack) == CHAR_STACK_POP_ERR)
char_stack_clear(&test_char_stack);
char_stack_push(&test_char_stack, 'E');
char_stack_push(&test_char_stack, EXPR_NEQ);
char_stack_push(&test_char_stack, 'E');
ASSERT_TRUE(expr_reduce(&test_char_stack) == OK)
ASSERT_TRUE(char_stack_pop(&test_char_stack) == 'E')
ASSERT_TRUE(char_stack_pop(&test_char_stack) == CHAR_STACK_POP_ERR)
char_stack_clear(&test_char_stack);
char_stack_push(&test_char_stack, 'E');
char_stack_push(&test_char_stack, EXPR_LT);
char_stack_push(&test_char_stack, 'E');
ASSERT_TRUE(expr_reduce(&test_char_stack) == OK)
ASSERT_TRUE(char_stack_pop(&test_char_stack) == 'E')
ASSERT_TRUE(char_stack_pop(&test_char_stack) == CHAR_STACK_POP_ERR)
char_stack_clear(&test_char_stack);
char_stack_push(&test_char_stack, 'E');
char_stack_push(&test_char_stack, EXPR_GT);
char_stack_push(&test_char_stack, 'E');
ASSERT_TRUE(expr_reduce(&test_char_stack) == OK)
ASSERT_TRUE(char_stack_pop(&test_char_stack) == 'E')
ASSERT_TRUE(char_stack_pop(&test_char_stack) == CHAR_STACK_POP_ERR)
char_stack_clear(&test_char_stack);
char_stack_push(&test_char_stack, 'E');
char_stack_push(&test_char_stack, EXPR_LE);
char_stack_push(&test_char_stack, 'E');
ASSERT_TRUE(expr_reduce(&test_char_stack) == OK)
ASSERT_TRUE(char_stack_pop(&test_char_stack) == 'E')
ASSERT_TRUE(char_stack_pop(&test_char_stack) == CHAR_STACK_POP_ERR)
char_stack_clear(&test_char_stack);
char_stack_push(&test_char_stack, 'E');
char_stack_push(&test_char_stack, EXPR_GE);
char_stack_push(&test_char_stack, 'E');
ASSERT_TRUE(expr_reduce(&test_char_stack) == OK)
ASSERT_TRUE(char_stack_pop(&test_char_stack) == 'E')
ASSERT_TRUE(char_stack_pop(&test_char_stack) == CHAR_STACK_POP_ERR)
char_stack_clear(&test_char_stack);
char_stack_push(&test_char_stack, EXPR_LBR);
char_stack_push(&test_char_stack, 'E');
char_stack_push(&test_char_stack, EXPR_RBR);
ASSERT_TRUE(expr_reduce(&test_char_stack) == OK)
ASSERT_TRUE(char_stack_pop(&test_char_stack) == 'E')
ASSERT_TRUE(char_stack_pop(&test_char_stack) == CHAR_STACK_POP_ERR)
char_stack_clear(&test_char_stack);
char_stack_push(&test_char_stack, EXPR_ID);
ASSERT_TRUE(expr_reduce(&test_char_stack) == OK)
ASSERT_TRUE(char_stack_pop(&test_char_stack) == 'E')
ASSERT_TRUE(char_stack_pop(&test_char_stack) == CHAR_STACK_POP_ERR)
char_stack_clear(&test_char_stack);
ENDTEST


TEST(T_expr_special_shift)
Char_stack_t test_char_stack;
char_stack_init(&test_char_stack);
char_stack_push(&test_char_stack, 'E');
char_stack_push(&test_char_stack, EXPR_ADD);
char_stack_push(&test_char_stack, 'E');
ASSERT_TRUE(expr_special_shift(&test_char_stack, EXPR_RBR) == OK)
ASSERT_TRUE(char_stack_pop(&test_char_stack) == EXPR_RBR)
ASSERT_TRUE(char_stack_pop(&test_char_stack) == 'E')
ASSERT_TRUE(char_stack_pop(&test_char_stack) == EXPR_ADD)
ASSERT_TRUE(char_stack_pop(&test_char_stack) == 'E')
ASSERT_TRUE(char_stack_pop(&test_char_stack) == CHAR_STACK_POP_ERR)
char_stack_clear(&test_char_stack);
ENDTEST

TEST(T_expr_special_shift_stack_bottom)
Char_stack_t test_char_stack;
char_stack_init(&test_char_stack);
ASSERT_TRUE(expr_special_shift(&test_char_stack, EXPR_RBR) == OK)
ASSERT_TRUE(char_stack_pop(&test_char_stack) == EXPR_RBR)
ASSERT_TRUE(char_stack_pop(&test_char_stack) == CHAR_STACK_POP_ERR)
char_stack_clear(&test_char_stack);
ENDTEST

TEST(T_expr_special_shift_null_stack)
ASSERT_TRUE(expr_special_shift(NULL, EXPR_RBR) == INTERNAL_ERR)
ENDTEST

TEST(T_expr_parse)
Char_stack_t test_char_stack;
char_stack_init(&test_char_stack);
Token_stack_t test_token_stack;
token_stack_init(&test_token_stack);
Token_t test_token;
test_token.type = T_ID;
int location = EXPR_LOC_ASSIGN;
ASSERT_TRUE(expr_parse(&test_char_stack, &test_token_stack, &test_token, location) == OK)
ASSERT_TRUE(char_stack_pop(&test_char_stack) == EXPR_ID)
ASSERT_TRUE(char_stack_pop(&test_char_stack) == '[')
ASSERT_TRUE(char_stack_pop(&test_char_stack) == EXPR_STACK_BOTTOM)
ENDTEST

TEST(T_expr_parse_sem)
Char_stack_t test_char_stack;
char_stack_init(&test_char_stack);
Token_stack_t test_token_stack;
token_stack_init(&test_token_stack);
Token_t test_token;
test_token.type = T_SEM;
int location = EXPR_LOC_ASSIGN;
ASSERT_TRUE(expr_parse(&test_char_stack, &test_token_stack, &test_token, location) == EOEXPR)
ASSERT_TRUE(char_stack_pop(&test_char_stack) == EXPR_STACK_BOTTOM)
ENDTEST

TEST(T_expr_parse_logical_operator_in_assignment)
Char_stack_t test_char_stack;
char_stack_init(&test_char_stack);
Token_stack_t test_token_stack;
token_stack_init(&test_token_stack);
Token_t test_token;
test_token.type = T_EQ;
int location = EXPR_LOC_ASSIGN;
ASSERT_TRUE(expr_parse(&test_char_stack, &test_token_stack, &test_token, location) == SYNTAX_ERR)
ASSERT_TRUE(char_stack_pop(&test_char_stack) == EXPR_STACK_BOTTOM)
ENDTEST

TEST(T_expr_parse_add)
Char_stack_t test_char_stack;
char_stack_init(&test_char_stack);
Token_stack_t test_token_stack;
token_stack_init(&test_token_stack);
Token_t test_token;
test_token.type = T_ID;
Token_t test_token2;
test_token2.type = T_ADD;
Token_t test_token3;
test_token3.type = T_ID;
Token_t test_token4;
test_token4.type = T_SEM;
Token_t test_token5;
test_token5.type = EOEXPR;
int location = EXPR_LOC_ASSIGN;
ASSERT_TRUE(expr_parse(&test_char_stack, &test_token_stack, &test_token, location) == OK)
ASSERT_TRUE(char_stack_get_head(&test_char_stack) == EXPR_ID)
ASSERT_TRUE(expr_parse(&test_char_stack, &test_token_stack, &test_token2, location) == OK)
ASSERT_TRUE(char_stack_get_head(&test_char_stack) == EXPR_ADD)
ASSERT_TRUE(expr_parse(&test_char_stack, &test_token_stack, &test_token3, location) == OK)
ASSERT_TRUE(char_stack_get_head(&test_char_stack) == EXPR_ID)
ASSERT_TRUE(expr_parse(&test_char_stack, &test_token_stack, &test_token4, location) == EOEXPR)
ASSERT_TRUE(char_stack_get_head(&test_char_stack) == EXPR_ID)
ASSERT_TRUE(expr_parse(&test_char_stack, &test_token_stack, &test_token5, location) == OK)
ASSERT_TRUE(char_stack_pop(&test_char_stack) == 'E')
ASSERT_TRUE(char_stack_pop(&test_char_stack) == EXPR_STACK_BOTTOM)
ENDTEST

TEST(T_expr_parse_add_mul)
Char_stack_t test_char_stack;
char_stack_init(&test_char_stack);
Token_stack_t test_token_stack;
token_stack_init(&test_token_stack);
Token_t test_token;
test_token.type = T_ID;
Token_t test_token2;
test_token2.type = T_ADD;
Token_t test_token3;
test_token3.type = T_ID;
Token_t test_token4;
test_token4.type = T_MUL;
Token_t test_token5;
test_token5.type = T_ID;
Token_t test_token6;
test_token6.type = T_SEM;
Token_t test_token7;
test_token7.type = EOEXPR;
int location = EXPR_LOC_ASSIGN;
ASSERT_TRUE(expr_parse(&test_char_stack, &test_token_stack, &test_token, location) == OK)
ASSERT_TRUE(char_stack_get_head(&test_char_stack) == EXPR_ID)
ASSERT_TRUE(expr_parse(&test_char_stack, &test_token_stack, &test_token2, location) == OK)
ASSERT_TRUE(char_stack_get_head(&test_char_stack) == EXPR_ADD)
ASSERT_TRUE(expr_parse(&test_char_stack, &test_token_stack, &test_token3, location) == OK)
ASSERT_TRUE(char_stack_get_head(&test_char_stack) == EXPR_ID)
ASSERT_TRUE(expr_parse(&test_char_stack, &test_token_stack, &test_token4, location) == OK)
ASSERT_TRUE(char_stack_get_head(&test_char_stack) == EXPR_MUL)
ASSERT_TRUE(expr_parse(&test_char_stack, &test_token_stack, &test_token5, location) == OK)
ASSERT_TRUE(char_stack_get_head(&test_char_stack) == EXPR_ID)
ASSERT_TRUE(expr_parse(&test_char_stack, &test_token_stack, &test_token6, location) == EOEXPR)
ASSERT_TRUE(char_stack_get_head(&test_char_stack) == EXPR_ID)
ASSERT_TRUE(expr_parse(&test_char_stack, &test_token_stack, &test_token7, location) == OK)
ASSERT_TRUE(char_stack_pop(&test_char_stack) == 'E')
ASSERT_TRUE(char_stack_pop(&test_char_stack) == EXPR_STACK_BOTTOM)
ENDTEST

TEST(T_expr_parse_simple_assign)
Char_stack_t test_char_stack;
char_stack_init(&test_char_stack);
Token_stack_t test_token_stack;
token_stack_init(&test_token_stack);
Token_t test_token;
test_token.type = T_ID;
Token_t test_token2;
test_token2.type = T_SEM;
Token_t test_token3;
test_token3.type = EOEXPR;
int location = EXPR_LOC_ASSIGN;
ASSERT_TRUE(expr_parse(&test_char_stack, &test_token_stack, &test_token, location) == OK)
ASSERT_TRUE(char_stack_get_head(&test_char_stack) == EXPR_ID)
ASSERT_TRUE(expr_parse(&test_char_stack, &test_token_stack, &test_token2, location) == EOEXPR)
ASSERT_TRUE(expr_parse(&test_char_stack, &test_token_stack, &test_token3, location) == OK)
ASSERT_TRUE(char_stack_pop(&test_char_stack) == 'E')
ASSERT_TRUE(char_stack_pop(&test_char_stack) == EXPR_STACK_BOTTOM)
ENDTEST

TEST(T_expr_parse_parentheses)
Char_stack_t test_char_stack;
char_stack_init(&test_char_stack);
Token_stack_t test_token_stack;
token_stack_init(&test_token_stack);
Token_t test_token;
test_token.type = T_LBR;
Token_t test_token2;
test_token2.type = T_ID;
Token_t test_token3;
test_token3.type = T_RBR;
Token_t test_token4;
test_token4.type = T_SEM;
Token_t test_token5;
test_token5.type = EOEXPR;
int location = EXPR_LOC_ASSIGN;
ASSERT_TRUE(expr_parse(&test_char_stack, &test_token_stack, &test_token, location) == OK)
ASSERT_TRUE(char_stack_get_head(&test_char_stack) == EXPR_LBR)
ASSERT_TRUE(expr_parse(&test_char_stack, &test_token_stack, &test_token2, location) == OK)
ASSERT_TRUE(char_stack_get_head(&test_char_stack) == EXPR_ID)
ASSERT_TRUE(expr_parse(&test_char_stack, &test_token_stack, &test_token3, location) == OK)
ASSERT_TRUE(char_stack_get_head(&test_char_stack) == EXPR_RBR)
ASSERT_TRUE(expr_parse(&test_char_stack, &test_token_stack, &test_token4, location) == EOEXPR)
ASSERT_TRUE(expr_parse(&test_char_stack, &test_token_stack, &test_token5, location) == OK)
ASSERT_TRUE(char_stack_pop(&test_char_stack) == 'E')
ASSERT_TRUE(char_stack_pop(&test_char_stack) == EXPR_STACK_BOTTOM)
ENDTEST

TEST(T_expr_parse_complex_arithmetic)
Char_stack_t test_char_stack;
char_stack_init(&test_char_stack);
Token_stack_t test_token_stack;
token_stack_init(&test_token_stack);
Token_t test_token;
test_token.type = T_ID;
Token_t test_token2;
test_token2.type = T_MUL;
Token_t test_token3;
test_token3.type = T_LBR;
Token_t test_token4;
test_token4.type = T_ID;
Token_t test_token5;
test_token5.type = T_ADD;
Token_t test_token6;
test_token6.type = T_ID;
Token_t test_token7;
test_token7.type = T_RBR;
Token_t test_token8;
test_token8.type = T_SUB;
Token_t test_token9;
test_token9.type = T_ID;
Token_t test_token10;
test_token10.type = T_SEM;
Token_t test_token11;
test_token11.type = EOEXPR;
int location = EXPR_LOC_ASSIGN;
ASSERT_TRUE(expr_parse(&test_char_stack, &test_token_stack, &test_token, location) == OK)
ASSERT_TRUE(char_stack_get_head(&test_char_stack) == EXPR_ID)
ASSERT_TRUE(expr_parse(&test_char_stack, &test_token_stack, &test_token2, location) == OK)
ASSERT_TRUE(char_stack_get_head(&test_char_stack) == EXPR_MUL)
ASSERT_TRUE(expr_parse(&test_char_stack, &test_token_stack, &test_token3, location) == OK)
ASSERT_TRUE(char_stack_get_head(&test_char_stack) == EXPR_LBR)
ASSERT_TRUE(expr_parse(&test_char_stack, &test_token_stack, &test_token4, location) == OK)
ASSERT_TRUE(char_stack_get_head(&test_char_stack) == EXPR_ID)
ASSERT_TRUE(expr_parse(&test_char_stack, &test_token_stack, &test_token5, location) == OK)
ASSERT_TRUE(char_stack_get_head(&test_char_stack) == EXPR_ADD)
ASSERT_TRUE(expr_parse(&test_char_stack, &test_token_stack, &test_token6, location) == OK)
ASSERT_TRUE(char_stack_get_head(&test_char_stack) == EXPR_ID)
ASSERT_TRUE(expr_parse(&test_char_stack, &test_token_stack, &test_token7, location) == OK)
ASSERT_TRUE(char_stack_get_head(&test_char_stack) == EXPR_RBR)
ASSERT_TRUE(expr_parse(&test_char_stack, &test_token_stack, &test_token8, location) == OK)
ASSERT_TRUE(char_stack_get_head(&test_char_stack) == EXPR_SUB)
ASSERT_TRUE(expr_parse(&test_char_stack, &test_token_stack, &test_token9, location) == OK)
ASSERT_TRUE(char_stack_get_head(&test_char_stack) == EXPR_ID)
ASSERT_TRUE(expr_parse(&test_char_stack, &test_token_stack, &test_token10, location) == EOEXPR)
ASSERT_TRUE(expr_parse(&test_char_stack, &test_token_stack, &test_token11, location) == OK)
ASSERT_TRUE(char_stack_pop(&test_char_stack) == 'E')
ASSERT_TRUE(char_stack_pop(&test_char_stack) == EXPR_STACK_BOTTOM)
ENDTEST

TEST(T_expr_parse_invalid)
Char_stack_t test_char_stack;
char_stack_init(&test_char_stack);
Token_stack_t test_token_stack;
token_stack_init(&test_token_stack);
Token_t test_token;
test_token.type = T_ID;
Token_t test_token2;
test_token2.type = T_MUL;
Token_t test_token3;
test_token3.type = T_ADD;
int location = EXPR_LOC_ASSIGN;
ASSERT_TRUE(expr_parse(&test_char_stack, &test_token_stack, &test_token, location) == OK)
ASSERT_TRUE(char_stack_get_head(&test_char_stack) == EXPR_ID)
ASSERT_TRUE(expr_parse(&test_char_stack, &test_token_stack, &test_token2, location) == OK)
ASSERT_TRUE(char_stack_get_head(&test_char_stack) == EXPR_MUL)
ASSERT_TRUE(expr_parse(&test_char_stack, &test_token_stack, &test_token3, location) == SYNTAX_ERR)
ENDTEST

TEST(T_expr_parse_basic_cond)
Char_stack_t test_char_stack;
char_stack_init(&test_char_stack);
Token_stack_t test_token_stack;
token_stack_init(&test_token_stack);
Token_t test_token;
test_token.type = T_ID;
Token_t test_token2;
test_token2.type = T_EQ;
Token_t test_token3;
test_token3.type = T_ID;
Token_t test_token4;
test_token4.type = T_SEM;
Token_t test_token5;
test_token5.type = EOEXPR;
int location = EXPR_LOC_RET;
ASSERT_TRUE(expr_parse(&test_char_stack, &test_token_stack, &test_token, location) == OK)
ASSERT_TRUE(char_stack_get_head(&test_char_stack) == EXPR_ID)
ASSERT_TRUE(expr_parse(&test_char_stack, &test_token_stack, &test_token2, location) == OK)
ASSERT_TRUE(char_stack_get_head(&test_char_stack) == EXPR_EQ)
ASSERT_TRUE(expr_parse(&test_char_stack, &test_token_stack, &test_token3, location) == OK)
ASSERT_TRUE(char_stack_get_head(&test_char_stack) == EXPR_ID)
ASSERT_TRUE(expr_parse(&test_char_stack, &test_token_stack, &test_token4, location) == EOEXPR)
ASSERT_TRUE(expr_parse(&test_char_stack, &test_token_stack, &test_token5, location) == OK)
ASSERT_TRUE(char_stack_pop(&test_char_stack) == 'E')
ASSERT_TRUE(char_stack_pop(&test_char_stack) == EXPR_STACK_BOTTOM)
ENDTEST

int run_expr_tests() {
    int errors = 0;
    printf("Running expression parser tests...\n");
    errors += T_expr_get_next_move_complex();
    errors += T_expr_shift();
    errors += T_expr_shift_stack_bottom();
    errors += T_expr_shift_null_stack();
    errors += T_expr_is_valid_rule();
    errors += T_expr_reduce();
    errors += T_expr_special_shift();
    errors += T_expr_special_shift_stack_bottom();
    errors += T_expr_special_shift_null_stack();
    errors += T_expr_parse();
    errors += T_expr_parse_sem();
    errors += T_expr_parse_logical_operator_in_assignment();
    errors += T_expr_parse_add();
    errors += T_expr_parse_add_mul();
    errors += T_expr_parse_simple_assign();
    errors += T_expr_parse_parentheses();
    errors += T_expr_parse_complex_arithmetic();
    errors += T_expr_parse_invalid();
    errors += T_expr_parse_basic_cond();
    return errors;
}
