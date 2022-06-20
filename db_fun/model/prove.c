#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

#include "trpdb.h"

void do_select_costumer(struct cliente *cliente)
{	 
	MYSQL_BIND param[8]; 
	MYSQL_FIELD *field;
	MYSQL_RES *data_field; 
	MYSQL_TIME datadocumentazione;
    MYSQL_TIME ddc; 

    struct cliente *get_data = NULL;

    char eml[VARCHAR_LEN];
	char nmc[VARCHAR_LEN];
	char cgm[VARCHAR_LEN];
	char ind[VARCHAR_LEN];
	char cdf[VARCHAR_LEN];
	char tel[VARCHAR_LEN]; //Corretto trasformandolo da carattere a puntatore di carattere
	char fax[VARCHAR_LEN];
	size_t num_fields = 0;
	int column_count; 
    int status; 
	
	printf("HERE\n");

	date_to_mysql_time(cliente->datadocumentazione, &datadocumentazione);
    init_mysql_timestamp(&ddc);

	set_binding_param(&param[0], MYSQL_TYPE_VAR_STRING, cliente->emailcliente, strlen(cliente->emailcliente));
	set_binding_param(&param[1], MYSQL_TYPE_VAR_STRING, cliente->nomecliente, strlen(cliente->nomecliente));
	set_binding_param(&param[2], MYSQL_TYPE_VAR_STRING, cliente->cognomecliente, strlen(cliente->cognomecliente));
	set_binding_param(&param[3], MYSQL_TYPE_VAR_STRING, cliente->indirizzocliente, strlen(cliente->indirizzocliente));
	set_binding_param(&param[4], MYSQL_TYPE_VAR_STRING, cliente->codicefiscale, strlen(cliente->codicefiscale));
	set_binding_param(&param[5], MYSQL_TYPE_DATE, &datadocumentazione, sizeof(datadocumentazione));
	set_binding_param(&param[6], MYSQL_TYPE_VAR_STRING, cliente->recapitotelefonico, strlen(cliente->recapitotelefonico));
	set_binding_param(&param[7], MYSQL_TYPE_VAR_STRING, cliente->fax, strlen(cliente->fax));

	printf("Bind declare\n");

	if(mysql_stmt_bind_param(select_costumer, param) != 0) {
		print_stmt_error(select_costumer, "Impossibile eseguire il bind dei parametri (select_costumer)\n");
		goto stop;
	}
	printf("Binding \n");
	if(mysql_stmt_execute(select_costumer) != 0) {
		print_stmt_error(select_costumer, "Impossibile eseguire la procedura select_costumer\n");
		goto stop;
		}

	printf("Execute \n");

	data_field = mysql_stmt_result_metadata(select_costumer);

	if( data_field == NULL) {
		print_stmt_error(select_costumer, "Impossile prelevare i campi dati ");
		printf("(select_costumer))\n\n"); 
		goto stop; 
	}
	printf("Metadata \n");
	column_count= mysql_num_fields(data_field);
	fprintf(stdout," total columns in SELECT statement: %d\n",column_count); 


	set_binding_param(&param[0], MYSQL_TYPE_VAR_STRING, eml, VARCHAR_LEN);
	set_binding_param(&param[1], MYSQL_TYPE_VAR_STRING, nmc, VARCHAR_LEN);
	set_binding_param(&param[2], MYSQL_TYPE_VAR_STRING, cgm, VARCHAR_LEN);
	set_binding_param(&param[3], MYSQL_TYPE_VAR_STRING, ind, VARCHAR_LEN);
	set_binding_param(&param[4], MYSQL_TYPE_VAR_STRING, cdf, VARCHAR_LEN);
	set_binding_param(&param[5], MYSQL_TYPE_TIMESTAMP, &ddc, sizeof(ddc));
	set_binding_param(&param[6], MYSQL_TYPE_VAR_STRING, tel, VARCHAR_LEN);
	set_binding_param(&param[7], MYSQL_TYPE_VAR_STRING, fax, VARCHAR_LEN);
	printf("Binding out \n");

	if(mysql_stmt_bind_result(select_costumer, param)) {
		print_stmt_error(select_costumer, "Impossibile eseguire il bind dei parametri (select_costumer)\n");
		goto stop; 
	}

	printf("Binding result!!!\n");

	if( mysql_stmt_store_result(select_costumer) != 0){
		print_stmt_error(select_costumer, "\nImpossibile eseguire lo store del result set ");
		printf("(select_costumer)"); 
		goto stop;
	}
	printf("Store result!!!\n");
	
	mysql_stmt_fetch(select_costumer);
    if (status == 1 || status == MYSQL_NO_DATA)
			goto: stop; 

		strcpy(cliente->emailcliente, eml);
		strcpy(cliente->nomecliente, nmc);
		strcpy(cliente->cgnomecliente, cgm);
        strcpy(cliente->codicefiscale, cdf)
        strcpy(cliente->indirizzocliente, ind);
        strcpy(cliente->recapitotelefonico, tel); 
        strcpy(cliente->fax, fax); 
        mysql_timestamp_to_string(&ddc, cliente->datadocumentazione)
		
/*	unsigned long offset = 0; 
	char *values; 
    values = malloc(sizeof(char *)*45); 

	param->buffer_type = type;
	param->buffer = buffer;
	param->buffer_length = len;

	while (num_fields<column_count) {
		//esaminare meglio la struct MYSQL_BIND 

		field = mysql_fetch_field_direct(data_field,num_fields);
		memcpy(values, ((char*)param[offset].buffer),param[num_fields].buffer_length); 
		fprintf(stdout,"%s: %s\n\n",field->name,((char*)param[offset].buffer) );
		num_fields++;*/


    stop:
	mysql_stmt_free_result(select_costumer);
	mysql_stmt_reset(select_costumer); 
	
}


data_field = mysql_stmt_result_metadata(select_costumer);

	if( data_field == NULL) {
		print_stmt_error(select_costumer, "Impossile prelevare i campi dati ");
		printf("(select_costumer))\n\n"); 
		goto stop; 
	}

	column_count= mysql_num_fields(data_field);
	fprintf(stdout," total columns in SELECT statement: %d\n",column_count);

    /*	unsigned long offset = 0; 
	char *values; 
    values = malloc(sizeof(char *)*45); 

	param->buffer_type = type;
	param->buffer = buffer;
	param->buffer_length = len;

	while (num_fields<column_count) {
		//esaminare meglio la struct MYSQL_BIND 

		field = mysql_fetch_field_direct(data_field,num_fields);
		memcpy(values, ((char*)param[offset].buffer),param[num_fields].buffer_length); 
		fprintf(stdout,"%s: %s\n\n",field->name,((char*)param[offset].buffer) );
		num_fields++;*/
