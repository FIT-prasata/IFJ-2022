// Filename: error.c
// IFJ 2022/2023 project
// TRP variant
//
// Error handler
//
// Author: <xsklen14> - David Sklenář
// Author: <xproch0o> - Marek Procházka
// Author: <xzavad20> - Lukáš Zavadil
// Author: <xsvetl07> - Adam Světlík

// LOCAL INCLUDES
#include "error.h"

void error_display(int type, int line_num) {
    switch (type) {
        // Custom errors will be added with more detailed description and return
        // values of the specification defined errors
        case LEX_ERR:
            fprintf(stderr, "Line: %d | Lexical analysis error\n", line_num);
            exit(LEX_ERR);
        case SYNTAX_ERR:
            fprintf(stderr, "Line: %d | Syntax analysis error\n", line_num);
            exit(SYNTAX_ERR);
        case UNDEF_FUNC_ERR:
            fprintf(stderr, "Line: %d | Undefined function / redefinition\n",
                    line_num);
            exit(UNDEF_FUNC_ERR);
        case FUNC_TYPE_ERR:
            fprintf(
                stderr,
                "Line: %d | Incorrect function parameter(s) / return type\n",
                line_num);
            exit(FUNC_TYPE_ERR);
        case UNDEF_VAR_ERR:
            fprintf(stderr, "Line: %d | Undefined variable\n", line_num);
            exit(UNDEF_VAR_ERR);
        case RET_ERR:
            fprintf(stderr, "Line: %d | Function return syntax error\n",
                    line_num);
            exit(RET_ERR);
        case EXPR_TYPE_ERR:
            fprintf(stderr, "Line: %d | Expression type incompatibility\n",
                    line_num);
            exit(EXPR_TYPE_ERR);
        case OTHER_ERR:
            fprintf(stderr, "Line: %d | Other semantics errors\n", line_num);
            exit(OTHER_ERR);
        case INTERNAL_ERR:
            fprintf(stderr,
                    "Line: %d | Internal compiler error (memory allocation)\n",
                    line_num);
            exit(INTERNAL_ERR);
    }
}

void try(int code) {
    if (code != OK) {
        error_display(code, line_num);
    }
}

void raise(int code) { error_display(code, 0); }
