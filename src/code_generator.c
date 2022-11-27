// Filename: code_generator.c
// IFJ 2022/2023 project
// TRP variant
//
// Scanner for lexical analysis
//
// Author: <xsklen14> - David Sklenář
// Author: <xproch0o> - Marek Procházka
// Author: <xzavad20> - Lukáš Zavadil
// Author: <xsvetl07> - Adam Světlík
#include "code_generator.h"

void generate_while_start(int label, char *condition, char *var1, char *var2,
                          FILE *file) {
    fprintf(file, "LABEL .while_start_%d\n", label);
    fprintf(file, "JUMPIF%s %s, %s, .while_body_%d\n", condition, var1, var2,
            label);
    fprintf(file, "JUMP .while_end_%d\n", label);
    fprintf(file, "LABEL .while_body_%d\n", label);
}

void generate_while_end(int label, FILE *file) {
    fprintf(file, "JUMP .while_start_%d\n", label);
    fprintf(file, "LABEL .while_end_%d\n", label);
}

void generate_if_start(int label, char *condition, char *var1, char *var2,
                       FILE *file) {
    fprintf(file, "JUMPIF%s %s, %s, .if_start_%d\n", condition, var1, var2,
            label);
    fprintf(file, "JUMP .if_end_%d\n", label);
    fprintf(file, "LABEL .if_start_%d\n", label);
}

void generate_if_end(int label, FILE *file) {
    fprintf(file, "LABEL .if_end_%d\n", label);
}

void generate_prolog(FILE *file) { fprintf(file, ".IFJcode22\n"); }

void generate_add(char *var1, char *var2, char *destination, FILE *file) {
    fprintf(file, "ADD %s, %s, %s\n", var1, var2, destination);
}

void generate_sub(char *var1, char *var2, char *destination, FILE *file) {
    fprintf(file, "SUB %s, %s, %s\n", var1, var2, destination);
}

void generate_mul(char *var1, char *var2, char *destination, FILE *file) {
    fprintf(file, "MUL %s, %s, %s\n", var1, var2, destination);
}

void generate_div(char *var1, char *var2, char *destination, FILE *file) {
    fprintf(file, "DIV %s, %s, %s\n", var1, var2, destination);
}

void generate_idiv(char *var1, char *var2, char *destination, FILE *file) {
    fprintf(file, "IDIV %s, %s, %s\n", var1, var2, destination);
}

void generate_move(char *source, char *destination, FILE *file) {
    fprintf(file, "MOVE %s, %s\n", source, destination);
}

void generate_lt(char *var1, char *var2, char *destination, FILE *file) {
    fprintf(file, "LT %s, %s, %s\n", var1, var2, destination);
}

void generate_gt(char *var1, char *var2, char *destination, FILE *file) {
    fprintf(file, "GT %s, %s, %s\n", var1, var2, destination);
}

void generate_eq(char *var1, char *var2, char *destination, FILE *file) {
    fprintf(file, "EQ %s, %s, %s\n", var1, var2, destination);
}

void generate_and(char *var1, char *var2, char *destination, FILE *file) {
    fprintf(file, "AND %s, %s, %s\n", var1, var2, destination);
}

void generate_or(char *var1, char *var2, char *destination, FILE *file) {
    fprintf(file, "OR %s, %s, %s\n", var1, var2, destination);
}

void generate_not(char *source, char *destination, FILE *file) {
    fprintf(file, "NOT %s, %s\n", source, destination);
}

int generate(T_type_t operation, char *var1, char *var2, char *destination, FILE *file) {
    // TODO maybe operation type should be something else
    return 0;
}

char *variable_convert(Htab_item_t *item, Frame_t frame) {
    DString_t *string;
    d_string_init(string);
    switch (frame) {
        case GF:
            d_string_add_str(string, "GF@");
            break;
        case LF:
            d_string_add_str(string, "LF@");
            break;
        case TF:
            d_string_add_str(string, "TF@");
            break;
    }
    d_string_add_str(string, item->data.name);
    return string->str;
}

char *const_convert(Token_t *token) {
    DString_t *string;
    d_string_init(string);
    if (token->type == T_INT) {
        d_string_add_str(string, "int@");
    } else if (token->type == T_FLOAT) {
        d_string_add_str(string, "float@");
    } else if (token->type == T_STRING) {
        d_string_add_str(string, "string@");
    }
    // TODO maybe will be added bool and nil
    /*else if (token->type == T_BOOL) {
        d_string_add_str(string, "bool@");
    }
    else if (token->type == T_NIL) {
        d_string_add_str(string, "nil@");
    }*/
    else {
        return NULL;
    }
    d_string_add_str(string, token->attribute.string);
    return string->str;
}

char *string_convert(Token_t *token) {
    DString_t *string;
    d_string_init(string);
    char code[3];
    d_string_add_str(string, "string@");
    int len = strlen(token->attribute.string);
    for (int i = 0; i < len; i++) {
        if (token->attribute.string[i] >= 0 && token->attribute.string[i] <= 32 ||
            token->attribute.string[i] == 35 || token->attribute.string[i] == 92) {
            d_string_add_char(string, '\\');
            sprintf(code, "%03d", token->attribute.string[i]);
            d_string_add_str(string, code);
        } else {
            d_string_add_char(string, token->attribute.string[i]);
        }
    }
    return string->str;
}

int main() {
    FILE *file = stdout;
    int while_count = 0;
    int if_count = 0;

    generate_prolog(file);

    generate_while_start(while_count, "NEQ", "GF@var1", "GF@var2", file);
    fprintf(file, "MOVE GF@var1 GF@var2\n");  // while body
    generate_while_end(while_count, file);
    while_count++;

    generate_if_start(if_count, "EQ", "GF@var1", "GF@var2", file);
    fprintf(file, "MOVE GF@var1 GF@var2\n");  // if body
    generate_if_end(if_count, file);

    fclose(file);

    return 0;
}
