#include <stdio.h>
#include <stdlib.h>
#include <mysql/my_global.h>
#include <mysql/my_sys.h>
#include <mysql/mysql.h>

#include "login.h"
#include "../utils/io.h"

static char *opt_host_name = NULL; /* host (default=localhost) */
static char *opt_user_name = NULL; /* username (default=login name)*/
static char *opt_password = NULL; /* password (default=none) */
static unsigned int opt_port_num = 0; /* port number (use built-in) */
static char *opt_socket_name = NULL; /* socket name (use built-in) */
static char *opt_db_name = NULL; /* database name (default=none) */
static unsigned int opt_flags = 0; /* connection flags (none) */
static MYSQL *conn; /* pointer to connection handler */

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


int main (int argc, char **argv)
{
/* initialize connection handler */
conn = mysql_init(NULL);
if(conn == NULL) {
fprintf(stderr, "mysql_init() failed\n");
exit(EXIT_FAILURE);
}
init_db();
/* connect to server */
if(mysql_real_connect(conn, opt_host_name, opt_user_name,
opt_password, opt_db_name, opt_port_num, opt_socket_name,
opt_flags) == NULL) {
fprintf(stderr, "mysql_real_connect() failed\n");
mysql_close(conn);
exit(EXIT_FAILURE);
}

/* disconnect from server */
mysql_close(conn);
exit(EXIT_SUCCESS);
return 0; 
}


