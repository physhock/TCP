#include    "unp.h"


//1.2.18 Система оповещения о событиях и подписки на них
//
//
//
int  clientsCount = 0;
pthread_t  clients [MAXCLIENTS][2];
pthread_mutex_t clnts;

static void *doit(void *);
void showClients();
void killCli(pthread_t);
void killall();
void shutdownServ(int, pthread_t);


int main(int argc, char **argv)
{
    int		              listenfd;
    char                     cmnd[128];
    pthread_t                      tid,id;
    struct sockaddr_in	      servaddr;

    listenfd = socket(AF_INET, SOCK_STREAM, 0);

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family      = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port        = htons(SERV_PORT);

    Bind(listenfd, (SA *) &servaddr, sizeof(servaddr));

    Listen(listenfd, LISTENQ);


    pthread_create(&tid, NULL, &doit, (void * ) listenfd );


    printf("Server started on port: %d\n",SERV_PORT);


    for( ; ; ) {

        scanf("%s", cmnd);

        if(strcmp(cmnd, "list") == 0){ showClients();}
        else if(strcmp(cmnd, "killCli") == 0){

            printf("id:");
            scanf("%lu", &id);
            killCli(id);
        }
        else if(strcmp(cmnd, "killall") == 0){ killall();}
        else if(strcmp(cmnd, "shutdown") == 0){
            shutdownServ(listenfd, tid);
            break;
        }

    }

    exit(1);
}


static void * doit(void *arg){

    while(true) {

        int connfd;
        socklen_t clilen;
        struct sockaddr_in cliadr;
        clilen=sizeof(cliadr);

        if((connfd = accept((int) arg, (SA *) &cliadr, &clilen)) <= 0){ break;};

        pthread_mutex_lock(&clnts);
        clientsCount++;
        clients[clientsCount][0] = connfd;
        pthread_mutex_unlock(&clnts);

        pthread_create(&clients[clientsCount][1], NULL, &str_echo, (void *) clients[clientsCount][0]);

        printf("New connection id: %lu  address: %s:%d\n",clients[clientsCount][1], inet_ntoa(cliadr.sin_addr), ntohs(cliadr.sin_port));
    }

}

void showClients(){

    printf("Number of clients: %d\n", clientsCount);
    if (clientsCount > 0) {
        for (int i = 1; i <= clientsCount; ++i) {
            printf("id: %lu\n", clients[i][1]);
        }
    }

}

void killCli(pthread_t id){


    for (int i = 1; i <= clientsCount; ++i) {
        if (clients[i][1] == id){

            shutdown(clients[i][0], 2);
            close(clients[i][0]);


            for (int j = i; j < clientsCount; ++j) {
                for (int k = 0; k < 2 ; ++k) {
                    pthread_mutex_lock(&clnts);
                    clients[j][k] = clients[j+1][k];
                    pthread_mutex_unlock(&clnts);
                }
            }

            pthread_mutex_lock(&clnts);
            clientsCount--;
            pthread_mutex_unlock(&clnts);
            return;
        }
    }

    printf("Client not found");

}

void killall(){

    int j;
    j = clientsCount;
    for (int i = 1; i <= j; ++i) {
        killCli(clients[1][1]);
    }

}

void shutdownServ(int fd, pthread_t tid) {

    shutdown(fd, 2);
    close(fd);

    killall();

    if (clientsCount > 0) {
        for (int i = 1; i <= clientsCount; ++i) {
            pthread_join(clients[i][1], NULL);
        }
    }

    printf("\nServer currently offline\n");

    pthread_join(tid, NULL);

}
