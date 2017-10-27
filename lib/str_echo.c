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
        fprintf(stdout,"id: %lu %s",handlingClient->thread,command);
        if(strcmp(command,"disconnect\n") == 0) {
            handlingClient->active = false;
            shutdown(handlingClient->sock, 2);
            close(handlingClient->sock);
            return 0;
        }

    }
}
