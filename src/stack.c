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
int stack_push(Stack_t *stack, Token_t token) {
    Stack_t *tmp = (Stack_t *)malloc(sizeof(Stack_t));
    if (tmp == NULL) return NULL;
    tmp->head = stack->head;
    tmp->next = stack->next;
    stack->head = token;
    stack->next = tmp;
}

// Pops token from the stack
int stack_pop(Stack_t *stack) {
    if (stack == NULL || stack->head.type == NO_TYPE) return EMPTY_STACK;
    Stack_t *tmp = stack->next;
    stack->head = stack->next->head;
    stack->next = stack->next->next;
    free(tmp);
}

// Clears whole stack
void stack_clear(Stack_t *stack) {
    while (stack_pop(stack) != EMPTY_STACK);
}

// Testing
int main(void) {
    Stack_t stack;
    Token_t token1, token2, result;
    token1.type = 20;
    token2.type = 40;
    stack_init(&stack);
    stack_push(&stack, token1);
    result = stack_get_head(&stack);
    printf("Token: %d\n", result.type);
    stack_push(&stack, token2);
    result = stack_get_head(&stack);
    printf("Token: %d\n", result.type);
    stack_clear(&stack);
    result = stack_get_head(&stack);
    printf("Token: %d\n", result.type);
    return 0;
}
