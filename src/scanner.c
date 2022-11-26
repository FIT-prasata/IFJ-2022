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

extern int line_num;

int is_white(int input)
{
    return (input == ' ' || input == '\t' || (input >= 11 && input <= 13));
}

// line comment
char skip_lc() {
    int curr;
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
int skip_bc(int *line_num) {
    char prev;
    int curr;
    while (true) {
        curr = getchar();
        if (curr == EOF) {
            return BC_EOF_ERR;
        }
        if (prev == '*' && curr == '/') {
            return OK;
        }
        if (curr == '\n') {
            line_num++;
        }
        prev = curr;
    }
}

int prolog_handler(){
    char prolog_start[25] = {'\0',};
    int curr;
    bool is_ok = false;

    // prolog handler
    for(int i = 0; i < 5; i++){
        curr = getchar();
        prolog_start[i] = curr;
    }
    if (strcmp(prolog_start, "<?php") == 0) {
        curr = getchar();
        while(is_white(curr)){
            curr = getchar();
            is_ok = true;
        }
        if (!is_ok && curr != '\n'){ // if there is no white space after prolog
            return 1;
        }
        if (curr == '\n'){ // add line count
            line_num++;
            curr = getchar();
        }
        for(int i = 0; i < 24; i++){
            prolog_start[i] = curr;
            curr = getchar();
        }
        if (strcmp(prolog_start, "declare(strict_types=1);") == 0){
            return 0;
        } else{
            return 1;
        }
    } else {
        return 1; // prolog is not present/contains some white chars at the start of file
    }
}


int keyword_handler(DString_t *dString, Token_t *token){
    char *keywords[] = {"else", "float",  "function", "if",   "int",
                        "null", "return", "string",   "void", "while", "?int", "?string", "?float"};
    int keyword_types[] = {K_ELSE, K_FLOAT, K_FUNC, K_IF,   K_INT,
                           K_NULL, K_RET,   K_STR,  K_VOID, K_WHILE, K_INT_NULL, K_STR_NULL, K_FLOAT_NULL};
    int keywords_array_size = sizeof(keywords) / sizeof(keywords[0]);

    for (int i = 0; i < keywords_array_size; i++) {
        if (strcmp(keywords[i], dString->str) == 0) {
            token->type = keyword_types[i];
            return OK;
        }
    }
    token->type = T_FUNC_ID;
    token->attribute.string = malloc(sizeof(char) * (dString->length + 1));
    if (token->attribute.string == NULL) {
        return INTERNAL_ERR;
    }
    strcpy(token->attribute.string, dString->str);
    return OK;
}


int string_handler(DString_t *dString, Token_t *token){ // NEFUNGUJE, dodelat \x a \octal

    int curr;
    // char last = '0';
    char oct_hex[4] = {0,};
    // oct_hex[3] = '\0';
    char *garbage_strtol;
    bool num_ok = true;
    // int decimal = 0;
    DString_t dString_local;
    d_string_init(&dString_local);
    // set_type(token, T_STRING);

    for (unsigned int i = 0; i < dString->length; i++) {
        curr = dString->str[i];
        if (curr >= 0 && curr <= 31) {
            return STR_ERR;
        }
        if (curr == '$'){
            continue;
        }
        if (curr == '\\') {
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
                case 'x':
                    for (int x = 0; x < 2; x++) {
                        curr = dString->str[++i];
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
                    if (num_ok) {
                        d_string_add_char(&dString_local, (char) strtol(oct_hex, &garbage_strtol, 16));
                    }
                    for(int j = 0; j < 4; j++){
                        oct_hex[j] = '\0';
                    }
                    num_ok = true;
                    break;
                case '0':
                case '1':
                case '2':
                case '3':
                    oct_hex[0] = dString->str[i];
                    for (int x = 1; x < 3; x++) {
                        curr = dString->str[++i];
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
                    if (num_ok) {
                        d_string_add_char(&dString_local, (char) strtol(oct_hex, &garbage_strtol, 8));
                    }
                    for(int j = 0; j < 4; j++){
                        oct_hex[j] = '\0';
                    }
                    num_ok = true;
                    break;
                default:
                    d_string_add_char(&dString_local, '\\'); // adds '\' to string
                    d_string_add_char(&dString_local, curr); // adds char after '\' to string
            }
        } else {
            d_string_add_char(&dString_local, curr);
        }
        // last = curr;
    }



    token->attribute.string = malloc(sizeof(char) * (dString_local.length + 1));
    if (token->attribute.string == NULL) {
        return INTERNAL_ERR;
    }
    strcpy(token->attribute.string, dString_local.str);
    d_string_free_and_clear(&dString_local);
    token->type = T_STRING;

    // token->attribute.string = malloc(sizeof(char) * (dString->length + 1));
    // if (token->attribute.string == NULL) {
    //     return INTERNAL_ERR;
    // }
    // strcpy(token->attribute.string, dString->str);
    // token->type = T_STRING;


    return OK;
}


T_State_t state(T_State_t act, int curr, DString_t *DString){
    switch(act){
        case S_START:
            if ((curr >= 'a' && curr <= 'z') || (curr >= 'A' && curr <= 'Z') || (curr == '_')){
                d_string_add_char(DString, curr);
                return S_KEYWORD; // muze byt i nazev funkce :)
            }
            if (curr == '?'){
                d_string_add_char(DString, curr);
                return QUEST_MARK;
            }
            if (curr == '('){
                return S_LBR;
            }
            if (curr == ')'){
                return S_RBR;
            }
            if (curr == '"'){
                return S_STRING;
            }
            if (curr == ';'){
                return S_SEM;
            }
            if (curr == '/'){
                return S_DIV;
            }
            return LEX_ERR;
        
        case S_DIV:
            if (curr == '/'){
                return S_LC;
            }
            else if (curr == '*'){
                return S_BC;
            }
            return LEX_ERR;
        case S_KEYWORD:
            if ((curr >= 'a' && curr <= 'z') || (curr >= 'A' && curr <= 'Z') || (curr == '_') || (curr >= '0' && curr <= '9')){
                d_string_add_char(DString, curr);
                return S_KEYWORD;
            }
            else{
                ungetc(curr, stdin);
                return S_KEYWORD_END;
            }
        case QUEST_MARK:
            if (curr == '>'){
                return S_PROL_END;
            }
            else if((curr >= 'a' && curr <= 'z') || (curr >= 'A' && curr <= 'Z') || (curr == '_')){
                d_string_add_char(DString, curr);
                return S_KEYWORD;
            }
            else{
                return LEX_ERR; // ex: ?8 or ?= ...
            }
        // strings
        case S_STRING:
            if (curr == '\\'){
                d_string_add_char(DString, curr);
                return S_STRING_ESC;
            }
            if (curr != '"'){
                d_string_add_char(DString, curr);
                return S_STRING;
            }
            else{
                return S_STRING_END;
            }
        case S_STRING_ESC:
            d_string_add_char(DString, curr);
            return S_STRING;
        // comments
        case S_LC:
            if (curr != '\n'){
                return S_LC;
            }
            return S_START;
        case S_BC:
            if (curr == '*'){
                return S_POSS_BC_END;
            }
            return S_BC;
        default: // should never happen, maybe raise error or something? TODO, temporary solution just to get rid of warnings
            return S_START;
    }
}

int scan(Token_t *token) {
    DString_t dString;
    d_string_init(&dString);
    int curr, return_type = -1;
    // static char last;
    T_State_t act_state = S_START;
    static bool start_of_file = true;
    //static int line_num = 1; // line counter

    // prolog handler
    if (start_of_file) {
        if (prolog_handler()) {
            return LEX_ERR;
        }
        start_of_file = false;
    }

    while(return_type == -1){
        curr = getchar();
        if (curr == EOF) {
            token->type = T_EOF;
            return_type = OK;
            break;
        }
        if (curr == '\n'){ // a zaroven stav neni string, TODO: spravit keywordy kdyz jsou na dalsim radku bez ; (return LEX_ERR)
            line_num++;
            if (act_state != S_LC){
                continue;
            }
            //continue;
        }
        if (is_white(curr) && act_state != S_STRING && act_state != S_STRING_ESC){ // skip white chars, except in string
            continue;
        }



        T_State_t next = state(act_state, curr, &dString);
        switch (next){
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
                return_type =  OK;
                break;
            case S_RBR:
                token->type = T_RBR;
                return_type = OK;
                break;
            case S_SEM:
                token->type = T_SEM;
                return_type = OK;
                break;

            // expressions
            case S_DIV:
                curr = getchar();
                if (curr == '/'){
                    ungetc(curr, stdin);
                    act_state = S_LC;
                    break;
                }
                else if (curr == '*'){
                    ungetc(curr, stdin);
                    act_state = S_BC;
                    break;
                }
                token->type = T_DIV;
                return_type = OK;
                break;
            
            // longer tokens but of known length
            case S_PROL_END:
                token->type = T_END_PROLOG;
                return_type = OK; // TODO: dodelat overovani ze za koncem prologu uz nic neni
                break;

            // keywords
            case S_KEYWORD:
                act_state = next;
                break;
            case S_KEYWORD_END:
                if (keyword_handler(&dString, token)){
                    return_type = INTERNAL_ERR; // zjistit jestli nevracet KEYWORD_ERR nebo tak neco
                    break;
                }
                return_type = OK;
                break;
            case QUEST_MARK:
                act_state = next;
                break;

            // strings
            case S_STRING:
                act_state = next;
                break;
            case S_STRING_END:
                if (string_handler(&dString, token) == INTERNAL_ERR){
                    return_type = INTERNAL_ERR;
                    break;
                }
                else if (string_handler(&dString, token) == LEX_ERR){
                    return_type = LEX_ERR;
                    break;
                }
                return_type = OK;
                break;
            case S_STRING_ESC:
                act_state = next;
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
                if (curr == '/'){
                    act_state = S_START;
                    break;
                }
                else{
                    //ungetc(curr, stdin);
                    act_state = S_BC;
                    break;
                }
            // something really bad happened
            default:
                printf("DEFAULT in next switch, shouldn't happen\n");
                return_type = LEX_ERR;
                break;
            
        }
    }
    d_string_free_and_clear(&dString);
    return return_type;
}