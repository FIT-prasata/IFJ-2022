#include "test_utils.h"

#include "../scanner.h"


FILE *f;
// mocked getchar
int getchar() { 
    return fgetc(f); 
    }


#define TEST__CODE_DEFAULT \
    "./src/__tests__/t_lex_analyzer_test_cases/test_default/test_default.code"
#define TEST_CODE_WHITESPACES                                          \
    "./src/__tests__/t_lex_analyzer_test_cases/test_whitespaces/" \
    "test_whitespaces.code"
#define TEST_EMPTY_FILE "./src/__tests__/t_lex_analyzer_test_cases/test_prolog/test_empty_file.code"


#define SET_FILE(filepath) f = fopen(filepath, "r");
#define CLOSE_FILE(f) fclose(f);

int compareFile(char *path1_ref, char *path2, int *line) {
    FILE *fPtr1 = fopen(path1_ref, "r");
    if (fPtr1 == NULL) {
        return 0;
    }
    FILE *fPtr2 = fopen(path2, "r");
    if (fPtr2 == NULL) {
        return 0;
    }
    char ch1, ch2;

    *line = 1;

    do {
        // Input character from both files
        ch1 = fgetc(fPtr1);
        ch2 = fgetc(fPtr2);

        // Increment line
        if (ch1 == '\n') {
            *line += 1;
        }

        // If characters are not same then return -1
        if (ch1 != ch2) return 0;

    } while (ch1 != EOF && ch2 != EOF);

    /* If both files have reached end */
    if (ch1 == EOF && ch2 == EOF)
        return 1;
    else
        return 0;
}

int line;
// Test - tokenize basic program
// TEST(T1_string) //TODO: zjistit jak funguje spousteni .exe, jeho vystup
// nasmerovat do test1.out ASSERT_TRUE(compareFile(TEST1_REF, TEST1, &line))
// ENDTEST_LEX

TEST(t_mock_getchar)
SET_FILE(TEST__CODE_DEFAULT)
ASSERT_TRUE(getchar() == '<')
ASSERT_TRUE(getchar() == '?')
ENDTEST

TEST(t_empty_file)
Token_t *token = malloc(sizeof(Token_t));
SET_FILE(TEST_EMPTY_FILE)
ASSERT_TRUE(scan(token) == SYNTAX_ERR)
CLOSE_FILE(f)
ENDTEST

int run_lex_analyzer_tests() {
    int errors = 0;
    printf("\nRunning Lex analyzer complex tests...\n");
    errors += t_mock_getchar();
    errors += t_empty_file();
    return errors;
}