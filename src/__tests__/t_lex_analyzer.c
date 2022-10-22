#include "../scanner.h"
#include "test_utils.h"

#define DEFAULT_PATH "./src/__tests__/t_lex_analyzer_test_cases/"[60]

int compareFile(char * path1_ref, char * path2, int * line)
{
    FILE *fPtr1 = fopen(path1_ref, "r");
    if (fPtr1 == NULL){
        return 0;
    }
    FILE *fPtr2 = fopen(path2, "r");
    if (fPtr2 == NULL){
        return 0;
    }
    char ch1, ch2;

    *line = 1;

    do
    {
        // Input character from both files
        ch1 = fgetc(fPtr1);
        ch2 = fgetc(fPtr2);
        
        // Increment line 
        if (ch1 == '\n')
        {
            *line += 1;
        }

        // If characters are not same then return -1
        if (ch1 != ch2)
            return 0;


    } while (ch1 != EOF && ch2 != EOF);


    /* If both files have reached end */
    if (ch1 == EOF && ch2 == EOF)
        return 1;
    else
        return 0;
}


// Test - tokenize basic program
TEST(T_test1_string) //TODO: asi cyklus pres get_token, jeho vystup nasmerovat do test1.out, zaroven upravit ASSERT_TRUE tak aby v pripade problemu vracel cislo radku
int line;
ASSERT_TRUE(compareFile(strcat(DEFAULT_PATH, "test1/test1_ref.out"), strcat(DEFAULT_PATH, "test1/test1.out"), &line)) //musim nejak pres makro, potrebuju vetsi string do DEFAULT_PATH
ENDTEST



int run_lex_analyzer_tests() {
    int errors = 0;
    printf("\nRunning Lex analyzer complex tests...\n");
    errors += T_test1_string();
    return errors;
}