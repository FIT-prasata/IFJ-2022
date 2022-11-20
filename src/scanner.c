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
                        "null", "return", "string",   "void", "while"};
    int keyword_types[] = {K_ELSE, K_FLOAT, K_FUNC, K_IF,   K_INT,
                           K_NULL, K_RET,   K_STR,  K_VOID, K_WHILE};
    int keywords_array_size = sizeof(keywords) / sizeof(keywords[0]);

    for (int i = 0; i < keywords_array_size; i++) {
        if (strcmp(keywords[i], dString->str) == 0) {
            token->type = keyword_types[i];
            return OK;
        }
    }
    token->type = T_FUNC_ID;
    token->attribute.string = malloc(sizeof(char) * (dString->length + 1));
    strcpy(token->attribute.string, dString->str);
    return OK;
}



T_State_t state(T_State_t act, int curr, DString_t *DString){
    switch(act){
        case S_START:
            if (curr >= 'a' && curr <= 'z'){
                d_string_add_char(DString, curr);
                return S_KEYWORD; // muze byt i nazev funkce :)
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
            return LEX_ERR;
        case S_KEYWORD:
            if (curr >= 'a' && curr <= 'z'){
                d_string_add_char(DString, curr);
                return S_KEYWORD;
            }
            else{
                ungetc(curr, stdin);
                return S_KEYWORD_END;
            }
        case S_STRING:
            if (curr != '"'){
                d_string_add_char(DString, curr);
                return S_STRING;
            }
            else{
                return S_STRING_END;
            }
        default: // should never happen, maybe raise error or something? TODO, temporary solution just to get rid of warnings
            return S_START;
    }
}

int scan(Token_t *token) {
    DString_t dString;
    d_string_init(&dString); // TODO: uvolnit pamet!!!!!!
    int curr;
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

    while(true){
        curr = getchar();
        if (curr == EOF) {
            token->type = T_EOF;
            return OK;
        }
        if (curr == '\n'){ // a zaroven stav neni string
            line_num++;
            continue;
        }
        if (is_white(curr)){ // skip white chars
            continue;
        }
        T_State_t next = state(act_state, curr, &dString);
        switch (next){
            // error case
            case S_ERR:
                return LEX_ERR;

            // one char tokens
            case S_LBR:
                token->type = T_LBR;
                return OK;
            case S_RBR:
                token->type = T_RBR;
                return OK;
            case S_SEM:
                token->type = T_SEM;
                return OK;

            // keywords
            case S_KEYWORD:
                act_state = next;
                break;
            case S_KEYWORD_END:
                if (keyword_handler(&dString, token)){
                    d_string_free_and_clear(&dString);
                    return LEX_ERR; // zjistit jestli nevracet KEYWORD_ERR nebo tak neco
                }
                d_string_free_and_clear(&dString);
                return OK;

            // strings
            case S_STRING:
                act_state = next;
                token->type = T_STRING;
                break;
            case S_STRING_END:
                token->attribute.string = malloc(sizeof(char) * dString.length + 1);
                strcpy(token->attribute.string, dString.str);
                //TODO: free string
                return OK;

            // something really bad happened
            default:
                printf("DEFAULT in next switch, shouldn't happen\n");
                return LEX_ERR;
            
        }
    }
}