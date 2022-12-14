#include "../dynamic_string.h"
#include "test_utils.h"

#define D_INIT          \
    DString_t d_string; \
    d_string_init(&d_string);

#define D_FREE d_string_free_and_clear(&d_string);

#define D2_INIT          \
    DString_t d_string2; \
    d_string_init(&d_string2);

#define D2_FREE d_string_free_and_clear(&d_string2);

// Test - dynamic string basic init
// Expected result - OK
TEST(T_d_string_init)
DString_t d_string;
ASSERT_TRUE(d_string_init(&d_string) == OK);
D_FREE
ENDTEST

// Test - dynamic string init with pointer set to NULL
// Expected result - INTERNAL_ERR
TEST(T_d_string_init_NULL)
DString_t* d_string = NULL;
ASSERT_TRUE(d_string_init(d_string) == INTERNAL_ERR);
ENDTEST

// Test - dynamic string init, check if allocated string is terminated with \0
// Expected result - OK
TEST(T_d_string_init_string_termination)
DString_t d_string;
ASSERT_TRUE(d_string_init(&d_string) == OK);
ASSERT_TRUE(d_string.str[d_string.length] == '\0');
D_FREE
ENDTEST

// Test - dynamic string free and clear
// Expected result - OK
TEST(T_d_string_free_and_clear)
D_INIT
ASSERT_TRUE(d_string_free_and_clear(&d_string) == OK);
ENDTEST

// Test - dynamic string add char
// Expected result - OK
TEST(T_d_string_add_char)
D_INIT
ASSERT_TRUE(d_string_add_char(&d_string, 'a') == OK);
ASSERT_TRUE(strcmp(d_string.str, "a") == 0);
ASSERT_TRUE(d_string_add_char(&d_string, 'b') == OK);
ASSERT_TRUE(strcmp(d_string.str, "ab") == 0);
D_FREE
ENDTEST

// Test - dynamic string add single char
// Expected result - OK
TEST(T_d_string_clear)
D_INIT
d_string_add_char(&d_string, 'a');
d_string_add_char(&d_string, 'b');
ASSERT_TRUE(d_string_clear(&d_string) == OK);
ASSERT_TRUE(strcmp(d_string.str, "") == 0);
D_FREE
ENDTEST

// Test - dynamic string add string
// Expected result - OK
TEST(T_d_string_add_str)
D_INIT
ASSERT_TRUE(d_string_add_str(&d_string, "Ahoj mami") == OK);
ASSERT_TRUE(strcmp(d_string.str, "Ahoj mami") == 0);
D_FREE
ENDTEST

// Test - dynamic string add dynamic string
// Expected result - OK
TEST(T_d_string_add_d_string)
D_INIT
D2_INIT
d_string_add_str(&d_string2, "Ignac Voprsal");
ASSERT_TRUE(d_string_add_d_string(&d_string, &d_string2) == NOT_IMPLEMENTED);
D_FREE
D2_FREE
ENDTEST

// Test - dynamic string compare with string
// Expected result - OK
TEST(T_d_string_cmp)
D_INIT
const char* c_str = "pepicek a eliska";
d_string_add_str(&d_string, c_str);
ASSERT_TRUE(d_string_cmp(&d_string, c_str) == 0);
D_FREE
ENDTEST

// Test - copy string into dynamic string
// Expected result - OK
TEST(T_d_string_copy)
D_INIT
D2_INIT
d_string_add_str(&d_string, "Ahoj mami");
ASSERT_TRUE(d_string_copy(&d_string, &d_string2) == OK);
ASSERT_TRUE(strcmp(d_string2.str, "Ahoj mami") == 0);
D_FREE
D2_FREE
ENDTEST

// Test - convert dynamic string to integer
// Expected result - OK
TEST(T_get_d_string_value_to_integer)
D_INIT
int value;
d_string_add_str(&d_string, "123");
ASSERT_TRUE(get_d_string_value_to_integer(&d_string, &value) == OK);
ASSERT_TRUE(value == 123);
d_string_add_str(&d_string, "abc");
ASSERT_TRUE(get_d_string_value_to_integer(&d_string, &value) == INTERNAL_ERR);
D_FREE
ENDTEST

// Test - convert dynamic string to double
// Expected result - OK
TEST(T_get_d_string_value_to_double)
D_INIT
double value;
d_string_add_str(&d_string, "123");
ASSERT_TRUE(get_d_string_value_to_double(&d_string, &value) == OK);
ASSERT_TRUE(value == 123);
d_string_add_str(&d_string, ".123");
ASSERT_TRUE(get_d_string_value_to_double(&d_string, &value) == OK);
ASSERT_TRUE(value == 123.123);
d_string_add_str(&d_string, "abc");
ASSERT_TRUE(get_d_string_value_to_double(&d_string, &value) == INTERNAL_ERR);
D_FREE
ENDTEST

// Test - d_string_insert_before function
// Expected result - OK
TEST(T_d_string_insert_before)
D_INIT
d_string_add_str(&d_string, "hoj mami");
ASSERT_TRUE(strcmp(d_string.str, "hoj mami") == 0);
ASSERT_TRUE(d_string_insert_before(&d_string, 'A') == OK);
ASSERT_TRUE(strcmp(d_string.str, "Ahoj mami") == 0);
D_FREE
ENDTEST

int run_d_string_tests() {
    int errors = 0;
    printf("\nRunning dynamic string tests...\n");
    errors += T_d_string_init();
    errors += T_d_string_init_NULL();
    errors += T_d_string_init_string_termination();
    errors += T_d_string_free_and_clear();
    errors += T_d_string_add_char();
    errors += T_d_string_clear();
    errors += T_d_string_add_str();
    errors += T_d_string_add_d_string();
    errors += T_d_string_cmp();
    errors += T_d_string_copy();
    errors += T_get_d_string_value_to_integer();
    errors += T_get_d_string_value_to_double();
    errors += T_d_string_insert_before();
    return errors;
}
