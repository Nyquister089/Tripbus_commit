#include "test_upd.h"

int main(void){
    init_validation();

    struct test_suite_context *suite_ctx = init_test_suite();
    if (suite_ctx == NULL){
        return 1;
    }

    struct test_case_context *test_ctx = init_unit_test(suite_ctx, "update_tour()", NULL);
    if (test_ctx == NULL){
        return 1;
    }

    struct tour *fixture_tour = init_tour();
    if (fixture_tour == NULL){
        return 1;
    }

    update_tour(fixture_tour);
    analyze_unit_test_ignoring_result(suite_ctx);
    fini_test_case(test_ctx);

    analyze_test_suite(suite_ctx);
    fini_validation();

    return 0;
}

struct tour *init_tour(){
    struct tour *tour = (struct tour*) malloc(sizeof(struct tour));
    if (tour == NULL){
        fprintf(stderr,"Out of memory: init_tour\n");
    }
    return tour;
}