#include	"unp.h"

void str_cli(FILE *fp, int sockfd)
{
	char	sendline[MAXLINE], recvline[MAXLINE];

	while (fgets(sendline, MAXLINE, fp) != NULL) {

		send(sockfd, sendline, strlen(sendline), NULL);

		if (Readline(sockfd, recvline, MAXLINE) == 0)
			err_quit("\nServer terminated prematurely");

		fputs(recvline, stdout);
	}
}
