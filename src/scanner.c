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

char get_non_white() {
    int tmp = getchar();
    return (is_white(tmp)) ? get_non_white() : tmp;
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
        case S_KEYWORD:
            if (curr >= 'a' && curr <= 'z'){
                d_string_add_char(DString, curr);
                return S_KEYWORD;
            }
            else{
                ungetc(curr, stdin);
                return S_ERR;
            }
        case S_STRING:
            if (curr != '"'){
                d_string_add_char(DString, curr);
                return S_STRING;
            }
            else{
                return S_ERR;
            }
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
        if (next == S_ERR){ // tady se ještě musí zavolat funkce na string nebo keyword, která u keyword zjistí jeslti to je keyword nebo volání fce nebo jméno fce nebo tak
                             // nebo u stringu ho zformátuje podle pravidel
            token->attribute.string = malloc(sizeof(char) * dString.length + 1);
            strcpy(token->attribute.string, dString.str);
            return OK;
        }
        if (next == S_LBR){
            token->type = T_LBR;
            return OK;
        }
        if (next == S_RBR){
            token->type = T_RBR;
            return OK;
        }
        if (next == S_SEM){
            token->type = T_SEM;
            return OK;
        }
        if (next == S_STRING){
            act_state = next;
            token->type = T_STRING;
            continue;
            return OK;
        }
        if (next == S_KEYWORD){
            act_state = next;
            token->type = T_KEYWORD; // do NOT set type here, could be keyword or function name
            continue;
            return OK;
        }
    }
}