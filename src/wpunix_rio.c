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

static ssize_t wp_rio_read (wp_rio_t *rp, char *usrbuf, size_t n);

ssize_t _wp_readn (int fd, void *ptr, size_t n)
{
	size_t nleft = n;
	ssize_t nread;

	while (nleft >0)
	{
		if ((nread = read (fd, ptr, nleft)) < 0)
		{
			wp_sys_func_warning ();
			return nread;
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
			return nwritten;
		}
		nleft -= nwritten;
		ptr += nwritten;
	}

	return n;
}


wp_rio_t *_wp_rio_new (int fd)
{
	wp_rio_t *rp = wp_malloc (sizeof (wp_rio_t));
	if (rp == NULL)
		return NULL;

	rp->wp_rio_fd = fd;
	rp->wp_rio_cnt = 0;
	rp->wp_rio_bufptr = rp->wp_rio_buf;

	return rp;
}

void wp_rio_free (wp_rio_t* rp)
{
	free (rp);
}

static ssize_t wp_rio_read (wp_rio_t *rp, char *usrbuf, size_t n)
{
	int cnt;

	/* the buffer is empty */
	while (rp->wp_rio_cnt <= 0)
	{
		rp->wp_rio_cnt = wp_read (rp->wp_rio_fd, rp->wp_rio_buf, sizeof (rp->wp_rio_buf));
		if (rp->wp_rio_cnt < 0)
		{
			return rp->wp_rio_cnt;
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

	cnt = rp->wp_rio_cnt < n ? rp->wp_rio_cnt : n;

	memcpy (usrbuf, rp->wp_rio_bufptr, cnt);
	rp->wp_rio_bufptr += cnt;
	rp->wp_rio_cnt -= cnt;

	return cnt;
}

ssize_t _wp_rio_readlineb (wp_rio_t *rp, void *usrbuf, size_t maxlen)
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

ssize_t _wp_rio_readnb (wp_rio_t *rp, void *usrbuf, size_t n)
{
	size_t nleft = n;
	ssize_t nread;
	char *bufp = usrbuf;

	while (nleft > 0)
	{
		if ((nread = wp_rio_read (rp, bufp, nleft)) < 0)
		{
			return nread;
		}
		else if (nread == 0)
			break;
		nleft -= nread;
		bufp += nread;
	}

	return (n - nleft);
}

ssize_t _wp_rio_writen (wp_rio_t *rio, void *ptr, size_t n)
{
	return wp_writen (rio->wp_rio_fd, ptr, n);
}

int wp_rio_getfd (wp_rio_t *rio)
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

wp_rio_t *wp_rio_new (int fd)
{
	wp_rio_t *r;
	if ((r = _wp_rio_new (fd)) == NULL)
		wp_sys_func_warning ();
	return r;
}

ssize_t wp_rio_readlineb (wp_rio_t *rp, void *usrbuf, size_t maxlen)
{
	ssize_t z;
	if ((z = _wp_rio_readlineb (rp, usrbuf, maxlen)) < 0)
		wp_sys_func_warning ();
	return z;
}

ssize_t wp_rio_readnb (wp_rio_t *rp, void *usrbuf, size_t n)
{
	ssize_t z;
	if ((z = _wp_rio_readnb (rp, usrbuf, n)) < 0)
		wp_sys_func_warning ();
	return z;
}

ssize_t wp_rio_writen (wp_rio_t *rp, void *ptr, size_t n)
{
	ssize_t z;
	if ((z = _wp_rio_writen (rp, ptr, n)) < 0)
		wp_sys_func_warning ();
	return z;
}

/* readline taken from unp, to make life easier */
ssize_t wp_readline(int fd, void *vptr, size_t maxlen)
{
    ssize_t n, rc;
    char    c, *ptr;

    ptr = vptr;
    for (n = 1; n < maxlen; n++) {
      again:
        if ( (rc = read(fd, &c, 1)) == 1) {
            *ptr++ = c;
            if (c == '\n')
                break;          /* newline is stored, like fgets() */
        } else if (rc == 0) {
            *ptr = 0;
            return (n - 1);     /* EOF, n - 1 bytes were read */
        } else {
            if (errno == EINTR)
                goto again;
            return (-1);        /* error, errno set by read() */
        }
    }

    *ptr = 0;                   /* null terminate like fgets() */
    return (n);
}
