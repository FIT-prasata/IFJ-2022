#pragma once

#include <assert.h>
#include <stdio.h>

typedef enum { PASSED, FAILED } TestResult_t;

#define TEST(NAME, DESCRIPTION)       \
    void NAME() {                     \
        TestResult_t result = FAILED; \
        char* t_name = #NAME;         \
        char* t_desc = #DESCRIPTION;
#define ENDTEST                                               \
    if (result == PASSED) {                                   \
        printf("[PASSED] %s", t_name);                        \
    } else {                                                  \
        fprintf(stderr, "[FAILED] %s -> %s", t_name, t_desc); \
    }                                                         \
    printf("\n");                                             \
    }

#define FAIL(REASON) printf("[FAILED] %s", REASON)
