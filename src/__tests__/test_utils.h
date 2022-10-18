#pragma once

#include <assert.h>
#include <stdio.h>

#include "../error.h"

typedef enum { PASSED, FAILED } TestResult_t;

#define TEST(NAME, DESCRIPTION)       \
    void NAME() {                     \
        TestResult_t result = FAILED; \
        char* t_name = #NAME;         \
        char* t_desc = #DESCRIPTION;  \
        char* e_msg = "no error";
#define ENDTEST                                                         \
    if (result == PASSED) {                                             \
        printf("[PASSED] %s", t_name);                                  \
    } else {                                                            \
        fprintf(stderr, "[FAILED] %s -> failed on: %s", t_name, e_msg); \
    }                                                                   \
    printf("\n");                                                       \
    }

#define ASSERT_TRUE(CONDITION) \
    if (!(CONDITION)) {        \
        result = FAILED;       \
        e_msg = #CONDITION;    \
    }