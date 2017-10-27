#include        "unp.h"


//handleClient
void *str_echo(void *arg) {

    ssize_t n;
    char command[MAXLINE];
    char result[MAXLINE];
    client *handlingClient = (client*) arg;



    for (;;) {
        if ((n = Readline(handlingClient->sock, command, MAXLINE)) == 0)
            return NULL;                /* connection closed by other end */
        //fputs(command, stdout);
        fprintf(stdout,"id: %d %s",handlingClient->id,command);

    }
}
