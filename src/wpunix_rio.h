#ifndef _WPUNIX_RIO_H
#define _WPUNIX_RIO_H

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

/* rio */
ssize_t _wp_readn (int fd, void *ptr, size_t n);
ssize_t _wp_writen (int fd, void *ptr, size_t n);

typedef struct _rio Rio;

Rio *_wp_rio_new (int fd);
void _wp_rio_free (Rio* rp);

ssize_t _wp_rio_readlineb (Rio *rp, void *usrbuf, size_t maxlen);
ssize_t _wp_rio_readnb (Rio *rp, void *usrbuf, size_t n);
ssize_t _wp_rio_writen (Rio *rp, void *ptr, size_t n);
#define _wp_rio_readline _wp_rio_readlineb
#define _wp_rio_readnb _wp_rio_readnb

ssize_t wp_readn (int fd, void *ptr, size_t n);
ssize_t wp_writen (int fd, void *ptr, size_t n);

Rio *wp_rio_new (int fd);
void wp_rio_free (Rio* rp);

ssize_t wp_rio_readlineb (Rio *rp, void *usrbuf, size_t maxlen);
ssize_t wp_rio_readnb (Rio *rp, void *usrbuf, size_t n);
ssize_t wp_rio_writen (Rio *rp, void *ptr, size_t n);
#define wp_rio_readline wp_rio_readlineb
#define wp_rio_readnb wp_rio_readnb

int wp_rio_getfd (Rio *rp);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _WPUNIX_RIO_H */
