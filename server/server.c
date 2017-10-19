#include    "unpthread.h"


static void *doit(void *);

int main(int argc, char **argv)
{
    int		listenfd, connfd;
    pthread_t   tid;
    pid_t	childpid;
    socklen_t			clilen;
    struct sockaddr_in	cliaddr, servaddr;

    listenfd = Socket(AF_INET, SOCK_STREAM, 0);

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family      = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port        = htons(SERV_PORT);

    Bind(listenfd, (SA *) &servaddr, sizeof(servaddr));

    Listen(listenfd, LISTENQ);

    for ( ; ; ) {
        clilen = sizeof(cliaddr);
        connfd = Accept(listenfd, (SA *) &cliaddr, &clilen);
        Pthread_create(&tid, NULL, &doit, (void * ) connfd );
    }
}

static void * doit(void *arg){

    Pthread_detach(pthread_self());
    str_echo((int)arg);
    Close((int)arg);
    return (NULL);
}