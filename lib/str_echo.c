#include	"unp.h"

void *str_echo(void *arg)
{
	ssize_t		n;
	char		command[MAXLINE];
	char		result[MAXLINE] = "HI\n";

	for ( ; ; ) {
		if ( (n = Readline((int)arg, command, MAXLINE)) == 0)
			return NULL;		/* connection closed by other end */
		fputs(command,stdout);


	}
}
