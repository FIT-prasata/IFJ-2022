#pragma once

#ifndef TEST_UTILS_H
#define TEST_UTILS_H

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../error.h"

// line counting
extern int line_num;

typedef enum { PASSED, FAILED } TestResult_t;

#define RED(str) "\x1b[31m" str "\x1b[0m"
#define GREEN(str) "\x1b[32m" str "\x1b[0m"

#define TEST(NAME)                    \
    int NAME() {                      \
        TestResult_t result = PASSED; \
        char* t_name = #NAME;
#define ENDTEST                                  \
    if (result == PASSED) {                      \
        printf(GREEN("[PASSED] %s \n"), t_name); \
        return 0;                                \
    } else {                                     \
        printf(RED("[FAILED] %s \n"), t_name);   \
        return 1;                                \
    }                                            \
    }

#define ASSERT_TRUE(CONDITION)                                               \
    if (!(CONDITION)) {                                                      \
        result = FAILED;                                                     \
        printf(RED("Failed assertion in '%s' -> ASSERT_TRUE(%s)\n"), t_name, \
               #CONDITION);                                                  \
    }

#endif // TEST_UTILS_H
