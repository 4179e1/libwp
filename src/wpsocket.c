#include <string.h>
#include "wpsocket.h"
#include "wpbase.h"
#include "wpunix.h"
#include "wpstdc.h"

#define LISTENQ 1024

int wp_socket (int domain, int type, int protocol)
{
	int n;
	if ((n = socket (domain, type, protocol)) == -1)
		wp_sys_func_warning ();
	return n;
}

int wp_shutdown (int sockfd, int how)
{
	int n;
	if ((n = shutdown (sockfd, how)) == -1)
		wp_sys_func_warning ();
	return n;
}

const char *wp_inet_ntop (int domain, const void *addr, char *str, socklen_t size)
{
	const char *p;
	if ((p = inet_ntop (domain, addr, str, size)) == NULL)
		wp_sys_func_warning ();
	return p;
}

int wp_inet_pton (int domain, const char *str, void *addr)
{
	int n;
	if ((n = inet_pton (domain, str, addr)) == -1)
		wp_sys_func_warning ();
	else if (n == 0)
		wp_sys_func_warning ();
	return n;
}

struct hostent *wp_gethostent (void)
{
	struct hostent *p;
	if ((p = gethostent ()) == NULL)
		wp_sys_func_warning ();
	return p;
}

struct netent *wp_getnetbyaddr (uint32_t net, int type)
{
	struct netent *p;
	if ((p = getnetbyaddr (net, type)) == NULL)
		wp_sys_func_warning ();
	return p;
}

struct netent *wp_getnetbyname (const char *name)
{
	struct netent *p;
	if ((p = getnetbyname (name)) == NULL)
		wp_sys_func_warning ();
	return p;
}

struct netent *wp_getnetent (void)
{
	struct netent *p;
	if ((p = getnetent ()) == NULL)
		wp_sys_func_warning ();
	return p;
}

struct protoent *wp_getprotobyname (const char *name)
{
	struct protoent *p;
	if ((p = getprotobyname (name)) == NULL)
		wp_sys_func_warning ();
	return p;
}

struct protoent *wp_getprotobynumber (int proto)
{
	struct protoent *p;
	if ((p = getprotobynumber (proto)) == NULL)
		wp_sys_func_warning ();
	return p;
}

struct protoent *wp_getprotoent (void)
{
	struct protoent *p;
	if ((p = getprotoent ()) == NULL)
		wp_sys_func_warning ();
	return p;
}

struct servent *wp_getservbyname (const char *name, const char *proto)
{
	struct servent *p;
	if ((p = getservbyname (name, proto)) == NULL)
		wp_sys_func_warning ();
	return p;
}

struct servent *wp_getservbyport (int prot, const char *proto)
{
	struct servent *p;
	if ((p = getservbyport (prot, proto)) == NULL)
		wp_sys_func_warning ();
	return p;
}

struct servent *wp_getservent (void)
{
	struct servent *p;
	if ((p = getservent ()) == NULL)
		wp_sys_func_warning ();
	return p;
}

int wp_getaddrinfo (const char *host, const char *service, const struct addrinfo *hint, struct addrinfo **res)
{
	int n;
	if ((n = getaddrinfo (host, service, hint, res)) != 0)
		wp_sys_func_warning ();
	return n;
}

int wp_getnameinfo (const struct sockaddr *addr, socklen_t alen, char *host, socklen_t hostlen, char *service, socklen_t servlen, unsigned int flags)
{
	int n;
	if ((n = getnameinfo (addr, alen, host, hostlen, service, servlen, flags)) != 0)
		wp_sys_func_warning ();
	return n;
}

int wp_bind (int sockfd, const struct sockaddr *addr, socklen_t len)
{
	int n;
	if ((n = bind (sockfd, addr, len)) == -1)
		wp_sys_func_warning ();
	return n;
}

int wp_getsockname (int sockfd, struct sockaddr *addr, socklen_t *alenp)
{
	int n;
	if ((n = getsockname (sockfd, addr, alenp)) == -1)
		wp_sys_func_warning ();
	return n;
}

int wp_getpeername (int sockfd, struct sockaddr *addr, socklen_t *alenp)
{
	int n;
	if ((n = getpeername (sockfd, addr, alenp)) == -1)
		wp_sys_func_warning ();
	return n;
}

int wp_connect (int sockfd, const struct sockaddr *addr, socklen_t len)
{
	int n;
	if ((n = connect (sockfd, addr, len)) == -1)
		wp_sys_func_warning ();
	return n;
}

int wp_listen (int sockfd, int backlog)
{
	int n;
	if ((n = listen (sockfd, backlog)) == -1)
		wp_sys_func_warning ();
	return n;
}

int wp_accept (int sockfd, struct sockaddr *addr, socklen_t *len)
{
	int n;
	if ((n = accept (sockfd, addr, len)) == -1)
		wp_sys_func_warning ();
	return n;
}

ssize_t wp_send (int sockfd, const void *buf, size_t nbytes, int flags)
{
	ssize_t n;
	if ((n = send (sockfd, buf, nbytes, flags)) == -1)
		wp_sys_func_warning ();
	return n;
}

ssize_t wp_sendto (int sockfd, const void *buf, size_t nbytes, int flags, const struct sockaddr *destaddr, socklen_t destlen)
{
	ssize_t n;
	if ((n = sendto (sockfd, buf, nbytes, flags, destaddr, destlen)) == -1)
		wp_sys_func_warning ();
	return n;
}

ssize_t wp_sendmsg (int sockfd, const struct msghdr *msg, int flags)
{
	ssize_t n;
	if ((n = sendmsg (sockfd, msg, flags)) == -1)
		wp_sys_func_warning ();
	return n;
}

ssize_t wp_recv (int sockfd, void *buf, size_t nbytes, int flags)
{
	ssize_t n;
	if ((n = recv (sockfd, buf, nbytes, flags)) == -1)
		wp_sys_func_warning ();
	return n;
}

ssize_t wp_recvfrom (int sockfd, void *buf, size_t len, int flags, struct sockaddr *addr, socklen_t *addrlen)
{
	ssize_t n;
	if ((n = recvfrom (sockfd, buf, len, flags, addr, addrlen)) == -1)
		wp_sys_func_warning ();
	return n;
}

ssize_t wp_recvmsg (int sockfd, struct msghdr *msg, int flags)
{
	ssize_t n;
	if ((n = recvmsg (sockfd, msg, flags)) == -1)
		wp_sys_func_warning ();
	return n;
}

int wp_setsockopt (int sockfd, int level, int option, const void *val, socklen_t len)
{
	int n;
	if ((n = setsockopt (sockfd, level, option, val, len)) == -1)
		wp_sys_func_warning ();
	return n;
}

int wp_getsockopt (int sockfd, int level, int option, void *val, socklen_t *lenp)
{
	int n;
	if ((n = getsockopt (sockfd, level, option, val, lenp)) == -1)
		wp_sys_func_warning ();
	return n;
}

int wp_sockatmark (int sockfd)
{
	int n;
	if ((n = sockatmark (sockfd)) == -1)
		wp_sys_func_warning ();
	return n;
}

#if 0
struct hostent *wp_gethostbyname (const char *name)
{
	struct hostent *p;

	if ((p = gethostbyname (name)) == NULL)
	{
		wp_sys_func_warning ();
	}
	return p;
}
#endif

int wp_select (int nfds, fd_set *readfds, fd_set *writefds, fd_set *errorfds, struct timeval *timeout)
{
	int n;
	if ((n = select (nfds, readfds, writefds, errorfds, timeout)) == -1)
	{
		wp_sys_func_warning ();
	}
	return n;
}

struct hostent *wp_gethostbyaddr (const char *addr, int len, int type)
{
	struct hostent *p;

	if ((p = gethostbyaddr (addr, len, type)) == NULL)
	{
		wp_sys_func_warning ();
	}
	return p;
}

int _wp_open_clientfd (char *ip, int port)
{
	int clientfd;
	struct sockaddr_in servaddr;

	memset (&servaddr, 0, sizeof (servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons (port);
	if (inet_pton (AF_INET, ip, &servaddr.sin_addr) <= 0)
	{
		wp_debug ("Address is not a dotted decimal, will check if it is a hostname");

		struct addrinfo hints;
		struct addrinfo *res;
		char port_name[16];
		snprintf (port_name, sizeof (port_name), "%d", port);

		memset (&hints, 0, sizeof (hints));

		hints.ai_flags = AI_CANONNAME;
		hints.ai_family = AF_INET;
		hints.ai_socktype = SOCK_STREAM;

		if (getaddrinfo (ip, port_name, &hints, &res) != 0)
		{
			return -1;
		}

		servaddr.sin_addr = ((struct sockaddr_in *)(res->ai_addr))->sin_addr;
		freeaddrinfo (res);
	}

	if ((clientfd = wp_socket (AF_INET, SOCK_STREAM, 0)) < 0)
	{
		return -2;
	}

	if (wp_connect (clientfd, (struct sockaddr*)&servaddr, sizeof (servaddr)) < 0)
	{
		wp_close (clientfd);
		return -3;
	}

	return clientfd;
}

int _wp_open_listenfd (int port)
{
	int listenfd, optval = 1;
	struct sockaddr_in servaddr;

	if ((listenfd = wp_socket (AF_INET, SOCK_STREAM, 0)) < 0)
	{
		return -1;
	}

	if (wp_setsockopt (listenfd, SOL_SOCKET, SO_REUSEADDR, (const void *)&optval, sizeof (int)) < 0)
	{
		return -2;
	}

	memset (&servaddr, 0, sizeof (servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons ((unsigned short)port);

	if (wp_bind (listenfd, (struct sockaddr*)&servaddr, sizeof (servaddr)) < 0)
	{
		return -3;
	}

	if (wp_listen (listenfd, LISTENQ) < 0)
	{
		return -4;
	}

	return listenfd;
}

int wp_open_clientfd (char *address, int port)
{
	int n;
	if ((n = _wp_open_clientfd (address, port)) < 0)
		wp_sys_func_warning ();
	return n;
}

int wp_open_listenfd (int port)
{
	int n;
	if ((n = _wp_open_listenfd (port)) < 0)
		wp_sys_func_warning ();
	return n;
}
