#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "login.h"
#include "hostess.h"
#include "cliente.h"
#include "meccanico.h"
#include "autista.h"
#include "manager.h"
#include "../utils/io.h"

void view_login(struct credentials *cred)
{
	//clear_screen();
	
	puts("*********************************");
	puts("*   BENVENUTI IN TRIPBUS *");
	puts("*********************************\n");
	get_input("Username: ", USERNAME_LEN, cred->username, false);
	get_input("Password: ", PASSWORD_LEN, cred->password, false);

}

bool ask_for_relogin(void)
{
	return yes_or_no("Vuoi accedere con utente differente?", 'y', 'n', false, true);
	

}

int main (void)
{	
	bool answer = false; 
	bool ans = true; 


	size_t role; 

	struct credentials *cred;

	cred = malloc(sizeof(struct credentials));

	init_db();

	while (!answer){
		
		if(ans){
			view_login(cred); 
			role = attempt_login(cred);
		}

		switch(role){
			case AUTISTA: 
				run_drvr_interface();  
				break;
			case CLIENTE:
				run_cstmr_interface(); 
				break; 
			case HOSTESS:
				run_hstss_interface(); 
				break; 
			case MECCANICO: 
				run_mch_interface();  
				break; 
			case MANAGER: 
				run_mngr_interface(); 
			case QUIT: 
				printf("Quit!\n");
			}
			
			ans = ask_for_relogin(); 
			if(!ans){
				answer = yes_or_no("\n\nVuoi chiudere il database? (s/n) ",'s','n',false,false);
					if(answer){
						fini_db();
					}
			}
	}
	
	return 0; 
}


