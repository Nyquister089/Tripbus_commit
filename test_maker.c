#include "test_maker.h"

/**
* Consente di inizializzare le variabili utili per l'esecuzione della suite di test.
*/
struct test_suite_context *init_test_suite(void){
    struct test_suite_context *ctx = (struct test_suite_context *) malloc (sizeof(struct test_suite_context));
    if (ctx == NULL){
        fprintf(stderr,"Out of memory: start_test_suite()\n");
        return NULL;
    }

    ctx->total_tests = 0;
    ctx->ok_tests = 0;
    ctx->fail_tests = 0;
    printf("Test suite ready to start\n\n");
    return ctx;
}

/**
* Consente di stampare un resoconto della test di suite appena eseguita (numero test eseguiti,
* test eseguiti con successo, ecc.)
*/
void analyze_test_suite(struct test_suite_context *ctx){
    printf("Test suite finished\n\n");

    double percentage_ok_tests;
    if (ctx->ok_tests != 0){
        percentage_ok_tests = (ctx->ok_tests/(float)ctx->total_tests)*100;
    }
    double percentage_fail_tests = (ctx->fail_tests/(float)ctx->total_tests)*100;
    double percentage_miss_tests = 100-(percentage_ok_tests+percentage_fail_tests);
    printf("Total tests: %d\n",ctx->total_tests);
    printf("Test    OK : %d (%.2f %%)\n",ctx->ok_tests,percentage_ok_tests);
    printf("Test   FAIL: %d (%.2f %%)\n",ctx->fail_tests,percentage_fail_tests);
    printf("Test   MISS: %d (%.2f %%)\n",ctx->total_tests-(ctx->ok_tests+ctx->fail_tests),percentage_miss_tests);

    free(ctx);
}

/**
 * Dealloca la memoria di test_suite_context
 */
void fini_test_suite(struct test_suite_context *ctx){
    free(ctx);
    printf("Deallocating test suite context done\n");
}

/**
* Consente di inizializzare le variabili utili per l'esecuzione di uno unit test.
*/
struct test_case_context *init_unit_test(struct test_suite_context *suite_ctx, char *test_name, void *expected_result){
    struct test_case_context *test_ctx = (struct test_case_context *) malloc(sizeof(struct test_case_context));
    if (test_ctx == NULL){
        fprintf(stderr,"Out of memory: start_unit_test()\n");
        return NULL;
    }

    test_ctx->name = test_name;
    test_ctx->expected_result = expected_result;

    printf("Test '%s' ready to start\n",test_ctx->name);
    suite_ctx->total_tests ++;

    return test_ctx;
}

/**
* Consente di verificare che il test appena eseguito restituisca un valore
* atteso booleano. In caso di errore mostra il risultato atteso.
*/
void analyze_unit_test_bool_result(struct test_suite_context *suite_ctx, struct test_case_context * test_ctx, bool test_result){
    bool *expected_result = test_ctx->expected_result;
    if (*expected_result != test_result) {
        sprintf(test_ctx->error_message,"FAIL: Expected '%d' instead '%d' \n",*expected_result, test_result);
        increment_fail_tests(&(suite_ctx->fail_tests));
        return;
    }
    increment_ok_tests(&(suite_ctx->ok_tests));
}

/**
* Consente di verificare che il test appena eseguito restituisca un valore
* atteso stringa. In caso di errore mostra il risultato atteso.
*/
void analyze_unit_test_string_result(struct test_suite_context *suite_ctx, struct test_case_context * test_ctx, char* test_result){
    char * expected_result = (char *) (test_ctx->expected_result);
    if (test_result == NULL){
        strcpy(test_ctx->error_message,"FAIL: Test result is not setted");
        increment_fail_tests(&(suite_ctx->fail_tests));
        return;
    }

    if (expected_result == NULL){
        strcpy(test_ctx->error_message,"FAIL: Expected result is not setted");
        increment_fail_tests(&(suite_ctx->fail_tests));
        return;
    }

    if (strcmp(test_result,expected_result)!=0) {
        sprintf(test_ctx->error_message,"FAIL: Expected '%s' instead '%s' \n",expected_result, test_result);
        increment_fail_tests(&(suite_ctx->fail_tests));
        return;
    }
        
    increment_ok_tests(&(suite_ctx->ok_tests));
}

/**
* Consente di salvare le informazioni di un test appena eseguito, ignorando il risultato ottenuto. 
*/
void analyze_unit_test_ignoring_result(struct test_suite_context *suite_ctx){
    increment_ok_tests(&(suite_ctx->ok_tests));
}

/**
 * Consente di incrementare il contatore dei test eseguiti con risultato atteso
 */
void increment_ok_tests(int *ok_tests){
    (*ok_tests) ++;
}

/**
 * Consente di incrementare il contatore dei test eseguiti con risultato diverso da quello atteso
 */
void increment_fail_tests(int *fail_tests){
    (*fail_tests) ++;
} 

/**
 * Dealloca la memoria di test_case_context
 */
void fini_test_case(struct test_case_context *ctx){
    
    free(ctx);
    printf("Deallocating test case context done\n");
}