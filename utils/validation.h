#pragma once

#include <stdbool.h>
#include <regex.h>

int setting_regex(regex_t *regex , char *pattern_to_match, char *regex_name);
extern bool init_validation(void);
bool validate(char *str, regex_t *regex);
extern bool validate_time(char *str);
extern bool validate_date(char *str);
extern bool validate_integer(char *str);
extern bool validate_double(char *str);
extern void fini_validation(void);
