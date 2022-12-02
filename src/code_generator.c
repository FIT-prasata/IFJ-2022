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
        case WHILE_LT:
            fprintf(file, "LABEL .while_start_%d\n", label);
            fprintf(file, "PUSHS %s\n", var2);
            fprintf(file, "PUSHS %s\n", var1);
            fprintf(file, "PUSHFRAME\n");
            fprintf(file, "CREATEFRAME\n");
            fprintf(file, "DEFVAR LF@var1\n");
            fprintf(file, "DEFVAR LF@var2\n");
            fprintf(file, "POPS LF@var1\n");
            fprintf(file, "POPS LF@var2\n");
            fprintf(file, "DEFVAR LF@var_ret\n");
            fprintf(file, "LT LF@var_ret LF@var1 LF@var2\n");
            fprintf(file, "JUMPIFEQ .while_body_%d LF@var_ret bool@true\n",
                    label);
            fprintf(file, "POPFRAME\n");
            fprintf(file, "JUMP .while_end_%d\n", label);
            fprintf(file, "LABEL .while_body_%d\n", label);
            fprintf(file, "POPFRAME\n");
            break;
        case WHILE_GT:
            fprintf(file, "LABEL .while_start_%d\n", label);
            fprintf(file, "PUSHS %s\n", var2);
            fprintf(file, "PUSHS %s\n", var1);
            fprintf(file, "PUSHFRAME\n");
            fprintf(file, "CREATEFRAME\n");
            fprintf(file, "DEFVAR LF@var1\n");
            fprintf(file, "DEFVAR LF@var2\n");
            fprintf(file, "POPS LF@var1\n");
            fprintf(file, "POPS LF@var2\n");
            fprintf(file, "DEFVAR LF@var_ret\n");
            fprintf(file, "GT LF@var_ret LF@var1 LF@var2\n");
            fprintf(file, "JUMPIFEQ .while_body_%d LF@var_ret bool@true\n",
                    label);
            fprintf(file, "POPFRAME\n");
            fprintf(file, "JUMP .while_end_%d\n", label);
            fprintf(file, "LABEL .while_body_%d\n", label);
            fprintf(file, "POPFRAME\n");
            break;
        case WHILE_LEQ:
            fprintf(file, "LABEL .while_start_%d\n", label);
            fprintf(file, "PUSHS %s\n", var2);
            fprintf(file, "PUSHS %s\n", var1);
            fprintf(file, "PUSHFRAME\n");
            fprintf(file, "CREATEFRAME\n");
            fprintf(file, "DEFVAR LF@var1\n");
            fprintf(file, "DEFVAR LF@var2\n");
            fprintf(file, "POPS LF@var1\n");
            fprintf(file, "POPS LF@var2\n");
            fprintf(file, "DEFVAR LF@var_ret\n");
            fprintf(file, "DEFVAR LF@tmp1\n");
            fprintf(file, "DEFVAR LF@tmp2\n");
            fprintf(file, "LT LF@tmp1 LF@var1 LF@var2\n");
            fprintf(file, "EQ LF@tmp2 LF@var1 LF@var2\n");
            fprintf(file, "OR LF@var_ret LF@tmp1 LF@tmp2\n");
            fprintf(file, "JUMPIFEQ .while_body_%d LF@var_ret bool@true\n",
                    label);
            fprintf(file, "POPFRAME\n");
            fprintf(file, "JUMP .while_end_%d\n", label);
            fprintf(file, "LABEL .while_body_%d\n", label);
            fprintf(file, "POPFRAME\n");
            break;
        case WHILE_GEQ:
            fprintf(file, "LABEL .while_start_%d\n", label);
            fprintf(file, "PUSHS %s\n", var2);
            fprintf(file, "PUSHS %s\n", var1);
            fprintf(file, "PUSHFRAME\n");
            fprintf(file, "CREATEFRAME\n");
            fprintf(file, "DEFVAR LF@var1\n");
            fprintf(file, "DEFVAR LF@var2\n");
            fprintf(file, "POPS LF@var1\n");
            fprintf(file, "POPS LF@var2\n");
            fprintf(file, "DEFVAR LF@var_ret\n");
            fprintf(file, "DEFVAR LF@tmp1\n");
            fprintf(file, "DEFVAR LF@tmp2\n");
            fprintf(file, "GT LF@tmp1 LF@var1 LF@var2\n");
            fprintf(file, "EQ LF@tmp2 LF@var1 LF@var2\n");
            fprintf(file, "OR LF@var_ret LF@tmp1 LF@tmp2\n");
            fprintf(file, "JUMPIFEQ .while_body_%d LF@var_ret bool@true\n",
                    label);
            fprintf(file, "POPFRAME\n");
            fprintf(file, "JUMP .while_end_%d\n", label);
            fprintf(file, "LABEL .while_body_%d\n", label);
            fprintf(file, "POPFRAME\n");
            break;
        case WHILE_EQ:
            fprintf(file, "LABEL .while_start_%d\n", label);
            fprintf(file, "JUMPIFEQ %s, %s, .while_body_%d\n", var1, var2,
                    label);
            fprintf(file, "JUMP .while_end_%d\n", label);
            fprintf(file, "LABEL .while_body_%d\n", label);
            break;
        case WHILE_NEQ:
            fprintf(file, "JUMPIFNEQ %s, %s, .while_body_%d\n", var1, var2,
                    label);
            fprintf(file, "JUMP .while_end_%d\n", label);
            fprintf(file, "LABEL .while_body_%d\n", label);
            break;
        default:
            break;
    }
}

void generate_while_end(int label, FILE *file) {
    fprintf(file, "JUMP .while_start_%d\n", label);
    fprintf(file, "LABEL .while_end_%d\n", label);
}

void generate_if_start(Operation_t type, char *var1, char *var2, int label,
                       FILE *file) {
    switch (type) {
        case IF_LT:
            fprintf(file, "PUSHS %s\n", var2);
            fprintf(file, "PUSHS %s\n", var1);
            fprintf(file, "PUSHFRAME\n");
            fprintf(file, "CREATEFRAME\n");
            fprintf(file, "DEFVAR LF@var1\n");
            fprintf(file, "DEFVAR LF@var2\n");
            fprintf(file, "POPS LF@var1\n");
            fprintf(file, "POPS LF@var2\n");
            fprintf(file, "DEFVAR LF@var_ret\n");
            fprintf(file, "LT LF@var_ret LF@var1 LF@var2\n");
            fprintf(file, "JUMPIFEQ .if_start_%d LF@var_ret bool@true\n",
                    label);
            fprintf(file, "POPFRAME\n");
            fprintf(file, "JUMP .if_else_%d\n", label);
            fprintf(file, "LABEL .if_start_%d\n", label);
            fprintf(file, "POPFRAME\n");
            break;
        case IF_GT:
            fprintf(file, "PUSHS %s\n", var2);
            fprintf(file, "PUSHS %s\n", var1);
            fprintf(file, "PUSHFRAME\n");
            fprintf(file, "CREATEFRAME\n");
            fprintf(file, "DEFVAR LF@var1\n");
            fprintf(file, "DEFVAR LF@var2\n");
            fprintf(file, "POPS LF@var1\n");
            fprintf(file, "POPS LF@var2\n");
            fprintf(file, "DEFVAR LF@var_ret\n");
            fprintf(file, "GT LF@var_ret LF@var1 LF@var2\n");
            fprintf(file, "JUMPIFEQ .if_start_%d LF@var_ret bool@true\n",
                    label);
            fprintf(file, "POPFRAME\n");
            fprintf(file, "JUMP .if_else_%d\n", label);
            fprintf(file, "LABEL .if_start_%d\n", label);
            fprintf(file, "POPFRAME\n");
            break;
        case IF_LEQ:
            fprintf(file, "PUSHS %s\n", var2);
            fprintf(file, "PUSHS %s\n", var1);
            fprintf(file, "PUSHFRAME\n");
            fprintf(file, "CREATEFRAME\n");
            fprintf(file, "DEFVAR LF@var1\n");
            fprintf(file, "DEFVAR LF@var2\n");
            fprintf(file, "POPS LF@var1\n");
            fprintf(file, "POPS LF@var2\n");
            fprintf(file, "DEFVAR LF@var_ret\n");
            fprintf(file, "DEFVAR LF@tmp1\n");
            fprintf(file, "DEFVAR LF@tmp2\n");
            fprintf(file, "LT LF@tmp1 LF@var1 LF@var2\n");
            fprintf(file, "EQ LF@tmp2 LF@var1 LF@var2\n");
            fprintf(file, "OR LF@var_ret LF@tmp1 LF@tmp2\n");
            fprintf(file, "JUMPIFEQ .if_start_%d LF@var_ret bool@true\n",
                    label);
            fprintf(file, "POPFRAME\n");
            fprintf(file, "JUMP .if_else_%d\n", label);
            fprintf(file, "LABEL .if_start_%d\n", label);
            fprintf(file, "POPFRAME\n");
            break;
        case IF_GEQ:
            fprintf(file, "PUSHS %s\n", var2);
            fprintf(file, "PUSHS %s\n", var1);
            fprintf(file, "PUSHFRAME\n");
            fprintf(file, "CREATEFRAME\n");
            fprintf(file, "DEFVAR LF@var1\n");
            fprintf(file, "DEFVAR LF@var2\n");
            fprintf(file, "POPS LF@var1\n");
            fprintf(file, "POPS LF@var2\n");
            fprintf(file, "DEFVAR LF@var_ret\n");
            fprintf(file, "DEFVAR LF@tmp1\n");
            fprintf(file, "DEFVAR LF@tmp2\n");
            fprintf(file, "GT LF@tmp1 LF@var1 LF@var2\n");
            fprintf(file, "EQ LF@tmp2 LF@var1 LF@var2\n");
            fprintf(file, "OR LF@var_ret LF@tmp1 LF@tmp2\n");
            fprintf(file, "JUMPIFEQ .if_start_%d LF@var_ret bool@true\n",
                    label);
            fprintf(file, "POPFRAME\n");
            fprintf(file, "JUMP .if_else_%d\n", label);
            fprintf(file, "LABEL .if_start_%d\n", label);
            fprintf(file, "POPFRAME\n");
            break;
        case IF_EQ:
            fprintf(file, "JUMPIFEQ %s, %s, .if_start_%d\n", var1, var2, label);
            fprintf(file, "JUMP .if_else_%d\n", label);
            fprintf(file, "LABEL .if_start_%d\n", label);
            break;
        case IF_NEQ:
            fprintf(file, "JUMPIFNEQ %s, %s, .if_start_%d\n", var1, var2,
                    label);
            fprintf(file, "JUMP .if_else_%d\n", label);
            fprintf(file, "LABEL .if_start_%d\n", label);
            break;
        default:
            break;
    }
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
    fprintf(file, "ADD %s, %s, %s\n", destination, var1, var2);
}

void generate_sub(char *var1, char *var2, char *destination, FILE *file) {
    fprintf(file, "SUB %s, %s, %s\n", destination, var1, var2);
}

void generate_mul(char *var1, char *var2, char *destination, FILE *file) {
    fprintf(file, "MUL %s, %s, %s\n", destination, var1, var2);
}

void generate_div(char *var1, char *var2, char *destination, FILE *file) {
    fprintf(file, "DIV %s, %s, %s\n", destination, var1, var2);
}

void generate_idiv(char *var1, char *var2, char *destination, FILE *file) {
    fprintf(file, "IDIV %s, %s, %s\n", destination, var1, var2);
}

void generate_move(char *source, char *destination, FILE *file) {
    fprintf(file, "MOVE %s, %s\n", destination, source);
}

void generate_lt(char *var1, char *var2, char *destination, FILE *file) {
    fprintf(file, "LT %s, %s, %s\n", destination, var1, var2);
}

void generate_gt(char *var1, char *var2, char *destination, FILE *file) {
    fprintf(file, "GT %s, %s, %s\n", destination, var1, var2);
}

void generate_eq(char *var1, char *var2, char *destination, FILE *file) {
    fprintf(file, "EQ %s, %s, %s\n", destination, var1, var2);
}

void generate_and(char *var1, char *var2, char *destination, FILE *file) {
    fprintf(file, "AND %s, %s, %s\n", destination, var1, var2);
}

void generate_or(char *var1, char *var2, char *destination, FILE *file) {
    fprintf(file, "OR %s, %s, %s\n", destination, var1, var2);
}

void generate_not(char *source, char *destination, FILE *file) {
    fprintf(file, "NOT %s, %s\n", destination, source);
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

void generate_return(FILE *file) { fprintf(file, "RETURN\n"); }

void generate_pushs(char *var, FILE *file) { fprintf(file, "PUSHS %s\n", var); }

void generate_pops(char *var, FILE *file) { fprintf(file, "POPS %s\n", var); }

void generate_clears(FILE *file) { fprintf(file, "CLEARS\n"); }

void generate_int2float(char *source, char *destination, FILE *file) {
    fprintf(file, "INT2FLOAT %s, %s\n", destination, source);
}

void generate_float2int(char *source, char *destination, FILE *file) {
    fprintf(file, "FLOAT2INT %s, %s\n", destination, source);
}

void generate_int2char(char *source, char *destination, FILE *file) {
    fprintf(file, "INT2CHAR %s, %s\n", destination, source);
}

void generate_stri2int(char *var1, char *var2, char *destination, FILE *file) {
    fprintf(file, "STRI2INT %s, %s, %s\n", destination, var1, var2);
}

void generate_read(char *var, char *type, FILE *file) {
    fprintf(file, "READ %s, %s\n", var, type);
}

void generate_write(char *var, FILE *file) { fprintf(file, "WRITE %s\n", var); }

void generate_concat(char *var1, char *var2, char *destination, FILE *file) {
    fprintf(file, "CONCAT %s, %s, %s\n", destination, var1, var2);
}

void generate_strlen(char *source, char *destination, FILE *file) {
    fprintf(file, "STRLEN %s, %s\n", destination, source);
}

void generate_getchar(char *var, char *pos, char *destination, FILE *file) {
    fprintf(file, "GETCHAR %s, %s, %s\n", destination, var, pos);
}

void generate_setchar(char *var, char *pos, char *ch, FILE *file) {
    fprintf(file, "SETCHAR %s, %s, %s\n", var, pos, ch);
}

void generate_type(char *source, char *destination, FILE *file) {
    fprintf(file, "TYPE %s, %s\n", destination, source);
}

void generate_label(char *label, FILE *file) {
    fprintf(file, "LABEL %s\n", label);
}

void generate_jump(char *label, FILE *file) {
    fprintf(file, "JUMP %s\n", label);
}

void generate_jumpifeq(char *label, char *var1, char *var2, FILE *file) {
    fprintf(file, "JUMPIFEQ %s, %s, %s\n", label, var1, var2);
}

void generate_jumpifneq(char *label, char *var1, char *var2, FILE *file) {
    fprintf(file, "JUMPIFNEQ %s, %s, %s\n", label, var1, var2);
}

void generate_exit(char *var, FILE *file) { fprintf(file, "EXIT %s\n", var); }

void generate_break(FILE *file) { fprintf(file, "BREAK\n"); }

void generate_dprint(char *var, FILE *file) {
    fprintf(file, "DPRINT %s\n", var);
}
// TODO: rename maybe to generate_instruction
int generate(Operation_t operation, Token_t *dest_in, Token_t *var_in_1,
             Token_t *var_in_2, int label, Frame_t frame, FILE *file) {
    DString_t var1, var2, dest;
    d_string_init(&var1);
    d_string_init(&var2);
    d_string_init(&dest);
    if (dest_in != NULL) {
        if (dest_in->type == T_ID) {
            CHECK_OK(variable_convert(dest_in->attribute.string, frame, &dest));
        } else if (dest_in->type == T_FUNC_ID) {
            // TODO: research if Functions need some conversion in IFJcode22
        } else {
            CHECK_OK(const_convert(dest_in, &dest));
        }
    }
    if (var_in_1 != NULL) {
        if (var_in_1->type == T_ID) {
            CHECK_OK(
                variable_convert(var_in_1->attribute.string, frame, &var1));
        } else if (var_in_1->type == T_FUNC_ID) {
            // TODO: research if Functions need some conversion in IFJcode22
        } else {
            CHECK_OK(const_convert(var_in_1, &var1));
        }
    }
    if (var_in_2 != NULL) {
        if (var_in_2->type == T_ID) {
            CHECK_OK(
                variable_convert(var_in_2->attribute.string, frame, &var2));
        } else if (var_in_2->type == T_FUNC_ID) {
            // TODO: research if Functions need some conversion in IFJcode22
        } else {
            CHECK_OK(const_convert(var_in_2, &var2));
        }
    }

    // TODO: frame maybe as a parameter of token, not as a parameter of function
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
        case READ:
            // TODO: refactor this - should not use attribute.string
            generate_read(dest.str, var_in_1->attribute.string, file);
            break;
        default:
            return INTERNAL_ERR;
    }
    return OK;
}

int variable_convert(char *str, Frame_t frame, DString_t *converted_var) {
    if (str == NULL || frame > 3) {
        return INTERNAL_ERR;
    }
    DString_t string;
    CHECK_OK(d_string_init(&string));

    switch (frame) {
        case GF:
            CHECK_OK(d_string_add_str(&string, "GF@"));
            break;
        case LF:
            CHECK_OK(d_string_add_str(&string, "LF@"));
            break;
        case TF:
            CHECK_OK(d_string_add_str(&string, "TF@"));
        case NO:
            return OK;
        default:
            break;
    }
    CHECK_OK(d_string_add_str(&string, str));
    CHECK_OK(d_string_copy(&string, converted_var));
    return OK;
}

int const_convert(Token_t *token, DString_t *converted_const) {
    CHECK_NULL(token);
    DString_t string;
    CHECK_OK(d_string_init(&string));
    if (token->type == T_INT) {
        CHECK_OK(d_string_add_str(&string, "int@"));
        CHECK_OK(d_string_add_str(&string, token->attribute.string));
    } else if (token->type == T_FLOAT) {
        CHECK_OK(d_string_add_str(&string, "float@"));
        CHECK_OK(d_string_add_str(&string, token->attribute.string));
    } else if (token->type == T_STRING) {
        CHECK_OK(string_convert(token, converted_const));
        return OK;
    } else if (token->type == K_NULL) {
        CHECK_OK(d_string_add_str(&string, "nil@nil"));
    } else {
        return INTERNAL_ERR;
    }
    CHECK_OK(d_string_copy(&string, converted_const));
    return OK;
}

int string_convert(Token_t *token, DString_t *converted_str) {
    char code[5];
    CHECK_OK(d_string_add_str(converted_str, "string@"));
    int len = (int)strlen(token->attribute.string);
    for (int i = 0; i < len; i++) {
        if ((token->attribute.string[i] >= 0 &&
             token->attribute.string[i] <= 32) ||
            token->attribute.string[i] == 35 ||
            token->attribute.string[i] == 92) {
            sprintf(code, "\\%03d", token->attribute.string[i]);
            CHECK_OK(d_string_add_str(converted_str, code));
        } else {
            CHECK_OK(
                d_string_add_char(converted_str, token->attribute.string[i]));
        }
    }
    return OK;
}
