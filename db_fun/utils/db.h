#pragma once

#include <stdbool.h>
#include <mysql/mysql.h>

extern void print_stmt_error (MYSQL_STMT *stmt, char *message);
extern void print_error(MYSQL *conn, char *message);
extern bool setup_prepared_stmt(MYSQL_STMT **stmt, char *statement, MYSQL *conn);
extern void finish_with_error(MYSQL *conn, char *message);
extern void finish_with_stmt_error(MYSQL *conn, MYSQL_STMT *stmt, char *message, bool close_stmt);
extern void set_binding_param(MYSQL_BIND *param, enum enum_field_types type, void *buffer, unsigned long len);
extern void date_to_mysql_time(char *str, MYSQL_TIME *time);
extern void time_to_mysql_time(char *str, MYSQL_TIME *time);
extern void init_mysql_timestamp(MYSQL_TIME *time);
extern void mysql_timestamp_to_string(MYSQL_TIME *time, char *str);
extern void mysql_date_to_string(MYSQL_TIME *date, char *str);
extern void mysql_time_to_string(MYSQL_TIME *time, char *str);

extern int exe_proc(MYSQL_STMT *procedure,  char * buff); 
extern int take_result(MYSQL_STMT *procedure, MYSQL_BIND *param, char *buff); 
extern size_t bind_exe(MYSQL_STMT *procedure, MYSQL_BIND *param, char * buff);
extern void init_mysql_date(MYSQL_TIME *time); 
extern size_t take_rows(MYSQL_STMT *procedure, char *buff); 
