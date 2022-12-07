// Filename: stack.c
// IFJ 2022/2023 project
// TRP variant
//
// Stack implementation for expression parsing
//
// Author: <xsklen14> - David Sklenář
// Author: <xproch0o> - Marek Procházka
// Author: <xzavad20> - Lukáš Zavadil
// Author: <xsvetl07> - Adam Světlík

// LOCAL INCLUDES
#include "stack.h"

// TOKEN STACK

int token_stack_init(Token_stack_t *t_stack) {
    if (t_stack == NULL) {
        return INTERNAL_ERR;
    }
    t_stack->token_head.type = NO_TYPE;
    t_stack->next_token = NULL;
    return OK;
}

T_type_t token_stack_get_head(Token_stack_t *t_stack) {
    if (t_stack == NULL) {
        return INTERNAL_ERR;
    }
    return t_stack->token_head.type;
}

int token_stack_push(Token_stack_t *t_stack, Token_t *token) {
    Token_stack_t *tmp = (Token_stack_t *)malloc(sizeof(Token_stack_t));
    if (tmp == NULL || token == NULL || token->type == NO_TYPE || t_stack == NULL) return INTERNAL_ERR;
    tmp->token_head = t_stack->token_head;
    tmp->next_token = t_stack->next_token;
    t_stack->token_head = *token;
    t_stack->next_token = tmp;
    return OK;
}

T_type_t token_stack_pop(Token_stack_t *t_stack, Token_t *token) {
    if (t_stack == NULL) {
        return INTERNAL_ERR;
    }
    if (t_stack->token_head.type == NO_TYPE) {
        return TOKEN_EMPTY_STACK;
    }
    *token = t_stack->token_head;
    T_type_t result = t_stack->token_head.type;
    Token_stack_t *tmp = t_stack;
    t_stack->token_head = t_stack->next_token->token_head;
    t_stack->next_token = t_stack->next_token->next_token;
    free(tmp);
    return result;
}

void token_stack_clear(Token_stack_t *t_stack) {
    Token_t *token = (Token_t *)malloc(sizeof(Token_t));
    while (token_stack_pop(t_stack, token) != TOKEN_EMPTY_STACK){
        free(token);
        Token_t *token = (Token_t *)malloc(sizeof(Token_t));
    }
    free(token);
}

// CHARACTER STACK

char all_terminals[TERMINALS_NUM] = {EXPR_STACK_BOTTOM, EXPR_ID, EXPR_ADD, EXPR_SUB, EXPR_MUL, EXPR_DIV, EXPR_DOT, EXPR_EQ,
                                     EXPR_NEQ,          EXPR_LT, EXPR_GT,  EXPR_LE,  EXPR_GE,  EXPR_LBR, EXPR_RBR};

int char_stack_init(Char_stack_t *c_stack) {
    if (c_stack == NULL) {
        return INTERNAL_ERR;
    }
    c_stack->char_head = CHAR_STACK_BOTTOM;
    c_stack->next_char = NULL;
    return OK;
}

char char_stack_get_head(Char_stack_t *c_stack) {
    if (c_stack == NULL) {
        return INTERNAL_ERR;
    }
    return c_stack->char_head;
}

int char_stack_push(Char_stack_t *c_stack, char character) {
    Char_stack_t *tmp = (Char_stack_t *)malloc(sizeof(Char_stack_t));
    if (tmp == NULL || c_stack == NULL)
        return INTERNAL_ERR;
    tmp->char_head = c_stack->char_head;
    tmp->next_char = c_stack->next_char;
    c_stack->char_head = character;
    c_stack->next_char = tmp;
    return OK;
}

char char_stack_pop(Char_stack_t *c_stack) {
    if (c_stack == NULL) {
        return INTERNAL_ERR;
    }
    if (c_stack->char_head == CHAR_STACK_BOTTOM) {
        return EXPR_STACK_BOTTOM;
    }
    char result = c_stack->char_head;
    Char_stack_t *tmp = c_stack->next_char;
    c_stack->char_head = c_stack->next_char->char_head;
    c_stack->next_char = c_stack->next_char->next_char;
    free(tmp);
    return result;
}

void char_stack_clear(Char_stack_t *c_stack) {
    while (char_stack_pop(c_stack) != EXPR_STACK_BOTTOM)
        ;
}

ptable_symbol_t char_stack_get_closest_terminal(Char_stack_t *c_stack) {
    if (c_stack == NULL) {
        return INTERNAL_ERR;
    }
    while (char_stack_get_head(c_stack) != CHAR_STACK_BOTTOM) {
        for (int i = 0; i < TERMINALS_NUM; i++) {
            if (c_stack->char_head == all_terminals[i]) {
                return c_stack->char_head;
            }
        }
        c_stack = c_stack->next_char;
    }
    return EXPR_STACK_BOTTOM;
}

int char_stack_push_shift(Char_stack_t *c_stack) {
    if (c_stack == NULL) {
        return INTERNAL_ERR;
    }
    Char_stack_t *prev = c_stack;
    bool is_first_term = true;
    while (char_stack_get_head(c_stack) != CHAR_STACK_BOTTOM) {
        for (int i = 0; i < TERMINALS_NUM; i++) {
            if (c_stack->char_head == all_terminals[i]) {
                Char_stack_t *tmp = malloc(sizeof(Char_stack_t));
                if (tmp == NULL) return INTERNAL_ERR;
                if (is_first_term != true) {
                    prev->next_char = tmp;
                    tmp->char_head = '[';
                    tmp->next_char = c_stack;
                } else {
                    char_stack_push(c_stack, '[');
                }
                return OK;
            }
        }
        is_first_term = false;
        prev = c_stack;
        c_stack = c_stack->next_char;
    }
    char_stack_push(c_stack, '[');
    return OK;
}