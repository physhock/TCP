#include        "unp.h"


//handleClient
void *str_echo(void *arg) {


    size_t n;
    char command[MAXLINE];

    for (;;) {
        if ((n = Readline((int) arg, command, MAXLINE)) <= 0)
            break;                /* connection closed by other end */

        if(strcmp(command,"disconnect\n") == 0) {

            shutdown((int) arg, 2);
            close((int) arg);
            break;
        }

        write((int) arg, &command, n);


    }
}
