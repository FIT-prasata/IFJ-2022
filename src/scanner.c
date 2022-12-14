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

// Checks if character is a white character (not a newline)
int is_white(int input) { return (input == ' ' || input == '\t' || (input >= 11 && input <= 13)); }

// Function for handling prolog
int prolog_handler(void) {
    char prolog_start[25] = {
        '\0',
    };
    int curr;
    bool is_ok = false, block_comment_end = false;

    for (int i = 0; i < 5; i++) {
        curr = getchar();
        prolog_start[i] = curr;
    }
    if (strcmp(prolog_start, "<?php") == 0) {
        // check if there is a white char/newline/comment
        curr = getchar();
        if (is_white(curr) || curr == '\n') {
            is_ok = true;
        } else if (curr == '/') {
            // possible comment
            is_ok = true;
        }
        if (is_ok) {
            do {
                // comments handling
                if (curr == '/') {
                    curr = getchar();
                    if (curr == '/') {  // line comment
                        while (curr != '\n') {
                            curr = getchar();
                        }
                    } else if (curr == '*') {  // block comment
                        while (block_comment_end == false) {
                            curr = getchar();
                            if (curr == EOF) {
                                return LEX_ERR;
                            }
                            if (curr == '*') {
                                curr = getchar();
                                if (curr == '/') {
                                    block_comment_end = true;
                                }
                            }
                            if (curr == '\n') {
                                line_num++;
                            }
                        }
                        block_comment_end = false;
                        curr = getchar();
                        continue;
                    } else {  // not a line comment
                        return SYNTAX_ERR;
                    }
                } else if (is_white(curr)) {
                    curr = getchar();
                    continue;
                }
                // line counting
                if (curr == '\n') {
                    line_num++;
                } else {
                    printf("now, curr = '%c'\n", curr);
                    return SYNTAX_ERR;
                }
                curr = getchar();
            } while (curr != 'd');
        } else {
            return SYNTAX_ERR;
        }

        ungetc(curr, stdin);
        // second part of prolog checking
        for (int i = 0; i < 24; i++) {
            curr = getchar();
            prolog_start[i] = curr;
        }
        if (strcmp(prolog_start, "declare(strict_types=1);") == 0) {
            return OK;
        } else {
            return SYNTAX_ERR;
        }
    } else {
        return SYNTAX_ERR;  // prolog is not present/contains some white chars
                            // at the start of file
    }
}

// Function for keyword handling
int keyword_handler(DString_t *dString, Token_t *token) {
    char *keywords[] = {"else", "float", "function", "if", "int", "null", "return", "string", "void", "while", "?int", "?string", "?float"};
    int keyword_types[] = {K_ELSE, K_FLOAT, K_FUNC, K_IF, K_INT, K_NULL, K_RET, K_STR, K_VOID, K_WHILE, K_INT_NULL, K_STR_NULL, K_FLOAT_NULL};
    int keywords_array_size = sizeof(keywords) / sizeof(keywords[0]);

    for (int i = 0; i < keywords_array_size; i++) {
        if (strcmp(keywords[i], dString->str) == 0) {
            token->type = keyword_types[i];
            return OK;
        }
    }
    if (dString->str[0] == '?') {
        return LEX_ERR;
    }
    token->type = T_FUNC_ID;
    token->attribute.string = malloc(sizeof(char) * (dString->length + 1));
    if (token->attribute.string == NULL) {
        return INTERNAL_ERR;
    }
    strcpy(token->attribute.string, dString->str);
    return OK;
}

// Function for string handling
int string_handler(DString_t *dString, Token_t *token) {
    int curr;
    char oct_hex[4] = {
        0,
    };
    char *garbage_strtol;
    bool num_ok = true;
    DString_t dString_local;
    d_string_init(&dString_local);

    for (unsigned int i = 0; i < dString->length; i++) {
        curr = dString->str[i];
        if (curr >= 0 && curr <= 31) {
            return LEX_ERR;
        }
        if (curr == '$') {
            continue;
        }
        if (curr == '\\') {  // escape sequence
            curr = dString->str[++i];
            switch (curr) {
                case 'n':
                    d_string_add_char(&dString_local, '\n');
                    break;
                case 't':
                    d_string_add_char(&dString_local, '\t');
                    break;
                case '\"':
                    d_string_add_char(&dString_local, curr);
                    break;
                case '\\':
                    d_string_add_char(&dString_local, curr);
                    break;
                case '$':
                    d_string_add_char(&dString_local, curr);
                    break;
                case 'x':  // hex case
                    for (int x = 0; x < 2; x++) {
                        curr = dString->str[++i];
                        // correct format handling
                        if (((x == 1 && oct_hex[0] == '0') ? curr >= '1' : curr >= '0') && curr <= '9') {
                            oct_hex[x] = curr;
                            oct_hex[x + 1] = '\0';
                        } else if (curr >= 'a' && curr <= 'f') {
                            oct_hex[x] = curr;
                            oct_hex[x + 1] = '\0';
                        } else if (curr >= 'A' && curr <= 'F') {
                            oct_hex[x] = curr;
                            oct_hex[x + 1] = '\0';
                        } else {
                            d_string_add_char(&dString_local, '\\');
                            d_string_add_char(&dString_local, 'x');
                            for (int j = 0; oct_hex[j] != '\0'; j++) {
                                d_string_add_char(&dString_local, oct_hex[j]);
                            }
                            d_string_add_char(&dString_local, curr);
                            num_ok = false;
                            break;
                        }
                    }
                    // convert value to int
                    if (num_ok) {
                        d_string_add_char(&dString_local, (char)strtol(oct_hex, &garbage_strtol, 16));
                    }
                    for (int j = 0; j < 4; j++) {
                        oct_hex[j] = '\0';
                    }
                    num_ok = true;
                    break;
                case '0':
                case '1':
                case '2':
                case '3':  // oct case
                    oct_hex[0] = dString->str[i];
                    for (int x = 1; x < 3; x++) {
                        curr = dString->str[++i];
                        // correct format handling
                        if (((x == 2 && oct_hex[0] == '0' && oct_hex[1] == '0') ? curr >= '1' : curr >= '0') && curr <= '7') {
                            oct_hex[x] = curr;
                            oct_hex[x + 1] = '\0';
                        } else {
                            d_string_add_char(&dString_local, '\\');
                            for (int j = 0; oct_hex[j] != '\0'; j++) {
                                d_string_add_char(&dString_local, oct_hex[j]);
                            }
                            d_string_add_char(&dString_local, curr);
                            num_ok = false;
                            break;
                        }
                    }
                    // convert value to int
                    if (num_ok) {
                        d_string_add_char(&dString_local, (char)strtol(oct_hex, &garbage_strtol, 8));
                    }
                    for (int j = 0; j < 4; j++) {
                        oct_hex[j] = '\0';
                    }
                    num_ok = true;
                    break;
                default:
                    // incorrect escape sequence, add everything to string as it
                    // is
                    d_string_add_char(&dString_local,
                                      '\\');  // adds '\' to string
                    d_string_add_char(&dString_local,
                                      curr);  // adds char after '\' to string
            }
        } else {
            d_string_add_char(&dString_local, curr);
        }
    }

    // Adds string to token
    token->attribute.string = malloc(sizeof(char) * (dString_local.length + 1));
    if (token->attribute.string == NULL) {
        return INTERNAL_ERR;
    }
    strcpy(token->attribute.string, dString_local.str);
    d_string_free_and_clear(&dString_local);
    token->type = T_STRING;
    return OK;
}

// Function for variable IDs hadling
int id_handler(DString_t *dString, Token_t *token) {
    if (strcmp(dString->str, "$") == 0) {
        return LEX_ERR;
    }
    token->attribute.string = malloc(sizeof(char) * (dString->length + 1));
    if (token->attribute.string == NULL) {
        return INTERNAL_ERR;
    }
    strcpy(token->attribute.string, dString->str);
    token->type = T_ID;
    return OK;
}

// Function for integer handling
int int_handler(DString_t *dString, Token_t *token) {
    char *garbage_strtol;
    int decimal = (int)strtol(dString->str, &garbage_strtol, 10);
    token->attribute.string = malloc(sizeof(char) * (dString->length + 1));
    if (token->attribute.string == NULL) {
        return INTERNAL_ERR;
    }
    strcpy(token->attribute.string, dString->str);
    token->attribute.value = decimal;
    token->type = T_INT;
    return OK;
}

// Function for double handling
int float_handler(DString_t *dString, Token_t *token) {
    char *garbage_strtol;
    double decimal = strtod(dString->str, &garbage_strtol);
    token->attribute.dec_value = decimal;
    token->type = T_FLOAT;
    // insert float value into token.attribute.string
    char output[100] = {0};
    snprintf(output, 100, "%a", decimal);
    token->attribute.string = malloc(sizeof(char) * (strlen(output) + 1));
    if (token->attribute.string == NULL) {
        return INTERNAL_ERR;
    }
    strcpy(token->attribute.string, output);
    return OK;
}

// Part of FSM implemetation, returns FSM STATE according to current state and
// input char
T_State_t state(T_State_t act, int curr, DString_t *DString) {
    switch (act) {
        case S_START:
            if ((curr >= 'a' && curr <= 'z') || (curr >= 'A' && curr <= 'Z') || (curr == '_')) {
                d_string_add_char(DString, curr);
                return S_KEYWORD;
            }
            if (curr >= '0' && curr <= '9') {
                d_string_add_char(DString, curr);
                return S_INT;
            }
            if (curr == '?') {
                d_string_add_char(DString, curr);
                return QUEST_MARK;
            }
            if (curr == '$') {
                d_string_add_char(DString, curr);
                curr = getchar();
                if (curr >= '0' && curr <= '9') {
                    return S_ERR;
                }
                ungetc(curr, stdin);
                return S_ID;
            }
            if (curr == '(') {
                return S_LBR;
            }
            if (curr == ')') {
                return S_RBR;
            }
            if (curr == '"') {
                return S_STRING;
            }
            if (curr == ';') {
                return S_SEM;
            }
            if (curr == '/') {
                return S_DIV;
            }
            if (curr == '+') {
                return S_ADD;
            }
            if (curr == '-') {
                return S_SUB;
            }
            if (curr == '*') {
                return S_MUL;
            }
            if (curr == ',') {
                return S_COMMA;
            }
            if (curr == '{') {
                return S_LCBR;
            }
            if (curr == '}') {
                return S_RCBR;
            }
            if (curr == ':') {
                return S_COL;
            }
            if (curr == '.') {
                return S_CONCAT;
            }
            if (curr == '<') {
                return S_LT;
            }
            if (curr == '>') {
                return S_GT;
            }
            if (curr == '=') {
                return S_ASSIGN;
            }
            if (curr == '!') {
                return S_NEQ;
            }
            return S_ERR;

        // divison and possible comments
        case S_DIV:
            if (curr == '/') {
                return S_LC;
            } else if (curr == '*') {
                return S_BC;
            }
            return S_ERR;

        // possible ===
        case S_POSS_EQ:
            if (curr == '=') {
                return S_EQ_OK;
            }
            return S_ERR;

        // possible !==
        case S_POSS_NEQ:
            if (curr == '=') {
                return S_NEQ_OK;
            }
            return S_ERR;

        // keywords and epilog
        case S_KEYWORD:
            if ((curr >= 'a' && curr <= 'z') || (curr >= 'A' && curr <= 'Z') || (curr == '_') || (curr >= '0' && curr <= '9')) {
                d_string_add_char(DString, curr);
                return S_KEYWORD;
            } else {
                ungetc(curr, stdin);
                return S_KEYWORD_END;
            }
        case QUEST_MARK:
            if (curr == '>') {
                return S_PROL_END;
            } else if ((curr >= 'a' && curr <= 'z') || (curr >= 'A' && curr <= 'Z') || (curr == '_')) {
                d_string_add_char(DString, curr);
                return S_KEYWORD;
            } else {
                return S_ERR;  // ex: ?8 or ?= ...
            }

        // strings
        case S_STRING:
            if (curr == '\\') {
                d_string_add_char(DString, curr);
                return S_STRING_ESC;
            }
            if (curr != '"') {
                d_string_add_char(DString, curr);
                return S_STRING;
            } else {
                return S_STRING_END;
            }
        case S_STRING_ESC:  // \ was in string
            d_string_add_char(DString, curr);
            return S_STRING;

        // identificators
        case S_ID:
            if ((curr >= 'a' && curr <= 'z') || (curr >= 'A' && curr <= 'Z') || (curr == '_') || (curr >= '0' && curr <= '9')) {
                d_string_add_char(DString, curr);
                return S_ID;
            } else {
                ungetc(curr, stdin);
                return S_ID_END;
            }

        // numbers
        case S_INT:
            if (curr >= '0' && curr <= '9') {
                d_string_add_char(DString, curr);
                return S_INT;
            }
            // num is float
            else if (curr == '.' || curr == 'e' || curr == 'E') {
                d_string_add_char(DString, curr);
                curr = getchar();
                if (curr == '+' || curr == '-') {
                    d_string_add_char(DString, curr);
                    curr = getchar();
                    if (curr >= '0' && curr <= '9') {
                        ungetc(curr, stdin);
                        return S_FLOAT;
                    } else {
                        return S_ERR;
                    }
                } else if (curr >= '0' && curr <= '9') {
                    ungetc(curr, stdin);
                } else {
                    return S_ERR;
                }
                return S_FLOAT;
            } else {
                ungetc(curr, stdin);
                return S_INT_END;
            }
        case S_FLOAT:
            if (curr >= '0' && curr <= '9') {
                d_string_add_char(DString, curr);
                return S_FLOAT;
            }
            // exponent
            else if (curr == 'e' || curr == 'E') {
                d_string_add_char(DString, curr);
                curr = getchar();
                if (curr == '+' || curr == '-') {
                    d_string_add_char(DString, curr);
                    curr = getchar();
                    if (curr >= '0' && curr <= '9') {
                        ungetc(curr, stdin);
                        return S_FLOAT;
                    } else {
                        return S_ERR;
                    }
                } else if (curr >= '0' && curr <= '9') {
                    ungetc(curr, stdin);
                } else {
                    return S_ERR;
                }
                return S_FLOAT;
            } else {
                ungetc(curr, stdin);
                return S_FLOAT_END;
            }

        // comments
        case S_LC:
            if (curr != '\n') {
                return S_LC;
            }
            return S_START;
        case S_BC:
            if (curr == '*') {
                return S_POSS_BC_END;
            }
            return S_BC;
        default:  // should never happen, unknown state handling (raises LEX_ERR)
            return S_ERR;
    }
}

// Function that returns the token through the pointer and returns if the token
// is valid
int scan(Token_t *token) {
    DString_t dString;
    d_string_init(&dString);
    int curr, return_type = -1;
    T_State_t act_state = S_START;
    static bool start_of_file = true;

    // prolog handler
    if (start_of_file) {
        int prol_ret = prolog_handler();
        if (prol_ret == LEX_ERR) {
            return_type = LEX_ERR;
        } else if (prol_ret == SYNTAX_ERR) {
            return_type = SYNTAX_ERR;
        }
        start_of_file = false;
    }

    while (return_type == -1) {
        curr = getchar();
        if (curr == EOF && act_state == S_START) {
            token->type = T_EOF;
            return_type = OK;
            break;
        } else if (curr == EOF && act_state != S_START) {
            // edge cases if some of these states occur at the end of file
            if (act_state == S_KEYWORD) {
                return_type = keyword_handler(&dString, token);
                ungetc(curr, stdin);
                break;
            }
            if (act_state == S_INT) {
                return_type = int_handler(&dString, token);
                ungetc(curr, stdin);
                break;
            }
            if (act_state == S_FLOAT) {
                return_type = float_handler(&dString, token);
                ungetc(curr, stdin);
                break;
            }
            if (act_state == S_ID) {
                return_type = id_handler(&dString, token);
                ungetc(curr, stdin);
                break;
            }
            if (act_state == S_LC) {
                act_state = S_START;
                ungetc(curr, stdin);
                continue;
            }
            return_type = LEX_ERR;
            break;
        }
        if (curr == '\n') {
            // edge cases if EOL occurs and state is some of the listed
            if (act_state == S_KEYWORD) {
                return_type = keyword_handler(&dString, token);
                ungetc(curr, stdin);
                break;
            }
            if (act_state == S_INT) {
                return_type = int_handler(&dString, token);
                ungetc(curr, stdin);
                break;
            }
            if (act_state == S_FLOAT) {
                return_type = float_handler(&dString, token);
                ungetc(curr, stdin);
                break;
            }
            if (act_state == S_ID) {
                return_type = id_handler(&dString, token);
                ungetc(curr, stdin);
                break;
            }
            line_num++;
            if (act_state != S_LC) {
                continue;
            }
        }
        // get rid of white chars
        if (is_white(curr) && act_state == S_START) {
            continue;
        }

        // FSM state determination
        T_State_t next = state(act_state, curr, &dString);
        switch (next) {
            // error case
            case S_ERR:
                return_type = LEX_ERR;
                break;

            case S_START:
                act_state = S_START;
                break;

            // one char tokens
            case S_LBR:
                token->type = T_LBR;
                return_type = OK;
                break;
            case S_RBR:
                token->type = T_RBR;
                return_type = OK;
                break;
            case S_SEM:
                token->type = T_SEM;
                return_type = OK;
                break;
            case S_ADD:
                token->type = T_ADD;
                return_type = OK;
                break;
            case S_SUB:
                token->type = T_SUB;
                return_type = OK;
                break;
            case S_MUL:
                token->type = T_MUL;
                return_type = OK;
                break;
            case S_COMMA:
                token->type = T_COMMA;
                return_type = OK;
                break;
            case S_LCBR:
                token->type = T_LCBR;
                return_type = OK;
                break;
            case S_RCBR:
                token->type = T_RCBR;
                return_type = OK;
                break;
            case S_COL:
                token->type = T_COL;
                return_type = OK;
                break;
            case S_CONCAT:
                token->type = T_CONCAT;
                return_type = OK;
                break;

            // division and possible comment
            case S_DIV:
                curr = getchar();
                if (curr == '/') {
                    ungetc(curr, stdin);
                    act_state = S_LC;
                    break;
                } else if (curr == '*') {
                    ungetc(curr, stdin);
                    act_state = S_BC;
                    break;
                }
                ungetc(curr, stdin);
                token->type = T_DIV;
                return_type = OK;
                break;

            // longer tokens but of known length
            case S_PROL_END:
                // epilog should be last thing in file
                curr = getchar();
                if (curr == EOF) {
                    token->type = T_EOF;
                    return_type = OK;
                    break;
                }
                return_type = LEX_ERR;
                break;
            case S_LT:
                curr = getchar();
                if (curr == '=') {
                    token->type = T_LEQ;
                    return_type = OK;
                } else {
                    ungetc(curr, stdin);
                    token->type = T_LT;
                    return_type = OK;
                }
                break;
            case S_GT:
                curr = getchar();
                if (curr == '=') {
                    token->type = T_GEQ;
                    return_type = OK;
                } else {
                    ungetc(curr, stdin);
                    token->type = T_GT;
                    return_type = OK;
                }
                break;
            case S_ASSIGN:
                curr = getchar();
                if (curr == '=') {
                    act_state = S_POSS_EQ;
                } else {
                    ungetc(curr, stdin);
                    token->type = T_ASSIGN;
                    return_type = OK;
                }
                break;
            case S_EQ_OK:
                token->type = T_EQ;
                return_type = OK;
                break;
            case S_NEQ:
                curr = getchar();
                if (curr == '=') {
                    act_state = S_POSS_NEQ;
                } else {  // IFJ22 does not have ! operator (negation) -> error
                    ungetc(curr, stdin);
                    return_type = LEX_ERR;
                }
                break;
            case S_NEQ_OK:
                token->type = T_NEQ;
                return_type = OK;
                break;

            // keywords
            case S_KEYWORD:
                act_state = next;
                break;
            case S_KEYWORD_END:
                return_type = keyword_handler(&dString, token);
                break;
            case QUEST_MARK:
                act_state = next;
                break;

            // identificators
            case S_ID:
                act_state = next;
                break;
            case S_ID_END:
                return_type = id_handler(&dString, token);
                break;

            // strings
            case S_STRING:
                act_state = next;
                break;
            case S_STRING_END:
                return_type = string_handler(&dString, token);
                break;
            case S_STRING_ESC:
                act_state = next;
                break;

            // numbers - int
            case S_INT:
                act_state = next;
                break;
            case S_INT_END:
                return_type = int_handler(&dString, token);
                break;

            // numbers - float
            case S_FLOAT:
                act_state = next;
                break;
            case S_FLOAT_END:
                return_type = float_handler(&dString, token);
                token->type = T_FLOAT;
                break;

            // comments
            case S_LC:
                act_state = next;
                break;
            case S_BC:
                act_state = next;
                break;
            case S_POSS_BC_END:
                curr = getchar();
                if (curr == '/') {
                    act_state = S_START;
                    break;
                } else {
                    act_state = S_BC;
                    break;
                }

            // unknown return type
            default:
                return_type = LEX_ERR;
                break;
        }
    }

    // free dynamic string
    d_string_free_and_clear(&dString);
    return return_type;
}
