#include "../dynamic_string.h"
#include "test_utils.h"

TEST(first_test, "dummy test to see if this works")
result = PASSED;
ENDTEST

TEST(second_test, "dummy test to see if this works")
result = FAILED;
ENDTEST

void run_all_tests() {
    first_test();
    second_test();
}
