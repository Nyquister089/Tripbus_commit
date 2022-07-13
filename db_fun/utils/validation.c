#include <stdbool.h>
#include <stdlib.h>
#include <regex.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

#include "validation.h"

regex_t regex_date;
regex_t regex_time;
regex_t regex_integer; 
regex_t regex_double; 

static void print_regerror(int errcode, size_t length, regex_t *compiled)
{
	char buffer[length];
	(void) regerror(errcode, compiled, buffer, length);
	fprintf(stderr, "Regex match failed: %s\n", buffer);
}

/**
* Consente di effettuare il setting della struttura regex_t, secondo il pattern desiderato.
* In caso di mancanza di memoria (REG_ESPACE) varrà stampato un messaggio d'errore indicante
* il nome della regex. Ritorna il risultato dell'istruzione regcomp().
*/
int setting_regex(regex_t *regex , char *pattern_to_match, char *regex_name){
	int result = regcomp(regex, pattern_to_match, REG_EXTENDED);
	if (result){
		if (result == REG_ESPACE){
			fprintf(stderr, "%s\n", strerror(ENOMEM));
		}
		else {
			fprintf(stderr, "Fatal error while setting up %s regex.\n",regex_name);
		}
	}
	return result;
}

/**
* Inizializza tutte le strutture regex_t utili al programma.
* Ritorna TRUE se tutte le strutture regex_t sono state inizializzate correttamente, altrimenti ritorna FALSE alla prima
* regex_t nopn correttamente inizializzata.
*/
bool init_validation(void)
{
	if (setting_regex(&regex_date, "^([12][0-9]{3}-(0[1-9]|1[0-2])-(0[1-9]|[12][0-9]|3[01]))", "date validation")){
		return false;
	}

	if (setting_regex(&regex_time, "^([0-1]?[0-9]|2?[0-3]|[0-9]):([0-5][0-9]|[0-9])", "time validation")){
		return false;
	}

	if (setting_regex(&regex_integer,"^\\d", "integer number validation")){
		return false;
	}
	
	if (setting_regex(&regex_double,"^[0-9]+(\\.[0-9]+)?", "double number validation")){
		return false;
	}


	return true;
}

/**
* Metodo di validazione generico delle stringhe inserite dall'utente. La funzione
* ottiene in input la stringa e la struttura regex_t contenente il pattern di confronto da utilizzare.
* Ritorna TRUE se il valori di ritorno di regexec è uguale a 0, in caso contrario
* stampa un messaggio d'errore indicante la regex fallita.
*/
bool validate(char *str, regex_t *regex){

	init_validation();
	//Questa istruzione causa Segfault ->
	int ret = regexec(regex, str, 0, NULL, REG_NOTEOL);

	if(ret != 0 && ret != REG_NOMATCH) {
		size_t length = regerror(ret, regex, NULL, 0);
		print_regerror(ret, length, regex);
		return false;
	}

	fini_validation(); 

	return ret == 0;
}

bool validate_date(char *str)
{
	return validate(str, &regex_date);
}

bool validate_time(char *str)
{
	return validate(str, &regex_time);
}

bool validate_integer(char *str){
	return validate(str, &regex_integer);
}

bool validate_double(char *str){
	return validate(str, &regex_double);
}


/**
* Libera la memoria allocata per le strutture regex_t allocate.
*/
void fini_validation(void)
{
	regfree(&regex_time);
	regfree(&regex_date);
	regfree(&regex_integer);
	regfree(&regex_double);
}
