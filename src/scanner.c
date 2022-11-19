// Filename: scanner.c
// IFJ 2022/2023 project
// TRP variant
//
// Scanner for lexical analysis
//
// Author: <xsklen14> - David Sklenář
// Author: <xproch0o> - Marek Procházka
// Author: <xzavad20> - Lukáš Zavadil
// Author: <xsvetl07> - Adam Světlík

// LOCAL INCLUDES
#include "scanner.h"


int scan(Token_t *token) {
    char curr;
    static char last;
    static bool use_last;
    int ret;

    if (last == EOF) {
        set_type(token, T_EOF);

        return NOT_IMPLEMENTED;  // Ultra edge case for calling scan after
                                 // receiving EOF somehow
    }
    if (use_last) {
        curr = last;
        use_last = false;
    } else {
        curr = get_non_white();
    }

    while (true) {
        switch (curr) {
            case '/':
                curr = getchar();
                if (curr == '*') {
                    if (skip_bc()) {
                        return BC_EOF_ERR;
                    } else {
                        curr = get_non_white();
                        break;
                    }
                } else if (curr == '/') {
                    if (skip_lc()) {
                        return LC_EOF_ERR;
                    } else {
                        curr = get_non_white();
                        break;
                    }
                } else {
                    last = curr;
                    if (isspace(curr)) {
                        last = get_non_white();
                    }
                    use_last = true;
                    set_type(token, T_DIV);
                    return OK;
                }

            case '\n':
                last = '\n';
                set_type(token, T_EOL);
                break;  // temp break to get rid of warnings
            case '_':   // 'a' ... 'z' might work for gcc, but too tired
            case 'a':
            case 'b':
            case 'c':
            case 'd':
            case 'e':
            case 'f':
            case 'g':
            case 'h':
            case 'i':
            case 'j':
            case 'k':
            case 'l':
            case 'm':
            case 'n':
            case 'o':
            case 'p':
            case 'q':
            case 'r':
            case 's':
            case 't':
            case 'u':
            case 'v':
            case 'w':
            case 'x':
            case 'y':
            case 'z':
            case 'A':
            case 'B':
            case 'C':
            case 'D':
            case 'E':
            case 'F':
            case 'G':
            case 'H':
            case 'I':
            case 'J':
            case 'K':
            case 'L':
            case 'M':
            case 'N':
            case 'O':
            case 'P':
            case 'Q':
            case 'R':
            case 'S':
            case 'T':
            case 'U':
            case 'V':
            case 'W':
            case 'X':
            case 'Y':
            case 'Z':
                if (keyword_handler(token, &curr) == OK) {
                    last = isspace(curr) ? get_non_white() : curr;
                    use_last = true;
                    return OK;
                } else {
                    return INTERNAL_ERR;
                }
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
                if ((ret = num_handler(token, &curr))) {
                    return ret;
                } else {
                    last = isspace(curr) ? get_non_white() : curr;
                    use_last = true;
                    return OK;
                }
            case '\"':
                if ((ret = string_handler(token))) {
                    return ret;
                }
                last = '\"';
                return OK;
            case '$':
                if ((ret = id_handler(token))) {
                    return ret;
                }
                return OK;
            case '<':
                curr = getchar();
                last = curr;

                if (curr == '=') {
                    set_type(token, T_LE);
                    return OK;
                } else {
                    if (isspace(curr)) {
                        last = get_non_white();
                    }
                    use_last = true;
                    set_type(token, T_LT);
                    return OK;
                }
            case '>':
                curr = getchar();
                last = curr;

                if (curr == '=') {
                    set_type(token, T_GE);
                    return OK;
                } else {
                    if (isspace(curr)) {
                        last = get_non_white();
                    }
                    use_last = true;
                    set_type(token, T_GT);
                    return OK;
                }
            case '(':
                last = curr;
                set_type(token, T_LBR);
                return OK;
            case ')':
                last = curr;
                set_type(token, T_RBR);
                return OK;
            case '{':
                last = curr;
                set_type(token, T_LCBR);
                return OK;
            case '}':
                last = curr;
                set_type(token, T_RCBR);
                return OK;
            case '+':
                last = curr;
                set_type(token, T_ADD);
                return OK;
            case '-':
                last = curr;
                set_type(token, T_SUB);
                return OK;
            case '*':
                last = curr;
                set_type(token, T_MUL);
                return OK;
            case ';':
                last = curr;
                set_type(token, T_SEM);
                return OK;
            case '?':
                if (type_handler(token) == OK) {
                    return OK;
                } else if (type_handler(token) == TYPE_ERR) {
                    return TYPE_ERR;
                } else {
                    return INTERNAL_ERR;
                }
            case '=':
                curr = getchar();
                if (curr == '=') {
                    curr = getchar();
                    if (curr == '=') {
                        last = curr;
                        set_type(token, T_EQ);
                        return OK;
                    } else {
                        return EQ_ERR;
                    }
                }
                if (isspace(curr)) {
                    last = get_non_white();
                }
                use_last = true;
                set_type(token, T_ASSIGN);
                return OK;
            case '!':
                curr = getchar();
                if (curr == '=') {
                    curr = getchar();
                    if (curr == '=') {
                        last = curr;
                        set_type(token, T_NE);
                        return OK;
                    } else {
                        return NE_ERR;
                    }
                }
                if (isspace(curr)) {
                    last = get_non_white();
                }
                use_last = true;
                set_type(token, T_NEG);
                return OK;
            case EOF:
                last = curr;
                set_type(token, T_EOF);
                return OK;
            default:
                return NOT_IMPLEMENTED;
        }
    }
}