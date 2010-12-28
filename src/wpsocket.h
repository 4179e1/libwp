#ifndef _WPSOCKET_H
#define _WPSOCKET_H

#include <sys/socket.h>
#include <sys/select.h>
#include <arpa/inet.h>
#include <netdb.h>

int _wp_socket (int domain, int type, int protocol);
int _wp_shutdown (int sockfd, int how);

const char *_wp_inet_ntop (int domain, const void *addr, char *str, socklen_t size);
int _wp_inet_pton (int domain, const char *str, void *addr);

struct hostent *_wp_gethostent (void);

struct netent *_wp_getnetbyaddr (uint32_t net, int type);
struct netent *_wp_getnetbyname (const char *name);
struct netent *_wp_getnetent (void);

struct protoent *_wp_getprotobyname (const char *name);
struct protoent *_wp_getprotobynumber (int proto);
struct protoent *_wp_getprotoent (void);

struct servent *_wp_getservbyname (const char *name, const char *proto);
struct servent *_wp_getservbyport (int prot, const char *proto);
struct servent *_wp_getservent (void);

int _wp_getaddrinfo (const char *host, const char *service, const struct addrinfo *hint, struct addrinfo **res);
int _wp_getnameinfo (const struct sockaddr *addr, socklen_t alen, char *host, socklen_t hostlen, char *service, socklen_t servlen, unsigned int flags);

int _wp_bind (int sockfd, const struct sockaddr *addr, socklen_t len);
int _wp_getsockname (int sockfd, struct sockaddr *addr, socklen_t *alenp);
int _wp_getpeername (int sockfd, struct sockaddr *addr, socklen_t *alenp);

int _wp_connect (int sockfd, const struct sockaddr *addr, socklen_t len);
int _wp_listen (int sockfd, int backlog);
int _wp_accept (int sockfd, struct sockaddr *addr, socklen_t *len);

ssize_t _wp_send (int sockfd, const void *buf, size_t nbytes, int flags);
ssize_t _wp_sendto (int sockfd, const void *buf, size_t nbytes, int flags, const struct sockaddr *destaddr, socklen_t destlen);
ssize_t _wp_sendmsg (int sockfd, const struct msghdr *msg, int flags);
ssize_t _wp_recv (int sockfd, void *buf, size_t nbytes, int flags);
ssize_t _wp_recvfrom (int sockfd, void *buf, size_t len, int flags, struct sockaddr *addr, socklen_t *addrlen);
ssize_t _wp_recvmsg (int sockfd, struct msghdr *msg, int flags);

int _wp_setsockopt (int sockfd, int level, int option, const void *val, socklen_t len);
int _wp_getsockopt (int sockfd, int level, int option, void *val, socklen_t *lenp);
int _wp_sockatmark (int sockfd);

#if 0
struct hostent *_wp_gethostbyname (const char *name);
#endif
struct hostent *_wp_gethostbyaddr (const char *addr, int len, int type);

int _wp_select (int nfds, fd_set *readfds, fd_set *writefds, fd_set *errorfds, struct timeval *timeout);

int __wp_open_clientfd (char *address, int port);
int __wp_open_listenfd (int port);
int _wp_open_clientfd (char *address, int port);
int _wp_open_listenfd (int port);
#endif /* _WPSOCKET_H */
