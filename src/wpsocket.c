#include <stdlib.h>
#include <string.h>
#include <errno.h>
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

wp_interface_info_t *get_interface_info (int family, bool doaliases)
{
	wp_interface_info_t *interface;
	wp_interface_info_t *ifhead = NULL;
	wp_interface_info_t **ifnext;
	int sockfd, len, save_size, flags, myflags, idx = 0, hlen = 0;
	char *ptr, *buf = NULL, lastname[IFNAMSIZ], *cptr, *haddr = NULL, *sdlname;
	struct ifconf ifc;
	struct ifreq *ifr, ifrcopy;
	struct sockaddr_in *sinptr;
	struct sockaddr_in6 *sin6ptr;

	save_size = 0;
	sockfd = wp_socket (AF_INET, SOCK_DGRAM, 0);
	if (sockfd < 0)
	{
		return NULL;
	}

	len = 100 * sizeof (struct ifreq);
	while (1)
	{
		buf = wp_malloc (len);
		if (buf < 0)
		{
			goto ERROR_OUT;
		}
		ifc.ifc_len = len;
		ifc.ifc_buf = buf;

		if (wp_ioctl (sockfd, SIOCGIFCONF, &ifc) == -1)
		{
			if (errno != EINVAL || save_size != 0)
			{
				goto ERROR_OUT;
			}
		}
		else
		{
			if (ifc.ifc_len == save_size)
			{
				break;	/* success, len has not changed */
			}
			save_size = ifc.ifc_len;
		}

		len += 10 * sizeof (struct ifreq);
		free (buf);
		buf = NULL;
	}

	ifhead = NULL;
	ifnext = &ifhead;
	lastname[0] = 0;
	sdlname = NULL;

	for (ptr = buf; ptr < buf + ifc.ifc_len;)
	{
		ifr = (struct ifreq *)ptr;
#ifdef HAVE_SOCKADDR_SA_LEN
		len = WP_MAX (sizeof (struct sockaddr), ifr->ifr_addr.sa_len);
#else
		switch (ifr->ifr_addr.sa_family)
		{
#ifdef IPV6
		case AF_INET6:
			len = sizeof (struct sockaddr_in6);
			break;
#endif /* IPV6 */
		case AF_INET:
		default:
			len = sizeof (struct sockaddr);
			break;
		}
#endif /* HAVE_SOCKADDR_SA_LEN */

		ptr += sizeof (ifr->ifr_name) + len;

#ifdef HAVE_SOCKADDR_SA_LEN
		/* assume that AF_LINK precedes AF_INET or AF_INET6 */
		if (ifr->ifr_addr.sa_family == AF_INET)
		{
			sturct sockaddr_dl *sdl = (struct socakddr_dl *)&ifr->ifr_addr;
			sdlname = ifr->ifr_name;
			idx = sdl->sdl_index;
			haddr = sdl->sdl_data + sdl->sdl_nlen;
			hlen = sdl->sdl_alen;
		}
#endif /* HAVE_SOCKADDR_SA_LEN */

		if (ifr->ifr_addr.sa_family != family)
		{
			continue;
		}

		myflags = 0;

		if ((cptr = strchr (ifr->ifr_name, ':')) != NULL)
		{
			*ptr = 0;
		}
		if (strncmp (lastname, ifr->ifr_name, IFNAMSIZ) == 0)
		{
			if (doaliases == 0)
			{
				continue;
			}
			myflags = IF_ALIAS;
		}
		memcpy (lastname, ifr->ifr_name, IFNAMSIZ);

		ifrcopy = *ifr;
		if (wp_ioctl (sockfd, SIOCGIFFLAGS, &ifrcopy) == -1)
		{
			goto ERROR_OUT;
		}
		flags = ifrcopy.ifr_flags;
		if ((flags & IFF_UP) == 0)
		{
			continue;	/* ignore if interface not up */
		}

		interface = wp_calloc (1, sizeof (wp_interface_info_t));
		if (interface == NULL)
		{
			goto ERROR_OUT;
		}

		*ifnext = interface;
		ifnext = &interface->next;
		interface->flags = flags;
		interface->myflags = myflags;
#if defined(SIOCGIFMTU) && defined (HAVE_STRUCT_IFREQ_IFR_MTU)
		if (wp_ioctl(sockfd, SIOCGIFMTU, &ifrcopy) == -1)
		{
			goto ERROR_OUT;
		}
		interface->mtu = ifrcopy.ifr_mtu;
#else
		interface->mtu = 0;
#endif /* defined(SIOCGIFMTU) && defined (HAVE_STRUCT_IFREQ_IFR_MTU) */
		memcpy (interface->name, ifr->ifr_name, IF_NAME);
		interface->name[IF_NAME - 1] = '\0';
		/* If the sockaddr_dl is from a different interface, ignore it */
		if (sdlname == NULL || strcmp (sdlname, ifr->ifr_name) != 0)
		{
			idx = hlen = 0;
		}
		interface->index = idx;
		interface->mac_len = hlen;
		if (interface->mac_len > IF_HADDR)
		{
			interface->mac_len = IF_HADDR;
		}
		if (hlen)
		{
			memcpy (interface->mac, haddr, interface->mac_len);
		}

		switch (ifr->ifr_addr.sa_family)
		{
		case AF_INET:
			sinptr = (struct sockaddr_in *)&ifr->ifr_addr;
			interface->address = wp_calloc (1, sizeof (struct sockaddr_in));
			if (interface->address == NULL)
			{
				goto ERROR_OUT;
			}
			memcpy (interface->address, sinptr, sizeof (struct sockaddr_in));

#ifdef SIOCGIFBRDADDR
			if (flags & IFF_BROADCAST)
			{
				if (wp_ioctl (sockfd, SIOCGIFBRDADDR, &ifrcopy) == -1)
				{
					goto ERROR_OUT;
				}
				sinptr = (struct sockaddr_in *)&ifrcopy.ifr_broadaddr;
				interface->broadcast_address = wp_calloc (1, sizeof (struct sockaddr_in));
				if (interface->broadcast_address == NULL)
				{
					goto ERROR_OUT;
				}
				memcpy (interface->broadcast_address, sinptr, sizeof (struct sockaddr_in));
			}
#endif /* SIOCGIFBRDADDR */

#ifdef SIOCGIFDSTADDR
			if (flags & IFF_POINTOPOINT)
			{
				if (wp_ioctl (sockfd, SIOCGIFDSTADDR, &ifrcopy) == -1)
				{
					goto ERROR_OUT;
				}
				sinptr = (struct sockaddr_in *) &ifrcopy.ifr_dstaddr;
				interface->destination_address = wp_calloc (1, sizeof (struct sockaddr_in));
				if (interface->destination_address == NULL)
				{
					goto ERROR_OUT;
				}
				memcpy (interface->destination_address, sinptr, sizeof (struct sockaddr_in));
			}
#endif /* SIOCGIFDSTADDR */
			break;

		case AF_INET6:
			sin6ptr = (struct sockaddr_in6 *)&ifr->ifr_addr;
			interface->address = wp_calloc (1, sizeof (struct sockaddr_in6));
			if (interface->address == NULL)
			{
				goto ERROR_OUT;
			}
			memcpy (interface->address, sin6ptr, sizeof (struct sockaddr_in6));

#ifdef SIOCGIFDSTADDR
			if (flags & IFF_POINTOPOINT)
			{
				if (wp_ioctl (sockfd, SIOCGIFDSTADDR, &ifrcopy) == -1)
				{
					goto ERROR_OUT;
				}
				sin6ptr = (struct sockaddr_in6 *)&ifrcopy.ifr_dstaddr;
				interface->destination_address = wp_calloc (1, sizeof (struct sockaddr_in6));
				if (interface->destination_address == NULL)
				{
					goto ERROR_OUT;
				}
				memcpy (interface->destination_address, sin6ptr, sizeof (struct sockaddr_in6));
			}
#endif /* SIOCGIFDSTADDR */
			break;

		default:
			break;
		}
	}

	free (buf);
	wp_close (sockfd);
	return (ifhead);

ERROR_OUT:
	if (buf)
	{
		free (buf);
	}
	wp_close(sockfd);
	wp_free_interface_info (ifhead);
	return NULL;
}

wp_interface_info_t *wp_get_interface_info (int family, bool doaliases)
{
	wp_interface_info_t *i;
	
	if ((i = get_interface_info (family, doaliases)) == NULL)
	{
		wp_sys_func_warning ();
	}
	return i;
}

void wp_free_interface_info (wp_interface_info_t *head)
{
	wp_interface_info_t *i, *next;

	for (i = head; i != NULL; i = next)
	{
		if (i->address != NULL)
		{
			free (i->address);
		}
		if (i->broadcast_address != NULL)
		{
			free (i->broadcast_address);
		}
		if (i->destination_address != NULL)
		{
			free (i->destination_address);
		}
		next = i->next;
		free (i);
	}
}
