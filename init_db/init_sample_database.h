#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>
#include <string.h>


void finish_with_error(MYSQL* conn);
void create_database(MYSQL *conn, char *stmt_ddl);
void create_table(MYSQL *conn, char *stmt_ddl);
bool is_already_in_table(MYSQL *conn, char *stmt_dml);