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

void generate_while_start(Operation_t type, char *var1, char *var2, int label,
                          FILE *file) {
    switch (type) {
        case WHILE_EQ:
            fprintf(file, "LABEL .while_start_%d\n", label);
            fprintf(file, "JUMPIFEQ .while_body_%d %s %s\n", label, var1, var2);
            break;
        case WHILE_NEQ:
            fprintf(file, "LABEL .while_start_%d\n", label);
            fprintf(file, "JUMPIFNEQ .while_body_%d %s %s\n", label, var1,
                    var2);
            break;
        case WHILE_LT:
        case WHILE_GT:
            fprintf(file, "DEFVAR GF@%%tmp%d\n", tmp_var_count++);
            fprintf(file, "LABEL .while_start_%d\n", label);
            if (type == WHILE_GT) {
                fprintf(file, "GT GF@%%tmp%d %s %s\n", tmp_var_count - 1, var1,
                        var2);
            } else {  // type == WHILE_LT
                fprintf(file, "LT GF@%%tmp%d %s %s\n", tmp_var_count - 1, var1,
                        var2);
            }
            fprintf(file, "JUMPIFEQ .while_body_%d GF@%%tmp%d bool@true\n",
                    label, tmp_var_count - 1);
            break;
        case WHILE_LEQ:
        case WHILE_GEQ:
            fprintf(file, "DEFVAR GF@%%tmp%d\n", tmp_var_count++);
            fprintf(file, "DEFVAR GF@%%tmp%d\n", tmp_var_count++);
            fprintf(file, "DEFVAR GF@%%tmp%d\n", tmp_var_count++);
            fprintf(file, "LABEL .while_start_%d\n", label);
            if (type == WHILE_GEQ) {
                fprintf(file, "GT GF@%%tmp%d %s %s\n", tmp_var_count - 3, var1,
                        var2);
            } else {  // type == WHILE_LEQ
                fprintf(file, "LT GF@%%tmp%d %s %s\n", tmp_var_count - 3, var1,
                        var2);
            }
            fprintf(file, "EQ GF@%%tmp%d %s %s\n", tmp_var_count - 2, var1,
                    var2);
            fprintf(file, "OR GF@%%tmp%d GF@%%tmp%d GF@%%tmp%d\n",
                    tmp_var_count - 1, tmp_var_count - 3, tmp_var_count - 2);
            fprintf(file, "JUMPIFEQ .while_body_%d GF@%%tmp%d bool@true\n",
                    label, tmp_var_count - 1);
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

void generate_if_start(Operation_t type, char *var1, char *var2, int label,
                       FILE *file) {
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
                fprintf(file, "GT GF@%%tmp%d %s %s\n", tmp_var_count - 1, var1,
                        var2);
            } else {  // type == IF_LT
                fprintf(file, "LT GF@%%tmp%d %s %s\n", tmp_var_count - 1, var1,
                        var2);
            }
            fprintf(file, "JUMPIFEQ .if_start_%d GF@%%tmp%d bool@true\n", label,
                    tmp_var_count - 1);
            break;
        case IF_LEQ:
        case IF_GEQ:
            fprintf(file, "DEFVAR GF@%%tmp%d\n", tmp_var_count++);
            fprintf(file, "DEFVAR GF@%%tmp%d\n", tmp_var_count++);
            fprintf(file, "DEFVAR GF@%%tmp%d\n", tmp_var_count++);
            if (type == IF_GEQ) {
                fprintf(file, "GT GF@%%tmp%d %s %s\n", tmp_var_count - 3, var1,
                        var2);
            } else {  // type == IF_LEQ
                fprintf(file, "LT GF@%%tmp%d %s %s\n", tmp_var_count - 3, var1,
                        var2);
            }
            fprintf(file, "EQ GF@%%tmp%d %s %s\n", tmp_var_count - 2, var1,
                    var2);
            fprintf(file, "OR GF@%%tmp%d GF@%%tmp%d GF@%%tmp%d\n",
                    tmp_var_count - 1, tmp_var_count - 3, tmp_var_count - 2);
            fprintf(file, "JUMPIFEQ .if_start_%d GF@%%tmp%d bool@true\n", label,
                    tmp_var_count - 1);
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

void generate_if_end(int label, FILE *file) {
    fprintf(file, "LABEL .if_end_%d\n", label);
}

void generate_prolog(FILE *file) { fprintf(file, ".IFJcode22\n"); }

void generate_add(char *var1, char *var2, char *destination, FILE *file) {
    fprintf(file, "ADD %s %s %s\n", destination, var1, var2);
}

void generate_sub(char *var1, char *var2, char *destination, FILE *file) {
    fprintf(file, "SUB %s %s %s\n", destination, var1, var2);
}

void generate_mul(char *var1, char *var2, char *destination, FILE *file) {
    fprintf(file, "MUL %s %s %s\n", destination, var1, var2);
}

void generate_div(char *var1, char *var2, char *destination, FILE *file) {
    fprintf(file, "DIV %s %s %s\n", destination, var1, var2);
}

void generate_idiv(char *var1, char *var2, char *destination, FILE *file) {
    fprintf(file, "IDIV %s %s %s\n", destination, var1, var2);
}

void generate_move(char *source, char *destination, FILE *file) {
    fprintf(file, "MOVE %s %s\n", destination, source);
}

void generate_lt(char *var1, char *var2, char *destination, FILE *file) {
    fprintf(file, "LT %s %s %s\n", destination, var1, var2);
}

void generate_gt(char *var1, char *var2, char *destination, FILE *file) {
    fprintf(file, "GT %s %s %s\n", destination, var1, var2);
}

void generate_eq(char *var1, char *var2, char *destination, FILE *file) {
    fprintf(file, "EQ %s %s %s\n", destination, var1, var2);
}

void generate_and(char *var1, char *var2, char *destination, FILE *file) {
    fprintf(file, "AND %s %s %s\n", destination, var1, var2);
}

void generate_or(char *var1, char *var2, char *destination, FILE *file) {
    fprintf(file, "OR %s %s %s\n", destination, var1, var2);
}

void generate_not(char *source, char *destination, FILE *file) {
    fprintf(file, "NOT %s %s\n", destination, source);
}

void generate_createframe(FILE *file) { fprintf(file, "CREATEFRAME\n"); }

void generate_pushframe(FILE *file) { fprintf(file, "PUSHFRAME\n"); }

void generate_popframe(FILE *file) { fprintf(file, "POPFRAME\n"); }

void generate_defvar(char *var, FILE *file) {
    fprintf(file, "DEFVAR %s\n", var);
}

void generate_call(char *label, FILE *file) {
    fprintf(file, "CALL %s\n", label);
}

void generate_pushs(char *var, FILE *file) { fprintf(file, "PUSHS %s\n", var); }

void generate_pops(char *var, FILE *file) { fprintf(file, "POPS %s\n", var); }

void generate_clears(FILE *file) { fprintf(file, "CLEARS\n"); }

void generate_int2float(char *source, char *destination, FILE *file) {
    fprintf(file, "INT2FLOAT %s %s\n", destination, source);
}

void generate_float2int(char *source, char *destination, FILE *file) {
    fprintf(file, "FLOAT2INT %s %s\n", destination, source);
}

void generate_int2char(char *source, char *destination, FILE *file) {
    fprintf(file, "INT2CHAR %s %s\n", destination, source);
}

void generate_stri2int(char *var1, char *var2, char *destination, FILE *file) {
    fprintf(file, "STRI2INT %s %s %s\n", destination, var1, var2);
}

void generate_read(char *var, char *type, FILE *file) {
    fprintf(file, "READ %s %s\n", var, type);
}

void generate_write(char *var, FILE *file) { fprintf(file, "WRITE %s\n", var); }

void generate_concat(char *var1, char *var2, char *destination, FILE *file) {
    fprintf(file, "CONCAT %s %s %s\n", destination, var1, var2);
}

void generate_strlen(char *source, char *destination, FILE *file) {
    fprintf(file, "STRLEN %s %s\n", destination, source);
}

void generate_getchar(char *var, char *pos, char *destination, FILE *file) {
    fprintf(file, "GETCHAR %s %s %s\n", destination, var, pos);
}

void generate_setchar(char *var, char *pos, char *ch, FILE *file) {
    fprintf(file, "SETCHAR %s %s %s\n", var, pos, ch);
}

void generate_type(char *source, char *destination, FILE *file) {
    fprintf(file, "TYPE %s %s\n", destination, source);
}

void generate_label(char *label, FILE *file) {
    fprintf(file, "LABEL %s\n", label);
}

void generate_jump(char *label, FILE *file) {
    fprintf(file, "JUMP %s\n", label);
}

void generate_jumpifeq(char *label, char *var1, char *var2, FILE *file) {
    fprintf(file, "JUMPIFEQ %s %s %s\n", label, var1, var2);
}

void generate_jumpifneq(char *label, char *var1, char *var2, FILE *file) {
    fprintf(file, "JUMPIFNEQ %s %s %s\n", label, var1, var2);
}

void generate_exit(char *var, FILE *file) { fprintf(file, "EXIT %s\n", var); }

void generate_break(FILE *file) { fprintf(file, "BREAK\n"); }

void generate_dprint(char *var, FILE *file) {
    fprintf(file, "DPRINT %s\n", var);
}

void generate_def_func(Symbol_t *func, FILE *file) {
    fprintf(file, "JUMP .end_%s\n", func->attribute);
    fprintf(file, "LABEL .%s\n", func->attribute);
    fprintf(file, "CREATEFRAME\n");
    fprintf(file, "PUSHFRAME\n");
    for (int i = 0; i < func->func->argc; i++) {
        fprintf(file, "DEFVAR LF@%s\n", func->func->argv[i].attribute);
        fprintf(file, "POPS LF@%s\n", func->func->argv[i].attribute);
    }
}

void generate_return(Symbol_t *func, Symbol_type_t type, char *attribute,
                     FILE *file) {
    // TODO: need to pass func->attribute from PARSER to write end label of
    // function
    if (attribute != NULL) {
        if (type == VARIABLE || type == CONSTANT) {
            fprintf(file, "PUSHS %s\n", attribute);
        } else if (type == INTERN_VAR) {
            fprintf(file, "PUSHS %%tmp%d\n", tmp_var_count - 1);
        }
    }
    fprintf(file, "POPFRAME\n");
    fprintf(file, "RETURN\n");
    fprintf(file, "LABEL .end_%s\n", func->attribute);
}

void generate_func_call(Symbol_t *func, FILE *file) {
    for (int i = func->func->argc; i > 0; i--) {
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
    fprintf(file, "CALL .%s\n", func->attribute);
}

void generate_func_call_assign(char *destination, Symbol_t *func, FILE *file) {
    for (int i = func->func->argc; i > 0; i--) {
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
    fprintf(file, "CALL .%s\n", func->attribute);
    fprintf(file, "POPS %s\n", destination);
}
// TODO: substring build-in function not implemented yet
int generate_instruction(Operation_t operation, Symbol_t *dest_in,
                         Symbol_t *var_in_1, Symbol_t *var_in_2, int label,
                         FILE *file) {
    DString_t var1, var2, dest;
    d_string_init(&var1);
    d_string_init(&var2);
    d_string_init(&dest);
    if (dest_in != NULL) {
        if (dest_in->symbol_type == VARIABLE ||
            dest_in->symbol_type == INTERN_VAR) {
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
        case WRITE:
            generate_write(var1.str, file);
            break;
        case READ:  // when reading, variable type is always in
                    // var_in_1->const_type
            // TODO: make this note in function description
            if (var_in_1->const_type == INT) {  // readi() function
                generate_read(dest.str, "int", file);
            } else if (var_in_1->const_type == FLOAT) {  // readf() function
                generate_read(dest.str, "float", file);
            } else if (var_in_1->const_type == STRING) {  // reads() function
                generate_read(dest.str, "string", file);
            }
            break;
        case CALL_FUNC:
            generate_func_call(var_in_1, file);
            break;
        case CALL_FUNC_ASSIGN:
            generate_func_call_assign(dest.str, var_in_1, file);
            break;
        case IN_STRLEN:  // built-in strlen function
            generate_strlen(var1.str, dest.str, file);  // snad OK
            break;
        case IN_ORD: // TODO: check if this is OK
            generate_stri2int(var1.str, "int@0", dest.str, file);
            break;
        case IN_CHR: // TODO: check if this is OK
            generate_int2char(var1.str, dest.str, file);
            break;
        case DEF_FUNC:
            generate_def_func(var_in_1, file);
            break;
        case RETURN:
            if (var_in_1 != NULL) {
                // TODO: need to pass func->attribute from PARSER to write end
                // label of function
                generate_return(var_in_2, var_in_1->symbol_type, var1.str,
                                file);
            } else {
                // TODO: need to pass func->attribute from PARSER to write end
                // label of function
                generate_return(var_in_2, 0, NULL, file);
            }
            break;

        default:
            return INTERNAL_ERR;
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
        if ((string->attribute[i] >= 0 && string->attribute[i] <= 32) ||
            string->attribute[i] == 35 || string->attribute[i] == 92) {
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
    fprintf(file, "JUMP $end_floatval\n");
    fprintf(file, "LABEL .floatval\n");
    fprintf(file, "CREATEFRAME\n");
    fprintf(file, "PUSHFRAME\n");
    fprintf(file, "DEFVAR LF@%%fvl_retval\n");
    fprintf(file, "DEFVAR LF@%%fvl_tmp1\n");
    fprintf(file, "DEFVAR LF@%%fvl_symb\n");

    fprintf(file, "POPS LF@%%fvl_tmp1\n");
    fprintf(file, "TYPE LF@%%fvl_symb LF@%%fvl_tmp1\n");
    fprintf(file, "JUMPIFEQ $floatval_int LF@%%fvl_symb string@int\n");
    fprintf(file, "JUMPIFEQ $floatval_float LF@%%fvl_symb string@float\n");
    fprintf(file, "JUMPIFEQ $floatval_nil LF@%%fvl_symb string@nil\n");
    fprintf(file, "MOVE LF@%%fvl_retval float@0x0p+0\n");
    fprintf(file, "JUMP $floatval$end\n");

    fprintf(file, "LABEL $floatval_int\n");
    fprintf(file, "INT2FLOAT LF@%%fvl_retval LF@%%fvl_tmp1\n");
    fprintf(file, "JUMP $floatval$end\n");

    fprintf(file, "LABEL $floatval_float\n");
    fprintf(file, "MOVE LF@%%fvl_retval LF@%%fvl_tmp1\n");
    fprintf(file, "JUMP $floatval$end\n");

    fprintf(file, "LABEL $floatval_nil\n");
    fprintf(file, "MOVE LF@%%fvl_retval float@0x0p+0\n");
    fprintf(file, "JUMP $floatval$end\n");

    fprintf(file, "LABEL $floatval$end\n");
    fprintf(file, "PUSHS LF@%%fvl_retval\n");
    fprintf(file, "POPFRAME\n");
    fprintf(file, "RETURN\n");
    fprintf(file, "LABEL $end_floatval\n");
}

void built_in_intval(FILE *file) {
    fprintf(file, "JUMP $end_intval\n");
    fprintf(file, "LABEL .intval\n");
    fprintf(file, "CREATEFRAME\n");
    fprintf(file, "PUSHFRAME\n");
    fprintf(file, "DEFVAR LF@%%ivl_retval\n");
    fprintf(file, "DEFVAR LF@%%ivl_tmp1\n");
    fprintf(file, "DEFVAR LF@%%ivl_symb\n");

    fprintf(file, "POPS LF@%%ivl_tmp1\n");
    fprintf(file, "TYPE LF@%%ivl_symb LF@%%ivl_tmp1\n");
    fprintf(file, "JUMPIFEQ $intval_int LF@%%ivl_symb string@int\n");
    fprintf(file, "JUMPIFEQ $intval_float LF@%%ivl_symb string@float\n");
    fprintf(file, "JUMPIFEQ $intval_nil LF@%%ivl_symb string@nil\n");
    fprintf(file, "MOVE LF@%%ivl_retval int@0\n");
    fprintf(file, "JUMP $intval$end\n");

    fprintf(file, "LABEL $intval_int\n");
    fprintf(file, "MOVE LF@%%ivl_retval LF@%%ivl_tmp1\n");
    fprintf(file, "JUMP $intval$end\n");

    fprintf(file, "LABEL $intval_float\n");
    fprintf(file, "FLOAT2INT LF@%%ivl_retval LF@%%ivl_tmp1\n");
    fprintf(file, "JUMP $intval$end\n");

    fprintf(file, "LABEL $intval_nil\n");
    fprintf(file, "MOVE LF@%%ivl_retval int@0\n");
    fprintf(file, "JUMP $intval$end\n");

    fprintf(file, "LABEL $intval$end\n");
    fprintf(file, "PUSHS LF@%%ivl_retval\n");
    fprintf(file, "POPFRAME\n");
    fprintf(file, "RETURN\n");
    fprintf(file, "LABEL $end_intval\n");
}

void built_in_strval(FILE *file) {
    fprintf(file, "JUMP $end_strval\n");
    fprintf(file, "LABEL .strval\n");
    fprintf(file, "CREATEFRAME\n");
    fprintf(file, "PUSHFRAME\n");
    fprintf(file, "DEFVAR LF@%%svl_retval\n");
    fprintf(file, "DEFVAR LF@%%svl_tmp1\n");
    fprintf(file, "DEFVAR LF@%%svl_symb\n");

    fprintf(file, "POPS LF@%%svl_tmp1\n");
    fprintf(file, "TYPE LF@%%svl_symb LF@%%svl_tmp1\n");
    fprintf(file, "JUMPIFEQ $strval_nil LF@%%svl_symb string@nil\n");
    fprintf(file, "JUMPIFEQ $strval_string LF@%%svl_symb string@string\n");
    fprintf(file, "MOVE LF@%%svl_retval string@\\000\n");
    fprintf(file, "JUMP $strval$end\n");

    fprintf(file, "LABEL $strval_nil\n");
    fprintf(file, "MOVE LF@%%svl_retval string@\\000\n");
    fprintf(file, "JUMP $strval$end\n");

    fprintf(file, "LABEL $strval_string\n");
    fprintf(file, "MOVE LF@%%svl_retval LF@%%svl_tmp1\n");
    fprintf(file, "JUMP $strval$end\n");

    fprintf(file, "LABEL $strval$end\n");
    fprintf(file, "PUSHS LF@%%svl_retval\n");
    fprintf(file, "POPFRAME\n");
    fprintf(file, "RETURN\n");
    fprintf(file, "LABEL $end_strval\n");
}

void built_in_substr(FILE *file){
    
}