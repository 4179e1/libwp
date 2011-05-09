#ifndef _WPPTHREAD_H
#define _WPPTHREAD_H

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif /* HAVE_CONFIG_H */

#include <pthread.h>
#include <signal.h>
#include <semaphore.h>

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

int wp_pthread_create (pthread_t *tidp, const pthread_attr_t *attr, void *(*start_rtn) (void *), void *arg);
int wp_pthread_join (pthread_t thread, void **rval_ptr);

int wp_pthread_cancel (pthread_t tid);

int wp_pthread_detach (pthread_t tid);

int wp_pthread_mutex_init (pthread_mutex_t *mutex, const pthread_mutexattr_t *attr);
int wp_pthread_mutex_destroy (pthread_mutex_t *mutex);
int wp_pthread_mutex_lock (pthread_mutex_t *mutex);
int wp_pthread_mutex_trylock (pthread_mutex_t *mutex);
int wp_pthread_mutex_unlock (pthread_mutex_t *mutex);

int wp_pthread_rwlock_init (pthread_rwlock_t *rwlock, const pthread_rwlockattr_t *attr);
int wp_pthread_rwlock_destroy (pthread_rwlock_t *rwlock);
int wp_pthread_rwlock_rdlock (pthread_rwlock_t *rwlock);
int wp_pthread_rwlock_wrlock (pthread_rwlock_t *rwlock);
int wp_pthread_rwlock_unlock (pthread_rwlock_t *rwlock);
int wp_pthread_rwlock_tryrdlock (pthread_rwlock_t *rwlock);
int wp_pthread_rwlock_trywrlock (pthread_rwlock_t *rwlock);

int wp_pthread_cond_init (pthread_cond_t *cond, pthread_condattr_t *buf);
int wp_pthread_cond_destroy (pthread_cond_t *cond);
int wp_pthread_cond_wait (pthread_cond_t *cond, pthread_mutex_t *mutex);
int wp_pthread_cond_timedwait (pthread_cond_t *cond, pthread_mutex_t *mutex, const struct timespec *timeout);
int wp_pthread_cond_signal (pthread_cond_t *cond);
int wp_pthread_cond_broadcast (pthread_cond_t *cond);

int wp_pthread_attr_init (pthread_attr_t *attr);
int wp_pthread_attr_destroy (pthread_attr_t *attr);
int wp_pthread_attr_getdetachstate (const pthread_attr_t *attr, int *detachstate);
int wp_pthread_attr_setdetachstate (pthread_attr_t *attr, int detachstate);
int wp_pthread_attr_getstack (const pthread_attr_t *attr, void **stackaddr, size_t *stacksize);
int wp_pthread_attr_setstack (pthread_attr_t *attr, void *stackaddr, size_t stacksize);
int wp_pthread_attr_getguardsize (const pthread_attr_t *attr, size_t *guardsize);
int wp_pthread_attr_setguardsize (pthread_attr_t *attr, size_t guardsize);

#ifdef __USE_UNIX98
int wp_pthread_setconcurrency (int level);
#endif /* __USE_UNIX98 */

int wp_pthread_mutexattr_init (pthread_mutexattr_t *attr);
int wp_pthread_mutexattr_destroy (pthread_mutexattr_t *attr);
int wp_pthread_mutexattr_getpshared (const pthread_mutexattr_t *attr, int *pshared);
int wp_pthread_mutexattr_setpshared (pthread_mutexattr_t *attr, int pshared);

#ifdef __USE_UNIX98
int wp_pthread_mutexattr_gettype (const pthread_mutexattr_t *attr, int *type);
int wp_pthread_mutexattr_settype (pthread_mutexattr_t *attr, int type);
#endif /* __USE_UNIX98 */

int wp_pthread_rwlockattr_init (pthread_rwlockattr_t *attr);
int wp_pthread_rwlockattr_destroy (pthread_rwlockattr_t *attr);
int wp_pthread_rwlockattr_getpshared (const pthread_rwlockattr_t *attr, int *pshared);
int wp_pthread_rwlockattr_setpshared (pthread_rwlockattr_t *attr, int pshared);

int wp_pthread_condattr_init (pthread_condattr_t *attr);
int wp_pthread_condattr_destroy (pthread_condattr_t *attr);
int wp_pthread_condattr_getpshared (const pthread_condattr_t *attr, int *pshared);
int wp_pthread_condattr_setpshared (pthread_condattr_t *attr, int pshared);

int wp_pthread_key_create (pthread_key_t *keyp, void (*destroctor)(void *));
int wp_pthread_key_delete (pthread_key_t key);
int wp_pthread_once (pthread_once_t *initflag, void (*initfn)(void));
void *wp_pthread_getspecific (pthread_key_t key);
int wp_pthread_setspecific (pthread_key_t key, const void *value);

int wp_pthread_setcancelstate (int state, int *oldstate);
int wp_pthread_setcanceltype (int type, int *oldtype);

int wp_phtread_sigmask (int how, const sigset_t *set, sigset_t *oset);
int wp_pthread_kill (pthread_t thread, int signo);
int wp_pthread_atfork (void (*prepare) (void), void (*parent) (void), void (*child) (void));

/* semaphore */
int wp_sem_init (sem_t *sem, int pshared, unsigned int value);
int wp_sem_destroy (sem_t *s);
int wp_sem_wait (sem_t *s);
int wp_sem_trywait (sem_t *s);
int wp_sem_post (sem_t *s);

#define P(S) (wp_sem_wait(S))
#define V(S) (wp_sem_post(S))


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _WPPTHREAD_H */
