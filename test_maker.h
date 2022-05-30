#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

/**
 * Struttura dati utile per contenere le informazioni della test suite inizializzata/in corso/terminata.
 * Una test suite è una collezione di test case.
 */
struct test_suite_context{
    int total_tests; //Totale di test case nella test suite
    int ok_tests; //Totale di test eseguiti con successo e con il risultato desiderato
    int fail_tests; //Totale di test eseguiti con successo ma con un risultato diverso da quello desiderato
};

struct test_suite_context *init_test_suite(void);
void analyze_test_suite(struct test_suite_context *ctx);
void fini_test_suite(struct test_suite_context *ctx);

/**
 * Struttura dati utile per contenere le informazioni di un test case inizializzato/in corso/terminata.
 * Un test case è un test su una specifica funzione dell'applicazione.
 */
struct test_case_context {
    char *name; //Nome del test case. Utile per identificare quale tipo di test è stato eseguito
    char error_message[100]; //Eventuale errore di messaggio salvato durante l'esecuzione del test
    void *expected_result; //Risultato desiderato dall'esecuzione del test
};

struct test_case_context *init_unit_test(struct test_suite_context *suite_ctx, char *test_name, void *expected_result);
void increment_ok_tests(int *ok_tests);
void increment_fail_tests(int *fail_tests);
void analyze_unit_test_bool_result(struct test_suite_context *suite_ctx, struct test_case_context *test_ctx, bool test_result);
void analyze_unit_test_string_result(struct test_suite_context *suite_ctx, struct test_case_context *test_ctx, char* test_result);
void analyze_unit_test_ignoring_result(struct test_suite_context *suite_ctx);
void fini_test_case(struct test_case_context *ctx);