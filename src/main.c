/**
 * @c file main.c
 * @project IFJ 2022/2023
 * @variant TRP
 *
 * @brief Main file
 *
 * @authors <xsklen14> - David Sklenář
 *          <xproch0o> - Marek Procházka
 *          <xzavad20> - Lukáš Zavadil
 *          <xsvetl07> - Adam Světlík
 */

// GLOBAL line number
int line_num = 1;
int tmp_var_count = 1;
// LOCAL INCLUDES - tohletoto legacy code nechat v tomto poradi plsky
#include "code_generator.h"
#include "dynamic_string.h"
#include "error.h"
#include "parser.h"
#include "scanner.h"
#include "stack.h"
#include "symtable.h"

int main(void) {
    int status = OK;

    FILE *file = fopen("test.out", "w");
    built_in_strval(file);

    fclose(file);

    return 0;
}
