#include "init_sample_database.h"

/**
 * Estrae lo statement SQL dal file di testo e lo concatena alla stringa statement_result
 */
int get_statement_from_sql_file(char *filename, char *statement_result)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        fprintf(stderr, "Error: Trying to open file %s but it fails\n", filename);
        return -1;
    }

    const int COUNTER_CHARACTER_TO_READ = 50;
    int counter_character = 0;
    char str[COUNTER_CHARACTER_TO_READ];
    while (fgets(str, COUNTER_CHARACTER_TO_READ, file) != NULL)
    {
        strcat(statement_result, str);
        counter_character += strlen(str) - 1;

        if (counter_character + COUNTER_CHARACTER_TO_READ > MAX_STATEMENT_LENGTH)
        {
            fprintf(stderr, "Error: The file %s contains more than %d characters. Reduce the length of the statement.", filename, MAX_STATEMENT_LENGTH);
            fclose(file);
            return -2;
        }
    }
    fclose(file);

    return 0;
}

void show_mysql_error()
{
    fprintf(stderr, "[%u] %s\n", mysql_errno(connection_init_db), mysql_error(connection_init_db));
}

void finish_init_db_with_error()
{
    show_mysql_error();
    mysql_close(connection_init_db);
    exit(1);
}

/**
 * Consente di eseguire lo statement contenuto all'interno del file
 */
int execute_query_from_file_sql(char *filename)
{
    char stmt[MAX_STATEMENT_LENGTH] = "";
    if (get_statement_from_sql_file(filename, stmt) != 0)
    {
        fprintf(stderr, "Error: Failed to read statement SQL from file %s\n", filename);
        return -1;
    }    

    if (mysql_query(connection_init_db,stmt))
    {
        fprintf(stderr, "Error: Failed to query file %s\n", filename);
        show_mysql_error();
        return -2;
    }

    int status = 0;
    do
    {
        status = mysql_next_result(connection_init_db);

        if (status > 0)
        {
            show_mysql_error();
            return -3;
        }

    } while (status == 0);

    fprintf(stdout,"Query in file %s executed successfully\n", filename);
}

MYSQL *start_connection_mysql()
{
    connection_init_db = mysql_init(NULL);
    if (connection_init_db == NULL)
    {
        fprintf(stderr, "Error: Fail to execute mysql_init(): Out of memory\n");
        exit(EXIT_FAILURE);
    }

    if (mysql_real_connect(connection_init_db, "localhost", "giordano", "root1989", NULL, 22, NULL, CLIENT_MULTI_STATEMENTS | CLIENT_MULTI_RESULTS) == NULL)
    {
        finish_init_db_with_error();
    }
}


void close_connection_mysql()
{
    mysql_close(connection_init_db);
}

void create_database()
{
    execute_query_from_file_sql("../sql/ddl/database/tripdb.sql");
    execute_query_from_file_sql("../sql/ddl/database/user.sql");
}

void drop_tables()
{
    execute_query_from_file_sql("../sql/ddl/table/drop_all.sql");
}

void create_tables()
{   //execute_query_from_file_sql("../sql/ddl/table/create_all.sql");
    execute_query_from_file_sql("../sql/ddl/table/localita.sql");
    execute_query_from_file_sql("../sql/ddl/table/meta.sql");
    execute_query_from_file_sql("../sql/ddl/table/servizio.sql");
    execute_query_from_file_sql("../sql/ddl/table/offre.sql");
    execute_query_from_file_sql("../sql/ddl/table/camera.sql");
    execute_query_from_file_sql("../sql/ddl/table/cliente.sql");
    execute_query_from_file_sql("../sql/ddl/table/prenotazione.sql");
    execute_query_from_file_sql("../sql/ddl/table/modello.sql");
    execute_query_from_file_sql("../sql/ddl/table/mezzo.sql");
    execute_query_from_file_sql("../sql/ddl/table/tour.sql");
    execute_query_from_file_sql("../sql/ddl/table/dipendenti.sql");
    execute_query_from_file_sql("../sql/ddl/table/viaggio.sql");
    execute_query_from_file_sql("../sql/ddl/table/postoprenotato.sql");
    execute_query_from_file_sql("../sql/ddl/table/associata.sql");
    execute_query_from_file_sql("../sql/ddl/table/comfort.sql");
    execute_query_from_file_sql("../sql/ddl/table/presenti.sql");
    execute_query_from_file_sql("../sql/ddl/table/revisione.sql");
    execute_query_from_file_sql("../sql/ddl/table/ricambio.sql");
    execute_query_from_file_sql("../sql/ddl/table/documentazionefotografica.sql");
    execute_query_from_file_sql("../sql/ddl/table/tagliando.sql");
    execute_query_from_file_sql("../sql/ddl/table/rt.sql");
    execute_query_from_file_sql("../sql/ddl/table/fme.sql");
    execute_query_from_file_sql("../sql/ddl/table/fmo.sql");
    execute_query_from_file_sql("../sql/ddl/table/tome.sql");
    execute_query_from_file_sql("../sql/ddl/table/mappa.sql");
    execute_query_from_file_sql("../sql/ddl/table/visita.sql");
    execute_query_from_file_sql("../sql/ddl/table/utente.sql");
    execute_query_from_file_sql("../sql/ddl/table/sostituito.sql");
    execute_query_from_file_sql("../sql/ddl/table/competenze.sql"); 
    
}

void drop_views()
{
    execute_query_from_file_sql("../sql/ddl/view/drop_all_views.sql");
}

void create_views()
{
    execute_query_from_file_sql("../sql/ddl/view/Autista_mete_visistate.sql");
    execute_query_from_file_sql("../sql/ddl/view/Cliente_mete_tour.sql");
    execute_query_from_file_sql("../sql/ddl/view/Cliente_modello_info.sql");
    execute_query_from_file_sql("../sql/ddl/view/Meccanico_pianifica_revisione.sql");
    execute_query_from_file_sql("../sql/ddl/view/Hostess_clienti_prenotazioni.sql");
    execute_query_from_file_sql("../sql/ddl/view/Mezzi_Con_Revisione_Scaduta.sql");
}

void populate_tables()
{
    execute_query_from_file_sql("../sql/dml/delete_and_insert_tour.sql"); 
    execute_query_from_file_sql("../sql/dml/delete_and_insert_servizio.sql");
    execute_query_from_file_sql("../sql/dml/delete_and_insert_localita.sql");
    execute_query_from_file_sql("../sql/dml/delete_and_insert_dipendenti.sql");
    execute_query_from_file_sql("../sql/dml/delete_and_insert_modello.sql");
    execute_query_from_file_sql("../sql/dml/delete_and_insert_mezzo.sql"); 
    execute_query_from_file_sql("../sql/dml/delete_and_insert_comfort.sql");
    execute_query_from_file_sql("../sql/dml/delete_and_insert_meta.sql");
    execute_query_from_file_sql("../sql/dml/delete_and_insert_utente.sql");
    execute_query_from_file_sql("../sql/dml/delete_and_insert_viaggio.sql");
    execute_query_from_file_sql("../sql/dml/delete_and_insert_cliente.sql");
    execute_query_from_file_sql("../sql/dml/delete_and_insert_camera.sql");
    execute_query_from_file_sql("../sql/dml/delete_and_insert_prenotazione.sql"); 
    execute_query_from_file_sql("../sql/dml/delete_and_insert_tome.sql"); 
    execute_query_from_file_sql("../sql/dml/delete_and_insert_visite.sql"); 
    execute_query_from_file_sql("../sql/dml/delete_and_insert_offre.sql"); 
    execute_query_from_file_sql("../sql/dml/delete_and_insert_presenti.sql");
    execute_query_from_file_sql("../sql/dml/delete_and_insert_foto.sql");
    execute_query_from_file_sql("../sql/dml/delete_and_insert_fmo.sql");
    execute_query_from_file_sql("../sql/dml/delete_and_insert_fme.sql");
    execute_query_from_file_sql("../sql/dml/delete_and_insert_revisione.sql");
    execute_query_from_file_sql("../sql/dml/delete_and_insert_ricambio.sql");
    execute_query_from_file_sql("../sql/dml/delete_and_insert_mappa.sql");
    execute_query_from_file_sql("../sql/dml/delete_and_insert_postoprenotato.sql");
    execute_query_from_file_sql("../sql/dml/delete_and_insert_associata.sql");
    execute_query_from_file_sql("../sql/dml/delete_and_insert_competenze.sql");
    execute_query_from_file_sql("../sql/dml/delete_and_insert_tagliando.sql");
}

void drop_procedures(){
    execute_query_from_file_sql("../sql/ddl/procedure/drop_all_procedures.sql");
}

void create_procedures(){
    
    execute_query_from_file_sql("../sql/ddl/procedure/login.sql");
    execute_query_from_file_sql("../sql/ddl/procedure/insert_assoc.sql");
    execute_query_from_file_sql("../sql/ddl/procedure/insert_costumer.sql");
    execute_query_from_file_sql("../sql/ddl/procedure/update_trip_seat.sql");
    execute_query_from_file_sql("../sql/ddl/procedure/update_km.sql");
    execute_query_from_file_sql("../sql/ddl/procedure/update_spareparts_number.sql"); 
    execute_query_from_file_sql("../sql/ddl/procedure/insert_seat.sql");
    execute_query_from_file_sql("../sql/ddl/procedure/update_data_doc.sql");
    execute_query_from_file_sql("../sql/ddl/procedure/insert_reservation.sql");
    execute_query_from_file_sql("../sql/ddl/procedure/validate_reservation.sql");
    execute_query_from_file_sql("../sql/ddl/procedure/insert_sostitution.sql"); 

    execute_query_from_file_sql("../sql/ddl/procedure/select_trip.sql");
    execute_query_from_file_sql("../sql/ddl/procedure/select_tour.sql");
    execute_query_from_file_sql("../sql/ddl/procedure/select_all_tour.sql");
    execute_query_from_file_sql("../sql/ddl/procedure/select_dest_tour.sql"); 
    execute_query_from_file_sql("../sql/ddl/procedure/select_hotel_service.sql"); 
    execute_query_from_file_sql("../sql/ddl/procedure/select_model_comfort.sql"); 
    execute_query_from_file_sql("../sql/ddl/procedure/select_expired_review.sql"); 
    execute_query_from_file_sql("../sql/ddl/procedure/select_sparepart.sql"); 
    execute_query_from_file_sql("../sql/ddl/procedure/select_review.sql"); 
    execute_query_from_file_sql("../sql/ddl/procedure/select_max_idreview.sql"); 
    execute_query_from_file_sql("../sql/ddl/procedure/select_assigned_trip.sql"); 
    execute_query_from_file_sql("../sql/ddl/procedure/select_dest_time.sql"); 
    execute_query_from_file_sql("../sql/ddl/procedure/select_dvr_map.sql"); 
    execute_query_from_file_sql("../sql/ddl/procedure/select_bus.sql"); 
    execute_query_from_file_sql("../sql/ddl/procedure/select_reservation.sql");
    execute_query_from_file_sql("../sql/ddl/procedure/select_costumer.sql");
    execute_query_from_file_sql("../sql/ddl/procedure/select_assoc.sql"); 
    execute_query_from_file_sql("../sql/ddl/procedure/select_skills.sql"); 
    execute_query_from_file_sql("../sql/ddl/procedure/select_employee.sql");  
    execute_query_from_file_sql("../sql/ddl/procedure/select_fmo.sql"); 
    execute_query_from_file_sql("../sql/ddl/procedure/select_fme.sql"); 
    execute_query_from_file_sql("../sql/ddl/procedure/select_ofr.sql");
    execute_query_from_file_sql("../sql/ddl/procedure/select_tome.sql");
    execute_query_from_file_sql("../sql/ddl/procedure/select_user.sql");  
    execute_query_from_file_sql("../sql/ddl/procedure/select_seat.sql"); 
    execute_query_from_file_sql("../sql/ddl/procedure/select_model.sql"); 
    execute_query_from_file_sql("../sql/ddl/procedure/select_certify.sql");
    execute_query_from_file_sql("../sql/ddl/procedure/select_destination.sql");
    execute_query_from_file_sql("../sql/ddl/procedure/select_visit.sql");
    execute_query_from_file_sql("../sql/ddl/procedure/select_location.sql"); 
    execute_query_from_file_sql("../sql/ddl/procedure/select_room.sql"); 
    execute_query_from_file_sql("../sql/ddl/procedure/select_map.sql"); 
    execute_query_from_file_sql("../sql/ddl/procedure/select_picture.sql"); 
    execute_query_from_file_sql("../sql/ddl/procedure/select_comfort.sql");
    execute_query_from_file_sql("../sql/ddl/procedure/select_service.sql"); 

    execute_query_from_file_sql("../sql/ddl/procedure/insert_tour.sql"); 
    execute_query_from_file_sql("../sql/ddl/procedure/insert_trip.sql"); 
    execute_query_from_file_sql("../sql/ddl/procedure/insert_destination.sql"); 
    execute_query_from_file_sql("../sql/ddl/procedure/insert_visit.sql");
    execute_query_from_file_sql("../sql/ddl/procedure/insert_room.sql"); 
    execute_query_from_file_sql("../sql/ddl/procedure/insert_location.sql"); 
    execute_query_from_file_sql("../sql/ddl/procedure/insert_map.sql"); 
    execute_query_from_file_sql("../sql/ddl/procedure/insert_picture.sql"); 
    execute_query_from_file_sql("../sql/ddl/procedure/insert_employee.sql"); 
    execute_query_from_file_sql("../sql/ddl/procedure/insert_user.sql"); 
    execute_query_from_file_sql("../sql/ddl/procedure/insert_offert.sql"); 
    execute_query_from_file_sql("../sql/ddl/procedure/insert_service.sql"); 
    execute_query_from_file_sql("../sql/ddl/procedure/insert_tome.sql"); 
    execute_query_from_file_sql("../sql/ddl/procedure/insert_fmo.sql"); 
    execute_query_from_file_sql("../sql/ddl/procedure/insert_fme.sql"); 
    execute_query_from_file_sql("../sql/ddl/procedure/insert_model.sql"); 
    execute_query_from_file_sql("../sql/ddl/procedure/insert_bus.sql"); 
    execute_query_from_file_sql("../sql/ddl/procedure/insert_sparepart.sql");
    execute_query_from_file_sql("../sql/ddl/procedure/insert_certify.sql"); 
    execute_query_from_file_sql("../sql/ddl/procedure/insert_comfort.sql"); 
    execute_query_from_file_sql("../sql/ddl/procedure/insert_skill.sql"); 
    execute_query_from_file_sql("../sql/ddl/procedure/insert_review.sql"); 

    execute_query_from_file_sql("../sql/ddl/procedure/delete_trip.sql"); 
    execute_query_from_file_sql("../sql/ddl/procedure/delete_tour.sql");
    execute_query_from_file_sql("../sql/ddl/procedure/delete_sparepart.sql"); 
    execute_query_from_file_sql("../sql/ddl/procedure/delete_review.sql"); 
    execute_query_from_file_sql("../sql/ddl/procedure/delete_bus.sql"); 
    execute_query_from_file_sql("../sql/ddl/procedure/delete_reservation.sql");
    execute_query_from_file_sql("../sql/ddl/procedure/delete_costumer.sql");
    execute_query_from_file_sql("../sql/ddl/procedure/delete_assoc.sql"); 
    execute_query_from_file_sql("../sql/ddl/procedure/delete_skills.sql");
    execute_query_from_file_sql("../sql/ddl/procedure/delete_employee.sql"); 
    execute_query_from_file_sql("../sql/ddl/procedure/delete_fmo.sql"); 
    execute_query_from_file_sql("../sql/ddl/procedure/delete_fme.sql");
    execute_query_from_file_sql("../sql/ddl/procedure/delete_ofr.sql");
    execute_query_from_file_sql("../sql/ddl/procedure/delete_tome.sql");
    execute_query_from_file_sql("../sql/ddl/procedure/delete_user.sql"); 
    execute_query_from_file_sql("../sql/ddl/procedure/delete_seat.sql");
    execute_query_from_file_sql("../sql/ddl/procedure/delete_model.sql"); 
    execute_query_from_file_sql("../sql/ddl/procedure/delete_certify.sql");
    execute_query_from_file_sql("../sql/ddl/procedure/delete_destination.sql");
    execute_query_from_file_sql("../sql/ddl/procedure/delete_visit.sql");
    execute_query_from_file_sql("../sql/ddl/procedure/delete_location.sql");
    execute_query_from_file_sql("../sql/ddl/procedure/delete_room.sql");
    execute_query_from_file_sql("../sql/ddl/procedure/delete_map.sql");
    execute_query_from_file_sql("../sql/ddl/procedure/delete_picture.sql");
    execute_query_from_file_sql("../sql/ddl/procedure/delete_comfort.sql");
    execute_query_from_file_sql("../sql/ddl/procedure/delete_service.sql");

    }

    void privileges (void){
        
        execute_query_from_file_sql("../sql/ddl/privileges/lgn_grant.sql"); 
        execute_query_from_file_sql("../sql/ddl/privileges/mngr_grant_sel.sql");
        execute_query_from_file_sql("../sql/ddl/privileges/mngr_grant_ins.sql");
        execute_query_from_file_sql("../sql/ddl/privileges/mngr_grant_dlt.sql");
        execute_query_from_file_sql("../sql/ddl/privileges/drvr_grant.sql");
        execute_query_from_file_sql("../sql/ddl/privileges/cstmr_grant.sql");
        execute_query_from_file_sql("../sql/ddl/privileges/hstss_grant.sql");
        execute_query_from_file_sql("../sql/ddl/privileges/mchn_grant.sql");
    }

int main(int argc, char *argv[]){
    start_connection_mysql();

    drop_tables();
    drop_views();
    drop_procedures();
    create_database();
    create_tables();
    create_views();
    create_procedures();
    populate_tables();
    privileges(); 

    close_connection_mysql();

}
