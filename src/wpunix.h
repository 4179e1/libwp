#ifndef _WPUNIX_H
#define _WPUNIX_H

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif /* HAVE_CONFIG_H */

#include <pwd.h>
#include <shadow.h>
#include <grp.h>
#include <unistd.h>
#include <sys/utsname.h>
#include <sys/resource.h>
#include <sys/times.h>
#include <sys/uio.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <signal.h>
#include <stdio.h>
#include <limits.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdbool.h>
#include <dirent.h>
#include <utime.h>
#include <sys/select.h>
#include <sys/poll.h>
#include <sys/time.h>

#ifdef HAVE_SYS_EPOLL_H
#include <sys/epoll.h>
#endif /* HAVE_SYS_EPOLL_H */

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

struct passwd *wp_getpwuid (uid_t uid);
struct passwd *wp_getpwanam (const char *name);
struct passwd *wp_getpwent (void);

struct spwd *wp_getspnam (const char *name);
struct spwd *wp_getspent (void);

struct group *wp_getgrgid (gid_t gid);
struct group *wp_getgrnam (const char *name);
struct group *wp_getgrent (void);

int wp_getgroups (int gidsetsize, gid_t grouplist[]);
int wp_setgroups (int ngroups, const gid_t grouplist[]);
int wp_initgroups (const char *username, gid_t basegid);

int wp_uname (struct utsname *name);
int wp_gethostname (char *name, int namelen);

int wp_getrlimit (int resource, struct rlimit *rlptr);
int wp_setrlimit (int resource, const struct rlimit *rlptr);

int wp_execv (const char *path, char *const argv[]);
int wp_execvp (const char *file, char *const argv[]);
int wp_execve (const char *path, char *const argv[], char *const envp[]);

pid_t wp_fork (void);
pid_t wp_wait (int *statloc);
pid_t wp_waitpid (pid_t pid, int *statloc, int options);

int wp_setuid (uid_t uid);
int wp_setgid (gid_t gid);
int wp_setreuid (uid_t ruid, uid_t euid);
int wp_setregid (gid_t rgid, gid_t egid);
int wp_seteuid (uid_t uid);
int wp_setegid (gid_t gid);

int wp_system (const char *cmd);

char *wp_getlogin (void);

clock_t wp_times (struct tms *buf);

int wp_setpgid (pid_t pid, pid_t pgid);

pid_t wp_setsid (void);
pid_t wp_getsid (pid_t pid);

int wp_kill (pid_t pid, int signo);
int wp_killpg (pid_t pid, int signo);
int wp_raise (int signo);

int wp_sigemptyset (sigset_t *set);
int wp_sigfillset (sigset_t *set);
int wp_sigaddset (sigset_t *set, int signo);
int wp_sigdelset (sigset_t *set, int signo);
int wp_sigismember (const sigset_t *set, int signo);
int wp_sigprocmask (int how, const sigset_t *set, sigset_t *oset);
int wp_sigpending (sigset_t *set);
int wp_sigaction (int signo, const struct sigaction *act, struct sigaction *oact);
int wp_sigqueue (pid_t pid, int signo, const union sigval value);

int wp_sigsuspend (const sigset_t *sigmask);

int wp_sigwait (const sigset_t *set, int *signop);

ssize_t wp_readv (int filedes, const struct iovec *iov, int iovcnt);
ssize_t wp_writev (int filedes, const struct iovec *iov, int iovcnt);

void *wp_mmap (void *addr, size_t len, int prot, int flag, int filedes, off_t off);
int wp_mprotect (void *addr, size_t len, int prot);
int wp_msync (void *addr, size_t len, int flags);
int wp_munmap (caddr_t addr, size_t len);
#ifdef _GUN_SOURCE
void *wp_mremap (void *old_address, size_t old_size, size_t new_size, int flags, void *new_address);
#endif /* _GUN_SOURCE */
int wp_posix_fadvise (int fd, off_t offset, off_t len, int advice);

int wp_pipe (int filedes[2]);

int wp_mkfifo (const char *pathname, mode_t mode);

key_t wp_ftok (const char *path, int id);

int wp_msgget (key_t key, int flag);
int wp_msgctl (int msqid, int cmd, struct msqid_ds *buf);
int wp_msgsnd (int msqid, const void *ptr, size_t nbytes, int flag);
ssize_t wp_msgrcv (int msqid, void *ptr, size_t nbytes, long type, int flag);

int wp_semget (key_t key, int nsems, int flag);
#if 0
int wp_semctl (int semid, int semnum, int cmd, union semun arg);
#endif
int wp_semop (int semid, struct sembuf semoparray[], size_t nops);

int wp_shmctl (int shmid, int cmd, struct shmid_ds *buf);
void *wp_shmat (int shmid, const void *addr, int flag);
int wp_shmdt (void *addr);

int wp_select (int nfds, fd_set *readfds, fd_set *writefds, fd_set *errorfds, struct timeval *timeout);
#ifdef __USE_XOPEN2k
int wp_pselect (int n, fd_set *readfds, fd_set *writefds, fd_set *execptfds, const struct timespec *timeout, const sigset_t *sigmask);
#endif /* __USE_XOPEN2k */
int wp_poll (struct pollfd *fds, unsigned int nfds, int timeout);

#ifdef HAVE_SYS_EPOLL_H
int wp_epoll_create (int size);
int wp_epoll_ctl (int epfd, int op, int fd, struct epoll_event *event);
int wp_epoll_wait (int epfd, struct epoll_event *events, int maxevents, int timeout);
#endif /* HAVE_SYS_EPOLL_H */

#ifdef HAVE_SYS_INOTIFY_H
int wp_inotify_init (void);
int wp_inotify_add_watch (int fd, const char *path, uint32_t mask);
int wp_inotify_rm_watch (int fd, uint32_t wd);
#endif /* HAVE_SYS_INOTIFY_H */

#ifdef __USE_UNIX98
/* aton operate, lseek and read/write */
ssize_t wp_pread (int filedes, void *buf, size_t nbytes, off_t offset);
ssize_t wp_pwrite (int filedes, void *but, size_t nbytes, off_t offset);
#endif /* __USE_UNIX98 */

/* utilities */
void wp_check_exit_status (int status);
ssize_t wp_readn (int fd, void *ptr, size_t n);
ssize_t wp_writen (int fd, void *ptr, size_t n);

/***************************************
 * wp file io
 **************************************/
int wp_access (const char *pathname, int mode);
int wp_chmod (const char *pathname, mode_t mode);
int wp_chown (const char *pathname, uid_t owner, gid_t group);
int wp_close (int filedes);
int wp_creat (const char *pathname, mode_t mode);
int wp_dup (int filedes);
int wp_dup2 (int filedes, int filedes2);

int wp_fchmod (int filedes, mode_t mode);
int wp_fchown (int filedes, uid_t user, gid_t group);
int wp_fcntl (int filedes, int cmd, int arg);
int wp_fdatasync (int filedes);
int wp_fstat (int filedes, struct stat *buf);
int wp_fsync (int filedes);
int wp_ftruncate (int filedes, off_t length);
int wp_ioctl (int filedes, int request, void *arg);
off_t wp_lseek (int filedes, off_t offset, int whence);
int wp_lchown (const char *pathname, uid_t owenr, gid_t group);
int wp_link (const char *exsitingpath, const char *newpath);
int wp_lstat (const char *pathname, struct stat *buf);
int wp_open (const char *pathname, int oflag, mode_t mode);
ssize_t wp_read (int filedes, void *buf, size_t nbytes);
ssize_t wp_readlink (const char *pathname, char *bug, size_t bufsize);
int wp_stat (const char *pathname, struct stat *buf);
int wp_symlink (const char *actualpath, const char *sympath);
int wp_truncate (const char *pathname, off_t length);
int wp_unlink (const char *pathname);
int wp_utime (const char *pathname, const struct utimbuf *times);
ssize_t wp_write (int filedes, const void *buf, size_t nbytes);

int wp_mlock (const void *addr, size_t len);
int wp_mlockall (int flags);
int wp_munlock (const void *addr, size_t len);
int wp_munlockall (void);

#ifdef HAVE_ATTR_XATTR_H
ssize_t wp_getxattr (const char *path, const char *key, void *value, size_t size);
ssize_t wp_lgetxattr (const char *path, const char *key, void *value, size_t size);
ssize_t wp_fgetxattr (int fd, const char *key, void *value, size_t size);

int wp_setxattr (const char *path, const char *key, const void *value, size_t size, int flags);
int wp_lsetxattr (const char *path, const char *key, const void *value, size_t size, int flags);
int wp_fsetxattr (int fd, const char *key, const void *value, size_t size, int flags);

ssize_t wp_listxattr (const char *path, char *list, size_t size);
ssize_t wp_llistxattr (const char *path, char *list, size_t size);
ssize_t wp_flistxattr (int fd, char *list, size_t size);

int wp_removexattr (const char *path, const char *key);
int wp_lremovexattr (const char *path, const char *key);
int wp_femovexattr (int fd, const char *key);

#endif /* HAVE_ATTR_XATTR_H */

/**************************************
 * wp io utilities
 *************************************/
int wp_fd_create (const char *pathname, mode_t mode);
int wp_fd_alloc (const char *pathname, mode_t mode, off_t offset);
int wp_fd_append (int filedes, off_t offset);

void wp_fd_set_flag (int fd, int flags);
void wp_fd_clear_flag (int fd, int flags);
bool wp_fd_is_flag_set (int fd, int flag);

typedef void (*wp_dopath_func) (const char *path, void *data);
void wp_dopath (char *path, wp_dopath_func func, void *data);

/**************************************
 * wp file utilities
 *************************************/
int wp_chdir (const char *pathname);
int wp_closedir (DIR *dp);
int wp_fchdir (int filedes);

char *wp_getcwd (char *bug, size_t size);
int wp_mkdir (const char *pathname, mode_t mode);
DIR *wp_opendir (const char *pathname);
struct dirent *wp_readdir (DIR *dp);
int wp_rmdir (const char *pathname);

ssize_t wp_readv (int filedes, const struct iovec *iov, int iovcnt);
ssize_t wp_writev (int filedes, const struct iovec *iov, int iovcnt);

int wp_gettimeofday (struct timeval *tv, struct timezone *tz);
int wp_settimeofday (const struct timeval *tv, const struct timezone *tz);
clock_t times (struct tms *buf);

int wp_getitimer (int which, struct itimerval *value);
int wp_setitimer (int which, struct itimerval *value, struct itimerval *ovalue);

int wp_nanosleep (const struct timespec *req, struct timespec *rem);

#ifdef _SVID_SOURCE
int wp_stime (time_t *t);
#endif /* _SVID_SOURCE */

/*************************************
 * wp timer utilities
 ************************************/

typedef struct timeval WpTimer;

WpTimer *wp_timer_new ();
void wp_timer_free (WpTimer *t);
void wp_timer_start (WpTimer *t);
double wp_timer_elapse (WpTimer *t);


/*************************************
 * wp timer utilities
 ************************************/
typedef struct _rio wp_rio_t;

wp_rio_t *_wp_rio_new (int fd);
void _wp_rio_free (wp_rio_t* rp);

/* b for buffer */
ssize_t _wp_rio_readlineb (wp_rio_t *rp, void *usrbuf, size_t maxlen);
ssize_t _wp_rio_readnb (wp_rio_t *rp, void *usrbuf, size_t n);
ssize_t _wp_rio_writen (wp_rio_t *rp, void *ptr, size_t n);
#define _wp_rio_readline _wp_rio_readlineb
#define _wp_rio_readn _wp_rio_readnb

ssize_t _wp_readn (int fd, void *ptr, size_t n);
ssize_t _wp_writen (int fd, void *ptr, size_t n);
ssize_t wp_readn (int fd, void *ptr, size_t n);
ssize_t wp_writen (int fd, void *ptr, size_t n);

int wp_rio_getfd (wp_rio_t *rp);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _WPUNIX_H */
