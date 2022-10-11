// Filename: main.c
// IFJ 2022/2023 project
// TRP variant
//
// Main file
//
// Author: <xsklen14> - David Sklenář
// Author: <xproch0o> - Marek Procházka
// Author: <xzavad20> - Lukáš Zavadil
// Author: <xsvetl07> - Adam Světlík

// LOCAL INCLUDES
#include "dynamic_string.h"
#include "error.h"
#include "stack.h"

int main(void) {
    FILE *file_ptr = stdin;

    // Testing dynamic strings
//    DString_t my_string;
//    fr(d_string_init(&my_string));
//    fr(d_string_add_char(&my_string, 'a'));
//    printf("%s \n", my_string.str);
//    fr(d_string_add_char(&my_string, 'b'));
//    printf("%s \n", my_string.str);
//    fr(d_string_add_str(&my_string, "cdef"));
//    printf("%s \n", my_string.str);
//    fr(d_string_clear(&my_string));
//    fr(d_string_add_str(&my_string, "ghij"));
//    printf("%s \n", my_string.str);
//    if (d_string_cmp(&my_string, "ghij") == 0) {
//        printf("Strings are equal \n");
//    } else {
//        printf("Strings are not equal \n");
//    }
//    fr(d_string_add_char(&my_string, 'k'));
//    if (d_string_cmp(&my_string, "ghij") == 0) {
//        printf("Strings are equal \n");
//    } else {
//        printf("Strings are not equal \n");
//    }
//    DString_t new_string;
//    fr(d_string_init(&new_string));
//    fr(d_string_copy(&my_string, &new_string));
//    printf("%s \n", new_string.str);
//    fr(d_string_free_and_clear(&my_string));
//    fr(d_string_free_and_clear(&new_string));
    //    DString_t not_initialized_string;
    //    fr(d_string_add_char(&not_initialized_string, 'a'));
    // Testing makefile
    /*
        Stack_t stack;
        Token_t token1, token2, result;
        token1.type = 20;
        token2.type = 40;
        stack_init(&stack);
        stack_push(&stack, token1);
        result = stack_get_head(&stack);
        printf("Token: %d\n", result.type);
        stack_push(&stack, token2);
        result = stack_get_head(&stack);
        printf("Token: %d\n", result.type);
        stack_clear(&stack);
        result = stack_get_head(&stack);
        printf("Token: %d", result.type);
    */
    return 0;
}