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

Htab_t *local_table;

int param_number;

Token_t *init_token(void) {
    Token_t *token = (Token_t *)malloc(sizeof(Token_t));
    if (token == NULL) return NULL;
    token->type = T_UNDEF;
    token->attribute.string = NULL;
    return token;
}

int add_built_in(Htab_t *global_table) {
    if (global_table == NULL) return INTERNAL_ERR;
    Token_t *token = init_token();
    if (token == NULL) return INTERNAL_ERR;
    token->type = T_FUNC_ID;
    token->attribute.string = "reads";
    if (htab_insert_item(global_table, token) != OK) return INTERNAL_ERR;
    token->attribute.string = "readi";
    if (htab_insert_item(global_table, token) != OK) return INTERNAL_ERR;
    token->attribute.string = "readf";
    if (htab_insert_item(global_table, token) != OK) return INTERNAL_ERR;
    token->attribute.string = "write";
    if (htab_insert_item(global_table, token) != OK) return INTERNAL_ERR;
    token->attribute.string = "floatval";
    if (htab_insert_item(global_table, token) != OK) return INTERNAL_ERR;
    token->attribute.string = "intval";
    if (htab_insert_item(global_table, token) != OK) return INTERNAL_ERR;
    token->attribute.string = "strval";
    if (htab_insert_item(global_table, token) != OK) return INTERNAL_ERR;
    token->attribute.string = "strlen";
    if (htab_insert_item(global_table, token) != OK) return INTERNAL_ERR;
    token->attribute.string = "substring";
    if (htab_insert_item(global_table, token) != OK) return INTERNAL_ERR;
    token->attribute.string = "ord";
    if (htab_insert_item(global_table, token) != OK) return INTERNAL_ERR;
    token->attribute.string = "chr";
    if (htab_insert_item(global_table, token) != OK) return INTERNAL_ERR;
    free(token);
    return OK;
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
    scope_t scope_state = {false, false, false, false, true, 0, 0, 0, 0};
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

    // generate prolog
    if ((status = generate_instruction(PROLOG, NULL, NULL, NULL, 0, stdout)) != OK) {
        free_token(token);
        htab_free(global_table);
        d_string_free_and_clear(&function_id);
        d_string_free_and_clear(&variable_id);
        d_string_free_and_clear(&func_call_id);
        return status;
    }

    // generate build-in functions
    print_built_in(stdout);

    // add build-in functions to global table
    if ((status = add_built_in(global_table)) != OK) {
        free_token(token);
        htab_free(global_table);
        d_string_free_and_clear(&function_id);
        d_string_free_and_clear(&variable_id);
        d_string_free_and_clear(&func_call_id);
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
            if ((status = def_func_rule(token, scope_state, global_table)) != OK) return status;
            break;
        case K_IF:
        case K_WHILE:
        case K_RET:
        case T_ID:
        case T_FUNC_ID:
            if ((status = stat_rule(token, scope_state, global_table)) != OK) return status;
            break;
        default:
            return SYNTAX_ERR;
    }
    // handle
    // ... -> ... <PROGRAM>

    return program_rule(token, scope_state, global_table);
}

int def_func_rule(Token_t *token, scope_t *scope_state, Htab_t *global_table) {
    // initialize local table
    local_table = htab_init(50);
    if (local_table == NULL) return INTERNAL_ERR;

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
    func_ptr->data.func->defined = true;

    // store key of function in global variable
    if ((status = d_string_replace_str(&function_id, token->attribute.string)) != OK) return status;

    // set function name
    func_ptr->data.attribute = function_id.str;

    // get new token
    if ((status = scan(token)) != OK) return status;

    // handle ... -> ... T_LBR
    if (token->type != T_LBR) return SYNTAX_ERR;

    // set function as defined
    func_ptr->data.func->defined = true;

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
    if ((status = type_rule(token, global_table, false, true)) != OK) return status;

    // get new token
    if ((status = scan(token)) != OK) return status;

    // handle ... -> ... T_LCBR
    if (token->type != T_LCBR) return SYNTAX_ERR;

    // set scope to function
    scope_state->in_func = true;
    scope_state->in_global = false;

    // generate function header
    if ((status = generate_instruction(DEF_FUNC, NULL, &(func_ptr->data), NULL, 0, stdout)) != OK) return status;

    // get new token
    if ((status = scan(token)) != OK) return status;

    // handle ... -> ... <STAT>
    if ((status = stat_rule(token, scope_state, global_table)) != OK) return status;

    // update scope
    scope_state->in_func = false;
    scope_state->in_global = true;

    // free local table
    htab_free(local_table);

    return OK;
}

int arg_rule(Token_t *token, Htab_t *global_table) {
    int status = OK;

    // handle <ARG> -> T_RBR (end of arguments)
    if (token->type == T_RBR) return OK;

    // get function pointer
    Htab_item_t *func_ptr = htab_find(global_table, function_id.str);
    if (func_ptr == NULL) return INTERNAL_ERR;

    func_ptr->data.symbol_type = FUNCTION;
    // inc argc
    func_ptr->data.func->argc++;
    // realloc argv
    func_ptr->data.func->argv = realloc(func_ptr->data.func->argv, func_ptr->data.func->argc * sizeof(Symbol_t));

    // handle ... -> <TYPE>
    if ((status = type_rule(token, global_table, true, false)) != OK) return status;

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

    if (current_token->type == T_RBR) return SYNTAX_ERR;
    // handle ... -> ... <ARG>
    if ((status = arg_rule(current_token, global_table)) != OK) return status;

    // get new token
    //    if ((status = scan(current_token)) != OK) return status;

    // handle ... -> ... <ARGLIST>
    //    if ((status = arg_list_rule(current_token, global_table)) != OK) return status;

    return status;
}

int param_rule(Token_t *token, Htab_t *global_table, bool func_call) {
    int status = OK;
    // handle <PARAM> -> <CONST>
    if (func_call == true) {
        if (const_rule(token, global_table, func_call) == OK) {
            return OK;
        }
    }

    // handle <PARAM> -> T_ID
    if (token->type != T_ID) return SYNTAX_ERR;

    // get/set id
    Htab_item_t *id_ptr;
    if (func_call == true) {
        id_ptr = htab_lookup_add(global_table, token);
        id_ptr->data.var->frame = GF;
    } else {
        id_ptr = htab_lookup_add(local_table, token);
        id_ptr->data.var->frame = LF;
    }

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
    func_ptr->data.func->argv[func_ptr->data.func->argc - 1].symbol_type = VARIABLE;
    func_ptr->data.func->argv[func_ptr->data.func->argc - 1].attribute = id_ptr->data.attribute;
    func_ptr->data.func->argv[func_ptr->data.func->argc - 1].var->frame = func_call ? LF : GF;

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
    if ((status = param_rule(current_token, global_table, false)) != OK) return status;

    // get new token
    if ((status = scan(current_token)) != OK) return status;

    // handle ... -> ... <PARAM_LIST>
    if ((status = param_list_rule(current_token, global_table)) != OK) return status;

    return status;
}

int type_rule(Token_t *token, Htab_t *global_table, bool is_func_def, bool is_func_type) {
    int status = OK;

    Htab_item_t *func_pointer = htab_find(global_table, function_id.str);
    Htab_item_t *variable = htab_find(global_table, variable_id.str);

    if (is_func_def == true) {
        // get function pointer
        func_pointer->data.func->argv[func_pointer->data.func->argc - 1].var = malloc(sizeof(Var_t));
        if (func_pointer == NULL) return INTERNAL_ERR;
    }
    switch (token->type) {
        case K_STR:
            if (is_func_def == true) {
                func_pointer->data.func->argv[func_pointer->data.func->argc - 1].var->var_type = STRING;
            }
            if (is_func_type == true) {
                func_pointer->data.func->return_type = STRING;
            }
            if (!is_func_def && !is_func_type) {
                variable->data.var->var_type = STRING;
                if (variable->data.var->asigned == false){
                    if ((status = generate_instruction(DEFVAR, NULL, &variable->data, NULL, 0, stdout)) != OK) return status;
                    variable->data.var->asigned = true;
                }
            }
            return OK;
        case K_INT:
            if (is_func_def == true) {
                func_pointer->data.func->argv[func_pointer->data.func->argc - 1].var->var_type = INT;
            }
            if (is_func_type == true) {
                func_pointer->data.func->return_type = INT;
            }
            if (!is_func_def && !is_func_type) {
                variable->data.var->var_type = INT;
                if (variable->data.var->asigned == false){
                    if ((status = generate_instruction(DEFVAR, NULL, &variable->data, NULL, 0, stdout)) != OK) return status;
                    variable->data.var->asigned = true;
                }
            }
            return OK;
        case K_FLOAT:
            if (is_func_def == true) {
                func_pointer->data.func->argv[func_pointer->data.func->argc - 1].var->var_type = FLOAT;
            }
            if (is_func_type == true) {
                func_pointer->data.func->return_type = FLOAT;
            }
            if (!is_func_def && !is_func_type) {
                variable->data.var->var_type = FLOAT;
                if (variable->data.var->asigned == false){
                    if ((status = generate_instruction(DEFVAR, NULL, &variable->data, NULL, 0, stdout)) != OK) return status;
                    variable->data.var->asigned = true;
                }
            }
            return OK;
        case K_FLOAT_NULL:
            if (is_func_def == true) {
                func_pointer->data.func->argv[func_pointer->data.func->argc - 1].var->var_type = FLOAT;  // TODO FLOAT_NULL mby
            }
            if (is_func_type == true) {
                func_pointer->data.func->return_type = FLOAT;
            }
            if (!is_func_def && !is_func_type) {
                variable->data.var->var_type = FLOAT;
                if (variable->data.var->asigned == false){
                    if ((status = generate_instruction(DEFVAR, NULL, &variable->data, NULL, 0, stdout)) != OK) return status;
                    variable->data.var->asigned = true;
                }
            }
            return OK;
        case K_INT_NULL:
            if (is_func_def == true) {
                func_pointer->data.func->argv[func_pointer->data.func->argc - 1].var->var_type = INT;  // TODO INT_NULL mby
            }
            if (is_func_type == true) {
                func_pointer->data.func->return_type = INT;
            }
            if (!is_func_def && !is_func_type) {
                variable->data.var->var_type = INT;
                if (variable->data.var->asigned == false){
                    if ((status = generate_instruction(DEFVAR, NULL, &variable->data, NULL, 0, stdout)) != OK) return status;
                    variable->data.var->asigned = true;
                }
            }
            return OK;
        case K_STR_NULL:
            if (is_func_def == true) {
                func_pointer->data.func->argv[func_pointer->data.func->argc - 1].var->var_type = STRING;  // TODO STR_NULL mby
            }
            if (is_func_type == true) {
                func_pointer->data.func->return_type = STRING;
            }
            if (!is_func_def && !is_func_type) {
                variable->data.var->var_type = STRING;
                if (variable->data.var->asigned == false){
                    if ((status = generate_instruction(DEFVAR, NULL, &variable->data, NULL, 0, stdout)) != OK) return status;
                    variable->data.var->asigned = true;
                }
            }
            return OK;
        case K_NULL:
            if (is_func_def == true) {
                func_pointer->data.func->argv[func_pointer->data.func->argc - 1].var->var_type = NIL;
            }
            if (is_func_type == true) {
                //                func_pointer->data.func->return_type = NIL;
            }if (!is_func_def && !is_func_type) {
                variable->data.var->var_type = NIL;
                if (variable->data.var->asigned == false){
                    if ((status = generate_instruction(DEFVAR, NULL, &variable->data, NULL, 0, stdout)) != OK) return status;
                    variable->data.var->asigned = true;
                }
            }
            return OK;
        default:
            return SYNTAX_ERR;
    }
}

int const_rule(Token_t *token, Htab_t *global_table, bool func_call) {
    // get function pointer
    Htab_item_t *func_ptr;
    if (func_call) {
        func_ptr = htab_find(global_table, func_call_id.str);
        if (func_ptr == NULL) return INTERNAL_ERR;
    } else {
        func_ptr = htab_find(global_table, function_id.str);
        if (func_ptr == NULL) return INTERNAL_ERR;
    }
    func_ptr->data.symbol_type = CONSTANT;
    switch (token->type) {
        case T_INT:
//            func_ptr->data.func->argv[func_ptr->data.func->argc - 1].const_type = INT;
//            func_ptr->data.func->argv[func_ptr->data.func->argc - 1].attribute = token->attribute.string;
            return OK;
        case T_FLOAT:
//            func_ptr->data.func->argv[func_ptr->data.func->argc - 1].const_type = FLOAT;
//            func_ptr->data.func->argv[func_ptr->data.func->argc - 1].attribute = token->attribute.string;
            return OK;
        case T_STRING:
//            func_ptr->data.func->argv[func_ptr->data.func->argc - 1].const_type = STRING;
//            func_ptr->data.func->argv[func_ptr->data.func->argc - 1].attribute = token->attribute.string;
            return OK;
        case K_NULL:
//            func_ptr->data.func->argv[func_ptr->data.func->argc - 1].const_type = NIL;
//            func_ptr->data.func->argv[func_ptr->data.func->argc - 1].attribute = token->attribute.string;
            return OK;
        default:
            return SYNTAX_ERR;
    }
}

int stat_rule(Token_t *current_token, scope_t *scope_state, Htab_t *global_table) {
    int status = OK;

    // handle <STAT> -> K_IF
    if (current_token->type == K_IF) {
        // update scope
        scope_state->in_if = true;
        scope_state->count_if++;

        int local_num_if = scope_state->num_if;
        scope_state->num_if++;
        // get new token
        if ((status = scan(current_token)) != OK) return status;

        // handle ... -> ... T_LBR
        if (current_token->type != T_LBR) return SYNTAX_ERR;

        // get new token
        if ((status = scan(current_token)) != OK) return status;

        // handle ... -> ... <EXPR>
        if ((status = expr_rule(current_token, global_table, EXPR_LOC_COND, scope_state)) != OK) return status;

        // generate if
        if ((status = generate_instruction(IF, NULL, NULL, NULL, local_num_if, stdout)) != OK) return status;

        // get new token
        if ((status = scan(current_token)) != OK) return status;

        // handle ... -> ... T_LCBR
        if (current_token->type != T_LCBR) return SYNTAX_ERR;

        // get new token
        if ((status = scan(current_token)) != OK) return status;

        // handle ... -> ... <STAT>
        if ((status = stat_rule(current_token, scope_state, global_table)) != OK) return status;

        // get new token
        if ((status = scan(current_token)) != OK) return status;

        // handle ... -> ... K_ELSE
        if (current_token->type != K_ELSE) return SYNTAX_ERR;

        // generate else
        if ((status = generate_instruction(IF_ELSE, NULL, NULL, NULL, local_num_if, stdout)) != OK) return status;

        // get new token
        if ((status = scan(current_token)) != OK) return status;

        // handle ... -> ... T_LCBR
        if (current_token->type != T_LCBR) return SYNTAX_ERR;

        // get new token
        if ((status = scan(current_token)) != OK) return status;

        // handle ... -> ... <STAT>
        if ((status = stat_rule(current_token, scope_state, global_table)) != OK) return status;

        // generate endif
        if ((status = generate_instruction(IF_END, NULL, NULL, NULL, local_num_if, stdout)) != OK) return status;

        // update scope
        scope_state->count_if--;
        if (scope_state->count_if == 0) scope_state->in_if = false;

        // get new token
        if ((status = scan(current_token)) != OK) return status;

        return stat_rule(current_token, scope_state, global_table);
    }

    // handle ... -> K_WHILE
    if (current_token->type == K_WHILE) {
        // update scope
        scope_state->in_while = true;
        scope_state->count_while++;

        int local_num_while = scope_state->num_while;
        scope_state->num_while++;

        // get new token
        if ((status = scan(current_token)) != OK) return status;

        // handle ... -> ... T_LBR
        if (current_token->type != T_LBR) return SYNTAX_ERR;

        // get new token
        if ((status = scan(current_token)) != OK) return status;

        // handle ... -> ... <EXPR>
        if ((status = expr_rule(current_token, global_table, EXPR_LOC_COND, scope_state)) != OK) return status;

        // generate while
        if ((status = generate_instruction(WHILE, NULL, NULL, NULL, local_num_while, stdout)) != OK) return status;

        // get new token
        if ((status = scan(current_token)) != OK) return status;

        // handle ... -> ... T_LCBR
        if (current_token->type != T_LCBR) return SYNTAX_ERR;

        // get new token
        if ((status = scan(current_token)) != OK) return status;

        // handle ... -> ... <STAT>
        if ((status = stat_rule(current_token, scope_state, global_table)) != OK) return status;

        // generate endwhile
        if ((status = generate_instruction(WHILE_END, NULL, NULL, NULL, local_num_while, stdout)) != OK) return status;

        // update scope
        scope_state->count_while--;
        scope_state->num_while++;
        if (scope_state->count_while == 0) scope_state->in_while = false;

        // get new token
        if ((status = scan(current_token)) != OK) return status;

        return stat_rule(current_token, scope_state, global_table);
    }

    // handle ... -> K_RET
    if (current_token->type == K_RET) {
        // get new token
        if ((status = scan(current_token)) != OK) return status;

        // handle ... -> ... <EXPR>
        if ((status = expr_rule(current_token, global_table, EXPR_LOC_RET, scope_state)) != OK) return status;

        // get new token
        if ((status = scan(current_token)) != OK) return status;

        // handle ... -> ... <STAT>
        if ((status = stat_rule(current_token, scope_state, global_table)) != OK) return status;

        //        // handle ... -> ... T_RCBR
        //        if (current_token->type != T_RCBR) return SYNTAX_ERR;
    }

    // handle ... -> T_ID
    if (current_token->type == T_ID) {
        // save id name to variable_id
        d_string_replace_str(&variable_id, current_token->attribute.string);
        // get variable from global table
        Htab_item_t *variable;
        if (scope_state->in_global == true) {
            if ((variable = htab_lookup_add(global_table, current_token)) == NULL) {
                return INTERNAL_ERR;
            }
            variable->data.var->frame = GF;
        } else {
            if ((variable = htab_lookup_add(local_table, current_token)) == NULL) {
                return INTERNAL_ERR;
            }
            variable->data.var->frame = LF;
        }

        // get new token
        if ((status = scan(current_token)) != OK) return status;

        // handle ... -> ... T_ASSIGN
        if (current_token->type == T_ASSIGN) {
            // get new token
            if ((status = scan(current_token)) != OK) return status;

            // handle ... -> ... <ASSIGN_TYPE>
            if ((status = assign_type_rule(current_token, scope_state, global_table)) != OK) return status;

            // get new token
            if ((status = scan(current_token)) != OK) return status;

            // handle ... -> ... <STAT>
            if ((status = stat_rule(current_token, scope_state, global_table)) != OK) return status;
        }
        // handle ... -> ...<TYPE>
        else {
            if ((status = type_rule(current_token, global_table, false, false)) != OK) return status;

            // get new token
            if ((status = scan(current_token)) != OK) return status;

            // handle .. -> ... T_SEM
            if (current_token->type != T_SEM) return SYNTAX_ERR;

            // get new token
            if ((status = scan(current_token)) != OK) return status;

            // handle ... -> ... <STAT>
            if ((status = stat_rule(current_token, scope_state, global_table)) != OK)return status;
        }
    }

    // handle ... -> <FUNC_CALL>
    if (current_token->type == T_FUNC_ID) {
        // save function id to func_call_id
        d_string_replace_str(&func_call_id, current_token->attribute.string);
        if ((status = func_call_rule(current_token, global_table)) != OK) return status;

        // get new token
        if ((status = scan(current_token)) != OK) return status;

        // handle ... -> ... T_SEM
        if (current_token->type != T_SEM) return SYNTAX_ERR;

        // get func pointer
        Htab_item_t *func_ptr = htab_find(global_table, func_call_id.str);

        // generate instruction
        if ((status = generate_instruction(CALL_FUNC, NULL, &func_ptr->data, NULL, 0, stdout)) != OK) return status;

        // get new token
        if ((status = scan(current_token)) != OK) return status;

        // handle ... -> ... <STAT>
        if ((status = stat_rule(current_token, scope_state, global_table)) != OK) return status;
    }

    // handle ... -> T_RCBR
    if (current_token->type == T_RCBR) {
        return status;
    }

    if (!scope_state->in_global || scope_state->in_if || scope_state->in_while) {
        if (current_token->type == T_EOF || current_token->type == K_FUNC) {
            return SYNTAX_ERR;
        }
    }

    // end + ε
    return status;
}

int assign_type_rule(Token_t *current_token, scope_t *scope_state, Htab_t *global_table) {
    int status = OK;

    // handle <ASSIGN_TYPE> -> <FUNC_CALL>
    if (current_token->type == T_FUNC_ID) {
        d_string_replace_str(&function_id, current_token->attribute.string);

        if ((status = func_call_rule(current_token, global_table)) != OK) return status;

        // get function from global table
        Htab_item_t *function = htab_find(global_table, func_call_id.str);
        Htab_item_t *variable = htab_find(global_table, variable_id.str);

        if (variable->data.var->asigned == false){
            if ((status = generate_instruction(DEFVAR, NULL, &variable->data, NULL, 0, stdout)) != OK) return status;
            variable->data.var->asigned = true;
        }
        if ((status = generate_instruction(CALL_FUNC_ASSIGN, &variable->data, &function->data, NULL, 0, stdout)) != OK) return status;
        return status;
    }

    // handle ... -> <EXPR>
    if ((status = expr_rule(current_token, global_table, EXPR_LOC_ASSIGN, scope_state)) != OK) return status;

    // generate assign
    Htab_item_t *variable;
    if (scope_state->in_global == true) {
        variable = htab_find(global_table, variable_id.str);
    } else {
        variable = htab_find(local_table, variable_id.str);
    }
    if (variable == NULL) return SYNTAX_ERR;
    if (variable->data.var->asigned == false){
        if ((status = generate_instruction(DEFVAR, NULL, &variable->data, NULL, 0, stdout)) != OK) return status;
        variable->data.var->asigned = true;
    }

    if ((status = generate_instruction(POPS, NULL, &variable->data, NULL, 0, stdout)) != OK) return status;

    return status;
}

int func_call_rule(Token_t *current_token, Htab_t *global_table) {
    int status = OK;

    // handle <FUNC_CALL> -> T_FUNC_ID
    if (current_token->type != T_FUNC_ID) return SYNTAX_ERR;

    Htab_item_t *function = htab_find(global_table, func_call_id.str);

    // check if func is defined
    if (function == NULL) return UNDEF_FUNC_ERR;  // TODO maybe comment out

    // get new token
    if ((status = scan(current_token)) != OK) return status;

    // handle ... -> ... T_LBR
    if (current_token->type != T_LBR) return SYNTAX_ERR;

    // get new token
    if ((status = scan(current_token)) != OK) return status;

    // handle ... -> ... <PARAM>
    if ((status = param_rule(current_token, global_table, true)) != OK) return status;

    // get new token
    if ((status = scan(current_token)) != OK) return status;

    // handle ... -> ... <PARAM_LIST>
    if ((status = param_list_rule(current_token, global_table)) != OK) return status;

    return status;
}

int expr_rule(Token_t *current_token, Htab_t *global_table, int location, scope_t *scope_state) {
    if (scope_state->in_global) {
        return expr_main(global_table, current_token, location);
    } else {
        return expr_main(local_table, current_token, location);
    }
}
