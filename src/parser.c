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
    scope_t scope_state = {false, false, false, false, true, 0, 0};
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

    // set scope states
    scope_state->in_global = true;

    // get token
    if ((status = scan(token)) != OK) return status;

    // handle
    // <PROGRAM> -> <DEFFUNC>>
    // <PROGRAM> -> <STAT>
    // <PROGRAM> -> EOF
    switch (token->type) {
        case T_EOF:
            return OK;  // TODO: maybe we want to throw error in some cases
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
    // handle
    // ... -> ... <PROGRAM>
    return program_rule(token, scope_state, global_table);
}

int def_func_rule(Token_t *token, scope_t *scope_state, Htab_t *global_table) {
    int status = OK;
    // no states to set yet

    // handle <DEFFUNC> -> K_FUNC
    if (token->type != K_FUNC) return SYNTAX_ERR;
    if ((status = scan(token)) != OK) return status;

    // handle ... -> ... T__FUNC_ID
    if (token->type != T_FUNC_ID) return SYNTAX_ERR;

    // get/set function id
    Htab_item_t *func_ptr = htab_lookup_add(global_table, token);
    if (func_ptr == NULL) return INTERNAL_ERR;

    // check if function wasn't already defined
    if (func_ptr->data.type.func.defined == true) return UNDEF_FUNC_ERR;

    // store key of function in global variable
    if ((status =
             d_string_replace_str(&function_id, token->attribute.string)) != OK)
        return status;

    // get new token
    if ((status = scan(token)) != OK) return status;

    // handle ... -> ... T_LBR
    if (token->type != T_LBR) return SYNTAX_ERR;

    // get new token
    if ((status = scan(token)) != OK) return status;

    // handle ... -> ... <ARG>
    if ((status = arg_rule(token, global_table)) != OK) return status;

    // get new token
    if ((status = scan(token)) != OK) return status;

    // handle ... -> ... T_COL
    if (token->type != T_COL) return SYNTAX_ERR;

    // get new token
    if ((status = scan(token)) != OK) return status;

    // handle ... -> ... <TYPE>
    if ((status = type_rule(token, global_table)) != OK) return status;

    // get new token
    if ((status = scan(token)) != OK) return status;

    // handle ... -> ... T_LCBR
    if (token->type != T_LCBR) return SYNTAX_ERR;

    // set scope to function
    scope_state->in_func = true;

    // get new token
    if ((status = scan(token)) != OK) return status;

    // handle ... -> ... <STAT>
    if ((status = stat_rule(token, scope_state, global_table)) != OK)
        return status;
    return OK;
}

int arg_rule(Token_t *token, Htab_t *global_table) {
    int status = OK;


    return OK;
}
