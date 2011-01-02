#ifndef _WPUNIX_RIO_H
#define _WPUNIX_RIO_H

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

/* rio */
ssize_t __wp_readn (int fd, void *ptr, size_t n);
ssize_t __wp_writen (int fd, void *ptr, size_t n);

typedef struct _rio wp_rio_t;

wp_rio_t *__wp_rio_new (int fd);
void __wp_rio_free (wp_rio_t* rp);

ssize_t __wp_rio_readlineb (wp_rio_t *rp, void *usrbuf, size_t maxlen);
ssize_t __wp_rio_readnb (wp_rio_t *rp, void *usrbuf, size_t n);
ssize_t __wp_rio_writen (wp_rio_t *rp, void *ptr, size_t n);
#define __wp_rio_readline __wp_rio_readlineb
#define __wp_rio_readnb __wp_rio_readnb

ssize_t _wp_readn (int fd, void *ptr, size_t n);
ssize_t _wp_writen (int fd, void *ptr, size_t n);

wp_rio_t *_wp_rio_new (int fd);
void _wp_rio_free (wp_rio_t* rp);

ssize_t _wp_rio_readlineb (wp_rio_t *rp, void *usrbuf, size_t maxlen);
ssize_t _wp_rio_readnb (wp_rio_t *rp, void *usrbuf, size_t n);
ssize_t _wp_rio_writen (wp_rio_t *rp, void *ptr, size_t n);
#define _wp_rio_readline _wp_rio_readlineb
#define _wp_rio_readnb _wp_rio_readnb

int _wp_rio_getfd (wp_rio_t *rp);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _WPUNIX_RIO_H */
