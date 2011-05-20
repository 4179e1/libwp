#ifdef HAVE_CONFIG_H
#include <config.h>
#endif /* HAVE_CONFIG_H */

#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <utime.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <assert.h>
#include <errno.h>
#include "wpunix.h"
#include "wpbase.h"
#include "wpstdc.h"

#ifdef HAVE_ATTR_XATTR_H
#include <attr/xattr.h>
#endif /* HAVE_ATTR_XATTR_H */

#ifdef HAVE_SYS_INOTIFY_H
#include <sys/inotify.h>
#endif /* HAVE_SYS_INOTIFY_H */

int wp_chdir (const char *pathname)
{
	int n;
	if ((n = chdir (pathname)) == -1)
		wp_sys_func_warning();
	return n;
}

int wp_closedir (DIR *dp)
{
	int n;
	if ((n = closedir (dp)) == -1)
		wp_sys_func_warning();
	return n;
}

int wp_fchdir (int filedes)
{
	int n;
	if ((n = fchdir (filedes)) == -1)
		wp_sys_func_warning();
	return n;
}

char *wp_getcwd (char *buf, size_t size)
{
	char *cwd;
	if ((cwd = getcwd (buf, size)) == NULL)
		wp_sys_func_warning();
	return cwd;
}

int wp_mkdir (const char *pathname, mode_t mode)
{
	int n;
	if ((n = mkdir (pathname, mode)) == -1)
		wp_sys_func_warning();
	return n;
}

DIR *wp_opendir (const char *pathname)
{
	DIR *dp;
	if ((dp = opendir (pathname)) == NULL)
		wp_sys_func_warning();
	return dp;
}

struct dirent *wp_readdir (DIR *dp)
{
	struct dirent *dir;
	errno = 0;
	if ((dir = readdir (dp)) == NULL)
	{
		if (errno != 0)
		{
			wp_sys_func_warning();
		}
	}
	return dir;
}

int wp_rmdir (const char *pathname)
{
	int n;
	if ((n = rmdir (pathname)) == -1)
		wp_sys_func_warning();
	return n;
}

int wp_access (const char *pathname, int mode)
{
	int n;
	if ((n = access (pathname, mode)) == -1)
		wp_sys_message ("access error");
	return n;
}

int wp_chmod (const char *pathname, mode_t mode)
{
	int n;
	if ((n = chmod (pathname, mode)) == -1)
		wp_sys_func_warning();
	return n;
}

int wp_chown (const char *pathname, uid_t owner, gid_t group)
{
	int n;
	if ((n = chown (pathname, owner, group)) == -1)
		wp_sys_func_warning();
	return n;
}

int wp_close (int filedes)
{
	int rt;
	if ((rt = close (filedes)) == -1)
		wp_sys_func_warning();
	return rt;
}

int wp_creat (const char *pathname, mode_t mode)
{
	int fd;
	if ( (fd = creat (pathname, mode)) == -1)
		wp_sys_func_warning();
	return fd;
}

int wp_dup (int filedes)
{
	int fd;
	if ((fd = dup (filedes)) == -1)
		wp_sys_func_warning();
	return fd;
}

int wp_dup2 (int filedes, int filedes2)
{
	int fd;
	if ((fd = dup2 (filedes, filedes2)) == -1)
		wp_sys_func_warning();
	return fd;
}

int wp_fchmod (int filedes, mode_t mode)
{
	int n;
	if ((n = fchmod (filedes, mode)) == -1)
		wp_sys_func_warning();
	return n;
}

int wp_fchown (int filedes, uid_t user, gid_t group)
{
	int n;
	if ((n = fchown (filedes, user, group)) == -1)
		wp_sys_func_warning();
	return n;
}

int wp_fcntl (int filedes, int cmd, int arg)
{
	int rt;
	if ((rt = fcntl (filedes, cmd, arg)) == -1)
		wp_sys_func_warning();
	return rt;
}

int wp_fdatasync (int filedes)
{
	int rt;
	if ((rt = fdatasync (filedes)) == -1)
		wp_sys_func_warning();
	return rt;
}

int wp_fstat (int filedes, struct stat *buf)
{
	int n;
	if ((n = fstat (filedes, buf)) == -1)
		wp_sys_func_warning();
	return n;
}

int wp_fsync (int filedes)
{
	int n;
	if ((n = fsync (filedes)) == -1)
	{
		/*
		* we prefer fsync(), but let's try fdatasync()
		* if fsync() fails, just in case
		*/
		if (errno == EINVAL)
		{
			if (fdatasync (filedes) == -1)
			{
				wp_sys_func_warning();
			}
		}
		else
		{
			wp_sys_func_warning();
		}
	}
	return n;
}

int wp_ftruncate (int filedes, off_t length)
{
	int n;
	if ((n = ftruncate (filedes, length)) == -1)
		wp_sys_func_warning();
	return n;
}

off_t wp_lseek (int filedes, off_t offset, int whence)
{
	off_t pos;
	if ((pos = lseek (filedes, offset, whence)) == -1)
		wp_sys_func_warning();
	return pos;
}

int wp_lchown (const char *pathname, uid_t owner, gid_t group)
{
	int n;
	if ((n = lchown (pathname, owner, group)) == -1)
		wp_sys_func_warning();
	return n;
}

int wp_link (const char *existingpath, const char *newpath)
{
	int n;
	if ((n = link (existingpath, newpath)) == -1)
		wp_sys_func_warning();
	return n;
}

int wp_lstat (const char *pathname, struct stat *buf)
{
	int n;
	if ((n = lstat (pathname, buf)) == -1)
		wp_sys_func_warning();
	return n;
}

int wp_ioctl (int filedes, int request, void *arg)
{
	int rt;
	if ((rt = ioctl (filedes, request, arg)) == -1)
		wp_sys_func_warning();
	return rt;
}

int wp_open (const char *pathname, int oflag, mode_t mode)
{
	int fd;
	if ((fd = open (pathname, oflag, mode)) == -1)
		wp_sys_func_warning();
	return fd;
}

ssize_t wp_read (int filedes, void *buf, size_t nbytes)
{
	ssize_t n;
	if ((n = read (filedes, buf, nbytes)) == -1)
		wp_sys_func_warning();
	return n;
}

ssize_t wp_readlink (const char *pathname, char *buf, size_t bufsize)
{
	ssize_t n;
	if ((n = readlink (pathname, buf, bufsize)) == -1)
		wp_sys_func_warning();
	return n;
}

int wp_stat (const char *pathname, struct stat *buf)
{
	int n;
	if ((n = stat (pathname, buf)) == -1)
		wp_sys_func_warning();
	return n;
}

int wp_symlink (const char *actualpath, const char *sympath)
{
	int n;
	if ((n = symlink (actualpath, sympath)) == -1)
		wp_sys_func_warning();
	return n;
}

int wp_truncate (const char *pathname, off_t length)
{
	int n;
	if ((n = truncate (pathname, length)) == -1)
		wp_sys_func_warning();
	return n;
}

int wp_unlink (const char *pathname)
{
	int n;
	if ((n = unlink (pathname)) == -1)
		wp_sys_func_warning();
	return n;
}

int wp_utime (const char *pathname, const struct utimbuf *times)
{
	int n;
	if ((n = utime (pathname, times)) == -1)
		wp_sys_func_warning();
	return n;
}

ssize_t wp_write (int filedes, const void *buf, size_t nbytes)
{
	ssize_t n;
	if ((n = write (filedes, buf, nbytes)) == -1)
		wp_sys_func_warning();
	return n;
}

int wp_mlock (const void *addr, size_t len)
{
	int n;
	if ((n = mlock (addr, len)) == -1)
		wp_sys_func_warning();
	return n;
}

int wp_mlockall (int flags)
{
	int n;
	if ((n = mlockall (flags)) == -1)
		wp_sys_func_warning ();
	return n;
}

int wp_munlock (const void *addr, size_t len)
{
	int n;
	if ((n = munlock (addr, len)) == -1)
		wp_sys_func_warning ();
	return n;
}

int wp_munlockall (void)
{
	int n;
	if ((n = munlockall ()) == -1)
		wp_sys_func_warning ();
	return n;
}

#ifdef __USE_UNIX98
ssize_t wp_pread (int filedes, void *buf, size_t nbytes, off_t offset)
{
	ssize_t n;
	if ((n = pread (filedes, buf, nbytes, offset)) == -1)
		wp_sys_func_warning();
	return n;
}

ssize_t wp_pwrite (int filedes, void *buf, size_t nbytes, off_t offset)
{
	ssize_t n;
	if ((n = pwrite (filedes, buf, nbytes, offset)) == -1)
		wp_sys_func_warning();
	return n;
}
#endif /* __USE_UNIX98 */

struct passwd *wp_getpwuid (uid_t uid)
{
	struct passwd *pw;
	if ((pw = getpwuid (uid)) == NULL)
		wp_sys_func_warning();
	return pw;
}

struct passwd *wp_getpwanam (const char *name)
{
	struct passwd *pw;
	if ((pw = getpwnam (name)) == NULL)
		wp_sys_func_warning();
	return pw;
}

struct passwd *wp_getpwent (void)
{
	struct passwd *pw;
	if ((pw = getpwent ()) == NULL)
		wp_sys_func_warning();
	return pw;
}

struct spwd *wp_getspnam (const char *name)
{
	struct spwd *sp;
	if ((sp = getspnam (name)) == NULL)
		wp_sys_func_warning();
	return sp;
}

struct spwd *wp_getspent (void)
{
	struct spwd *sp;
	if ((sp = getspent ()) == NULL)
		wp_sys_func_warning();
	return sp;
}

struct group *wp_getgrgid (gid_t gid)
{
	struct group *gr;
	if ((gr = getgrgid (gid)) == NULL)
		wp_sys_func_warning();
	return gr;
}
struct group *wp_getgrnam (const char *name)
{
	struct group *gr;
	if ((gr = getgrnam (name)) == NULL)
		wp_sys_func_warning();
	return gr;
}

struct group *wp_getgrent (void)
{
	struct group *gr;
	if ((gr = getgrent ()) == NULL)
		wp_sys_func_warning();
	return gr;
}

int wp_getgroups (int gidsetsize, gid_t grouplist[])
{
	int n;
	if ((n = getgroups (gidsetsize, grouplist)) == -1)
		wp_sys_func_warning();
	return n;
}

int wp_setgroups (int ngroups, const gid_t grouplist[])
{
	int n;
	if ((n = setgroups (ngroups, grouplist)) == -1)
		wp_sys_func_warning();
	return n;
}

int wp_initgroups (const char *username, gid_t basegid)
{
	int n;
	if ((n = initgroups (username, basegid)) == -1)
		wp_sys_func_warning();
	return n;
}

int wp_uname (struct utsname *name)
{
	int n;
	if ((n = uname (name)) == -1)
		wp_sys_func_warning();
	return n;
}

int wp_gethostname (char *name, int namelen)
{
	int n;
	if ((n = gethostname (name, namelen)) == -1)
		wp_sys_func_warning();
	return n;
}

int wp_getrlimit (int resource, struct rlimit *rlptr)
{
	int n;
	if ((n = getrlimit (resource, rlptr)) != 0)
		wp_sys_func_warning();
	return n;
}

int wp_setrlimit (int resource, const struct rlimit *rlptr)
{
	int n;
	if ((n = setrlimit (resource, rlptr)) != 0)
		wp_sys_func_warning();
	return n;
}

int wp_execv (const char *path, char *const argv[])
{
	int n;
	if ((n = execv (path, argv)) == -1)
	{
		wp_sys_func_warning ();
	}
	return n;
}

int wp_execvp (const char *file, char *const argv[])
{
	int n;
	if ((n = execvp (file, argv)) == -1)
	{
		wp_sys_func_warning ();
	}
	return n;
}

int wp_execve (const char *path, char *const argv[], char *const envp[])
{
	int n;
	if ((n = execve (path, argv, envp)) == -1)
	{
		wp_sys_func_warning ();
	}
	return n;
}

pid_t wp_fork (void)
{
	pid_t p;
	if ((p = fork ()) < 0)
		wp_sys_func_warning();
	return p;
}

pid_t wp_wait (int *statloc)
{
	pid_t p;
	if ((p = wait (statloc)) == -1)
		wp_sys_func_warning();
	return p;
}

pid_t wp_waitpid (pid_t pid, int *statloc, int options)
{
	pid_t p;
	if ((p = waitpid (pid, statloc, options)) == -1)
		wp_sys_func_warning();
	return p;
}

int wp_setuid (uid_t uid)
{
	int n;
	if ((n = setuid (uid)) ==-1)
		wp_sys_func_warning();
	return n;
}

int wp_setgid (gid_t gid)
{
	int n;
	if ((n = setgid (gid)) == -1)
		wp_sys_func_warning();
	return n;
}

int wp_setreuid (uid_t ruid, uid_t euid)
{
	int n;
	if ((n = setreuid (ruid, euid)) == -1)
		wp_sys_func_warning();
	return n;
}

int wp_setregid (gid_t rgid, gid_t egid)
{
	int n;
	if ((n = setregid (rgid, egid)) == -1)
		wp_sys_func_warning();
	return n;
}
int wp_seteuid (uid_t uid)
{
	int n;
	if ((n = seteuid (uid)) == -1)
		wp_sys_func_warning();
	return n;
}

int wp_setegid (gid_t gid)
{
	int n;
	if ((n = setgid (gid)) == -1)
		wp_sys_func_warning();
	return n;
}

int wp_system (const char *cmd)
{
	int n;
	n = system (cmd);
	if (n == -1)
		wp_sys_func_warning();
	else if (n == 127)
		wp_sys_func_warning();

	return n;
}

char *wp_getlogin (void)
{
	char *p;
	if ((p = getlogin ()) == NULL)
		wp_sys_func_warning();
	return p;
}

clock_t wp_times (struct tms *buf)
{
	clock_t t;
	if ((t = times (buf)) == -1)
		wp_sys_func_warning();
	return t;
}

int wp_setpgid (pid_t pid, pid_t pgid)
{
	int n;
	if ((n = setpgid (pid, pgid)) == -1)
		wp_sys_func_warning();
	return n;
}

pid_t wp_setsid (void)
{
	pid_t n;
	if ((n = setsid ()) == -1)
		wp_sys_func_warning();
	return n;
}

int wp_kill (pid_t pid, int signo)
{
	int n;
	if ((n = kill (pid, signo)) == -1)
		wp_sys_func_warning();
	return n;
}

int wp_killpg (pid_t pid, int signo)
{
	int n;
	if ((n = killpg (pid, signo)) == -1)
		wp_sys_func_warning ();
	return n;
}

int wp_raise (int signo)
{
	int n;
	if ((n = raise (signo)) == -1)
		wp_sys_func_warning();
	return n;
}

int wp_sigemptyset (sigset_t *set)
{
	int n;
	if ((n = sigemptyset (set)) == -1)
		wp_sys_func_warning();
	return n;
}

int wp_sigfillset (sigset_t *set)
{
	int n;
	if ((n = sigfillset (set)) == -1)
		wp_sys_func_warning();
	return n;
}

int wp_sigaddset (sigset_t *set, int signo)
{
	int n;
	if ((n = sigaddset (set, signo)) == -1)
		wp_sys_func_warning();
	return n;
}

int wp_sigdelset (sigset_t *set, int signo)
{
	int n;
	if ((n = sigdelset (set, signo)) == -1)
		wp_sys_func_warning();
	return n;
}

int wp_sigismember (const sigset_t *set, int signo)
{
	int n;
	if ((n = sigismember (set, signo)) == -1)
		wp_sys_func_warning();
	return n;
}

int wp_sigprocmask (int how, const sigset_t *set, sigset_t *oset)
{
	int n;
	if ((n = sigprocmask (how, set, oset)) == -1)
		wp_sys_func_warning();
	return n;
}

int wp_sigpending (sigset_t *set)
{
	int n;
	if ((n = sigpending (set)) == -1)
		wp_sys_func_warning();
	return n;
}

int wp_sigaction (int signo, const struct sigaction *act, struct sigaction *oact)
{
	int n;
	if ((n = sigaction (signo, act, oact)) == -1)
		wp_sys_func_warning();
	return n;
}

int wp_sigqueue (pid_t pid, int signo, const union sigval value)
{
	int n;
	if ((n = sigqueue (pid, signo, value))  == -1)
		wp_sys_func_warning ();
	return n;
}

int wp_sigsuspend (const sigset_t *sigmask)
{
	int n;
	if ((n = sigsuspend (sigmask)) == -1)
		wp_sys_func_warning();
	return n;
}

int wp_sigwait (const sigset_t *set, int *signop)
{
	int n;
	if ((n = sigwait (set, signop)) != 0)
		wp_sys_func_warning();
	return n;
}

ssize_t wp_readv (int filedes, const struct iovec *iov, int iovcnt)
{
	ssize_t n;
	if ((n = readv (filedes, iov, iovcnt)) == -1)
		wp_sys_func_warning();
	return n;
}

ssize_t wp_writev (int filedes, const struct iovec *iov, int iovcnt)
{
	ssize_t n;
	if ((n = writev (filedes, iov, iovcnt)) == -1)
		wp_sys_func_warning();
	return n;
}

void *wp_mmap (void *addr, size_t len, int prot, int flag, int filedes, off_t off)
{
	void *p;
	if ((p = mmap (addr, len, prot, flag, filedes, off)) == MAP_FAILED)
		wp_sys_func_warning();
	return p;
}

int wp_mprotect (void *addr, size_t len, int prot)
{
	int n;
	if ((n = mprotect (addr, len, prot)) == -1)
		wp_sys_func_warning();
	return n;
}

int wp_msync (void *addr, size_t len, int flags)
{
	int n;
	if ((n = msync (addr, len, flags)) == -1)
		wp_sys_func_warning();
	return n;
}

int wp_munmap (caddr_t addr, size_t len)
{
	int n;
	if ((n = munmap (addr, len)) == -1)
		wp_sys_func_warning();
	return n;
}

#ifdef _GUN_SOURCE
void *wp_mremap (void *old_address, size_t old_size, size_t new_size, int flags, void *new_address)
{
	void *p;
	if ((p = mremap (old_address, old_size, new_size, flags, new_address)) == MAP_FAILED)
	{
		wp_sys_func_warning ();
	}
	return p;
}
#endif /* _GUN_SOURCE */

int wp_posix_fadvise (int fd, off_t offset, off_t len, int advice)
{
	int n;
	if ((n = posix_fadvise (fd, offset, len, advice)) != 0)
	{
		wp_sys_func_warning ();
	}
	return n;
}

int wp_pipe (int filedes[2])
{
	int n;
	if ((n = pipe (filedes)) == -1)
		wp_sys_func_warning();
	return n;
}

int wp_mkfifo (const char *pathname, mode_t mode)
{
	int n;
	if ((n = mkfifo (pathname, mode)) == -1)
		wp_sys_func_warning();
	return n;
}

key_t wp_ftok (const char *path, int id)
{
	key_t k;
	if ((k = ftok (path, id)) == (key_t)-1)
		wp_sys_func_warning();
	return k;
}

int wp_msgget (key_t key, int flag)
{
	int n;
	if ((n = msgget (key, flag)) == -1)
		wp_sys_func_warning();
	return n;
}
int wp_msgctl (int msqid, int cmd, struct msqid_ds *buf)
{
	int n;
	if ((n = msgctl (msqid, cmd, buf)) == -1)
		wp_sys_func_warning();
	return n;
}

int wp_msgsnd (int msqid, const void *ptr, size_t nbytes, int flag)
{
	int n;
	if ((n = msgsnd (msqid, ptr, nbytes, flag)) == -1)
		wp_sys_func_warning();
	return n;
}

ssize_t wp_msgrcv (int msqid, void *ptr, size_t nbytes, long type, int flag)
{
	int n;
	if ((n = msgrcv (msqid, ptr, nbytes, type, flag)) == -1)
		wp_sys_func_warning();
	return n;
}

int wp_semget (key_t key, int nsems, int flag)
{
	int n;
	if ((n = semget (key, nsems, flag)) == -1)
		wp_sys_func_warning();
	return n;
}

#if 0
int wp_semctl (int semid, int semnum, int cmd, union semun arg)
{
	int n;
	if ((n = semctl (semid, semnum, cmd, arg)) == -1)
		wp_sys_func_warning();
	return n;
}
#endif

int wp_semop (int semid, struct sembuf semoparray[], size_t nops)
{
	int n;
	if ((n = semop (semid, semoparray, nops)) == -1)
		wp_sys_func_warning();
	return n;
}

int wp_shmctl (int shmid, int cmd, struct shmid_ds *buf)
{
	int n;
	if ((n = shmctl (shmid, cmd, buf)) == -1)
		wp_sys_func_warning();
	return n;
}

void *wp_shmat (int shmid, const void *addr, int flag)
{
	void *p;
	if ((p = shmat (shmid, addr, flag)) == (void *)-1)
		wp_sys_func_warning();
	return p;
}

int wp_shmdt (void *addr)
{
	int n;
	if ((n = shmdt (addr)) == -1)
		wp_sys_func_warning();
	return n;
}

#ifdef HAVE_ATTR_XATTR_H
ssize_t wp_getxattr (const char *path, const char *key, void *value, size_t size)
{
	ssize_t n;
	if ((n = getxattr (path, key, value, size)) == -1)
		wp_sys_func_warning ();
	return n;
}

ssize_t wp_lgetxattr (const char *path, const char *key, void *value, size_t size)
{
	ssize_t n;
	if ((n = lgetxattr (path, key, value, size)) == -1)
		wp_sys_func_warning ();
	return n;
}

ssize_t wp_fgetxattr (int fd, const char *key, void *value, size_t size)
{
	ssize_t n;
	if ((n = fgetxattr (fd, key, value, size)) == -1)
		wp_sys_func_warning ();
	return n;
}

int wp_setxattr (const char *path, const char *key, const void *value, size_t size, int flags)
{
	int n;
	if ((n = setxattr (path, key, value, size, flags)) == -1)
		wp_sys_func_warning ();
	return n;
}

int wp_lsetxattr (const char *path, const char *key, const void *value, size_t size, int flags)
{
	int n;
	if ((n = lsetxattr (path, key, value, size, flags)) == -1)
		wp_sys_func_warning ();
	return n;
}

int wp_fsetxattr (int fd, const char *key, const void *value, size_t size, int flags)
{
	int n;
	if ((n = fsetxattr (fd, key, value, size, flags)) == -1)
		wp_sys_func_warning ();
	return n;
}

ssize_t wp_listxattr (const char *path, char *list, size_t size)
{
	ssize_t n;
	if ((n = listxattr (path, list, size)) == -1)
		wp_sys_func_warning ();
	return n;
}

ssize_t wp_llistxattr (const char *path, char *list, size_t size)
{
	ssize_t n;
	if ((n = llistxattr (path, list, size)) == -1)
		wp_sys_func_warning ();
	return n;
}

ssize_t wp_flistxattr (int fd, char *list, size_t size)
{
	ssize_t n;
	if ((n = flistxattr (fd, list, size)) == -1)
		wp_sys_func_warning ();
	return n;
}

int wp_removexattr (const char *path, const char *key)
{
	int n;
	if ((n = removexattr (path, key)) == -1)
		wp_sys_func_warning ();
	return n;
}

int wp_lremovexattr (const char *path, const char *key)
{
	int n;
	if ((n = lremovexattr (path, key)) == -1)
		wp_sys_func_warning ();
	return n;
}

int wp_femovexattr (int fd, const char *key)
{
	int n;
	if ((n = fremovexattr (fd, key)) == -1)
		wp_sys_func_warning ();
	return n;
}
#endif /* HAVE_ATTR_XATTR_H */

#ifdef HAVE_SYS_INOTIFY_H
int wp_inotify_init (void)
{
	int n;
	if ((n = inotify_init ()) == -1)
		wp_sys_func_warning ();
	return n;
}

int wp_inotify_add_watch (int fd, const char *path, uint32_t mask)
{
	int n;
	if ((n = inotify_add_watch (fd, path, mask)) == -1)
		wp_sys_func_warning ();
	return n;
}

int wp_inotify_rm_watch (int fd, uint32_t wd)
{
	int n;
	if ((n = inotify_rm_watch (fd, wd)) == -1)
		wp_sys_func_warning ();
	return n;
}
#endif /* HAVE_SYS_INOTIFY_H */

int wp_select (int nfds, fd_set *readfds, fd_set *writefds, fd_set *errorfds, struct timeval *timeout)
{
	int n;
	if ((n = select (nfds, readfds, writefds, errorfds, timeout)) == -1)
	{
		wp_sys_func_warning ();
	}
	return n;
}

#ifdef __USE_XOPEN2k
int wp_pselect (int n, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, const struct timespec *timeout, const sigset_t *sigmask)
{
	int n;
	if ((n = pselect (n, readfds, writefds, exceptfds, timeout, sigmask)) == -1)
	{
		wp_sys_func_warning ();
	}
	return n;
}
#endif /* __USE_XOPEN2k */

int wp_poll (struct pollfd *fds, unsigned int nfds, int timeout)
{
	int n;
	if ((n = poll (fds, nfds, timeout)) == -1)
	{
		wp_sys_func_warning ();
	}
	return n;
}

#ifdef HAVE_SYS_EPOLL_H
int wp_epoll_create (int size)
{
	int n;
	if ((n = epoll_create (size)) == -1)
	{
		wp_sys_func_warning ();
	}
	return n;
}

int wp_epoll_ctl (int epfd, int op, int fd, struct epoll_event *event)
{
	int n;
	if ((n = epoll_ctl (epfd, op, fd, event)) == -1)
	{
		wp_sys_func_warning ();
	}
	return n;
}

int wp_epoll_wait (int epfd, struct epoll_event *events, int maxevents, int timeout)
{
	int n;
	if ((n = epoll_wait (epfd, events, maxevents, timeout)) == -1)
	{
		wp_sys_func_warning ();
	}
	return n;
}
#endif /* HAVE_SYS_EPOLL_H */

int wp_gettimeofday (struct timeval *tv, struct timezone *tz)
{
	int n;
	if ((n = gettimeofday (tv, tz)) == -1)
		wp_sys_func_warning ();
	return n;
}

int wp_settimeofday (const struct timeval *tv, const struct timezone *tz)
{
	int n;
	if ((n = settimeofday (tv, tz)) == -1)
		wp_sys_func_warning ();
	return n;
}

clock_t times (struct tms *buf)
{
	clock_t t;
	if ((t = times (buf)) == (clock_t)-1)
		wp_sys_func_warning ();
	return t;
}

#ifdef _SVID_SOURCE
int wp_stime (time_t *t)
{
	int n;
	if ((n = stime (t)) == -1)
		wp_sys_func_warning ();
	return n;
}
#endif /* _SVID_SOURCE */

int wp_getitimer (int which, struct itimerval *value)
{
	int n;
	if ((n = getitimer (which, value)) == -1)
		wp_sys_func_warning ();
	return n;
}

int wp_setitimer (int which, struct itimerval *value, struct itimerval *ovalue)
{
	int n;
	if ((n = setitimer (which, value, ovalue)) == -1)
		wp_sys_func_warning ();
	return n;
}

void wp_check_exit_status (int status)
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

WpTimer *wp_timer_new ()
{
	return (WpTimer *)wp_malloc (sizeof (WpTimer));
}

void wp_timer_free (WpTimer *t)
{
	assert (t != NULL);
	free (t);
}


void wp_timer_start (WpTimer *t)
{
	assert (t != NULL);
	gettimeofday (t, NULL);
}

double wp_timer_elapse (WpTimer *t)
{
	struct timeval tfinish;
	long sec, usec;

	assert (t != NULL);

	gettimeofday (&tfinish, NULL);
	sec = tfinish.tv_sec - t->tv_sec;
	usec = tfinish.tv_usec - t->tv_usec;
	return sec + 1e-6*usec;
}

int wp_fd_create (const char *pathname, mode_t mode)
{
	return wp_open (pathname, O_RDWR | O_CREAT | O_TRUNC, mode);
}

int wp_fd_alloc (const char *pathname, mode_t mode, off_t offset)
{
	int fd;
	fd = wp_open (pathname, O_RDWR | O_CREAT | O_TRUNC, mode);
	wp_lseek (fd, offset, SEEK_SET);
	return fd;
}

int wp_fd_append (int filedes, off_t offset)
{
	wp_lseek (filedes, offset, SEEK_CUR);
	return filedes;
}

void wp_fd_set_flag (int fd, int flags)
{
	int val;

	val = wp_fcntl (fd, F_GETFL, 0);
	val |= flags;
	wp_fcntl (fd, F_SETFL, val);
}

void wp_fd_clear_flag (int fd, int flags)
{
	int val;

	val = wp_fcntl (fd, F_GETFL, 0);
	val &= ~flags;
	wp_fcntl (fd, F_SETFL, val);
}

bool wp_fd_is_flag_set (int fd, int flag)
{
	int val;

	val = wp_fcntl (fd, F_GETFL, 0);
	return (val & flag);
}

void wp_dopath (char *path, wp_dopath_func func, void *data)
{
	struct stat statbuf;
	struct dirent *dirp;
	DIR *dp;
	char *ptr;

	if (wp_lstat (path, &statbuf) == -1)
		return;
	if (S_ISDIR (statbuf.st_mode) == 0)
		func (path, data);

	ptr = path + strlen (path);
	*ptr++ = '/';
	*ptr = 0;

	if ((dp = wp_opendir (path)) == NULL)
		return;

	while ((dirp = readdir (dp)) != NULL)
	{
		if (strcmp (dirp->d_name, ".") == 0 || 
				strcmp (dirp->d_name, "..") == 0)
			continue;

		strcpy (ptr, dirp->d_name);
		wp_dopath (path, func, data);
	}

	ptr[-1] = 0;

	wp_closedir (dp);
}
