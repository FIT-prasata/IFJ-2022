#pragma once

#include <assert.h>
#include <stdio.h>

#include "../error.h"

typedef enum { PASSED, FAILED } TestResult_t;

#define RED(str) "\x1b[31m" str "\x1b[0m"
#define GREEN(str) "\x1b[32m" str "\x1b[0m"

#define TEST(NAME)                    \
    int NAME() {                      \
        TestResult_t result = PASSED; \
        char* t_name = #NAME;         \
        char* e_msg = "no error";
#define ENDTEST                                                         \
    if (result == PASSED) {                                             \
        printf(GREEN("[PASSED] %s \n"), t_name);                        \
        return 0;                                                       \
    } else {                                                            \
        printf(RED("[FAILED] %s -> failed on: %s \n"), t_name, \
                e_msg);                                                 \
        return 1;                                                       \
    }                                                                   \
    }

#define ASSERT_TRUE(CONDITION) \
    if (!(CONDITION)) {        \
        result = FAILED;       \
        e_msg = #CONDITION;    \
    }
