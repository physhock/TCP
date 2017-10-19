#include	"unp.h"

void
str_echo(int sockfd)
{
	ssize_t		n;
	char		command[MAXLINE];

	for ( ; ; ) {
		if ( (n = Readline(sockfd, command, MAXLINE)) == 0)
			return;		/* connection closed by other end */
		if ((n = strcmp(command,"hi")) == 0)
			Write(sockfd,command, n);

	}
}
