#include    "unp.h"


static void *doit(void *);


int main(int argc, char **argv)
{
    int		              listenfd;
    pthread_t                      tid;
    struct sockaddr_in	      servaddr;

    listenfd = socket(AF_INET, SOCK_STREAM, 0);

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family      = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port        = htons(SERV_PORT);

    Bind(listenfd, (SA *) &servaddr, sizeof(servaddr));

    Listen(listenfd, LISTENQ);

    //Start main thread
    pthread_create(&tid, NULL, &doit, (void * ) listenfd );

    printf("Server started on port: %d\n",SERV_PORT);

    //getline()
    for( ; ; ) {

    }




}

static void * doit(void *arg){

    while(true) {
        int connfd;
        socklen_t clilen;
        struct sockaddr_in cliadr;
        pthread_t tid;
        client *newConnection = malloc(sizeof(client));
        map *clientBase = malloc(sizeof(map));

        clilen=sizeof(cliadr);


        connfd = Accept((int) arg, (SA *) &cliadr, &clilen);

        newConnection->id = 2;
        newConnection->sock = connfd;
        newConnection->addr = cliadr;
        newConnection->active = true;
        newConnection->thread = tid;
        pthread_detach(pthread_self());
        pthread_create(&tid, NULL, &str_echo, (void *) connfd);

        clientBase->id = 1;
        clientBase->n = newConnection;

        printf("New client connected: %s%d\n",inet_ntoa(newConnection->addr.sin_addr), ntohs(newConnection->addr.sin_port));
    }
//    Pthread_detach(pthread_self());
//    str_echo((int)arg);
//    Close((int)arg);
//    return (NULL);
}