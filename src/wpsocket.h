#ifndef _WPSOCKET_H
#define _WPSOCKET_H

#include <sys/socket.h>
#include <sys/select.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <net/if.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

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

#if 0
struct hostent *wp_gethostbyname (const char *name);
#endif
struct hostent *wp_gethostbyaddr (const char *addr, int len, int type);

int wp_select (int nfds, fd_set *readfds, fd_set *writefds, fd_set *errorfds, struct timeval *timeout);

int _wp_open_clientfd (char *address, int port);
int _wp_open_listenfd (int port);
int wp_open_clientfd (char *address, int port);
int wp_open_listenfd (int port);


/* interface info */

#define IF_NAME 	IFNAMSIZ /* 16 */
#define IF_HADDR	8	/* allow for 64-bit EUI-64 in future */

typedef struct _wp_interface_info_t wp_interface_info_t;

struct _wp_interface_info_t
{
	char 			name[IF_NAME];	/* interface name, null-terminated */
	short			index;			/* interface index */
	short			mtu;				/* interface MTU */
	unsigned char	mac[IF_HADDR];	/* hardware address */
	unsigned short	mac_len;			/* bytes in hardware address: 0, 6, 8 */
	short			flags;			/* IFF_xxx constants from <net/if.h> */
	short			myflags;			/* our own IF_xxx flags */
	struct sockaddr *address; 			/* primary address */
	struct sockaddr *broadcast_address;		/* broadcast address */
	struct sockaddr *destination_address;		/* destination address */
	wp_interface_info_t* next;		/* next of these structures */
};

#define IF_ALIAS	1

wp_interface_info_t *wp_get_interface_info (int family, bool doalias);
void wp_free_interface_info (wp_interface_info_t *interface);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _WPSOCKET_H */
