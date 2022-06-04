#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>
#include <string.h>


void get_statement_from_sql_file(char *filename, char *statement_result);
void finish_with_error(MYSQL* conn);
void execute_query_ddl_from_sql_file(MYSQL *conn, char *filename);
void execute_query_dml_from_sql_file(MYSQL *conn, char *filename);