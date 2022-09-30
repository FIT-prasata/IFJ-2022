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
void stack_init(Stack_t *stack) {
    stack->head.type = NO_TYPE;
    stack->next = NULL;
}

// Returns token that is currently on top of the stack
Token_t stack_get_head(Stack_t *stack) {
    return stack->head;
}

// Pushes token into the stack
void stack_push(Stack_t *stack, Token_t token) {
    Stack_t *tmp = (Stack_t *)malloc(sizeof(Stack_t));
    if (tmp == NULL) return;
    tmp->head = stack->head;
    tmp->next = stack->next;
    stack->head = token;
    stack->next = tmp;
}

// Pops token from the stack
int stack_pop(Stack_t *stack) {
    if (stack == NULL || stack->head.type == NO_TYPE) return EMPTY_STACK;
    int result = stack->head.type;
    Stack_t *tmp = stack->next;
    stack->head = stack->next->head;
    stack->next = stack->next->next;
    free(tmp);
    return result;
}

// Clears whole stack
void stack_clear(Stack_t *stack) {
    while (stack_pop(stack) != EMPTY_STACK);
}