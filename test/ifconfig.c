#include <stdlib.h>
#include <libwp.h>
#include <errno.h>



int main (int argc, char *argv[])
{
	wp_interface_t *interface, *ifhead;
	struct sockaddr_in *sa;
	unsigned char *ptr;
	int i, family, doaliases;
	char address[INET_ADDRSTRLEN];

	if (argc != 3)
	{
		wp_critical ("usage: %s <inet4|inet6> <doaliases>", argv[0]);
	}

	if (strcmp (argv[1], "inet4") == 0)
	{
		family = AF_INET;
	}
	else if (strcmp (argv[1], "inet6") == 0)
	{
		family = AF_INET6;
	}
	else
	{
		wp_critical ("usage: %s <inet4|inet6> <doaliases>", argv[0]);
	}

	doaliases = atoi (argv[2]);

	ifhead = interface = wp_get_interface_info (family, doaliases);

	for (;interface != NULL; interface = interface->if_next)
	{
		printf ("%s:", interface->if_name);
		if (interface->if_index != 0)
		{
			printf ("(%d) ", interface->if_index);
		}
		printf ("<");
		if (interface->if_flags & IFF_UP)	printf ("UP ");
		if (interface->if_flags & IFF_BROADCAST)	printf ("BCAST ");
		if (interface->if_flags & IFF_MULTICAST)	printf ("MCAST ");
		if (interface->if_flags & IFF_LOOPBACK)	printf ("LOOP ");
		if (interface->if_flags & IFF_POINTOPOINT)	printf ("P2P ");
		printf (">\n");

		if ((i = interface->if_hlen) > 0)
		{
			ptr = interface->if_haddr;
			do
			{
				printf ("%s%x", (i == interface->if_hlen) ? "": ":", *ptr++);
			} while (--i > 0);
			printf ("\n");
		}

		if (interface->if_mtu != 0)
		{
			printf ("MTU: %d\n", interface->if_mtu);
		}

		if ((sa = interface->if_addr) !=NULL)
		{
			printf ("IP addr: %s\n", wp_inet_ntop (family, &(sa->sin_addr), address, sizeof (address)));
		}
		if ((sa = interface->if_brdaddr) !=NULL)
		{
			printf ("broadcast addr: %s\n", wp_inet_ntop (family, &sa->sin_addr, address, sizeof (address)));
		}
		if ((sa = interface->if_dstaddr) !=NULL)
		{
			printf ("destination addr: %s\n", wp_inet_ntop (family, &sa->sin_addr, address, sizeof (address)));
		}
		printf ("\n");
			
	}

	wp_free_interface_info (interface);

	return 0;
}
