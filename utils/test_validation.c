#include "test_validation.h"

int main(void){
    bool res;
    bool exp_res;
    struct test_case_context *test_ctx;
    struct test_suite_context *suite_ctx = init_test_suite();

    test_ctx = init_unit_test(suite_ctx,"init_validation()",NULL);
    init_validation();
    analyze_unit_test_ignoring_result(suite_ctx);
    fini_test_case(test_ctx);

    exp_res = true;
    test_ctx = init_unit_test(suite_ctx,"true for validate_date(2022-01-01)", (void *) &exp_res);
    res = validate_date("2022-01-01");
    analyze_unit_test_bool_result(suite_ctx,test_ctx, res);
    fini_test_case(test_ctx);

    exp_res = false;
    test_ctx = init_unit_test(suite_ctx,"false for validate_date(2022-02-32)", (void *)&exp_res);
    res = validate_date("2022-02-32");
    analyze_unit_test_bool_result(suite_ctx,test_ctx, res);
    fini_test_case(test_ctx);

    exp_res = true;
    test_ctx = init_unit_test(suite_ctx,"true for validate_time(00:00)",(void *)&exp_res);
    res = validate_time("00:00");
    analyze_unit_test_bool_result(suite_ctx,test_ctx, res);
    fini_test_case(test_ctx);

    exp_res = false;
    test_ctx = init_unit_test(suite_ctx,"false for validate_time(99:99)",(void *)&exp_res);
    res = validate_time("99:99");
    analyze_unit_test_bool_result(suite_ctx,test_ctx, res);
    fini_test_case(test_ctx);

    exp_res = true;
    test_ctx = init_unit_test(suite_ctx,"true for validate_time(19:30)",(void *)&exp_res);
    res = validate_time("19:30");
    analyze_unit_test_bool_result(suite_ctx,test_ctx, res);
    fini_test_case(test_ctx);

    exp_res = true;
    test_ctx = init_unit_test(suite_ctx,"true for validate_integer(0)",(void *)&exp_res);;
    res = validate_integer("0");
    analyze_unit_test_bool_result(suite_ctx,test_ctx, res);
    fini_test_case(test_ctx);

    exp_res = false;
    test_ctx = init_unit_test(suite_ctx,"false for validate_integer(aex)",(void *)&exp_res);
    res = validate_integer("aex");
    analyze_unit_test_bool_result(suite_ctx,test_ctx, res);
    fini_test_case(test_ctx);

    exp_res = true;
    test_ctx = init_unit_test(suite_ctx,"true for validate_integer(1234)",(void *)&exp_res);;
    res = validate_integer("1234");
    analyze_unit_test_bool_result(suite_ctx,test_ctx, res);
    fini_test_case(test_ctx);

    exp_res = true;
    test_ctx = init_unit_test(suite_ctx,"true for validate_double(0.0)",(void *)&exp_res);;
    res = validate_integer("0.0");
    analyze_unit_test_bool_result(suite_ctx,test_ctx, res);
    fini_test_case(test_ctx);

    exp_res = true;
    test_ctx = init_unit_test(suite_ctx,"true for validate_double(120.10)",(void *)&exp_res);;
    res = validate_integer("120.10");
    analyze_unit_test_bool_result(suite_ctx,test_ctx,res);
    fini_test_case(test_ctx);

    test_ctx = init_unit_test(suite_ctx,"fini_validation()",NULL);
    analyze_unit_test_ignoring_result(suite_ctx);

    analyze_test_suite(suite_ctx);

    fini_validation();
    return 0;
}