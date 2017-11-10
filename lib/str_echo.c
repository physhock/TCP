#include        "unp.h"


//handleClient
void *str_echo(void *arg) {

    pthread_mutex_t client_mutex;
    pthread_mutex_lock(&client_mutex);

    size_t n;
    char command[MAXLINE];
    int connfd = *((int*) arg);

    for (;;) {
        if ((n = Readline(connfd, command, MAXLINE)) == 0)
            return NULL;                /* connection closed by other end */

        if(strcmp(command,"disconnect\n") == 0) {

            shutdown(connfd, 2);
            close(connfd);
            return NULL;
        }

        write(connfd, &command, n);

        pthread_mutex_unlock(&client_mutex);

    }
}
