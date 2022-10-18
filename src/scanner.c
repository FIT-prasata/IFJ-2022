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

// TODO error handle wrapper to all d_string related function once it's created

char get_non_white() {
    char tmp = getchar();
    return (isspace(tmp)) ? get_non_white() : tmp;
}

void set_type(Token_t *token, T_type_t type) { token->type = type; }

char skip_lc() {
    char tmp = getchar();
    return (tmp != '\n' && tmp != EOF) ? skip_lc() : tmp;
}

int skip_bc() {
    char prev, curr;
    while (true) {
        curr = getchar();
        if (curr == EOF) {
            return BC_EOF_ERR;
        }
        if (prev == '*' && curr == '/') {
            return OK;
        }
        prev = curr;
    }
}

int keyword_handler(Token_t *token, char *curr) {
    char *keywords[] = {"else", "float",  "function", "if",   "int",
                        "null", "return", "dString",  "void", "while"};

    DString_t dString;
    d_string_init(&dString);

    do {
        if ((*curr >= 'A' && *curr <= 'Z') || (*curr >= 'a' && *curr <= 'z') ||
            (*curr >= '0' && *curr <= '9') || (*curr == '_')) {
            *curr = getchar();
            d_string_add_char(&dString, *curr);
        } else {
            break;
        }
    } while (true);

    for (int i = 0; i < 10; i++) {
        // TODO
        // Compare dString and keywords[i], if matches free allocated dString
        // and call set_type
        set_type(token,
                 keywords[i]);  // This needs better approach -> Future Luke :{
    }
    set_type(token, T_FUNC_ID);
    strcpy(token->attribute.string, dString.str);
    d_string_free_and_clear(&dString);
    return OK;
}

int num_handler(Token_t *token, char *curr) {
    bool dec_pt = false, exp = false;
    char last;

    DString_t dString;
    d_string_init(&dString);
    d_string_add_char(&dString, *curr);
    last = *curr;
    set_type(token, T_INT);

    while (true) {
        *curr = getchar();
        if (*curr >= '0' && *curr <= '9') {
            d_string_add_char(&dString, *curr);
        } else if (*curr == '.' && (dec_pt == false) && (exp == false)) {
            d_string_add_char(&dString, *curr);
            dec_pt = true;
            set_type(token, T_FLOAT);
        } else if ((*curr == 'e' || *curr == 'E') && (exp == false) &&
                   (last >= '0') && (last <= '9')) {
            d_string_add_char(&dString, *curr);
            exp = true;
            set_type(token, T_FLOAT);
        } else if ((*curr == '+' || *curr == '-') &&
                   (last == 'e' || last == 'E')) {
            d_string_add_char(&dString, *curr);
        } else {
            if (last >= '0' && last <= '9') {
                break;
            } else {
                return NUM_ERR;
            }
        }
        last = *curr;
    }
    if (token->type == T_INT) {
        get_d_string_value_to_integer(&dString, &(token->attribute.value));
    } else {
        get_d_string_value_to_double(&dString, &(token->attribute.dec_value));
    }
    d_string_free_and_clear(&dString);
    return OK;
}

int string_handler(Token_t *token) {
    char curr, last = '0';

    DString_t dString;
    d_string_init(&dString);
    set_type(token, T_STRING);

    while (true) {
        curr = getchar();
        if (curr == '\"' && last != '\\') {
            break;
        }
        if (curr >= 0 && curr <= 31) {
            return STR_ERR;
        }
        if (curr == '\\') {
            curr = getchar();
            switch (curr) {
                case 'n':
                    // Add curr to string
                    d_string_add_char(&dString, curr);
                    break;
                case 't':
                    d_string_add_char(&dString, curr);
                    break;
                case '\"':
                    d_string_add_char(&dString, curr);
                    break;
                case '\\':
                    d_string_add_char(&dString, curr);
                    break;
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
                    // TODO
                    // Future Luke -> function to convert escaped nums
                    // If correct -> convert if not -> just add the whole thing
                    // to string
                    break;
                default:
                    return STR_ERR;
            }
        } else {
            d_string_add_char(&dString, curr);
        }
        last = curr;
    }
    strcpy(token->attribute.string, dString.str);
    d_string_free_and_clear(&dString);
    return 0;
}

int id_handler(Token_t *token) {
    // TODO
}

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
                // TODO: handle if is lc or bc
                curr = getchar();
                if (curr == '*') {
                    if (skip_bc()) {
                        return BC_EOF_ERR;
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

            case '_':  // 'a' ... 'z' might work for gcc, but too tired to look
                       // into it, sorry for this mess...
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
                if (keyword_handler(token, curr) == OK) {
                    last = isspace(curr) ? get_non_white() : curr;
                    use_last = true;
                    return OK;
                } else {
                    return INTERNAL_ERR;  // I guess that nothing else could go
                                          // wrong here
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