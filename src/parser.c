// Filename: parser.c
// IFJ 2022/2023 project
// TRP variant
//
// Parser for syntax analysis
//
// Author: <xsklen14> - David Sklenář
// Author: <xproch0o> - Marek Procházka
// Author: <xzavad20> - Lukáš Zavadil
// Author: <xsvetl07> - Adam Světlík

// LOCAL INCLUDES
#include "parser.h"

DString_t function_id;
int param_number;

Token_t *init_token(void) {
    Token_t *token = (Token_t *)malloc(sizeof(Token_t));
    if (token == NULL) return NULL;
    token->type = NO_TYPE;
    token->attribute.string = NULL;
    return token;
}

int free_token(Token_t *token) {
    int status = OK;
    if (token == NULL) return INTERNAL_ERR;
    free(token->attribute.string);
    free(token);
    return status;
}

int parse(void) {
    int status = OK;
    // Initializing necessary variables and structures
    Token_t *token = init_token();
    if (token == NULL) return INTERNAL_ERR;
    Htab_t *global_table = htab_init(50);
    if (global_table == NULL) {
        free_token(token);
        return INTERNAL_ERR;
    }
    scope_t scope_state = {false, false, false, false, false, 0, 0};
    if ((status = d_string_init(&function_id)) != OK) {
        free_token(token);
        htab_free(global_table);
        return status;
    }

    // Start recursive descent
    if ((status = program_rule(token, &scope_state, global_table)) != OK) {
        free_token(token);
        htab_free(global_table);
        d_string_free_and_clear(&function_id);
        return status;
    }

    // Freeing memory after parsing
    free_token(token);
    htab_free(global_table);
    d_string_free_and_clear(&function_id);
    return status;
}

int program_rule(Token_t *token, scope_t *scope_state, Htab_t *global_table) {
    int status = OK;
    if ((status = scan(token)) != OK) return status;
    switch (token->type) {
        case T_EOF:
            return OK;
        case K_FUNC:
            if ((status = def_func_rule(token, scope_state, global_table)) !=
                OK)
                return status;
            break;
        case K_IF:
        case K_WHILE:
        case K_RET:
        case T_ID:
        case T_FUNC_ID:
            if ((status = stat_rule(token, scope_state, global_table) != OK))
                return status;
            break;
        default:
            return SYNTAX_ERR;
    }
    return program_rule(token, scope_state, global_table);
}

int def_func_rule(Token_t *token, scope_t *scope_state, Htab_t *global_table) {
    int status = OK;
    if (token->type != K_FUNC) return SYNTAX_ERR;
    if ((status = scan(token)) != OK) return status;
    if (token->type != T_FUNC_ID) return SYNTAX_ERR;
    Htab_item_t *func = htab_lookup_add(global_table, token);
    if ((status = scan(token)) != OK) return status;
    if (token->type != T_LBR) return SYNTAX_ERR;
    if ((status = scan(token)) != OK) return status;
    if ((status = arg_rule(token, func, global_table)) != OK) return status;
    if ((status = scan(token)) != OK) return status;
    if (token->type != T_COL) return SYNTAX_ERR;
    if ((status = scan(token)) != OK) return status;
    if ((status = type_rule(token, global_table)) != OK) return status;
    if ((status = scan(token)) != OK) return status;
    if (token->type != T_LCBR) return SYNTAX_ERR;
    if ((status = scan(token)) != OK) return status;
    if ((status = stat_rule(token, scope_state, global_table)) != OK)
        return status;
    return OK;
}

int arg_rule(Token_t *token, Htab_item_t *func, Htab_t *global_table) {
    int status = OK;

    return OK;
}
