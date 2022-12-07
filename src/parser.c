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
DString_t variable_id;
DString_t func_call_id;

int param_number;

Token_t *init_token(void) {
    Token_t *token = (Token_t *)malloc(sizeof(Token_t));
    if (token == NULL) return NULL;
    token->type = T_UNDEF;
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
    if ((status = d_string_init(&variable_id)) != OK) {
        free_token(token);
        htab_free(global_table);
        d_string_free_and_clear(&function_id);
        return status;
    }
    if ((status = d_string_init(&func_call_id)) != OK) {
        free_token(token);
        htab_free(global_table);
        d_string_free_and_clear(&function_id);
        d_string_free_and_clear(&variable_id);
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
    d_string_free_and_clear(&variable_id);
    d_string_free_and_clear(&func_call_id);
    return status;
}

int program_rule(Token_t *token, scope_t *scope_state, Htab_t *global_table) {
    int status = OK;

    // set scope states
    scope_state->in_global = true;

    // get token
    if ((status = scan(token)) != OK) return status;

    // handle
    // <PROGRAM> -> <DEFFUNC>
    // <PROGRAM> -> <STAT>
    // <PROGRAM> -> EOF
    switch (token->type) {
        case T_EOF:
            // check if values in scope are ok
            if (scope_state->count_if != 0 || scope_state->count_while != 0) {
                return SYNTAX_ERR;  // TODO check if relly syntax error or
                                    // something else
            }
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

    // get token
    if ((status = scan(token)) != OK) return status;

    // handle ... -> ... T__FUNC_ID
    if (token->type != T_FUNC_ID) return SYNTAX_ERR;

    // get/set function id
    Htab_item_t *func_ptr = htab_lookup_add(global_table, token);
    if (func_ptr == NULL) return INTERNAL_ERR;

    // check if function wasn't already defined
    if (func_ptr->data.func->defined != false) return UNDEF_FUNC_ERR;

    // store key of function in global variable
    if ((status =
             d_string_replace_str(&function_id, token->attribute.string)) != OK)
        return status;

    // set function name
    func_ptr->data.attribute = function_id.str;

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
    if ((status = type_rule(token, global_table, false, true)) != OK)
        return status;

    // get new token
    if ((status = scan(token)) != OK) return status;

    // handle ... -> ... T_LCBR
    if (token->type != T_LCBR) return SYNTAX_ERR;

    // set scope to function
    scope_state->in_func = true;

    // generate function header
    if ((status = generate_instruction(DEF_FUNC, NULL, &(func_ptr->data), NULL,
                                       0, stdout)) != OK)
        return status;

    // get new token
    if ((status = scan(token)) != OK) return status;

    // handle ... -> ... <STAT>
    if ((status = stat_rule(token, scope_state, global_table)) != OK)
        return status;

    // set function as defined
    func_ptr->data.func->defined = true;

    // update scope
    scope_state->in_func = false;

    return OK;
}

int arg_rule(Token_t *token, Htab_t *global_table) {
    int status = OK;

    // handle <ARG> -> T_RBR (end of arguments)
    if (token->type == T_RBR) return OK;

    // get function pointer
    Htab_item_t *func_ptr = htab_find(global_table, function_id.str);
    if (func_ptr == NULL) return INTERNAL_ERR;

    // inc argc
    func_ptr->data.func->argc++;

    // handle ... -> <TYPE>
    if ((status = type_rule(token, global_table, true, false)) != OK)
        return status;

    // get new token
    if ((status = scan(token)) != OK) return status;

    // handle ... -> ... <PARAM>
    if ((status = param_rule(token, global_table, false)) != OK) return status;

    // get new token
    if ((status = scan(token)) != OK) return status;

    // handle ... -> ... <ARGLIST>
    if ((status = arg_list_rule(token, global_table)) != OK) return status;

    return status;
}

int arg_list_rule(Token_t *current_token, Htab_t *global_table) {
    int status = OK;

    // handle <ARGLIST> -> T_RBR (end of arguments)
    if (current_token->type == T_RBR) return OK;

    // handle ... -> T_COMMA
    if (current_token->type != T_COMMA) return SYNTAX_ERR;

    // get new token
    if ((status = scan(current_token)) != OK) return status;

    // handle ... -> ... <ARG>
    if ((status = arg_rule(current_token, global_table)) != OK) return status;

    // get new token
    if ((status = scan(current_token)) != OK) return status;

    // handle ... -> ... <ARGLIST>
    if ((status = arg_list_rule(current_token, global_table)) != OK)
        return status;

    return status;
}

int param_rule(Token_t *token, Htab_t *global_table, bool func_call) {
    int status = OK;
    // handle <PARAM> -> <CONST>
    if (const_rule(token, global_table, false) == OK) {
        return OK;
    }

    // handle <PARAM> -> T_ID
    if (token->type != T_ID) return SYNTAX_ERR;

    // get/set id
    Htab_item_t *id_ptr = htab_lookup_add(global_table, token);
    if (id_ptr == NULL) return INTERNAL_ERR;
    // get function pointer
    Htab_item_t *func_ptr;

    if (func_call) {
        func_ptr = htab_find(global_table, func_call_id.str);
        if (func_ptr == NULL) return INTERNAL_ERR;
    } else {
        func_ptr = htab_find(global_table, function_id.str);
        if (func_ptr == NULL) return INTERNAL_ERR;
    }

    func_ptr->data.func->argv[func_ptr->data.func->argc - 1].attribute =
        id_ptr->data.attribute;
    func_ptr->data.func->argv[func_ptr->data.func->argc - 1].var->frame = LF;

    return status;
}

int param_list_rule(Token_t *current_token, Htab_t *global_table) {
    int status = OK;

    // handle <PARAMLIST> -> T_RBR (end of parameters)
    if (current_token->type == T_RBR) return OK;

    // handle ... -> T_COMMA
    if (current_token->type != T_COMMA) return SYNTAX_ERR;

    // get new token
    if ((status = scan(current_token)) != OK) return status;

    // handle ... -> ... <PARAM>
    if ((status = param_rule(current_token, global_table, false)) != OK)
        return status;

    // get new token
    if ((status = scan(current_token)) != OK) return status;

    // handle ... -> ... <PARAM_LIST>
    if ((status = param_list_rule(current_token, global_table)) != OK)
        return status;

    return status;
}

int type_rule(Token_t *token, Htab_t *global_table, bool is_func_def,
              bool is_func_type) {
    int status = OK;

    Htab_item_t *func_pointer = NULL;
    if (is_func_def == true) {
        // get function pointer
        Htab_item_t *func_ptr = htab_find(global_table, function_id.str);
        if (func_ptr == NULL) return INTERNAL_ERR;
    }

    switch (token->type) {
        case K_STR:
            if (is_func_def == true) {
                func_pointer->data.func->argv[func_pointer->data.func->argc - 1]
                    .var->var_type = STRING;
            }
            if (is_func_type == true) {
                func_pointer->data.func->return_type = STRING;
            }
            return OK;
        case K_INT:
            if (is_func_def == true) {
                func_pointer->data.func->argv[func_pointer->data.func->argc - 1]
                    .var->var_type = INT;
            }
            if (is_func_type == true) {
                func_pointer->data.func->return_type = INT;
            }
            return OK;
        case K_FLOAT:
            if (is_func_def == true) {
                func_pointer->data.func->argv[func_pointer->data.func->argc - 1]
                    .var->var_type = FLOAT;
            }
            if (is_func_type == true) {
                func_pointer->data.func->return_type = FLOAT;
            }
            return OK;
        case K_FLOAT_NULL:
            if (is_func_def == true) {
                func_pointer->data.func->argv[func_pointer->data.func->argc - 1]
                    .var->var_type = FLOAT;  // TODO FLOAT_NULL mby
            }
            if (is_func_type == true) {
                func_pointer->data.func->return_type =
                    FLOAT;  // TODO FLOAT_NULL mby
            }
            return OK;
        case K_INT_NULL:
            if (is_func_def == true) {
                func_pointer->data.func->argv[func_pointer->data.func->argc - 1]
                    .var->var_type = INT;  // TODO INT_NULL mby
            }
            if (is_func_type == true) {
                func_pointer->data.func->return_type =
                    INT;  // TODO INT_NULL mby
            }
            return OK;
        case K_STR_NULL:
            if (is_func_def == true) {
                func_pointer->data.func->argv[func_pointer->data.func->argc - 1]
                    .var->var_type = STRING;  // TODO STR_NULL mby
            }
            if (is_func_type == true) {
                func_pointer->data.func->return_type =
                    STRING;  // TODO STR_NULL mby
            }
            return OK;
        case K_NULL:
            if (is_func_def == true) {
                func_pointer->data.func->argv[func_pointer->data.func->argc - 1]
                    .var->var_type = NIL;
            }
            if (is_func_type == true) {
                func_pointer->data.func->return_type = NIL;
            }
            return OK;
        default:
            return SYNTAX_ERR;
    }
}

int const_rule(Token_t *token, Htab_t *global_table, bool func_call) {
    int status = OK;

    // get function pointer
    Htab_item_t *func_ptr;
    if (func_call) {
        func_ptr = htab_find(global_table, func_call_id.str);
        if (func_ptr == NULL) return INTERNAL_ERR;
    } else {
        func_ptr = htab_find(global_table, function_id.str);
        if (func_ptr == NULL) return INTERNAL_ERR;
    }

    switch (token->type) {
        case T_INT:
            func_ptr->data.func->argv[func_ptr->data.func->argc - 1]
                .const_type = INT;
            func_ptr->data.func->argv[func_ptr->data.func->argc - 1].attribute =
                token->attribute.string;
            return OK;
        case T_FLOAT:
            func_ptr->data.func->argv[func_ptr->data.func->argc - 1]
                .const_type = FLOAT;
            func_ptr->data.func->argv[func_ptr->data.func->argc - 1].attribute =
                token->attribute.string;
            return OK;
        case T_STRING:
            func_ptr->data.func->argv[func_ptr->data.func->argc - 1]
                .const_type = STRING;
            func_ptr->data.func->argv[func_ptr->data.func->argc - 1].attribute =
                token->attribute.string;
            return OK;
        case K_NULL:
            func_ptr->data.func->argv[func_ptr->data.func->argc - 1]
                .const_type = NIL;
            func_ptr->data.func->argv[func_ptr->data.func->argc - 1].attribute =
                token->attribute.string;
            return OK;
        default:
            return SYNTAX_ERR;
    }
}

int stat_rule(Token_t *current_token, scope_t *scope_state,
              Htab_t *global_table) {
    int status = OK;

    // handle <STAT> -> K_IF
    if (current_token->type == K_IF) {
        // update scope
        scope_state->in_if = true;
        scope_state->count_if++;
        // get new token
        if ((status = scan(current_token)) != OK) return status;

        // handle ... -> ... T_LBR
        if (current_token->type != T_LBR) return SYNTAX_ERR;

        // get new token
        if ((status = scan(current_token)) != OK) return status;

        // handle ... -> ... <EXPR>
        if ((status = expr_rule(current_token, global_table, EXPR_LOC_COND)) !=
            OK)
            return status;

        // get new token
        if ((status = scan(current_token)) != OK) return status;

        // handle ... -> ... T_LCBR
        if (current_token->type != T_LCBR) return SYNTAX_ERR;

        // get new token
        if ((status = scan(current_token)) != OK) return status;

        // handle ... -> ... <STAT>
        if ((status = stat_rule(current_token, scope_state, global_table)) !=
            OK)
            return status;

        // get new token
        if ((status = scan(current_token)) != OK) return status;

        // handle ... -> ... K_ELSE
        if (current_token->type != K_ELSE) return SYNTAX_ERR;

        // get new token
        if ((status = scan(current_token)) != OK) return status;

        // handle ... -> ... T_LCBR
        if (current_token->type != T_LCBR) return SYNTAX_ERR;

        // get new token
        if ((status = scan(current_token)) != OK) return status;

        // handle ... -> ... <STAT>
        if ((status = stat_rule(current_token, scope_state, global_table)) !=
            OK)
            return status;

        // update scope
        scope_state->count_if--;
        if (scope_state->count_if == 0) scope_state->in_if = false;
    }

    // handle ... -> K_WHILE
    if (current_token->type == K_WHILE) {
        // update scope
        scope_state->in_while = true;
        scope_state->count_while++;
        // get new token
        if ((status = scan(current_token)) != OK) return status;

        // handle ... -> ... T_LBR
        if (current_token->type != T_LBR) return SYNTAX_ERR;

        // get new token
        if ((status = scan(current_token)) != OK) return status;

        // handle ... -> ... <EXPR>
        if ((status = expr_rule(current_token, global_table, EXPR_LOC_COND)) !=
            OK)
            return status;

        // get new token
        if ((status = scan(current_token)) != OK) return status;

        // handle ... -> ... T_LCBR
        if (current_token->type != T_LCBR) return SYNTAX_ERR;

        // get new token
        if ((status = scan(current_token)) != OK) return status;

        // handle ... -> ... <STAT>
        if ((status = stat_rule(current_token, scope_state, global_table)) !=
            OK)
            return status;

        // update scope
        scope_state->count_while--;
        if (scope_state->count_while == 0) scope_state->in_while = false;
    }

    // handle ... -> K_RET
    if (current_token->type == K_RET) {
        // get new token
        if ((status = scan(current_token)) != OK) return status;

        // handle ... -> ... <EXPR>
        if ((status = expr_rule(current_token, global_table, EXPR_LOC_RET)) !=
            OK)
            return status;

        // get new token
        if ((status = scan(current_token)) != OK) return status;

        // handle ... -> ... T_SEM
        if (current_token->type != T_SEM) return SYNTAX_ERR;

        // get new token
        if ((status = scan(current_token)) != OK) return status;

        // handle ... -> ... <STAT>
        if ((status = stat_rule(current_token, scope_state, global_table)) !=
            OK)
            return status;

        //        // handle ... -> ... T_RCBR
        //        if (current_token->type != T_RCBR) return SYNTAX_ERR;
    }

    // handle ... -> T_ID
    if (current_token->type == T_ID) {
        // save id name to variable_id
        d_string_replace_str(&variable_id, current_token->attribute.string);

        // get new token
        if ((status = scan(current_token)) != OK) return status;

        // handle ... -> ... T_ASSIGN
        if (current_token->type == T_ASSIGN) {
            // get new token
            if ((status = scan(current_token)) != OK) return status;

            // handle ... -> ... <ASSIGN_TYPE>
            if ((status = assign_type_rule(current_token, scope_state,
                                           global_table)) != OK)
                return status;

            // get new token
            if ((status = scan(current_token)) != OK) return status;

            // handle ... -> ... <STAT>
            if ((status =
                     stat_rule(current_token, scope_state, global_table)) != OK)
                return status;
        }
        // handle ... -> ...<TYPE>
        else {
            if ((status = type_rule(current_token, global_table, false,
                                    false)) != OK)
                return status;

            // get new token
            if ((status = scan(current_token)) != OK) return status;

            // handle .. -> ... T_SEM
            if (current_token->type != T_SEM) return SYNTAX_ERR;

            // get new token
            if ((status = scan(current_token)) != OK) return status;

            // handle ... -> ... <STAT>
            if ((status =
                     stat_rule(current_token, scope_state, global_table)) != OK)
                ;
        }
    }

    // handle ... -> <FUNC_CALL>
    if (current_token->type == T_FUNC_ID) {
        // save function id to func_call_id
        d_string_replace_str(&func_call_id, current_token->attribute.string);
        if ((status = func_call_rule(current_token, scope_state,
                                     global_table)) != OK)
            return status;

        // get func pointer
        Htab_item_t *func_ptr = htab_find(global_table, func_call_id.str);

        // generate instruction
        if ((status = generate_instruction(CALL_FUNC, NULL, &func_ptr->data,
                                           NULL, 0, stdout)) != OK)
            return status;
    }

    // handle ... -> T_RCBR
    if (current_token->type == T_RCBR) {
        // get new token
        if ((status = scan(current_token)) != OK) return status;

        // handle ... -> ... <STAT>
        if ((status = stat_rule(current_token, scope_state, global_table)) !=
            OK)
            return status;
    }

    // end + ε
    return status;
}

int assign_type_rule(Token_t *current_token, scope_t *scope_state,
                     Htab_t *global_table) {
    int status = OK;

    // handle <ASSIGN_TYPE> -> <FUNC_CALL>
    if (current_token->type == T_FUNC_ID) {
        d_string_replace_str(&function_id, current_token->attribute.string);

        if ((status = func_call_rule(current_token, scope_state,
                                     global_table)) != OK)
            return status;

        // get variable from global table
        Htab_item_t *variable = htab_find(global_table, variable_id.str);

        // get function from global table
        Htab_item_t *function = htab_find(global_table, func_call_id.str);

        if ((status = generate_instruction(CALL_FUNC_ASSIGN, &variable->data,
                                           &function->data, NULL, 0, stdout)) !=
            OK)
            return status;
    }

    // handle ... -> <EXPR>
    if ((status = expr_rule(current_token, global_table, EXPR_LOC_ASSIGN)) !=
        OK)
        return status;

    return status;
}

int func_call_rule(Token_t *current_token, scope_t *scope_state,
                   Htab_t *global_table) {
    int status = OK;

    // handle <FUNC_CALL> -> T_FUNC_ID
    if (current_token->type != T_FUNC_ID) return SYNTAX_ERR;

    Htab_item_t *function = htab_find(global_table, func_call_id.str);

    // check if func is defined
    if (function->data.func->defined == false)
        return UNDEF_FUNC_ERR;  // TODO maybe comment out

    // get new token
    if ((status = scan(current_token)) != OK) return status;

    // handle ... -> ... T_LBR
    if (current_token->type != T_LBR) return SYNTAX_ERR;

    // get new token
    if ((status = scan(current_token)) != OK) return status;

    // handle ... -> ... <PARAM>
    if ((status = param_rule(current_token, global_table, true)) != OK)
        return status;

    // get new token
    if ((status = scan(current_token)) != OK) return status;

    // handle ... -> ... <PARAM_LIST>
    if ((status = param_list_rule(current_token, global_table)) != OK)
        return status;

    return status;
}

int expr_rule(Token_t *current_token, Htab_t *global_table, int location) {
    int status = OK;
    expr_main(global_table, current_token, location);
    return status;
}
