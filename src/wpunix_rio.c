#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <errno.h>
#include <unistd.h>
#include "wpunix.h"
#include "wpbase.h"
#include "wpstdc.h"

#define RIO_BUFSIZE 8192

struct _rio
{
	int wp_rio_fd;
	int wp_rio_cnt;	/* unread bytes */
	char *wp_rio_bufptr;
	char wp_rio_buf[RIO_BUFSIZE];
};

static ssize_t wp_rio_read (Rio *rp, char *usrbuf, size_t n);

ssize_t _wp_readn (int fd, void *ptr, size_t n)
{
	size_t nleft = n;
	ssize_t nread;

	while (nleft >0)
	{
		if ((nread = read (fd, ptr, nleft)) < 0)
		{
			if (errno == EINTR)
			{
				nread = 0;
			}
			else
			{
				wp_sys_func_warning ();
				return -1;
			}
		}
		else if (nread == 0)
		{
			break; /* EOF */
		}
		nleft -= nread;
		ptr += nread;
	}

	return (n - nleft);
}

ssize_t _wp_writen (int fd, void *ptr, size_t n)
{
	size_t nleft = n;
	size_t nwritten;

	while (nleft > 0)
	{
		if ((nwritten = write (fd, ptr, nleft)) < 0)
		{
			if (errno == EINTR)
			{
				nwritten = 0;
			}
			else
			{
				return -1;
			}
		}
		nleft -= nwritten;
		ptr += nwritten;
	}

	return n;
}


Rio *_wp_rio_new (int fd)
{
	Rio *rp = wp_malloc (sizeof (Rio));
	if (rp == NULL)
		return NULL;

	rp->wp_rio_fd = fd;
	rp->wp_rio_cnt = 0;
	rp->wp_rio_bufptr = rp->wp_rio_buf;

	return rp;
}

void wp_rio_free (Rio* rp)
{
	free (rp);
}

static ssize_t wp_rio_read (Rio *rp, char *usrbuf, size_t n)
{
	int cnt;

	while (rp->wp_rio_cnt <= 0)
	{
		rp->wp_rio_cnt = wp_read (rp->wp_rio_fd, rp->wp_rio_buf, sizeof (rp->wp_rio_buf));
		if (rp->wp_rio_cnt < 0)
		{
			if (errno != EINTR)
			{
				return -1;
			}
		}
		else if (rp->wp_rio_cnt == 0)
		{
			return 0;	/* EOF */
		}
		else
		{
			rp->wp_rio_bufptr = rp->wp_rio_buf;
		}
	}

	cnt = n;
	if (rp->wp_rio_cnt < n)
		cnt = rp->wp_rio_cnt;

	memcpy (usrbuf, rp->wp_rio_bufptr, cnt);
	rp->wp_rio_bufptr += cnt;
	rp->wp_rio_cnt -= cnt;

	return cnt;
}

ssize_t _wp_rio_readlineb (Rio *rp, void *usrbuf, size_t maxlen)
{
	int n, rc;
	char c;
	char *bufp = usrbuf;

	for (n = 1; n < maxlen; n++)
	{
		if ((rc = wp_rio_read (rp, &c, 1)) == 1)
		{
			*bufp++ = c;
			if (c == '\n')
				break;
		}
		else if (rc == 0)
		{
			if (n == 1)
				return 0;	/* EOF, no data read */
			else 
				break;		/* EOF, some data read */
		}
		else
			return -1;
	}

	*bufp = 0;
	return n;
}

ssize_t _wp_rio_readnb (Rio *rp, void *usrbuf, size_t n)
{
	size_t nleft = n;
	ssize_t nread;
	char *bufp = usrbuf;

	while (nleft > 0)
	{
		if ((nread = wp_rio_read (rp, bufp, nleft)) < 0)
		{
			if (errno == EINTR)
				nread = 0;
			else
				return -1;
		}
		else if (nread == 0)
			break;
		nleft -= nread;
		bufp += nread;
	}

	return (n - nleft);
}

ssize_t _wp_rio_writen (Rio *rio, void *ptr, size_t n)
{
	return wp_writen (rio->wp_rio_fd, ptr, n);
}

int wp_rio_getfd (Rio *rio)
{
	assert (rio != NULL);
	return rio->wp_rio_fd;
}

ssize_t wp_readn (int fd, void *ptr, size_t n)
{
	ssize_t z;
	if ((z = _wp_readn (fd, ptr, n)) < 0)
		wp_sys_func_warning ();
	return z;
}

ssize_t wp_writen (int fd, void *ptr, size_t n)
{
	ssize_t z;
	if ((z = _wp_writen (fd, ptr, n)) < 0)
		wp_sys_func_warning ();
	return z;
}

Rio *wp_rio_new (int fd)
{
	Rio *r;
	if ((r = _wp_rio_new (fd)) == NULL)
		wp_sys_func_warning ();
	return r;
}

ssize_t wp_rio_readlineb (Rio *rp, void *usrbuf, size_t maxlen)
{
	ssize_t z;
	if ((z = _wp_rio_readlineb (rp, usrbuf, maxlen)) < 0)
		wp_sys_func_warning ();
	return z;
}

ssize_t wp_rio_readnb (Rio *rp, void *usrbuf, size_t n)
{
	ssize_t z;
	if ((z = _wp_rio_readnb (rp, usrbuf, n)) < 0)
		wp_sys_func_warning ();
	return z;
}

ssize_t wp_rio_writen (Rio *rp, void *ptr, size_t n)
{
	ssize_t z;
	if ((z = _wp_rio_writen (rp, ptr, n)) < 0)
		wp_sys_func_warning ();
	return z;
}
