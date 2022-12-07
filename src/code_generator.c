/**
 * @c file code_generator.c
 * @project IFJ 2022/2023
 * @variant TRP
 *
 * @brief Code generator for IFJcode22
 *
 * @authors <xsklen14> - David Sklenář
 *          <xproch0o> - Marek Procházka
 *          <xzavad20> - Lukáš Zavadil
 *          <xsvetl07> - Adam Světlík
 */

#include "code_generator.h"

void generate_while_start(Operation_t type, char *var1, char *var2, int label, FILE *file) {
    switch (type) {
        case WHILE_EQ:
            fprintf(file, "LABEL .while_start_%d\n", label);

            fprintf(file, "JUMPIFEQ .while_body_%d %s %s\n", label, var1, var2);
            break;
        case WHILE_NEQ:
            fprintf(file, "LABEL .while_start_%d\n", label);
            fprintf(file, "JUMPIFNEQ .while_body_%d %s %s\n", label, var1, var2);
            break;
        case WHILE_LT:
        case WHILE_GT:
            fprintf(file, "DEFVAR GF@%%tmp%d\n", tmp_var_count++);
            fprintf(file, "LABEL .while_start_%d\n", label);
            if (type == WHILE_GT) {
                fprintf(file, "GT GF@%%tmp%d %s %s\n", tmp_var_count - 1, var1, var2);
            } else {  // type == WHILE_LT
                fprintf(file, "LT GF@%%tmp%d %s %s\n", tmp_var_count - 1, var1, var2);
            }
            fprintf(file, "JUMPIFEQ .while_body_%d GF@%%tmp%d bool@true\n", label, tmp_var_count - 1);
            break;
        case WHILE_LEQ:
        case WHILE_GEQ:
            fprintf(file, "DEFVAR GF@%%tmp%d\n", tmp_var_count++);
            fprintf(file, "DEFVAR GF@%%tmp%d\n", tmp_var_count++);
            fprintf(file, "DEFVAR GF@%%tmp%d\n", tmp_var_count++);
            fprintf(file, "LABEL .while_start_%d\n", label);
            if (type == WHILE_GEQ) {
                fprintf(file, "GT GF@%%tmp%d %s %s\n", tmp_var_count - 3, var1, var2);
            } else {  // type == WHILE_LEQ
                fprintf(file, "LT GF@%%tmp%d %s %s\n", tmp_var_count - 3, var1, var2);
            }
            fprintf(file, "EQ GF@%%tmp%d %s %s\n", tmp_var_count - 2, var1, var2);
            fprintf(file, "OR GF@%%tmp%d GF@%%tmp%d GF@%%tmp%d\n", tmp_var_count - 1, tmp_var_count - 3, tmp_var_count - 2);
            fprintf(file, "JUMPIFEQ .while_body_%d GF@%%tmp%d bool@true\n", label, tmp_var_count - 1);
            break;
        default:
            break;
    }
    fprintf(file, "JUMP .while_end_%d\n", label);
    fprintf(file, "LABEL .while_body_%d\n", label);
}

void generate_while_end(int label, FILE *file) {
    fprintf(file, "JUMP .while_start_%d\n", label);
    fprintf(file, "LABEL .while_end_%d\n", label);
}

void generate_if_start(Operation_t type, char *var1, char *var2, int label, FILE *file) {
    switch (type) {
        case IF_EQ:
            fprintf(file, "JUMPIFEQ .if_start_%d %s %s\n", label, var1, var2);
            break;
        case IF_NEQ:
            fprintf(file, "JUMPIFNEQ .if_start_%d %s %s\n", label, var1, var2);
            break;
        case IF_LT:
        case IF_GT:
            fprintf(file, "DEFVAR GF@%%tmp%d\n", tmp_var_count++);
            if (type == IF_GT) {
                fprintf(file, "GT GF@%%tmp%d %s %s\n", tmp_var_count - 1, var1, var2);
            } else {  // type == IF_LT
                fprintf(file, "LT GF@%%tmp%d %s %s\n", tmp_var_count - 1, var1, var2);
            }
            fprintf(file, "JUMPIFEQ .if_start_%d GF@%%tmp%d bool@true\n", label, tmp_var_count - 1);
            break;
        case IF_LEQ:
        case IF_GEQ:
            fprintf(file, "DEFVAR GF@%%tmp%d\n", tmp_var_count++);
            fprintf(file, "DEFVAR GF@%%tmp%d\n", tmp_var_count++);
            fprintf(file, "DEFVAR GF@%%tmp%d\n", tmp_var_count++);
            if (type == IF_GEQ) {
                fprintf(file, "GT GF@%%tmp%d %s %s\n", tmp_var_count - 3, var1, var2);
            } else {  // type == IF_LEQ
                fprintf(file, "LT GF@%%tmp%d %s %s\n", tmp_var_count - 3, var1, var2);
            }
            fprintf(file, "EQ GF@%%tmp%d %s %s\n", tmp_var_count - 2, var1, var2);
            fprintf(file, "OR GF@%%tmp%d GF@%%tmp%d GF@%%tmp%d\n", tmp_var_count - 1, tmp_var_count - 3, tmp_var_count - 2);
            fprintf(file, "JUMPIFEQ .if_start_%d GF@%%tmp%d bool@true\n", label, tmp_var_count - 1);
            break;
        default:
            break;
    }
    fprintf(file, "JUMP .if_else_%d\n", label);
    fprintf(file, "LABEL .if_start_%d\n", label);
}

void generate_else(int label, FILE *file) {
    fprintf(file, "JUMP .if_end_%d\n", label);
    fprintf(file, "LABEL .if_else_%d\n", label);
}

void generate_if_end(int label, FILE *file) { fprintf(file, "LABEL .if_end_%d\n", label); }

void generate_prolog(FILE *file) { fprintf(file, ".IFJcode22\n"); }

void generate_add(char *var1, char *var2, char *destination, FILE *file) { fprintf(file, "ADD %s %s %s\n", destination, var1, var2); }

void generate_sub(char *var1, char *var2, char *destination, FILE *file) { fprintf(file, "SUB %s %s %s\n", destination, var1, var2); }

void generate_mul(char *var1, char *var2, char *destination, FILE *file) { fprintf(file, "MUL %s %s %s\n", destination, var1, var2); }

void generate_div(char *var1, char *var2, char *destination, FILE *file) { fprintf(file, "DIV %s %s %s\n", destination, var1, var2); }

void generate_idiv(char *var1, char *var2, char *destination, FILE *file) { fprintf(file, "IDIV %s %s %s\n", destination, var1, var2); }

void generate_move(char *source, char *destination, FILE *file) { fprintf(file, "MOVE %s %s\n", destination, source); }

void generate_defvar(char *var, FILE *file) { fprintf(file, "DEFVAR %s\n", var); }

void generate_concat(FILE *file) {
    fprintf(file, "DEFVAR GF@%%tmp_concat%d\n", tmp_var_count++);
    fprintf(file, "DEFVAR GF@%%tmp_concat%d\n", tmp_var_count++);
    fprintf(file, "DEFVAR GF@%%tmp_concat%d\n", tmp_var_count++);
    fprintf(file, "POPS GF@%%tmp_concat%d\n", tmp_var_count - 2);
    fprintf(file, "POPS GF@%%tmp_concat%d\n", tmp_var_count - 3);
    fprintf(file, "CONCAT GF@%%tmp_concat%d GF@%%tmp_concat%d GF@%%tmp_concat%d\n", tmp_var_count - 1, tmp_var_count - 3, tmp_var_count - 2);
    fprintf(file, "PUSHS GF@%%tmp_concat%d\n", tmp_var_count - 1);
}

void generate_def_func(Symbol_t *func, FILE *file) {
    fprintf(file, "JUMP .%%end_%s\n", func->attribute);
    fprintf(file, "LABEL .%%%s\n", func->attribute);
    fprintf(file, "CREATEFRAME\n");
    fprintf(file, "PUSHFRAME\n");
    for (int i = 0; i < func->func->argc; i++) {
        fprintf(file, "DEFVAR LF@%s\n", func->func->argv[i].attribute);
        fprintf(file, "POPS LF@%s\n", func->func->argv[i].attribute);
    }
}

void generate_return(Symbol_t *func, Symbol_type_t type, char *attribute, FILE *file) {
    if (attribute != NULL) {
        if (type == VARIABLE || type == CONSTANT) {
            fprintf(file, "PUSHS %s\n", attribute);
        } else if (type == INTERN_VAR) {
            fprintf(file, "PUSHS %%tmp%d\n", tmp_var_count - 1);
        }
    }
    fprintf(file, "POPFRAME\n");
    fprintf(file, "RETURN\n");
    fprintf(file, "LABEL .%%end_%s\n", func->attribute);
}

void generate_func_call(Symbol_t *func, FILE *file) {
    for (int i = func->func->argc; i > 0; i--) {
        if (func->func->argv[i - 1].symbol_type == CONSTANT) {
            switch (func->func->argv[i - 1].const_type) {
                case INT:
                    fprintf(file, "PUSHS int@%s\n", func->func->argv[i - 1].attribute);
                    break;
                case FLOAT:
                    fprintf(file, "PUSHS float@%s\n", func->func->argv[i - 1].attribute);
                    break;
                case STRING:
                    fprintf(file, "PUSHS string@%s\n", func->func->argv[i - 1].attribute);
                    break;
                case BOOL:
                    fprintf(file, "PUSHS bool@%s\n", func->func->argv[i - 1].attribute);
                    break;
                case NIL:
                    fprintf(file, "PUSHS nil@nil\n");
                    break;
            }
        } else if (func->func->argv[i - 1].symbol_type == VARIABLE) {
            switch (func->func->argv[i - 1].var->frame) {
                case GF:
                    fprintf(file, "PUSHS GF@%s\n", func->func->argv[i - 1].attribute);
                    break;
                case LF:
                    fprintf(file, "PUSHS LF@%s\n", func->func->argv[i - 1].attribute);
                    break;
                case TF:
                    fprintf(file, "PUSHS TF@%s\n", func->func->argv[i - 1].attribute);
                    break;
                default:
                    break;
            }
        }
    }
    fprintf(file, "CALL .%%%s\n", func->attribute);
}

void generate_func_call_assign(char *destination, Symbol_t *func, FILE *file) {
    for (int i = func->func->argc; i > 0; i--) {
        if (func->func->argv[i - 1].symbol_type == CONSTANT) {
            switch (func->func->argv[i - 1].const_type) {
                case INT:
                    fprintf(file, "PUSHS int@%s\n", func->func->argv[i - 1].attribute);
                    break;
                case FLOAT:
                    fprintf(file, "PUSHS float@%s\n", func->func->argv[i - 1].attribute);
                    break;
                case STRING:
                    fprintf(file, "PUSHS string@%s\n", func->func->argv[i - 1].attribute);
                    break;
                case BOOL:
                    fprintf(file, "PUSHS bool@%s\n", func->func->argv[i - 1].attribute);
                    break;
                case NIL:
                    fprintf(file, "PUSHS nil@nil\n");
                    break;
            }
        } else if (func->func->argv[i - 1].symbol_type == VARIABLE) {
            switch (func->func->argv[i - 1].var->frame) {
                case GF:
                    fprintf(file, "PUSHS GF@%s\n", func->func->argv[i - 1].attribute);
                    break;
                case LF:
                    fprintf(file, "PUSHS LF@%s\n", func->func->argv[i - 1].attribute);
                    break;
                case TF:
                    fprintf(file, "PUSHS TF@%s\n", func->func->argv[i - 1].attribute);
                    break;
                default:
                    break;
            }
        }
    }
    fprintf(file, "CALL .%%%s\n", func->attribute);
    fprintf(file, "POPS %s\n", destination);
}
int generate_instruction(Operation_t operation, Symbol_t *dest_in, Symbol_t *var_in_1, Symbol_t *var_in_2, int label, FILE *file) {
    DString_t var1, var2, dest;
    d_string_init(&var1);
    d_string_init(&var2);
    d_string_init(&dest);
    if (dest_in != NULL) {
        if (dest_in->symbol_type == VARIABLE || dest_in->symbol_type == INTERN_VAR) {
            CHECK_OK(variable_convert(dest_in, &dest));
        } else if (dest_in->symbol_type == CONSTANT) {
            CHECK_OK(const_convert(dest_in, &dest));
        }
    }
    if (var_in_1 != NULL) {
        if (var_in_1->symbol_type == VARIABLE) {
            CHECK_OK(variable_convert(var_in_1, &var1));
        } else if (var_in_1->symbol_type == CONSTANT) {
            CHECK_OK(const_convert(var_in_1, &var1));
        }
    }
    if (var_in_2 != NULL) {
        if (var_in_2->symbol_type == VARIABLE) {
            CHECK_OK(variable_convert(var_in_2, &var2));
        } else if (var_in_2->symbol_type == CONSTANT) {
            CHECK_OK(const_convert(var_in_2, &var2));
        }
    }

    // generate
    switch (operation) {
        // IF CASES
        case IF_LT:
        case IF_GT:
        case IF_EQ:
        case IF_GEQ:
        case IF_LEQ:
        case IF_NEQ:
            generate_if_start(operation, var1.str, var2.str, label, file);
            break;
        case IF_ELSE:
            generate_else(label, file);
            break;
        case IF_END:
            generate_if_end(label, file);
            break;
        // WHILE CASES
        case WHILE_LT:
        case WHILE_GT:
        case WHILE_EQ:
        case WHILE_GEQ:
        case WHILE_LEQ:
        case WHILE_NEQ:
            generate_while_start(operation, var1.str, var2.str, label, file);
            break;
        case WHILE_END:
            generate_while_end(label, file);
            break;
        // ARITHMETIC CASES
        case ADD:
            generate_add(var1.str, var2.str, dest.str, file);
            break;
        case SUB:
            generate_sub(var1.str, var2.str, dest.str, file);
            break;
        case MUL:
            generate_mul(var1.str, var2.str, dest.str, file);
            break;
        case DIV:
            generate_div(var1.str, var2.str, dest.str, file);
            break;
        case IDIV:
            generate_idiv(var1.str, var2.str, dest.str, file);
            break;

        case ASSIGN:
            generate_move(var1.str, dest.str, file);
            break;
        case DEFVAR:
            generate_defvar(var1.str, file);
            break;
        case PROLOG:
            generate_prolog(file);
            break;
        case CALL_FUNC:
            if (strcmp(var1.str, "write") == 0) {
                for (int i = 0; i < var_in_1->func->argc; i++) {
                    if (var_in_1->func->argv[i - 1].symbol_type == CONSTANT) {
                        switch (var_in_1->func->argv[i - 1].const_type) {
                            case INT:
                                fprintf(file, "PUSHS int@%s\n", var_in_1->func->argv[i - 1].attribute);
                                break;
                            case FLOAT:
                                fprintf(file, "PUSHS float@%s\n", var_in_1->func->argv[i - 1].attribute);
                                break;
                            case STRING:
                                fprintf(file, "PUSHS string@%s\n", var_in_1->func->argv[i - 1].attribute);
                                break;
                            case BOOL:
                                fprintf(file, "PUSHS bool@%s\n", var_in_1->func->argv[i - 1].attribute);
                                break;
                            case NIL:
                                fprintf(file, "PUSHS string@\n");
                                break;
                        }
                    } else if (var_in_1->func->argv[i - 1].symbol_type == VARIABLE) {
                        switch (var_in_1->func->argv[i - 1].var->frame) {
                            case GF:
                                fprintf(file, "PUSHS GF@%s\n", var_in_1->func->argv[i - 1].attribute);
                                break;
                            case LF:
                                fprintf(file, "PUSHS LF@%s\n", var_in_1->func->argv[i - 1].attribute);
                                break;
                            case TF:
                                fprintf(file, "PUSHS TF@%s\n", var_in_1->func->argv[i - 1].attribute);
                                break;
                            default:
                                break;
                        }
                    }
                    fprintf(file, "CALL .%%write\n");
                }
            } else {
                generate_func_call(var_in_1, file);
            }
            break;
        case CALL_FUNC_ASSIGN:
            generate_func_call_assign(dest.str, var_in_1, file);
            break;
        case DEF_FUNC:
            generate_def_func(var_in_1, file);
            break;
        case CONCAT:
            generate_concat(file);
            break;
        case RETURN:
            if (var_in_1 != NULL) {
                generate_return(var_in_2, var_in_1->symbol_type, var1.str, file);
            } else {
                generate_return(var_in_2, 0, NULL, file);
            }
            break;
        default:
            return INTERNAL_ERR;

        case PUSHS:
            fprintf(file, "PUSHS %s\n", var1.str);
            break;
        case IF:
            fprintf(file, "PUSHS bool@true\n");
            fprintf(file, "JUMPIFEQS .if_start_%d\n", label);
            fprintf(file, "JUMP .if_else_%d\n", label);
            fprintf(file, "LABEL .if_start_%d\n", label);
            break;
        case WHILE:
            fprintf(file, "LABEL .while_start_%d\n", label);
            fprintf(file, "PUSHS bool@true\n");
            fprintf(file, "JUMPIFEQS .while_body_%d\n", label);
            fprintf(file, "JUMP .while_end_%d\n", label);
            fprintf(file, "LABEL .while_body_%d\n", label);
            break;
        case ADDS:
            fprintf(file, "ADDS\n");
            break;
        case SUBS:
            fprintf(file, "SUBS\n");
            break;
        case MULS:
            fprintf(file, "MULS\n");
            break;
        case DIVS:
            fprintf(file, "DIVS\n");
            break;
        case IDIVS:
            fprintf(file, "IDIVS\n");
            break;
        case LTS:
            fprintf(file, "LTS\n");
            break;
        case GTS:
            fprintf(file, "GTS\n");
            break;
        case EQS:
            fprintf(file, "EQS\n");
            break;
        case ANDS:
            fprintf(file, "ANDS\n");
            break;
        case ORS:
            fprintf(file, "ORS\n");
            break;
        case NOTS:
            fprintf(file, "NOTS\n");
            break;
        case POPS:
            fprintf(file, "POPS %s\n", var1.str);
            break;
    }
    return OK;
}

int variable_convert(Symbol_t *variable, DString_t *converted_var) {
    CHECK_NULL(variable);
    DString_t string;
    CHECK_OK(d_string_init(&string));
    if (variable->symbol_type == INTERN_VAR) {
        char tmp[INTERN_VAR_LEN + 1];
        sprintf(tmp, "GF@%%tmp%d", tmp_var_count++);
        CHECK_OK(d_string_add_str(&string, tmp));
        return OK;
    }
    switch (variable->var->frame) {
        case GF:
            CHECK_OK(d_string_add_str(&string, "GF@"));
            break;
        case LF:
            CHECK_OK(d_string_add_str(&string, "LF@"));
            break;
        case TF:
            CHECK_OK(d_string_add_str(&string, "TF@"));
            break;
        case UNDEF:
            return OK;
        default:
            break;
    }
    CHECK_OK(d_string_add_str(&string, variable->attribute));
    CHECK_OK(d_string_copy(&string, converted_var));
    return OK;
}

int const_convert(Symbol_t *constant, DString_t *converted_const) {
    CHECK_NULL(constant);
    DString_t string;
    CHECK_OK(d_string_init(&string));
    if (constant->const_type == INT) {
        CHECK_OK(d_string_add_str(&string, "int@"));
        CHECK_OK(d_string_add_str(&string, constant->attribute));
    } else if (constant->const_type == FLOAT) {
        CHECK_OK(d_string_add_str(&string, "float@"));
        CHECK_OK(d_string_add_str(&string, constant->attribute));
    } else if (constant->const_type == STRING) {
        CHECK_OK(string_convert(constant, converted_const));
        return OK;
    } else if (constant->const_type == NIL) {
        CHECK_OK(d_string_add_str(&string, "nil@nil"));
    } else {
        return INTERNAL_ERR;
    }
    CHECK_OK(d_string_copy(&string, converted_const));
    return OK;
}

int string_convert(Symbol_t *string, DString_t *converted_str) {
    char code[5];
    CHECK_OK(d_string_add_str(converted_str, "string@"));
    int len = (int)strlen(string->attribute);
    for (int i = 0; i < len; i++) {
        if ((string->attribute[i] >= 0 && string->attribute[i] <= 32) || string->attribute[i] == 35 || string->attribute[i] == 92) {
            sprintf(code, "\\%03d", string->attribute[i]);
            CHECK_OK(d_string_add_str(converted_str, code));
        } else {
            CHECK_OK(d_string_add_char(converted_str, string->attribute[i]));
        }
    }
    return OK;
}

// Build-in functions

void built_in_floatval(FILE *file) {
    fprintf(file, "JUMP .%%end_floatval\n");
    fprintf(file, "LABEL .%%floatval\n");
    fprintf(file, "CREATEFRAME\n");
    fprintf(file, "PUSHFRAME\n");
    fprintf(file, "DEFVAR LF@%%fvl_retval\n");
    fprintf(file, "DEFVAR LF@%%fvl_tmp1\n");
    fprintf(file, "DEFVAR LF@%%fvl_symb\n");

    fprintf(file, "POPS LF@%%fvl_tmp1\n");
    fprintf(file, "TYPE LF@%%fvl_symb LF@%%fvl_tmp1\n");
    fprintf(file, "JUMPIFEQ .%%floatval_int LF@%%fvl_symb string@int\n");
    fprintf(file, "JUMPIFEQ .%%floatval_float LF@%%fvl_symb string@float\n");
    fprintf(file, "JUMPIFEQ .%%floatval_nil LF@%%fvl_symb string@nil\n");
    fprintf(file, "EXIT int@4\n");

    fprintf(file, "LABEL .%%floatval_int\n");
    fprintf(file, "INT2FLOAT LF@%%fvl_retval LF@%%fvl_tmp1\n");
    fprintf(file, "JUMP .%%floatval$end\n");

    fprintf(file, "LABEL .%%floatval_float\n");
    fprintf(file, "MOVE LF@%%fvl_retval LF@%%fvl_tmp1\n");
    fprintf(file, "JUMP .%%floatval$end\n");

    fprintf(file, "LABEL .%%floatval_nil\n");
    fprintf(file, "MOVE LF@%%fvl_retval float@0x0p+0\n");
    fprintf(file, "JUMP .%%floatval$end\n");

    fprintf(file, "LABEL .%%floatval$end\n");
    fprintf(file, "PUSHS LF@%%fvl_retval\n");
    fprintf(file, "POPFRAME\n");
    fprintf(file, "RETURN\n");
    fprintf(file, "LABEL .%%end_floatval\n");
}

void built_in_intval(FILE *file) {
    fprintf(file, "JUMP .%%end_intval\n");
    fprintf(file, "LABEL .%%intval\n");
    fprintf(file, "CREATEFRAME\n");
    fprintf(file, "PUSHFRAME\n");
    fprintf(file, "DEFVAR LF@%%ivl_retval\n");
    fprintf(file, "DEFVAR LF@%%ivl_tmp1\n");
    fprintf(file, "DEFVAR LF@%%ivl_symb\n");

    fprintf(file, "POPS LF@%%ivl_tmp1\n");
    fprintf(file, "TYPE LF@%%ivl_symb LF@%%ivl_tmp1\n");
    fprintf(file, "JUMPIFEQ .%%intval_int LF@%%ivl_symb string@int\n");
    fprintf(file, "JUMPIFEQ .%%intval_float LF@%%ivl_symb string@float\n");
    fprintf(file, "JUMPIFEQ .%%intval_nil LF@%%ivl_symb string@nil\n");
    fprintf(file, "EXIT int@4\n");

    fprintf(file, "LABEL .%%intval_int\n");
    fprintf(file, "MOVE LF@%%ivl_retval LF@%%ivl_tmp1\n");
    fprintf(file, "JUMP .%%intval$end\n");

    fprintf(file, "LABEL .%%intval_float\n");
    fprintf(file, "FLOAT2INT LF@%%ivl_retval LF@%%ivl_tmp1\n");
    fprintf(file, "JUMP .%%intval$end\n");

    fprintf(file, "LABEL .%%intval_nil\n");
    fprintf(file, "MOVE LF@%%ivl_retval int@0\n");
    fprintf(file, "JUMP .%%intval$end\n");

    fprintf(file, "LABEL .%%intval$end\n");
    fprintf(file, "PUSHS LF@%%ivl_retval\n");
    fprintf(file, "POPFRAME\n");
    fprintf(file, "RETURN\n");
    fprintf(file, "LABEL .%%end_intval\n");
}

void built_in_strval(FILE *file) {
    fprintf(file, "JUMP .%%end_strval\n");
    fprintf(file, "LABEL .%%strval\n");
    fprintf(file, "CREATEFRAME\n");
    fprintf(file, "PUSHFRAME\n");
    fprintf(file, "DEFVAR LF@%%svl_retval\n");
    fprintf(file, "DEFVAR LF@%%svl_tmp1\n");
    fprintf(file, "DEFVAR LF@%%svl_symb\n");

    fprintf(file, "POPS LF@%%svl_tmp1\n");
    fprintf(file, "TYPE LF@%%svl_symb LF@%%svl_tmp1\n");
    fprintf(file, "JUMPIFEQ .%%strval_nil LF@%%svl_symb string@nil\n");
    fprintf(file, "JUMPIFEQ .%%strval_string LF@%%svl_symb string@string\n");
    fprintf(file, "EXIT int@4\n");

    fprintf(file, "LABEL .%%strval_nil\n");
    fprintf(file, "MOVE LF@%%svl_retval string@\\000\n");
    fprintf(file, "JUMP .%%strval$end\n");

    fprintf(file, "LABEL .%%strval_string\n");
    fprintf(file, "MOVE LF@%%svl_retval LF@%%svl_tmp1\n");
    fprintf(file, "JUMP .%%strval$end\n");

    fprintf(file, "LABEL .%%strval$end\n");
    fprintf(file, "PUSHS LF@%%svl_retval\n");
    fprintf(file, "POPFRAME\n");
    fprintf(file, "RETURN\n");
    fprintf(file, "LABEL .%%end_strval\n");
}

void built_in_substring(FILE *file) {
    fprintf(file, "JUMP .%%end_substring\n");
    fprintf(file, "LABEL .%%substring\n");
    fprintf(file, "CREATEFRAME\n");
    fprintf(file, "PUSHFRAME\n");
    fprintf(file, "DEFVAR LF@%%str_retval\n");
    fprintf(file, "MOVE LF@%%str_retval string@\n");
    fprintf(file, "DEFVAR LF@%%str_j\n");
    fprintf(file, "DEFVAR LF@%%str_i\n");
    fprintf(file, "DEFVAR LF@%%str_str\n");
    fprintf(file, "POPS LF@%%str_str\n");

    fprintf(file, "DEFVAR LF@%%str_type\n");
    fprintf(file, "TYPE LF@%%str_type LF@%%str_str\n");
    fprintf(file, "JUMPIFNEQ .%%str_type_wrong LF@%%str_type string@string\n");

    fprintf(file, "POPS LF@%%str_i\n");

    fprintf(file, "TYPE LF@%%str_type LF@%%str_i\n");
    fprintf(file, "JUMPIFNEQ .%%str_type_wrong LF@%%str_type string@int\n");

    fprintf(file, "POPS LF@%%str_j\n");

    fprintf(file, "TYPE LF@%%str_type LF@%%str_j\n");
    fprintf(file, "JUMPIFNEQ .%%str_type_wrong LF@%%str_type string@int\n");

    fprintf(file, "DEFVAR LF@%%str_bool_tmp1\n");
    fprintf(file, "LT LF@%%str_bool_tmp1 LF@%%str_i int@0\n");
    fprintf(file, "JUMPIFEQ .%%nil_ret LF@%%str_bool_tmp1 bool@true\n");
    fprintf(file, "LT LF@%%str_bool_tmp1 LF@%%str_j int@0\n");
    fprintf(file, "JUMPIFEQ .%%nil_ret LF@%%str_bool_tmp1 bool@true\n");
    fprintf(file, "GT LF@%%str_bool_tmp1 LF@%%str_i LF@%%str_j\n");
    fprintf(file, "JUMPIFEQ .%%nil_ret LF@%%str_bool_tmp1 bool@true\n");
    fprintf(file, "DEFVAR LF@%%str_bool_tmp2\n");
    fprintf(file, "DEFVAR LF@%%str_bool_tmp3\n");
    fprintf(file, "DEFVAR LF@%%str_int_len\n");
    fprintf(file, "STRLEN LF@%%str_int_len LF@%%str_str\n");
    fprintf(file, "GT LF@%%str_bool_tmp2 LF@%%str_i LF@%%str_int_len\n");
    fprintf(file, "EQ LF@%%str_bool_tmp3 LF@%%str_i LF@%%str_int_len\n");
    fprintf(file, "OR LF@%%str_bool_tmp1 LF@%%str_bool_tmp2 LF@%%str_bool_tmp3\n");
    fprintf(file, "JUMPIFEQ .%%nil_ret LF@%%str_bool_tmp1 bool@true\n");
    fprintf(file, "GT LF@%%str_bool_tmp1 LF@%%str_j LF@%%str_int_len\n");
    fprintf(file, "JUMPIFEQ .%%nil_ret LF@%%str_bool_tmp1 bool@true\n");
    fprintf(file, "DEFVAR LF@%%str_curr_char\n");
    fprintf(file, "LABEL .%%substr_loop\n");
    fprintf(file, "GETCHAR LF@%%str_curr_char LF@%%str_str LF@%%str_i\n");
    fprintf(file, "CONCAT LF@%%str_retval LF@%%str_retval LF@%%str_curr_char\n");
    fprintf(file, "ADD LF@%%str_i LF@%%str_i int@1\n");
    fprintf(file, "JUMPIFNEQ .%%substr_loop LF@%%str_i LF@%%str_j\n");
    fprintf(file, "PUSHS LF@%%str_retval\n");
    fprintf(file, "POPFRAME\n");
    fprintf(file, "RETURN\n");
    fprintf(file, "LABEL .%%str_type_wrong\n");
    fprintf(file, "EXIT int@4\n");
    fprintf(file, "LABEL .%%end_substring\n");
}

void built_in_reads(FILE *file) {
    fprintf(file, "JUMP .%%end_reads\n");
    fprintf(file, "LABEL .%%reads\n");
    fprintf(file, "CREATEFRAME\n");
    fprintf(file, "PUSHFRAME\n");
    fprintf(file, "DEFVAR LF@%%reads_retval\n");
    fprintf(file, "READ LF@%%reads_retval string\n");

    fprintf(file, "DEFVAR LF@%%reads_type\n");
    fprintf(file, "TYPE LF@%%reads_type LF@%%reads_retval\n");
    fprintf(file, "JUMPIFEQ .%%reads_no_err LF@%%reads_type string@string\n");
    fprintf(file, "MOVE LF@%%reads_retval nil@nil\n");
    fprintf(file, "LABEL .%%reads_no_err\n");

    fprintf(file, "PUSHS LF@%%reads_retval\n");
    fprintf(file, "POPFRAME\n");
    fprintf(file, "RETURN\n");
    fprintf(file, "LABEL .%%end_reads\n");
}

void built_in_readi(FILE *file) {
    fprintf(file, "JUMP .%%end_readi\n");
    fprintf(file, "LABEL .%%readi\n");
    fprintf(file, "CREATEFRAME\n");
    fprintf(file, "PUSHFRAME\n");
    fprintf(file, "DEFVAR LF@%%readi_retval\n");
    fprintf(file, "READ LF@%%readi_retval int\n");

    fprintf(file, "DEFVAR LF@%%readi_type\n");
    fprintf(file, "TYPE LF@%%readi_type LF@%%readi_retval\n");
    fprintf(file, "JUMPIFEQ .%%readi_no_err LF@%%readi_type string@int\n");
    fprintf(file, "MOVE LF@%%readi_retval nil@nil\n");
    fprintf(file, "LABEL .%%readi_no_err\n");

    fprintf(file, "PUSHS LF@%%readi_retval\n");
    fprintf(file, "POPFRAME\n");
    fprintf(file, "RETURN\n");
    fprintf(file, "LABEL .%%end_readi\n");
}

void built_in_readf(FILE *file) {
    fprintf(file, "JUMP .%%end_readf\n");
    fprintf(file, "LABEL .%%readf\n");
    fprintf(file, "CREATEFRAME\n");
    fprintf(file, "PUSHFRAME\n");
    fprintf(file, "DEFVAR LF@%%readf_retval\n");
    fprintf(file, "READ LF@%%readf_retval float\n");

    fprintf(file, "DEFVAR LF@%%readf_type\n");
    fprintf(file, "TYPE LF@%%readf_type LF@%%readf_retval\n");
    fprintf(file, "JUMPIFEQ .%%readf_no_err LF@%%readf_type string@float\n");
    fprintf(file, "MOVE LF@%%readf_retval nil@nil\n");
    fprintf(file, "LABEL .%%readf_no_err\n");

    fprintf(file, "PUSHS LF@%%readf_retval\n");
    fprintf(file, "POPFRAME\n");
    fprintf(file, "RETURN\n");
    fprintf(file, "LABEL .%%end_readf\n");
}

void built_in_write(FILE *file) {
    fprintf(file, "JUMP .%%end_write\n");
    fprintf(file, "LABEL .%%write\n");
    fprintf(file, "CREATEFRAME\n");
    fprintf(file, "PUSHFRAME\n");
    fprintf(file, "DEFVAR LF@%%write_str\n");
    fprintf(file, "DEFVAR LF@%%write_type\n");
    fprintf(file, "POPS LF@%%write_str\n");
    fprintf(file, "TYPE LF@%%write_type LF@%%write_str\n");
    fprintf(file, "JUMPIFEQ .%%write_empty_str LF@%%write_type string@nil\n");
    fprintf(file, "WRITE LF@%%write_str\n");
    fprintf(file, "POPFRAME\n");
    fprintf(file, "RETURN\n");
    fprintf(file, "LABEL .%%write_empty_str\n");
    fprintf(file, "WRITE string@\n");
    fprintf(file, "POPFRAME\n");
    fprintf(file, "RETURN\n");
    fprintf(file, "LABEL .%%end_write\n");
}

void built_in_strlen(FILE *file) {
    fprintf(file, "JUMP .%%end_strlen\n");
    fprintf(file, "LABEL .%%strlen\n");
    fprintf(file, "CREATEFRAME\n");
    fprintf(file, "PUSHFRAME\n");
    fprintf(file, "DEFVAR LF@%%strlen_retval\n");
    fprintf(file, "DEFVAR LF@%%strlen_str\n");

    fprintf(file, "DEFVAR LF@%%strlen_type\n");
    fprintf(file, "POPS LF@%%strlen_str\n");

    fprintf(file, "TYPE LF@%%strlen_type LF@%%strlen_str\n");
    fprintf(file, "JUMPIFEQ .%%strlen_no_err LF@%%strlen_type string@string\n");
    fprintf(file, "EXIT int@4\n");
    fprintf(file, "LABEL .%%strlen_no_err\n");

    fprintf(file, "STRLEN LF@%%strlen_retval LF@%%strlen_str\n");
    fprintf(file, "PUSHS LF@%%strlen_retval\n");
    fprintf(file, "POPFRAME\n");
    fprintf(file, "RETURN\n");
    fprintf(file, "LABEL .%%end_strlen\n");
}

void built_in_ord(FILE *file) {
    fprintf(file, "JUMP .%%end_ord\n");
    fprintf(file, "LABEL .%%ord\n");
    fprintf(file, "CREATEFRAME\n");
    fprintf(file, "PUSHFRAME\n");
    fprintf(file, "DEFVAR LF@%%ord_str\n");
    fprintf(file, "POPS LF@%%ord_str\n");

    fprintf(file, "DEFVAR LF@%%ord_type\n");
    fprintf(file, "TYPE LF@%%ord_type LF@%%ord_str\n");
    fprintf(file, "JUMPIFEQ .%%ord_no_err LF@%%ord_type string@string\n");
    fprintf(file, "EXIT int@4\n");
    fprintf(file, "LABEL .%%ord_no_err\n");

    fprintf(file, "JUMPIFEQ .%%ord_ret LF@%%ord_str string@\n");
    fprintf(file, "DEFVAR LF@%%ord_retval\n");
    fprintf(file, "STRI2INT LF@%%ord_retval LF@%%ord_str int@0\n");
    fprintf(file, "PUSHS LF@%%ord_retval\n");
    fprintf(file, "POPFRAME\n");
    fprintf(file, "RETURN\n");
    fprintf(file, "LABEL .%%ord_ret\n");
    fprintf(file, "PUSHS int@0\n");
    fprintf(file, "POPFRAME\n");
    fprintf(file, "RETURN\n");
    fprintf(file, "LABEL .%%end_ord\n");
}

void built_in_chr(FILE *file) {
    fprintf(file, "JUMP .%%end_chr\n");
    fprintf(file, "LABEL .%%chr\n");
    fprintf(file, "CREATEFRAME\n");
    fprintf(file, "PUSHFRAME\n");
    fprintf(file, "DEFVAR LF@%%chr_retval\n");
    fprintf(file, "DEFVAR LF@%%chr_int\n");
    fprintf(file, "POPS LF@%%chr_int\n");

    fprintf(file, "DEFVAR LF@%%chr_type\n");
    fprintf(file, "TYPE LF@%%chr_type LF@%%chr_int\n");
    fprintf(file, "JUMPIFEQ .%%chr_no_err LF@%%chr_type string@int\n");
    fprintf(file, "EXIT int@4\n");
    fprintf(file, "LABEL .%%chr_no_err\n");

    fprintf(file, "INT2CHAR LF@%%chr_retval LF@%%chr_int\n");
    fprintf(file, "PUSHS LF@%%chr_retval\n");
    fprintf(file, "POPFRAME\n");
    fprintf(file, "RETURN\n");
    fprintf(file, "LABEL .%%end_chr\n");
}

void print_built_in(FILE *file) {
    built_in_readi(file);
    built_in_readf(file);
    built_in_reads(file);
    built_in_write(file);
    built_in_floatval(file);
    built_in_intval(file);
    built_in_strval(file);
    built_in_strlen(file);
    built_in_substring(file);
    built_in_ord(file);
    built_in_chr(file);
}
