#include "../symtable.h"
#include "test_utils.h"



#define HTAB_INIT       \
    Htab_t *test_table; \
    size_t size = 10;   \
    test_table = htab_init(size);

#define HTAB_FREE \
    htab_free(test_table);

#define HTAB_TOKEN_INIT                            \
    Token_t *test_token = malloc(sizeof(Token_t)); \
    test_token->type = T_ID;                            \
    test_token->attribute.string = "test";

#define HTAB_TOKEN_FREE \
    free(test_token);

#define HTAB_INSERT \
    htab_insert_item(test_table, test_token);



TEST(T_htab_init_1, "test htab_init")
Htab_t *test_table;
size_t size = 69;
ASSERT_TRUE((test_table = htab_init(size)) != NULL)
HTAB_FREE
ENDTEST

TEST(T_htab_init_2, "test htab_init")
Htab_t *test_table;
size_t size = 0;
ASSERT_TRUE((test_table = htab_init(size)) == NULL)
ENDTEST



TEST(T_htab_hash_function_1, "test htab_hash_function")
ASSERT_TRUE(htab_hash_function(NULL) == -1)
ENDTEST

TEST(T_htab_hash_function_2, "test htab_hash_function")
ASSERT_TRUE(htab_hash_function("test") > 0)
ENDTEST



TEST(T_htab_insert_item_1, "test htab_insert_item")
HTAB_TOKEN_INIT
ASSERT_TRUE(htab_insert_item(NULL, test_token) == INTERNAL_ERR)
HTAB_TOKEN_FREE
ENDTEST

TEST(T_htab_insert_item_2, "test htab_insert_item")
HTAB_INIT
ASSERT_TRUE(htab_insert_item(test_table, NULL) == INTERNAL_ERR)
HTAB_FREE
ENDTEST

TEST(T_htab_insert_item_3, "test htab_insert_item")
HTAB_INIT
HTAB_TOKEN_INIT
ASSERT_TRUE(htab_insert_item(test_table,test_token) == OK)
HTAB_TOKEN_FREE
HTAB_FREE
ENDTEST



TEST(T_htab_find_1, "test htab_find")
ASSERT_TRUE(htab_find(NULL, "test") == NULL)
ENDTEST

TEST(T_htab_find_2, "test htab_find")
HTAB_INIT
ASSERT_TRUE(htab_find(test_table, NULL) == NULL)
HTAB_FREE
ENDTEST

TEST(T_htab_find_3, "test htab_find")
HTAB_INIT
ASSERT_TRUE(htab_find(test_table, "test") == NULL)
HTAB_FREE
ENDTEST

TEST(T_htab_find_4, "test htab_find")
HTAB_INIT
HTAB_TOKEN_INIT
HTAB_INSERT
ASSERT_TRUE(htab_find(test_table, "test") != NULL)
HTAB_TOKEN_FREE
HTAB_FREE
ENDTEST

TEST(T_htab_find_5, "test htab_find")
HTAB_INIT
HTAB_TOKEN_INIT
HTAB_INSERT
ASSERT_TRUE(htab_find(test_table, "wrong") == NULL)
HTAB_TOKEN_FREE
HTAB_FREE
ENDTEST



TEST(T_htab_lookup_add_1, "test htab_lookup_add")
HTAB_TOKEN_INIT
ASSERT_TRUE(htab_lookup_add(NULL, test_token) == NULL)
HTAB_TOKEN_FREE
ENDTEST

TEST(T_htab_lookup_add_2, "test htab_lookup_add")
HTAB_INIT
ASSERT_TRUE(htab_lookup_add(test_table, NULL) == NULL)
HTAB_FREE
ENDTEST

TEST(T_htab_lookup_add_3, "test htab_lookup_add")
HTAB_INIT
HTAB_TOKEN_INIT
ASSERT_TRUE(htab_lookup_add(test_table, test_token) != NULL)
HTAB_TOKEN_FREE
HTAB_FREE
ENDTEST

TEST(T_htab_lookup_add_4, "test htab_lookup_add")
HTAB_INIT
HTAB_TOKEN_INIT
HTAB_INSERT
ASSERT_TRUE(htab_lookup_add(test_table, test_token) != NULL)
HTAB_TOKEN_FREE
HTAB_FREE
ENDTEST



TEST(T_htab_erase_1, "test htab_erase")
ASSERT_TRUE(htab_erase(NULL, "test") == INTERNAL_ERR)
ENDTEST

TEST(T_htab_erase_2, "test htab_erase")
HTAB_INIT
ASSERT_TRUE(htab_erase(test_table, NULL) == INTERNAL_ERR)
HTAB_FREE
ENDTEST

TEST(T_htab_erase_3, "test htab_erase")
HTAB_INIT
ASSERT_TRUE(htab_erase(test_table, "test") == INTERNAL_ERR)
HTAB_FREE
ENDTEST

TEST(T_htab_erase_4, "test htab_erase")
HTAB_INIT
HTAB_TOKEN_INIT
HTAB_INSERT
ASSERT_TRUE(htab_erase(test_table, "test") == OK)
HTAB_TOKEN_FREE
HTAB_FREE
ENDTEST



TEST(T_htab_clear_1, "test htab_clear")
ASSERT_TRUE(htab_clear(NULL) == INTERNAL_ERR)
ENDTEST

TEST(T_htab_clear_2, "test htab_clear")
HTAB_INIT
ASSERT_TRUE(htab_clear(test_table) == OK)
HTAB_FREE
ENDTEST

TEST(T_htab_clear_3, "test htab_clear")
HTAB_INIT
HTAB_TOKEN_INIT
HTAB_INSERT
ASSERT_TRUE(htab_clear(test_table) == OK)
HTAB_TOKEN_FREE
HTAB_FREE
ENDTEST



TEST(T_htab_free_1, "test htab_free")
ASSERT_TRUE(htab_free(NULL) == INTERNAL_ERR)
ENDTEST

TEST(T_htab_free_2, "test htab_free")
HTAB_INIT
ASSERT_TRUE(htab_free(test_table) == OK)
ENDTEST

TEST(T_htab_free_3, "test htab_free")
HTAB_INIT
HTAB_TOKEN_INIT
HTAB_INSERT
ASSERT_TRUE(htab_free(test_table) == OK)
HTAB_TOKEN_FREE
ENDTEST



int run_symtable_tests() {
    int errors = 0;
    printf("Running symtable tests...\n");
    errors += T_htab_init_1();
    errors += T_htab_init_2();
    errors += T_htab_hash_function_1();
    errors += T_htab_hash_function_2();
    errors += T_htab_insert_item_1();
    errors += T_htab_insert_item_2();
    errors += T_htab_insert_item_3();
    errors += T_htab_find_1();
    errors += T_htab_find_2();
    errors += T_htab_find_3();
    errors += T_htab_find_4();
    errors += T_htab_find_5();
    errors += T_htab_lookup_add_1();
    errors += T_htab_lookup_add_2();
    errors += T_htab_lookup_add_3();
    errors += T_htab_lookup_add_4();
    errors += T_htab_erase_1();
    errors += T_htab_erase_2();
    errors += T_htab_erase_3();
    errors += T_htab_erase_4();
    errors += T_htab_clear_1();
    errors += T_htab_clear_2();
    errors += T_htab_clear_3();
    errors += T_htab_free_1();
    errors += T_htab_free_2();
    errors += T_htab_free_3();
    return errors;
}
