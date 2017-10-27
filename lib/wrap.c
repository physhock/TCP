#include "unp.h"


int Socket(int family, int type, int protocol)
{
    int     n;

    if((n = socket(family, type, protocol)) < 0)
        err_sys("socket error");
    return (n);
}

void Bind(int fd, const SA *addr, socklen_t len)
{
    int     n;

    if((n = bind(fd, addr,len )) < 0)
        err_sys("binding error");
}

void Listen(int fd, int num)
{
    int     n;

    if((n = listen(fd, num)) < 0)
        err_sys("listen error");
}

int Accept(int fd, SA *addr, socklen_t *len)
{
    int     n;

    if((n = accept(fd, addr, len)) < 0)
        err_sys("accept error");
    return (n);
}

void Write(int fd, void *ptr, size_t nbytes)
{
    if (write(fd, ptr, nbytes) != nbytes)
        err_sys("write error");
}

void Close(int fd)
{
    if (close(fd) == -1)
        err_sys("close error");
}


void Pthread_detach(pthread_t tid)
{
    int		n;

    if ( (n = pthread_detach(tid)) == 0)
        return;
    errno = n;
    err_sys("pthread_detach error");
}

void Pthread_create(pthread_t *tid, const pthread_attr_t *attr,
               void * (*func)(void *), void *arg)
{
    int		n;

    if ( (n = pthread_create(tid, attr, func, arg)) == 0)
        return;
    errno = n;
    err_sys("pthread_create error");
}
