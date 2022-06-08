#include <stdio.h>
#include <stdlib.h>

#include "login.h"
#include "../utils/io.h"


void view_login(struct credentials *cred)
{
	clear_screen();
	attempt_login(cred); 
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
	printf("Esecuzione main\n"); 
	init_db();
	printf("Avvio login"); 
	struct credentials *cred; 
	view_login(cred); 
	bool answer = yes_or_no("\n\n Vuoi chiudere il database? (s/n) ",'s','n',false,false);
	if(answer){
		fini_db(); 
		}
	return 0; 
}


