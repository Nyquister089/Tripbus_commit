#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>
#include <string.h>

#define MAX_STATEMENT_LENGTH 4000

MYSQL *connection_init_db;
FILE *log_file;

MYSQL* start_connection_mysql();
void close_connection_mysql();
void finish_init_db_with_error();
int get_statement_from_sql_file(char *filename, char *statement_result);
int execute_query_from_file_sql(char *filename);
void create_database();
void drop_tables();
void create_tables();
void drop_views();
void create_views();
void populate_tables();
void show_mysql_error();
void finish_init_db_with_error();
void create_file_log(int argc, char *argv[]);
void close_file_log();
void set_argument_as_log_file(char *log_filename);
void set_stderr_as_log_file();