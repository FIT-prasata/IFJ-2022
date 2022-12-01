// Filename: stack.c
// IFJ 2022/2023 project
// TRP variant
//
// Stack implementation for FA
//
// Author: <xsklen14> - David Sklenář
// Author: <xproch0o> - Marek Procházka
// Author: <xzavad20> - Lukáš Zavadil
// Author: <xsvetl07> - Adam Světlík

// LOCAL INCLUDES
#include "stack.h"


// Initializes stack
int token_stack_init(Token_stack_t *t_stack) {
    if (t_stack == NULL) {
        return INTERNAL_ERR;
    }
    t_stack->head.type = NO_TYPE;
    t_stack->next = NULL;
    return OK;
}

// Returns token that is currently on top of the stack
Token_t token_stack_get_head(Token_stack_t *t_stack) { return t_stack->head; }

// Pushes token into the stack
void token_stack_push(Token_stack_t *t_stack, Token_t token) {
    Token_stack_t *tmp = (Token_stack_t *)malloc(sizeof(Token_stack_t));
    if (tmp == NULL) return;
    tmp->head = t_stack->head;
    tmp->next = t_stack->next;
    t_stack->head = token;
    t_stack->next = tmp;
}

// Pops token from the stack
int token_stack_pop(Token_stack_t *t_stack) {
    if (t_stack == NULL || t_stack->head.type == NO_TYPE) return EMPTY_STACK;
    int result = t_stack->head.type;
    Token_stack_t *tmp = t_stack->next;
    t_stack->head = t_stack->next->head;
    t_stack->next = t_stack->next->next;
    free(tmp);
    return result;
}

// Clears whole stack
void token_stack_clear(Token_stack_t *t_stack) {
    while (token_stack_pop(t_stack) != EMPTY_STACK);
}
