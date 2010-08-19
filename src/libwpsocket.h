#ifndef _WPSOCKET_H
#define _WPSOCKET_H

#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>

int wp_socket (int domain, int type, int protocol);
int wp_shutdown (int sockfd, int how);

const char *wp_inet_ntop (int domain, const void *addr, char *str, socklen_t size);
int wp_inet_pton (int domain, const char *str, void *addr);

struct hostent *wp_gethostent (void);

struct netent *wp_getnetbyaddr (uint32_t net, int type);
struct netent *wp_getnetbyname (const char *name);
struct netent *wp_getnetent (void);

struct protoent *wp_getprotobyname (const char *name);
struct protoent *wp_getprotobynumber (int proto);
struct protoent *wp_getprotoent (void);

struct servent *wp_getservbyname (const char *name, const char *proto);
struct servent *wp_getservbyport (int prot, const char *proto);
struct servent *wp_getservent (void);

int wp_getaddrinfo (const char *host, const char *service, const struct addrinfo *hint, struct addrinfo **res);
int wp_getnameinfo (const struct sockaddr *addr, socklen_t alen, char *host, socklen_t hostlen, char *service, socklen_t servlen, unsigned int flags);

int wp_bind (int sockfd, const struct sockaddr *addr, socklen_t len);
int wp_getsockname (int sockfd, struct sockaddr *addr, socklen_t *alenp);
int wp_getpeername (int sockfd, struct sockaddr *addr, socklen_t *alenp);

int wp_connect (int sockfd, const struct sockaddr *addr, socklen_t len);
int wp_listen (int sockfd, int backlog);
int wp_accept (int sockfd, struct sockaddr *addr, socklen_t *len);

ssize_t wp_send (int sockfd, const void *buf, size_t nbytes, int flags);
ssize_t wp_sendto (int sockfd, const void *buf, size_t nbytes, int flags, const struct sockaddr *destaddr, socklen_t destlen);
ssize_t wp_sendmsg (int sockfd, const struct msghdr *msg, int flags);
ssize_t wp_recv (int sockfd, void *buf, size_t nbytes, int flags);
ssize_t wp_recvfrom (int sockfd, void *buf, size_t len, int flags, struct sockaddr *addr, socklen_t *addrlen);
ssize_t wp_recvmsg (int sockfd, struct msghdr *msg, int flags);

int wp_setsockopt (int sockfd, int level, int option, const void *val, socklen_t len);
int wp_getsockopt (int sockfd, int level, int option, void *val, socklen_t *lenp);
int wp_sockatmark (int sockfd);

#endif /* _WPSOCKET_H */
