#include "init_sample_database.h"

void finish_with_error(MYSQL* conn){
  fprintf(stderr, "%s\n", mysql_error(conn));
  mysql_close(conn);
  exit(1);
}

void create_database(MYSQL *conn, char *stmt_ddl){
    if (mysql_query(conn,stmt_ddl)){
        finish_with_error(conn);
    }
}

void create_table(MYSQL *conn, char *stmt_ddl){
    if (mysql_query(conn, stmt_ddl)) {
      finish_with_error(conn);
    }
}

bool is_already_in_table(MYSQL *conn, char *stmt_dml){
    bool result = false;

    if (mysql_query(conn, stmt_dml))
    {
        finish_with_error(conn);
    }
    MYSQL_RES *result_query = mysql_store_result(conn);

    if (result_query == NULL)
    {
        finish_with_error(conn);
    }

    int num_fields = mysql_num_fields(result_query);

    MYSQL_ROW row;

    if (row = mysql_fetch_row(result_query))
    {
        result = strcmp(row[0],"1") == 0;
    }

    mysql_free_result(result_query);

    return result;
}

void insert_into_table(MYSQL *conn, char *stmt_dml){
    if (mysql_query(conn, stmt_dml)) {
      finish_with_error(conn);
    }
}


int main(void)
{
    MYSQL *conn = mysql_init(NULL);
    if (conn == NULL)
    {
        fprintf(stderr, "mysql_init() failed (probably out of memory)\n");
        exit(EXIT_FAILURE);
    }

    if (mysql_real_connect(conn, "localhost" , "root", "password", NULL, 22, NULL, CLIENT_MULTI_STATEMENTS | CLIENT_MULTI_RESULTS) == NULL)
    {
        finish_with_error(conn);
    }

    create_database(conn, "CREATE DATABASE IF NOT EXISTS tripdb");
    create_table(conn, "CREATE TABLE IF NOT EXISTS `tripdb`.`dipendente` (  `IdDipendente` int unsigned NOT NULL AUTO_INCREMENT,  `TipologiaDipendente` varchar(45) NOT NULL,  `TelefonoAziendale` int NOT NULL,  `NomeDipendente` varchar(45) NOT NULL,  `CogrnomeDipendente` varchar(45) NOT NULL,  PRIMARY KEY (`IdDipendente`),  UNIQUE KEY `IdDipendente_UNIQUE` (`IdDipendente`)) ENGINE=InnoDB DEFAULT CHARSET=latin1;");
    
    bool isDipendente1InDB  = is_already_in_table(conn,"SELECT COUNT(1) FROM `tripdb`.`dipendente` WHERE `IdDipendente` = '1'");
    if (!isDipendente1InDB){
        insert_into_table(conn,"INSERT INTO `tripdb`.`dipendente` (`IdDipendente`, `TipologiaDipendente`, `TelefonoAziendale`, `NomeDipendente`, `CogrnomeDipendente`) VALUES ('1', 'meccanico', '1234', 'Mario', 'Rossi');");
    }

    bool isDipendente2InDB  = is_already_in_table(conn,"SELECT COUNT(1) FROM `tripdb`.`dipendente` WHERE `IdDipendente` = '2'");
    if (!isDipendente2InDB){
        insert_into_table(conn,"INSERT INTO `tripdb`.`dipendente` (`IdDipendente`, `TipologiaDipendente`, `TelefonoAziendale`, `NomeDipendente`, `CogrnomeDipendente`) VALUES ('2', 'hostess', '4453', 'Anna', 'Bianchi');");
    }

    bool isDipendente3InDB  = is_already_in_table(conn,"SELECT COUNT(1) FROM `tripdb`.`dipendente` WHERE `IdDipendente` = '3'");
    if (!isDipendente3InDB){
        insert_into_table(conn,"INSERT INTO `tripdb`.`dipendente` (`IdDipendente`, `TipologiaDipendente`, `TelefonoAziendale`, `NomeDipendente`, `CogrnomeDipendente`) VALUES ('3', 'meccanico', '7801', 'Paolo', 'Verdi');");
    }

    mysql_close(conn);
}

