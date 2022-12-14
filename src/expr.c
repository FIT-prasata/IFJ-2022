// Filename: expr.c
// IFJ 2022/2023 project
// TRP variant
//
// Bottom up parser
//
// Author: <xsklen14> - David Sklenář
// Author: <xproch0o> - Marek Procházka
// Author: <xzavad20> - Lukáš Zavadil
// Author: <xsvetl07> - Adam Světlík

// LOCAL INCLUDES
#include "expr.h"

// Precedence table
//
// [ - shift
// ] - reduce
// = - special shift
// ! - error
char ptable[P_TABLE_SIZE][P_TABLE_SIZE] = {
    /*
      STACK | INPUT -->
        |
        v       $    i    +    -    *    /    .   ===  !==   <    >    <=   >=
      (    ) */
    /*  $  */ {'!', '[', '[', '[', '[', '[', '[', '[', '[', '[', '[', '[', '[', '[', '!'},
    /*  i  */
    {']', '!', ']', ']', ']', ']', ']', ']', ']', ']', ']', ']', ']', '!', ']'},
    /*  +  */
    {']', '[', ']', ']', '[', '[', ']', ']', ']', ']', ']', ']', ']', '[', ']'},
    /*  -  */
    {']', '[', ']', ']', '[', '[', ']', ']', ']', ']', ']', ']', ']', '[', ']'},
    /*  *  */
    {']', '[', ']', ']', ']', ']', ']', ']', ']', ']', ']', ']', ']', '[', ']'},
    /*  /  */
    {']', '[', ']', ']', ']', ']', ']', ']', ']', ']', ']', ']', ']', '[', ']'},
    /*  .  */
    {']', '[', ']', ']', '[', '[', ']', ']', ']', ']', ']', ']', ']', '[', ']'},
    /* === */
    {']', '[', '[', '[', '[', '[', '[', '!', '!', '!', '!', '!', '!', '[', ']'},
    /* !== */
    {']', '[', '[', '[', '[', '[', '[', '!', '!', '!', '!', '!', '!', '[', ']'},
    /*  <  */
    {']', '[', '[', '[', '[', '[', '[', '!', '!', '!', '!', '!', '!', '[', ']'},
    /*  >  */
    {']', '[', '[', '[', '[', '[', '[', '!', '!', '!', '!', '!', '!', '[', ']'},
    /*  <= */
    {']', '[', '[', '[', '[', '[', '[', '!', '!', '!', '!', '!', '!', '[', ']'},
    /*  >= */
    {']', '[', '[', '[', '[', '[', '[', '!', '!', '!', '!', '!', '!', '[', ']'},
    /*  (  */
    {'!', '[', '[', '[', '[', '[', '[', '[', '[', '[', '[', '[', '[', '[', '='},
    /*  )  */
    {']', '!', ']', ']', ']', ']', ']', ']', ']', ']', ']', ']', ']', '!', ']'}};

// Right hand sides of rules
char grammar_rules[RULES_NUM][MAX_RULE_LEN] = {
    {EXPR_NONTERM, EXPR_ADD, EXPR_NONTERM, '\0'}, {EXPR_NONTERM, EXPR_SUB, EXPR_NONTERM, '\0'}, {EXPR_NONTERM, EXPR_MUL, EXPR_NONTERM, '\0'},
    {EXPR_NONTERM, EXPR_DIV, EXPR_NONTERM, '\0'}, {EXPR_NONTERM, EXPR_DOT, EXPR_NONTERM, '\0'}, {EXPR_ID, '\0'},
    {EXPR_LBR, EXPR_NONTERM, EXPR_RBR, '\0'},     {EXPR_NONTERM, EXPR_EQ, EXPR_NONTERM, '\0'},  {EXPR_NONTERM, EXPR_NEQ, EXPR_NONTERM, '\0'},
    {EXPR_NONTERM, EXPR_LT, EXPR_NONTERM, '\0'},  {EXPR_NONTERM, EXPR_GT, EXPR_NONTERM, '\0'},  {EXPR_NONTERM, EXPR_LE, EXPR_NONTERM, '\0'},
    {EXPR_NONTERM, EXPR_GE, EXPR_NONTERM, '\0'}};

ptable_move_t ptable_get_next_move(ptable_symbol_t stack, ptable_symbol_t input) {
    if ((stack < P_TABLE_SIZE && stack >= 0 && input < P_TABLE_SIZE) || input >= 0) {
        switch (ptable[stack][input]) {
            case '[':
                return EXPR_SHIFT;
            case ']':
                return EXPR_REDUCE;
            case '=':
                return EXPR_SPECIAL_SHIFT;
            case '!':
                return EXPR_ERROR;
            default:
                // Incorrect precedence table character
                return EXPR_ERROR;
        }
    } else {
        return INTERNAL_ERR;
    }
}

int expr_shift(Char_stack_t *c_stack, char character) {
    char_stack_push_shift(c_stack);
    if (char_stack_push(c_stack, character) == INTERNAL_ERR) {
        return INTERNAL_ERR;
    }
    return OK;
}

int expr_reduce(Htab_t *table, Char_stack_t *c_stack, Token_stack_t *t_stack) {
    DString_t d_string;
    int gen_res;
    if (d_string_init(&d_string) == INTERNAL_ERR) {
        return INTERNAL_ERR;
    };
    char term = char_stack_get_closest_terminal(c_stack);

    if ((gen_res = expr_instr_gen(table, t_stack, term)) != OK) {
        d_string_free_and_clear(&d_string);
        return gen_res;
    }

    // Reduction of expression
    char head_char = char_stack_pop(c_stack);
    while (head_char != EXPR_STACK_BOTTOM && head_char != '[') {
        if (d_string_insert_before(&d_string, head_char) == INTERNAL_ERR) {
            d_string_free_and_clear(&d_string);
            return INTERNAL_ERR;
        }
        head_char = char_stack_pop(c_stack);
    }
    if (is_valid_rule(&d_string) == SYNTAX_ERR) {
        d_string_free_and_clear(&d_string);
        return SYNTAX_ERR;
    }
    d_string_free_and_clear(&d_string);

    // Pushing left hand side of rule
    if (char_stack_push(c_stack, 'E') == INTERNAL_ERR) {
        return INTERNAL_ERR;
    }
    return OK;
}

int expr_special_shift(Char_stack_t *c_stack, char character) {
    if (char_stack_push(c_stack, character) == INTERNAL_ERR) {
        return INTERNAL_ERR;
    }
    return OK;
}

int is_valid_rule(DString_t *d_string) {
    for (int i = 0; i < RULES_NUM; i++) {
        if (d_string_cmp(d_string, grammar_rules[i]) == 0) {
            return OK;
        }
    }
    return SYNTAX_ERR;
}

int expr_parse(Htab_t *table, Char_stack_t *c_stack, Token_stack_t *t_stack, Token_t *token, int location) {
    ptable_symbol_t input;

    // Handle logical operators inside assignment
    switch (token->type) {
        case T_EQ:
        case T_NEQ:
        case T_LT:
        case T_GT:
        case T_LEQ:
        case T_GEQ:
            if (location == EXPR_LOC_ASSIGN) {
                return SYNTAX_ERR;
            }
            break;
        default:
            break;
    }
    switch (token->type) {
        case T_ADD:
            input = EXPR_ADD;
            break;
        case T_SUB:
            input = EXPR_SUB;
            break;
        case T_MUL:
            input = EXPR_MUL;
            break;
        case T_DIV:
            input = EXPR_DIV;
            break;
        case T_CONCAT:
            input = EXPR_DOT;
            break;
        case T_LBR:
            input = EXPR_LBR;
            break;
        case T_RBR:
            input = EXPR_RBR;
            break;
        case T_EQ:
            input = EXPR_EQ;
            break;
        case T_NEQ:
            input = EXPR_NEQ;
            break;
        case T_LT:
            input = EXPR_LT;
            break;
        case T_GT:
            input = EXPR_GT;
            break;
        case T_LEQ:
            input = EXPR_LE;
            break;
        case T_GEQ:
            input = EXPR_GE;
            break;
        case T_ID:
            input = EXPR_ID;
            break;
        case T_INT:
        case T_FLOAT:
        case T_STRING:
            input = EXPR_ID;
            token_stack_push(t_stack, token);
            break;
        case T_SEM:
            if (location == EXPR_LOC_ASSIGN || location == EXPR_LOC_RET) {
                if (char_stack_get_closest_terminal(c_stack) == EXPR_STACK_BOTTOM && char_stack_get_head(c_stack) == 'E') {
                    return OK;
                }
                return EOEXPR;
            } else {
                return SYNTAX_ERR;
            }
        default:
            if (token->type == EOEXPR) {
                input = EXPR_STACK_BOTTOM;
            } else {
                return EOEXPR;
            }
            break;
    }
    ptable_symbol_t stack = char_stack_get_closest_terminal(c_stack);
    if (stack == EXPR_STACK_BOTTOM && input == EXPR_STACK_BOTTOM && c_stack->char_head == 'E') {
        return OK;
    }
    if (stack == EXPR_STACK_BOTTOM && input == EXPR_RBR && c_stack->char_head == 'E') {
        if (location == EXPR_LOC_COND) {
            return EOEXPR;
        } else {
            return SYNTAX_ERR;
        }
    }
    ptable_move_t next_move = ptable_get_next_move(stack, input);

    switch (next_move) {
        case EXPR_SHIFT:
            return expr_shift(c_stack, input);
        case EXPR_REDUCE: {
            int ret;
            if ((ret = expr_reduce(table, c_stack, t_stack)) != OK) {
                return ret;
            }
            return expr_parse(table, c_stack, t_stack, token, location);
        }
        case EXPR_SPECIAL_SHIFT:
            return expr_special_shift(c_stack, input) == INTERNAL_ERR;
        case EXPR_ERROR:
            return SYNTAX_ERR;
        default:
            return INTERNAL_ERR;  // Just how ...
    }
}

int expr_main(Htab_t *table, Token_t *token, int location) {
    Char_stack_t c_stack;
    Token_stack_t t_stack;
    bool load_tokens = true;
    Token_t *eoexpr = malloc(sizeof(Token_t));
    eoexpr->type = EOEXPR;
    if (char_stack_init(&c_stack) == INTERNAL_ERR) {
        return INTERNAL_ERR;
    }
    if (token_stack_init(&t_stack) == INTERNAL_ERR) {
        return INTERNAL_ERR;
    }
    if (token == NULL) {
        return INTERNAL_ERR;
    }
    if (table == NULL) {
        return INTERNAL_ERR;
    }
    if (token->type == T_RBR && location == EXPR_LOC_COND) {
        return SYNTAX_ERR;
    }
    if (token->type == T_SEM && location == EXPR_LOC_ASSIGN) {
        return SYNTAX_ERR;
    }
    while (load_tokens == true) {
        if (token->type == T_EOF) {
            return SYNTAX_ERR;
        }
        if (token->type == T_ID) {
            Htab_item_t *item;
            if ((item = htab_find(table, token->attribute.string)) == NULL) {
                return UNDEF_VAR_ERR;
            }
            if (token_stack_push(&t_stack, token) == INTERNAL_ERR) {
                return INTERNAL_ERR;
            }
        }
        int status = expr_parse(table, &c_stack, &t_stack, token, location);
        if (status == EOEXPR) {
            load_tokens = false;
        } else {
            if (status != OK) {
                return status;
            }
            // Get new token
            if ((status = scan(token)) != OK) return status;
        }
    }
    int status = OK;

    while ((status = expr_parse(table, &c_stack, &t_stack, eoexpr, location)) == EOEXPR)
        ;
    free(eoexpr);
    return status;  // Generate result instruction here
}

int expr_instr_gen(Htab_t *table, Token_stack_t *t_stack, char term) {
    Token_t *tmp1 = malloc(sizeof(Token_t));
    token_stack_pop(t_stack, tmp1);
    Symbol_t *instr_var1 = malloc(sizeof(Symbol_t));
    if (instr_var1 == NULL) {
        return INTERNAL_ERR;
    }
    switch (term) {
        case EXPR_ID:
            // GENERATE INSTRUCTION
            if (tmp1->type == T_INT || tmp1->type == T_FLOAT || tmp1->type == T_STRING) {
                instr_var1->symbol_type = CONSTANT;
                if (tmp1->type == T_INT) {
                    instr_var1->const_type = INT;
                } else if (tmp1->type == T_FLOAT) {
                    instr_var1->const_type = FLOAT;
                } else if (tmp1->type == T_STRING) {
                    instr_var1->const_type = STRING;
                }
                instr_var1->attribute = malloc(sizeof(char) * strlen(tmp1->attribute.string) + 1);
                strcpy(instr_var1->attribute, tmp1->attribute.string);
            } else if (tmp1->type == T_ID) {
                instr_var1 = &(htab_find(table, tmp1->attribute.string)->data);
                if (instr_var1 == NULL) {
                    return INTERNAL_ERR;
                }
            } else {
                return INTERNAL_ERR;
            }
            generate_instruction(PUSHS, NULL, instr_var1, NULL, 0, stdout);
            break;
        case EXPR_ADD:
            // GENERATE INSTRUCTION
            generate_instruction(ADDS, NULL, NULL, NULL, 0, stdout);
            break;
        case EXPR_SUB:
            // GENERATE INSTRUCTION
            generate_instruction(SUBS, NULL, NULL, NULL, 0, stdout);
            break;
        case EXPR_MUL:
            // GENERATE INSTRUCTION
            generate_instruction(MULS, NULL, NULL, NULL, 0, stdout);
            break;
        case EXPR_DIV:
            // GENERATE INSTRUCTION
            generate_instruction(DIVS, NULL, NULL, NULL, 0, stdout);
            break;
        case EXPR_DOT:
            // GENERATE INSTRUCTION
            generate_instruction(CONCAT, NULL, NULL, NULL, 0, stdout);
            break;
        case EXPR_EQ:
            // GENERATE INSTRUCTION
            generate_instruction(EQS, NULL, NULL, NULL, 0, stdout);
            break;
        case EXPR_NEQ:
            // GENERATE INSTRUCTION
            generate_instruction(EQS, NULL, NULL, NULL, 0, stdout);
            generate_instruction(NOTS, NULL, NULL, NULL, 0, stdout);
            break;
        case EXPR_LT:
            // GENERATE INSTRUCTION
            generate_instruction(LTS, NULL, NULL, NULL, 0, stdout);
            break;
        case EXPR_GT:
            // GENERATE INSTRUCTION
            generate_instruction(GTS, NULL, NULL, NULL, 0, stdout);
            break;
        case EXPR_LE:
            // GENERATE INSTRUCTION
            generate_instruction(GTS, NULL, NULL, NULL, 0, stdout);
            generate_instruction(NOTS, NULL, NULL, NULL, 0, stdout);
            break;
        case EXPR_GE:
            // GENERATE INSTRUCTION
            generate_instruction(LTS, NULL, NULL, NULL, 0, stdout);
            generate_instruction(NOTS, NULL, NULL, NULL, 0, stdout);
            break;
        case EXPR_RBR:
            // GENERATE INSTRUCTION
            break;
        default:
            return INTERNAL_ERR;
    }
    return OK;
}
