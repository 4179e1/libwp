#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <utime.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <assert.h>
#include "wpunix.h"
#include "wpbase.h"
#include "wpstdc.h"

int _wp_chdir (const char *pathname)
{
	int n;
	if ((n = chdir (pathname)) == -1)
		wp_sys_func_warning();
	return n;
}

int _wp_closedir (DIR *dp)
{
	int n;
	if ((n = closedir (dp)) == -1)
		wp_sys_func_warning();
	return n;
}

int _wp_fchdir (int filedes)
{
	int n;
	if ((n = fchdir (filedes)) == -1)
		wp_sys_func_warning();
	return n;
}

char *_wp_getcwd (char *buf, size_t size)
{
	char *cwd;
	if ((cwd = getcwd (buf, size)) == NULL)
		wp_sys_func_warning();
	return cwd;
}

int _wp_mkdir (const char *pathname, mode_t mode)
{
	int n;
	if ((n = mkdir (pathname, mode)) == -1)
		wp_sys_func_warning();
	return n;
}

DIR *_wp_opendir (const char *pathname)
{
	DIR *dp;
	if ((dp = opendir (pathname)) == NULL)
		wp_sys_func_warning();
	return dp;
}

struct dirent *_wp_readdir (DIR *dp)
{
	struct dirent *dir;
	if ((dir = readdir (dp)) == NULL)
		wp_sys_func_warning();
	return dir;
}

int _wp_rmdir (const char *pathname)
{
	int n;
	if ((n = rmdir (pathname)) == -1)
		wp_sys_func_warning();
	return n;
}

int _wp_access (const char *pathname, int mode)
{
	int n;
	if ((n = access (pathname, mode)) == -1)
		wp_sys_message ("access error");
	return n;
}

int _wp_chmod (const char *pathname, mode_t mode)
{
	int n;
	if ((n = chmod (pathname, mode)) == -1)
		wp_sys_func_warning();
	return n;
}

int _wp_chown (const char *pathname, uid_t owner, gid_t group)
{
	int n;
	if ((n = chown (pathname, owner, group)) == -1)
		wp_sys_func_warning();
	return n;
}

int _wp_close (int filedes)
{
	int rt;
	if ((rt = close (filedes)) == -1)
		wp_sys_func_warning();
	return rt;
}

int _wp_creat (const char *pathname, mode_t mode)
{
	int fd;
	if ( (fd = creat (pathname, mode)) == -1)
		wp_sys_func_warning();
	return fd;
}

int _wp_dup (int filedes)
{
	int fd;
	if ((fd = dup (filedes)) == -1)
		wp_sys_func_warning();
	return fd;
}

int _wp_dup2 (int filedes, int filedes2)
{
	int fd;
	if ((fd = dup2 (filedes, filedes2)) == -1)
		wp_sys_func_warning();
	return fd;
}

int _wp_fchmod (int filedes, mode_t mode)
{
	int n;
	if ((n = fchmod (filedes, mode)) == -1)
		wp_sys_func_warning();
	return n;
}

int _wp_fchown (int filedes, uid_t user, gid_t group)
{
	int n;
	if ((n = fchown (filedes, user, group)) == -1)
		wp_sys_func_warning();
	return n;
}

int _wp_fcntl (int filedes, int cmd, int arg)
{
	int rt;
	if ((rt = fcntl (filedes, cmd, arg)) == -1)
		wp_sys_func_warning();
	return rt;
}

int _wp_fdatasync (int filedes)
{
	int rt;
	if ((rt = fdatasync (filedes)) == -1)
		wp_sys_func_warning();
	return rt;
}

int _wp_fstat (int filedes, struct stat *buf)
{
	int n;
	if ((n = fstat (filedes, buf)) == -1)
		wp_sys_func_warning();
	return n;
}

int _wp_fsync (int filedes)
{
	int n;
	if ((n = fsync (filedes)) == -1)
		wp_sys_func_warning();
	return n;
}

int ftruncate (int filedes, off_t length)
{
	int n;
	if ((n = ftruncate (filedes, length)) == -1)
		wp_sys_func_warning();
	return n;
}

off_t _wp_lseek (int filedes, off_t offset, int whence)
{
	off_t pos;
	if ((pos = lseek (filedes, offset, whence)) == -1)
		wp_sys_func_warning();
	return pos;
}

int _wp_lchown (const char *pathname, uid_t owner, gid_t group)
{
	int n;
	if ((n = lchown (pathname, owner, group)) == -1)
		wp_sys_func_warning();
	return n;
}

int _wp_link (const char *existingpath, const char *newpath)
{
	int n;
	if ((n = link (existingpath, newpath)) == -1)
		wp_sys_func_warning();
	return n;
}

int _wp_lstat (const char *pathname, struct stat *buf)
{
	int n;
	if ((n = lstat (pathname, buf)) == -1)
		wp_sys_func_warning();
	return n;
}

int _wp_ioctl (int filedes, int request, void *arg)
{
	int rt;
	if ((rt = ioctl (filedes, request, arg)) == -1)
		wp_sys_func_warning();
	return rt;
}

int _wp_open (const char *pathname, int oflag, mode_t mode)
{
	int fd;
	if ((fd = open (pathname, oflag, mode)) == -1)
		wp_sys_func_warning();
	return fd;
}

ssize_t _wp_read (int filedes, void *buf, size_t nbytes)
{
	ssize_t n;
	if ((n = read (filedes, buf, nbytes)) == -1)
		wp_sys_func_warning();
	return n;
}

ssize_t _wp_readlink (const char *pathname, char *buf, size_t bufsize)
{
	ssize_t n;
	if ((n = readlink (pathname, buf, bufsize)) == -1)
		wp_sys_func_warning();
	return n;
}

int _wp_stat (const char *pathname, struct stat *buf)
{
	int n;
	if ((n = stat (pathname, buf)) == -1)
		wp_sys_func_warning();
	return n;
}

int _wp_symlink (const char *actualpath, const char *sympath)
{
	int n;
	if ((n = symlink (actualpath, sympath)) == -1)
		wp_sys_func_warning();
	return n;
}

int _wp_truncate (const char *pathname, off_t length)
{
	int n;
	if ((n = truncate (pathname, length)) == -1)
		wp_sys_func_warning();
	return n;
}

int _wp_unlink (const char *pathname)
{
	int n;
	if ((n = unlink (pathname)) == -1)
		wp_sys_func_warning();
	return n;
}

int _wp_utime (const char *pathname, const struct utimbuf *times)
{
	int n;
	if ((n = utime (pathname, times)) == -1)
		wp_sys_func_warning();
	return n;
}

ssize_t _wp_write (int filedes, const void *buf, size_t nbytes)
{
	ssize_t n;
	if ((n = write (filedes, buf, nbytes)) == -1)
		wp_sys_func_warning();
	return n;
}

#ifdef __USE_UNIX98
ssize_t _wp_pread (int filedes, void *buf, size_t nbytes, off_t offset)
{
	ssize_t n;
	if ((n = pread (filedes, buf, nbytes, offset)) == -1)
		wp_sys_func_warning();
	return n;
}

ssize_t _wp_pwrite (int filedes, void *buf, size_t nbytes, off_t offset)
{
	ssize_t n;
	if ((n = pwrite (filedes, buf, nbytes, offset)) == -1)
		wp_sys_func_warning();
	return n;
}
#endif /* __USE_UNIX98 */

struct passwd *_wp_getpwuid (uid_t uid)
{
	struct passwd *pw;
	if ((pw = getpwuid (uid)) == NULL)
		wp_sys_func_warning();
	return pw;
}

struct passwd *_wp_getpwanam (const char *name)
{
	struct passwd *pw;
	if ((pw = getpwnam (name)) == NULL)
		wp_sys_func_warning();
	return pw;
}

struct passwd *_wp_getpwent (void)
{
	struct passwd *pw;
	if ((pw = getpwent ()) == NULL)
		wp_sys_func_warning();
	return pw;
}

struct spwd *_wp_getspnam (const char *name)
{
	struct spwd *sp;
	if ((sp = getspnam (name)) == NULL)
		wp_sys_func_warning();
	return sp;
}

struct spwd *_wp_getspent (void)
{
	struct spwd *sp;
	if ((sp = getspent ()) == NULL)
		wp_sys_func_warning();
	return sp;
}

struct group *_wp_getgrgid (gid_t gid)
{
	struct group *gr;
	if ((gr = getgrgid (gid)) == NULL)
		wp_sys_func_warning();
	return gr;
}
struct group *_wp_getgrnam (const char *name)
{
	struct group *gr;
	if ((gr = getgrnam (name)) == NULL)
		wp_sys_func_warning();
	return gr;
}

struct group *_wp_getgrent (void)
{
	struct group *gr;
	if ((gr = getgrent ()) == NULL)
		wp_sys_func_warning();
	return gr;
}

int _wp_getgroups (int gidsetsize, gid_t grouplist[])
{
	int n;
	if ((n = getgroups (gidsetsize, grouplist)) == -1)
		wp_sys_func_warning();
	return n;
}

int _wp_setgroups (int ngroups, const gid_t grouplist[])
{
	int n;
	if ((n = setgroups (ngroups, grouplist)) == -1)
		wp_sys_func_warning();
	return n;
}

int _wp_initgroups (const char *username, gid_t basegid)
{
	int n;
	if ((n = initgroups (username, basegid)) == -1)
		wp_sys_func_warning();
	return n;
}

int _wp_uname (struct utsname *name)
{
	int n;
	if ((n = uname (name)) == -1)
		wp_sys_func_warning();
	return n;
}

int _wp_gethostname (char *name, int namelen)
{
	int n;
	if ((n = gethostname (name, namelen)) == -1)
		wp_sys_func_warning();
	return n;
}

int _wp_getrlimit (int resource, struct rlimit *rlptr)
{
	int n;
	if ((n = getrlimit (resource, rlptr)) != 0)
		wp_sys_func_warning();
	return n;
}

int _wp_setrlimit (int resource, const struct rlimit *rlptr)
{
	int n;
	if ((n = setrlimit (resource, rlptr)) != 0)
		wp_sys_func_warning();
	return n;
}

pid_t _wp_fork (void)
{
	pid_t p;
	if ((p = fork ()) < 0)
		wp_sys_func_warning();
	return p;
}

pid_t _wp_wait (int *statloc)
{
	pid_t p;
	if ((p = wait (statloc)) == -1)
		wp_sys_func_warning();
	return p;
}

pid_t _wp_waitpid (pid_t pid, int *statloc, int options)
{
	pid_t p;
	if ((p = waitpid (pid, statloc, options)) == -1)
		wp_sys_func_warning();
	return p;
}

int _wp_setuid (uid_t uid)
{
	int n;
	if ((n = setuid (uid)) ==-1)
		wp_sys_func_warning();
	return n;
}

int _wp_setgid (gid_t gid)
{
	int n;
	if ((n = setgid (gid)) == -1)
		wp_sys_func_warning();
	return n;
}

int _wp_setreuid (uid_t ruid, uid_t euid)
{
	int n;
	if ((n = setreuid (ruid, euid)) == -1)
		wp_sys_func_warning();
	return n;
}

int _wp_setregid (gid_t rgid, gid_t egid)
{
	int n;
	if ((n = setregid (rgid, egid)) == -1)
		wp_sys_func_warning();
	return n;
}
int _wp_seteuid (uid_t uid)
{
	int n;
	if ((n = seteuid (uid)) == -1)
		wp_sys_func_warning();
	return n;
}

int _wp_setegid (gid_t gid)
{
	int n;
	if ((n = setgid (gid)) == -1)
		wp_sys_func_warning();
	return n;
}

int _wp_system (const char *cmd)
{
	int n;
	n = system (cmd);
	if (n == -1)
		wp_sys_func_warning();
	else if (n == 127)
		wp_sys_func_warning();

	return n;
}

char *_wp_getlogin (void)
{
	char *p;
	if ((p = getlogin ()) == NULL)
		wp_sys_func_warning();
	return p;
}

clock_t _wp_times (struct tms *buf)
{
	clock_t t;
	if ((t = times (buf)) == -1)
		wp_sys_func_warning();
	return t;
}

int _wp_setpgid (pid_t pid, pid_t pgid)
{
	int n;
	if ((n = setpgid (pid, pgid)) == -1)
		wp_sys_func_warning();
	return n;
}

pid_t _wp_setsid (void)
{
	pid_t n;
	if ((n = setsid ()) == -1)
		wp_sys_func_warning();
	return n;
}

void (*_wp_signal (int signo, void (*func)(int)))(int)
{
	void (*f)(int) ;
	if ((f = signal (signo, func)) == SIG_ERR)
		wp_sys_func_warning();
	return f;
}

int _wp_kill (pid_t pid, int signo)
{
	int n;
	if ((n = kill (pid, signo)) == -1)
		wp_sys_func_warning();
	return n;
}

int _wp_raise (int signo)
{
	int n;
	if ((n = raise (signo)) == -1)
		wp_sys_func_warning();
	return n;
}

int _wp_sigemptyset (sigset_t *set)
{
	int n;
	if ((n = sigemptyset (set)) == -1)
		wp_sys_func_warning();
	return n;
}

int _wp_sigfillset (sigset_t *set)
{
	int n;
	if ((n = sigfillset (set)) == -1)
		wp_sys_func_warning();
	return n;
}

int _wp_sigaddset (sigset_t *set, int signo)
{
	int n;
	if ((n = sigaddset (set, signo)) == -1)
		wp_sys_func_warning();
	return n;
}

int _wp_sigdelset (sigset_t *set, int signo)
{
	int n;
	if ((n = sigdelset (set, signo)) == -1)
		wp_sys_func_warning();
	return n;
}

int _wp_sigismember (const sigset_t *set, int signo)
{
	int n;
	if ((n = sigismember (set, signo)) == -1)
		wp_sys_func_warning();
	return n;
}

int _wp_sigprocmask (int how, const sigset_t *set, sigset_t *oset)
{
	int n;
	if ((n = sigprocmask (how, set, oset)) == -1)
		wp_sys_func_warning();
	return n;
}

int _wp_sigpending (sigset_t *set)
{
	int n;
	if ((n = sigpending (set)) == -1)
		wp_sys_func_warning();
	return n;
}

int _wp_sigaction (int signo, const struct sigaction *act, struct sigaction *oact)
{
	int n;
	if ((n = sigaction (signo, act, oact)) == -1)
		wp_sys_func_warning();
	return n;
}

int _wp_sigsuspend (const sigset_t *sigmask)
{
	int n;
	if ((n = sigsuspend (sigmask)) == -1)
		wp_sys_func_warning();
	return n;
}

int _wp_sigwait (const sigset_t *set, int *signop)
{
	int n;
	if ((n = sigwait (set, signop)) != 0)
		wp_sys_func_warning();
	return n;
}

ssize_t _wp_readv (int filedes, const struct iovec *iov, int iovcnt)
{
	ssize_t n;
	if ((n = readv (filedes, iov, iovcnt)) == -1)
		wp_sys_func_warning();
	return n;
}

ssize_t _wp_writev (int filedes, const struct iovec *iov, int iovcnt)
{
	ssize_t n;
	if ((n = writev (filedes, iov, iovcnt)) == -1)
		wp_sys_func_warning();
	return n;
}

void *_wp_mmap (void *addr, size_t len, int prot, int flag, int filedes, off_t off)
{
	void *p;
	if ((p = mmap (addr, len, prot, flag, filedes, off)) == MAP_FAILED)
		wp_sys_func_warning();
	return p;
}

int _wp_mprotect (void *addr, size_t len, int prot)
{
	int n;
	if ((n = mprotect (addr, len, prot)) == -1)
		wp_sys_func_warning();
	return n;
}

int _wp_msync (void *addr, size_t len, int flags)
{
	int n;
	if ((n = msync (addr, len, flags)) == -1)
		wp_sys_func_warning();
	return n;
}

int _wp_munmap (caddr_t addr, size_t len)
{
	int n;
	if ((n = munmap (addr, len)) == -1)
		wp_sys_func_warning();
	return n;
}

int _wp_pipe (int filedes[2])
{
	int n;
	if ((n = pipe (filedes)) == -1)
		wp_sys_func_warning();
	return n;
}

int _wp_mkfifo (const char *pathname, mode_t mode)
{
	int n;
	if ((n = mkfifo (pathname, mode)) == -1)
		wp_sys_func_warning();
	return n;
}

key_t _wp_ftok (const char *path, int id)
{
	key_t k;
	if ((k = ftok (path, id)) == (key_t)-1)
		wp_sys_func_warning();
	return k;
}

int _wp_msgget (key_t key, int flag)
{
	int n;
	if ((n = msgget (key, flag)) == -1)
		wp_sys_func_warning();
	return n;
}
int _wp_msgctl (int msqid, int cmd, struct msqid_ds *buf)
{
	int n;
	if ((n = msgctl (msqid, cmd, buf)) == -1)
		wp_sys_func_warning();
	return n;
}

int _wp_msgsnd (int msqid, const void *ptr, size_t nbytes, int flag)
{
	int n;
	if ((n = msgsnd (msqid, ptr, nbytes, flag)) == -1)
		wp_sys_func_warning();
	return n;
}

ssize_t _wp_msgrcv (int msqid, void *ptr, size_t nbytes, long type, int flag)
{
	int n;
	if ((n = msgrcv (msqid, ptr, nbytes, type, flag)) == -1)
		wp_sys_func_warning();
	return n;
}

int _wp_semget (key_t key, int nsems, int flag)
{
	int n;
	if ((n = semget (key, nsems, flag)) == -1)
		wp_sys_func_warning();
	return n;
}

#if 0
int _wp_semctl (int semid, int semnum, int cmd, union semun arg)
{
	int n;
	if ((n = semctl (semid, semnum, cmd, arg)) == -1)
		wp_sys_func_warning();
	return n;
}
#endif

int _wp_semop (int semid, struct sembuf semoparray[], size_t nops)
{
	int n;
	if ((n = semop (semid, semoparray, nops)) == -1)
		wp_sys_func_warning();
	return n;
}

int _wp_shmctl (int shmid, int cmd, struct shmid_ds *buf)
{
	int n;
	if ((n = shmctl (shmid, cmd, buf)) == -1)
		wp_sys_func_warning();
	return n;
}

void *_wp_shmat (int shmid, const void *addr, int flag)
{
	void *p;
	if ((p = shmat (shmid, addr, flag)) == (void *)-1)
		wp_sys_func_warning();
	return p;
}

int _wp_shmdt (void *addr)
{
	int n;
	if ((n = shmdt (addr)) == -1)
		wp_sys_func_warning();
	return n;
}


void _wp_check_exit_status (int status)
{
	if (WIFEXITED (status))
		printf ("normal termination, exit status = %d\n", WEXITSTATUS(status));
	else if (WIFSIGNALED (status))
		printf ("abnormal termination, signal number = %d%s\n", WTERMSIG(status), 
#ifdef WCOREDUMP
				WCOREDUMP (status) ? "core file generated" : ""
#else
				""
#endif
			   );
	else if (WIFSTOPPED (status))
		printf ("child stopped, signal number = %d\n", WSTOPSIG (status));
}

