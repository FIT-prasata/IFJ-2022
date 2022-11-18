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



TEST(T_htab_init_normal, "Init with normal size")
Htab_t *test_table;
size_t size = 69;
ASSERT_TRUE((test_table = htab_init(size)) != NULL)
HTAB_FREE
ENDTEST

TEST(T_htab_init_zero, "Init with zero size")
Htab_t *test_table;
size_t size = 0;
ASSERT_TRUE((test_table = htab_init(size)) == NULL)
ENDTEST



TEST(T_htab_hash_function_no_key, "Creating hash with no key")
ASSERT_TRUE(htab_hash_function(NULL) == -1)
ENDTEST

TEST(T_htab_hash_function_normal, "Creating hash with normal key")
ASSERT_TRUE(htab_hash_function("test") > 0)
ENDTEST



TEST(T_htab_insert_item_no_table, "Inserting item with no table")
HTAB_TOKEN_INIT
ASSERT_TRUE(htab_insert_item(NULL, test_token) == INTERNAL_ERR)
HTAB_TOKEN_FREE
ENDTEST

TEST(T_htab_insert_item_no_token, "Inserting item with no token")
HTAB_INIT
ASSERT_TRUE(htab_insert_item(test_table, NULL) == INTERNAL_ERR)
HTAB_FREE
ENDTEST

TEST(T_htab_insert_item_normal, "Inserting item with normal token")
HTAB_INIT
HTAB_TOKEN_INIT
ASSERT_TRUE(htab_insert_item(test_table,test_token) == OK)
HTAB_TOKEN_FREE
HTAB_FREE
ENDTEST



TEST(T_htab_find_no_table, "Finding item with no table")
ASSERT_TRUE(htab_find(NULL, "test") == NULL)
ENDTEST

TEST(T_htab_find_no_key, "Finding item with no key")
HTAB_INIT
ASSERT_TRUE(htab_find(test_table, NULL) == NULL)
HTAB_FREE
ENDTEST

TEST(T_htab_find_empty, "Finding item in empty table")
HTAB_INIT
ASSERT_TRUE(htab_find(test_table, "test") == NULL)
HTAB_FREE
ENDTEST

TEST(T_htab_find_normal, "Finding item in table")
HTAB_INIT
HTAB_TOKEN_INIT
HTAB_INSERT
ASSERT_TRUE(htab_find(test_table, "test") != NULL)
HTAB_TOKEN_FREE
HTAB_FREE
ENDTEST

TEST(T_htab_find_missing, "Finding missing item in table")
HTAB_INIT
HTAB_TOKEN_INIT
HTAB_INSERT
ASSERT_TRUE(htab_find(test_table, "wrong") == NULL)
HTAB_TOKEN_FREE
HTAB_FREE
ENDTEST



TEST(T_htab_lookup_add_no_table, "Lookup add with no table")
HTAB_TOKEN_INIT
ASSERT_TRUE(htab_lookup_add(NULL, test_token) == NULL)
HTAB_TOKEN_FREE
ENDTEST

TEST(T_htab_lookup_add_no_token, "Lookup add with no token")
HTAB_INIT
ASSERT_TRUE(htab_lookup_add(test_table, NULL) == NULL)
HTAB_FREE
ENDTEST

TEST(T_htab_lookup_add_insert, "Lookup add with insert")
HTAB_INIT
HTAB_TOKEN_INIT
ASSERT_TRUE(htab_lookup_add(test_table, test_token) != NULL)
HTAB_TOKEN_FREE
HTAB_FREE
ENDTEST

TEST(T_htab_lookup_add_find, "Lookup add with find")
HTAB_INIT
HTAB_TOKEN_INIT
HTAB_INSERT
ASSERT_TRUE(htab_lookup_add(test_table, test_token) != NULL)
HTAB_TOKEN_FREE
HTAB_FREE
ENDTEST



TEST(T_htab_erase_no_table, "Erasing item with no table")
ASSERT_TRUE(htab_erase(NULL, "test") == INTERNAL_ERR)
ENDTEST

TEST(T_htab_erase_no_key, "Erasing item with no key")
HTAB_INIT
ASSERT_TRUE(htab_erase(test_table, NULL) == INTERNAL_ERR)
HTAB_FREE
ENDTEST

TEST(T_htab_erase_missing, "Erasing missing item")
HTAB_INIT
ASSERT_TRUE(htab_erase(test_table, "test") == INTERNAL_ERR)
HTAB_FREE
ENDTEST

TEST(T_htab_erase_normal, "Erasing item")
HTAB_INIT
HTAB_TOKEN_INIT
HTAB_INSERT
ASSERT_TRUE(htab_erase(test_table, "test") == OK)
HTAB_TOKEN_FREE
HTAB_FREE
ENDTEST



TEST(T_htab_clear_no_table, "Clearing table with no table")
ASSERT_TRUE(htab_clear(NULL) == INTERNAL_ERR)
ENDTEST

TEST(T_htab_clear_empty, "Clearing empty table")
HTAB_INIT
ASSERT_TRUE(htab_clear(test_table) == OK)
HTAB_FREE
ENDTEST

TEST(T_htab_clear_normal, "Clearing table")
HTAB_INIT
HTAB_TOKEN_INIT
HTAB_INSERT
ASSERT_TRUE(htab_clear(test_table) == OK)
HTAB_TOKEN_FREE
HTAB_FREE
ENDTEST



TEST(T_htab_free_no_table, "Freeing table with no table")
ASSERT_TRUE(htab_free(NULL) == INTERNAL_ERR)
ENDTEST

TEST(T_htab_free_empty, "Freeing empty table")
HTAB_INIT
ASSERT_TRUE(htab_free(test_table) == OK)
ENDTEST

TEST(T_htab_free_normal, "Freeing table")
HTAB_INIT
HTAB_TOKEN_INIT
HTAB_INSERT
ASSERT_TRUE(htab_free(test_table) == OK)
HTAB_TOKEN_FREE
ENDTEST



int run_symtable_tests() {
    int errors = 0;
    printf("Running symtable tests...\n");
    errors += T_htab_init_normal();
    errors += T_htab_init_zero();
    errors += T_htab_hash_function_no_key();
    errors += T_htab_hash_function_normal();
    errors += T_htab_insert_item_no_table();
    errors += T_htab_insert_item_no_token();
    errors += T_htab_insert_item_normal();
    errors += T_htab_find_no_table();
    errors += T_htab_find_no_key();
    errors += T_htab_find_empty();
    errors += T_htab_find_normal();
    errors += T_htab_find_missing();
    errors += T_htab_lookup_add_no_table();
    errors += T_htab_lookup_add_no_token();
    errors += T_htab_lookup_add_insert();
    errors += T_htab_lookup_add_find();
    errors += T_htab_erase_no_table();
    errors += T_htab_erase_no_key();
    errors += T_htab_erase_missing();
    errors += T_htab_erase_normal();
    errors += T_htab_clear_no_table();
    errors += T_htab_clear_empty();
    errors += T_htab_clear_normal();
    errors += T_htab_free_no_table();
    errors += T_htab_free_empty();
    errors += T_htab_free_normal();
    return errors;
}
