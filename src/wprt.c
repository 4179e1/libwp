#include "wprt.h"
#include "wpbase.h"

mqd_t wp_mq_open(const char *name, int oflag, mode_t mode, struct mq_attr *attr)
{
	mqd_t m;
	if ((m = mq_open (name, oflag, mode, attr)) == (mqd_t)-1)
		wp_sys_path_warning (name);
	return m;
}

int wp_mq_close (mqd_t mqdes)
{
	int n;
	if ((n = mq_close (mqdes)) == -1)
		wp_sys_func_warning();
	return n;
}

int wp_mq_unlink (const char *name)
{
	int n;
	if ((n = mq_unlink (name)) == -1)
		wp_sys_path_warning (name);

	return n;
}

int wp_mq_getattr (mqd_t mqdes, struct mq_attr *attr)
{
	int n;
	if ((n = mq_getattr (mqdes, attr)) == -1)
		wp_sys_func_warning();
	
	return n;
}

int wp_mq_setattr (mqd_t mqdest, struct mq_attr *attr, struct mq_attr *oattr)
{
	int n;
	if ((n = mq_setattr (mqdest, attr, oattr)) == -1)
		wp_sys_func_warning ();
	
	return n;
}

int wp_mq_send (mqd_t mqdes, const char *ptr, size_t len, unsigned int prio)
{
	int n;
	if ((n = mq_send (mqdes, ptr, len, prio)) == -1)
		wp_sys_func_warning ();

	return n;
}

int wp_mq_receive (mqd_t mqdes, char *ptr, size_t len, unsigned int *priop)
{
	int n;
	if ((n = mq_receive (mqdes, ptr, len, priop)) == -1)
		wp_sys_func_warning ();

	return n;
}

int wp_mq_notify (mqd_t mqdes, const struct sigevent *notification)
{
	int n;
	if ((n = mq_notify (mqdes, notification)) == -1)
		wp_sys_func_warning ();

	return n;
}

sem_t *wp_sem_open(const char *name, int oflag, mode_t mode, unsigned int value)
{
	sem_t *s;
	if ((s = sem_open (name, oflag, mode, value)) == SEM_FAILED)
		wp_sys_path_warning (name);
	return s;
}

int wp_sem_close (sem_t *sem)
{
	int n;
	if ((n = sem_close (sem)) == -1)
		wp_sys_func_warning ();
	return n;
}

int wp_sem_unlink (const char *name)
{
	int n;
	if ((n = sem_unlink (name)) == -1)
		wp_sys_path_warning (name);
	return n;
}

int wp_sem_wait (sem_t *sem)
{
	int n;
	if ((n = sem_wait (sem)) == -1)
		wp_sys_func_warning ();
	return n;
}

int wp_sem_trywait (sem_t *sem)
{
	int n;
	if ((n = sem_trywait (sem)) == -1)
		wp_sys_func_warning ();
	return n;
}

int wp_sem_post (sem_t *sem)
{
	int n;
	if ((n = sem_post (sem)) == -1)
		wp_sys_func_warning ();
	return n;
}

int wp_sem_getvalue (sem_t *sem, int *valp)
{
	int n;
	if ((n = sem_getvalue (sem, valp)) ==  -1)
		wp_sys_func_warning ();
	return n;
}

int wp_sem_init (sem_t *sem, int shared, unsigned int value)
{
	int n;
	if ((n = sem_init (sem,  shared, value)) == -1)
		wp_sys_func_warning ();
	return n;
}

int wp_sem_destroy (sem_t *sem)
{
	int n;
	if ((n = sem_destroy (sem)) == -1)
		wp_sys_func_warning ();
	return n;
}

int wp_shm_open (const char *name, int oflag, mode_t mode)
{
	int n;
	if ((n = shm_open (name, oflag, mode)) == -1)
		wp_sys_path_warning (name);
	return n;
}

int wp_shm_unlink (const char *name)
{
	int n;
	if ((n = shm_unlink (name)) == -1)
		wp_sys_path_warning (name);
	return n;
}
