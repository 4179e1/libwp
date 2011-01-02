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

struct hostent *_wp_gethostbyaddr (const char *addr, int len, int type);

int _wp_select (int nfds, fd_set *readfds, fd_set *writefds, fd_set *errorfds, struct timeval *timeout);

int __wp_open_clientfd (char *address, int port);
int __wp_open_listenfd (int port);
int _wp_open_clientfd (char *address, int port);
int _wp_open_listenfd (int port);

#ifdef DISABLE_WP
#define wp_socket socket
#define wp_shutdown shutdown
#define wp_inet_ntop inet_ntop
#define wp_inet_pton inet_pton
#define wp_gethostent gethostent
#define wp_getnetbyaddr getnetbyaddr
#define wp_getnetbyname getnetbyname
#define wp_getnetent getnetent
#define wp_getprotobyname getprotobyname
#define wp_getprotobynumber getprotobynumber
#define wp_getprotoent getprotoent
#define wp_getservbyname getservbyname
#define wp_getservbyport getservbyport
#define wp_getservent getservent
#define wp_getaddrinfo getaddrinfo
#define wp_getnameinfo getnameinfo
#define wp_bind bind
#define wp_getsockname getsockname
#define wp_getpeername getpeername
#define wp_connect connect
#define wp_listen listen
#define wp_accept accept
#define wp_send send
#define wp_sendto sendto
#define wp_sendmsg sendmsg
#define wp_recv recv
#define wp_recvfrom recvfrom
#define wp_recvmsg recvmsg
#define wp_setsockopt setsockopt
#define wp_getsockopt getsockopt
#define wp_sockatmark sockatmark
#define wp_gethostbyaddr gethostbyaddr
#define wp_select select
#define wp_open_clientfd __wp_open_clientfd
#define wp_open_listenfd __wp_open_listenfd
#else
#define wp_socket _wp_socket
#define wp_shutdown _wp_shutdown
#define wp_inet_ntop _wp_inet_ntop
#define wp_inet_pton _wp_inet_pton
#define wp_gethostent _wp_gethostent
#define wp_getnetbyaddr _wp_getnetbyaddr
#define wp_getnetbyname _wp_getnetbyname
#define wp_getnetent _wp_getnetent
#define wp_getprotobyname _wp_getprotobyname
#define wp_getprotobynumber _wp_getprotobynumber
#define wp_getprotoent _wp_getprotoent
#define wp_getservbyname _wp_getservbyname
#define wp_getservbyport _wp_getservbyport
#define wp_getservent _wp_getservent
#define wp_getaddrinfo _wp_getaddrinfo
#define wp_getnameinfo _wp_getnameinfo
#define wp_bind _wp_bind
#define wp_getsockname _wp_getsockname
#define wp_getpeername _wp_getpeername
#define wp_connect _wp_connect
#define wp_listen _wp_listen
#define wp_accept _wp_accept
#define wp_send _wp_send
#define wp_sendto _wp_sendto
#define wp_sendmsg _wp_sendmsg
#define wp_recv _wp_recv
#define wp_recvfrom _wp_recvfrom
#define wp_recvmsg _wp_recvmsg
#define wp_setsockopt _wp_setsockopt
#define wp_getsockopt _wp_getsockopt
#define wp_sockatmark _wp_sockatmark
#define wp_gethostbyaddr _wp_gethostbyaddr
#define wp_select _wp_select
#define wp_open_clientfd _wp_open_clientfd
#define wp_open_listenfd _wp_open_listenfd
#endif /* DISABLE_WP */

#endif /* _WPSOCKET_H */
