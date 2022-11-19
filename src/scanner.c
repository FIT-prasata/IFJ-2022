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

char get_non_white() {
    char tmp = (char)getchar();
    return (isspace(tmp)) ? get_non_white() : tmp;
}

void set_type(Token_t *token, T_type_t type) { token->type = type; }

// line comment
char skip_lc() {
    char curr;
    while (true) {
        curr = getchar();
        if (curr == EOF) {
            return LC_EOF_ERR;
        }
        if (curr == '\n') {
            return OK;
        }
    }
}

// block comment
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

int type_handler(Token_t *token) {
    char *id_types[] = {"int", "float", "string"};
    int types[] = {K_INT, K_FLOAT, K_STR};
    int types_array_size = sizeof(types) / sizeof(types[0]);

    DString_t dString;
    d_string_init(&dString);
    char curr = getchar();

    do {
        if ((curr >= 'A' && curr <= 'Z') || (curr >= 'a' && curr <= 'z') ||
            (curr >= '0' && curr <= '9') || (curr == '_')) {
            curr = getchar();
            d_string_add_char(&dString, curr);
        } else {
            break;
        }
    } while (true);

    for (int i = 0; i < types_array_size; i++) {
        if (strcmp(id_types[i], dString.str) == 0) {
            set_type(token, types[i]);
            d_string_free_and_clear(&dString);
            return OK;
        }
    }
    strcpy(token->attribute.string, dString.str);
    d_string_free_and_clear(&dString);
    return TYPE_ERR;
}

int keyword_handler(Token_t *token, char *curr) {
    char *keywords[] = {"else", "float",  "function", "if",   "int",
                        "null", "return", "string",   "void", "while"};
    int keyword_types[] = {K_ELSE, K_FLOAT, K_FUNC, K_IF,   K_INT,
                           K_NULL, K_RET,   K_STR,  K_VOID, K_WHILE};
    int keywords_array_size = sizeof(keywords) / sizeof(keywords[0]);

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

    for (int i = 0; i < keywords_array_size; i++) {
        if (strcmp(keywords[i], dString.str) == 0) {
            set_type(token, keyword_types[i]);
            d_string_free_and_clear(&dString);
            return T_KEYWORD;
        }
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
    char oct_hex[4] = {
        0,
    };
    oct_hex[3] = '\0';
    char *garbage_strtol;
    bool num_ok = true;
    int decimal = 0;
    DString_t dString;
    d_string_init(&dString);
    set_type(token, T_STRING);

    while (true) {
        if (last !=
            '"') {  // should secure that when <\x6"> is the end of string, next
                    // char (most time ';' or ')') should not be schroustán xd
            curr = getchar();
        }
        if ((curr == '\"' || last == '"') && last != '\\') {
            break;
        }
        if (curr >= 0 && curr <= 31) {
            return STR_ERR;
        }
        if (curr == '\\') {
            curr = getchar();
            switch (curr) {
                case 'n':
                    d_string_add_char(&dString, curr);  //??
                    break;
                case 't':
                    d_string_add_char(&dString, curr);  //??
                    break;
                case '\"':
                    d_string_add_char(&dString, curr);
                    break;
                case '\\':
                    d_string_add_char(&dString, curr);
                    break;
                case 'x':
                    for (int i = 0; i < 2; i++) {
                        oct_hex[i] =
                            getchar();  // get next number of octal (2. and 3.)
                        oct_hex[i + 1] = '\0';  // move string termination char
                        if (oct_hex[i] ==
                            '"') {  // pokud je uživatel kokot a dá něco v tomto
                                    // stylu: ...\x6"    :)
                            num_ok = false;
                            curr = '"';
                        }
                        if ((oct_hex[i] < '0' || oct_hex[i] > '9') &&
                            (oct_hex[i] < 'A' || oct_hex[i] > 'F') &&
                            (oct_hex[i] < 'a' ||
                             oct_hex[i] > 'f')) {  // check if oct char are in
                                                   // valid range
                            d_string_add_char(
                                &dString, '\\');  // if not, write into string
                                                  // '\' (by instructions)
                            d_string_add_char(&dString, 'x');
                            for (int j = 0;
                                 oct_hex[j] != '\0' && oct_hex[j] != '"'; j++) {
                                d_string_add_char(
                                    &dString,
                                    oct_hex[j]);  // insert into string rest of
                                                  // loaded items
                            }
                            num_ok = false;
                            break;
                        }
                    }
                    if (num_ok == true) {
                        decimal = strtol(oct_hex, &garbage_strtol, 16);
                        d_string_add_char(&dString, (char)decimal);
                    }
                    decimal = 0;
                    num_ok = true;
                    break;
                case '0':
                case '1':
                case '2':
                case '3':
                    oct_hex[0] = curr;  // get first number of octal (0-3)
                    for (int i = 1; i < 3; i++) {
                        oct_hex[i] =
                            getchar();  // get next number of octal (2. and 3.)
                        oct_hex[i + 1] = '\0';  // move string termination char
                        if (oct_hex[i] ==
                            '"') {  // pokud je uživatel kokot a dá něco v tomto
                                    // stylu: ...\x6"    :)
                            num_ok = false;
                            curr = '"';
                        }
                        if (oct_hex[i] < '0' ||
                            oct_hex[i] >
                                '7') {  // check if oct char are in valid range
                            d_string_add_char(
                                &dString, '\\');  // if not, write into string
                                                  // '\' (by instructions)
                            for (int j = 0;
                                 oct_hex[j] != '\0' && oct_hex[j] != '"'; j++) {
                                d_string_add_char(
                                    &dString,
                                    oct_hex[j]);  // insert into string rest of
                                                  // loaded items
                            }
                            num_ok = false;
                            break;
                        }
                    }
                    if (num_ok == true) {
                        decimal = strtol(oct_hex, &garbage_strtol, 8);
                        d_string_add_char(&dString, (char)decimal);
                    }
                    decimal = 0;
                    num_ok = true;
                    break;
                default:
                    return STR_ERR;  // insert into string full loaded
                                     // statement, '\' included
            }
        } else {
            d_string_add_char(&dString, curr);
        }
        last = curr;
    }
    printf("stringhere: %s\n", dString.str);
    printf("%d\n", dString.length);
    token->attribute.string = malloc(sizeof(char) * dString.length + 1);
    strcpy(token->attribute.string, dString.str);
    d_string_free_and_clear(&dString);
    return 0;
}

int id_handler(Token_t *token) {
    DString_t dString;
    d_string_init(&dString);
    char curr = getchar();

    if ((curr >= 'A' && curr <= 'Z') || (curr >= 'a' && curr <= 'z') ||
        (curr == '_')) {
        do {
            if ((curr >= 'A' && curr <= 'Z') || (curr >= 'a' && curr <= 'z') ||
                (curr >= '0' && curr <= '9') || (curr == '_')) {
                curr = getchar();
                d_string_add_char(&dString, curr);
            } else {
                break;
            }
        } while (true);

        set_type(token, T_ID);
        strcpy(token->attribute.string, dString.str);
        d_string_free_and_clear(&dString);
        return OK;
    } else {
        d_string_free_and_clear(&dString);
        return ID_ERR;
    }
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