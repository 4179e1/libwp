#ifndef WPRT_H
#define WPRT_H

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif /* HAVE_CONFIG_H */

#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <mqueue.h>
#include <sys/mman.h>

#ifdef __cplusplus
extern "C" 
{
#endif /* __cpluspluse */

mqd_t wp_mq_open(const char *name, int oflag, mode_t mode, struct mq_attr *attr);
int wp_mq_close (mqd_t mqdes);
int wp_mq_unlink (const char *name);
int wp_mq_getattr (mqd_t mqdes, struct mq_attr *attr);
int wp_mq_setattr (mqd_t mqdest, struct mq_attr *attr, struct mq_attr *oattr);
int wp_mq_send (mqd_t mqdes, const char *ptr, size_t len, unsigned int prio);
int wp_mq_receive (mqd_t mqdes, char *ptr, size_t len, unsigned int *priop);
int wp_mq_notify (mqd_t mqdes, const struct sigevent *notification);

#include <semaphore.h>

sem_t *wp_sem_open(const char *name, int oflag, mode_t mode, unsigned int value);
int wp_sem_close (sem_t *sem);
int wp_sem_unlink (const char *name);
int wp_sem_wait (sem_t *sem);
int wp_sem_trywait (sem_t *sem);
int wp_sem_post (sem_t *sem);
int wp_sem_getvalue (sem_t *sem, int *valp);
int wp_sem_init (sem_t *sem, int shared, unsigned int value);
int wp_sem_destroy (sem_t *sem);

int wp_shm_open (const char *name, int oflag, mode_t mode);
int wp_shm_unlink (const char *name);

#ifdef __cplusplus
}
#endif /* __cpluspluse */

#endif /* WPRT_H */
