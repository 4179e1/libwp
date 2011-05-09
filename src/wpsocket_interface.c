#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include "wpbase.h"
#include "wpunix.h"
#include "wpsocket.h"
#include "wpstdc.h"

wp_interface_info_t *wp_get_interface_info (int family, bool doaliases)
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

