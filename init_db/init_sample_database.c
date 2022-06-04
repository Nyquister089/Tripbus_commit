#include "init_sample_database.h"

/**
 * Estrae lo statement SQL dal file di testo e lo concatena alla stringa statement_result
 */
void get_statement_from_sql_file(char *filename, char *statement_result)
{
    char *statement = malloc(4000);

    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        fprintf(stderr, "Errore\n");
    }

    char str[50];
    while (fgets(str, 50, file) != NULL)
    {
        strcat(statement_result, str);
    }
    fclose(file);
}

/**
 * Chiude con eleganza l'applicazione, terminando la connessione mysql e mostrando l'errore ottenuto.
 */
void finish_with_error(MYSQL *conn)
{
    fprintf(stderr, "[%u] %s\n", mysql_errno(conn), mysql_error(conn));
    mysql_close(conn);
    exit(1);
}

/**
 * Consente di eseguire lo statement DDL contenuto all'interno del file
 */
void execute_query_ddl_from_sql_file(MYSQL *conn, char *filename)
{
    char stmt[4000] = "";
    get_statement_from_sql_file(filename, stmt);

    if (mysql_query(conn, stmt))
    {
        fprintf(stderr, "failed to query file %s\n", filename);
        finish_with_error(conn);
    }
}

/**
 * Consente di eseguire lo statement DML contenuto all'interno del file.
 * I risultati sono ignorati.
 */
void execute_query_dml_from_sql_file(MYSQL *conn, char *filename)
{
    char stmt[4000] = "";
    get_statement_from_sql_file(filename, stmt);

    if (mysql_query(conn, stmt))
    {
        fprintf(stderr, "failed to query file %s\n", filename);
        finish_with_error(conn);
    }

    int status = 0;
    do
    {
        status = mysql_next_result(conn);

        if (status > 0)
        {
            finish_with_error(conn);
        }

    } while (status == 0);
}

int main(void)
{
    MYSQL *conn = mysql_init(NULL);
    if (conn == NULL)
    {
        fprintf(stderr, "fail mysql_init(): Out of memory\n");
        exit(EXIT_FAILURE);
    }

    if (mysql_real_connect(conn, "localhost", "root", "password", NULL, 22, NULL, CLIENT_MULTI_STATEMENTS | CLIENT_MULTI_RESULTS) == NULL)
    {
        finish_with_error(conn);
    }

    execute_query_ddl_from_sql_file(conn, "../sql/ddl/create_database.sql");
    printf("database: ok\n");

    execute_query_ddl_from_sql_file(conn, "../sql/ddl/create_table_servizio.sql");
    execute_query_ddl_from_sql_file(conn, "../sql/ddl/create_table_meta.sql");
    execute_query_ddl_from_sql_file(conn, "../sql/ddl/create_table_offre.sql");
    execute_query_ddl_from_sql_file(conn, "../sql/ddl/create_table_camera.sql");
    execute_query_ddl_from_sql_file(conn, "../sql/ddl/create_table_cliente.sql");
    execute_query_ddl_from_sql_file(conn, "../sql/ddl/create_table_prenotazione.sql");
    execute_query_ddl_from_sql_file(conn, "../sql/ddl/create_table_modello.sql");
    execute_query_ddl_from_sql_file(conn, "../sql/ddl/create_table_mezzo.sql");
    execute_query_ddl_from_sql_file(conn, "../sql/ddl/create_table_tour.sql");
    execute_query_ddl_from_sql_file(conn, "../sql/ddl/create_table_dipendenti.sql");
    execute_query_ddl_from_sql_file(conn, "../sql/ddl/create_table_viaggi.sql");
    execute_query_ddl_from_sql_file(conn, "../sql/ddl/create_table_postoprenotato.sql");
    execute_query_ddl_from_sql_file(conn, "../sql/ddl/create_table_associata.sql");
    execute_query_ddl_from_sql_file(conn, "../sql/ddl/create_table_comfort.sql");
    execute_query_ddl_from_sql_file(conn, "../sql/ddl/create_table_presenti.sql");
    execute_query_ddl_from_sql_file(conn, "../sql/ddl/create_table_revisione.sql");
    execute_query_ddl_from_sql_file(conn, "../sql/ddl/create_table_ricambio.sql");
    execute_query_ddl_from_sql_file(conn, "../sql/ddl/create_table_documentazionefotografica.sql");
    execute_query_ddl_from_sql_file(conn, "../sql/ddl/create_table_tagliando.sql");
    execute_query_ddl_from_sql_file(conn, "../sql/ddl/create_table_rt.sql");
    execute_query_ddl_from_sql_file(conn, "../sql/ddl/create_table_fme.sql");
    execute_query_ddl_from_sql_file(conn, "../sql/ddl/create_table_fmo.sql");
    execute_query_ddl_from_sql_file(conn, "../sql/ddl/create_table_localita.sql");
    execute_query_ddl_from_sql_file(conn, "../sql/ddl/create_table_tome.sql");
    execute_query_ddl_from_sql_file(conn, "../sql/ddl/create_table_mappa.sql");
    execute_query_ddl_from_sql_file(conn, "../sql/ddl/create_table_visita.sql");
    printf("tables: ok\n");

    execute_query_dml_from_sql_file(conn, "../sql/dml/delete_and_insert_servizio.sql");
    execute_query_dml_from_sql_file(conn, "../sql/dml/delete_and_insert_localita.sql");
    execute_query_dml_from_sql_file(conn, "../sql/dml/delete_and_insert_dipendenti.sql");
    execute_query_dml_from_sql_file(conn, "../sql/dml/delete_and_insert_modello.sql");
    execute_query_dml_from_sql_file(conn, "../sql/dml/delete_and_insert_comfort.sql");
    execute_query_dml_from_sql_file(conn, "../sql/dml/delete_and_insert_meta.sql");
    printf("deletes and inserts: ok\n");

    mysql_close(conn);
}
