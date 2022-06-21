#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "login.h"
#include "hostess.h"
#include "cliente.h"
#include "../utils/io.h"

void view_login(struct credentials *cred)
{
	//clear_screen();
	
	puts("*********************************");
	puts("*   BENVENUTI IN TRIPBUS *");
	puts("*********************************\n");
	get_input("Username: ", USERNAME_LEN, cred->username, false);
	get_input("Password: ", PASSWORD_LEN, cred->password, true);

}

bool ask_for_relogin(void)
{
	return yes_or_no("Vuoi accedere con utente differente?", 'y', 'n', false, true);
}

int main (void)
{	
	bool answer = false; 

	size_t role; 

	struct credentials *cred;

	cred = malloc(sizeof(struct credentials));

	init_db();

	while (!answer){

		view_login(cred); 
		role = attempt_login(cred);
		

		switch(role){
			case AUTISTA: 
				printf("Autista\n"); 
				break;
			case CLIENTE:
				run_cstmr_interface(); 
				break; 
			case HOSTESS:
				run_hstss_interface(); 
				break; 
			case MECCANICO: 
				printf("Meccanico\n"); 
				break; 
			case QUIT: 
				printf("Quit!\n");
			}
		answer = yes_or_no("\n\nVuoi chiudere il database? (s/n) ",'s','n',false,false);
		if(answer){
			fini_db();
			}
	}
	
	return 0; 
}


