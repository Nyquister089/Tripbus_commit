#include <stdio.h>
#include <stdlib.h>

#include "login.h"
#include "../utils/io.h"


void view_login(struct credentials *cred)
{
	clear_screen();
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


