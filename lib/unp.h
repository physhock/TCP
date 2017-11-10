#ifndef        __unp_h
#define        __unp_h

#include        <sys/types.h>        /* basic system data types */
#include        <sys/socket.h>        /* basic socket definitions */
#include        <sys/time.h>        /* timeval{} for select() */
#include        <time.h>                /* timespec{} for pselect() */
#include        <netinet/in.h>        /* sockaddr_in{} and other Internet defns */
#include        <arpa/inet.h>        /* inet(3) functions */
#include        <errno.h>
#include        <fcntl.h>                /* for nonblocking */
#include        <netdb.h>
#include        <signal.h>
#include        <stdio.h>
#include        <stdlib.h>
#include        <string.h>
#include        <sys/stat.h>        /* for S_xxx file mode constants */
#include        <sys/uio.h>                /* for iovec{} and readv/writev */
#include        <unistd.h>
#include        <sys/wait.h>
#include        <sys/un.h>                /* for Unix domain sockets */
#include        <stdarg.h>
#include        <syslog.h>
#include        <stdbool.h>
#include        <pthread.h>



#define        LISTENQ                1024
#define        MAXLINE                4096
#define        SERV_PORT              9877
#define        SA                     struct sockaddr
#define        MAXCLIENTS             90



extern pthread_t clients[MAXCLIENTS][2];
extern int clientsCount;

ssize_t readline(int, void *, size_t);
void *str_echo(void *arg);
void str_cli(FILE *, int);


int Accept(int, SA *, socklen_t *);
void Bind(int, const SA *, socklen_t);
void Listen(int, int);
ssize_t Readline(int, void *, size_t);
int Socket(int, int, int);
int get_id();


void err_quit(const char *, ...);
void err_sys(const char *, ...);

#endif        /* __unp_h */
