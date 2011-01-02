#ifndef _WPUNIX_H
#define _WPUNIX_H

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
#include "wpunix_rio.h"

struct passwd *_wp_getpwuid (uid_t uid);
struct passwd *_wp_getpwanam (const char *name);
struct passwd *_wp_getpwent (void);

struct spwd *_wp_getspnam (const char *name);
struct spwd *_wp_getspent (void);

struct group *_wp_getgrgid (gid_t gid);
struct group *_wp_getgrnam (const char *name);
struct group *_wp_getgrent (void);

int _wp_getgroups (int gidsetsize, gid_t grouplist[]);
int _wp_setgroups (int ngroups, const gid_t grouplist[]);
int _wp_initgroups (const char *username, gid_t basegid);

int _wp_uname (struct utsname *name);
int _wp_gethostname (char *name, int namelen);

int _wp_getrlimit (int resource, struct rlimit *rlptr);
int _wp_setrlimit (int resource, const struct rlimit *rlptr);

pid_t _wp_fork (void);
pid_t _wp_wait (int *statloc);
pid_t _wp_waitpid (pid_t pid, int *statloc, int options);

int _wp_setuid (uid_t uid);
int _wp_setgid (gid_t gid);
int _wp_setreuid (uid_t ruid, uid_t euid);
int _wp_setregid (gid_t rgid, gid_t egid);
int _wp_seteuid (uid_t uid);
int _wp_setegid (gid_t gid);

int _wp_system (const char *cmd);

char *_wp_getlogin (void);

clock_t _wp_times (struct tms *buf);

int _wp_setpgid (pid_t pid, pid_t pgid);

pid_t _wp_setsid (void);
pid_t _wp_getsid (pid_t pid);

void (*_wp_signal (int signo, void (*func)(int)))(int);

int _wp_kill (pid_t pid, int signo);
int _wp_raise (int signo);

int _wp_sigemptyset (sigset_t *set);
int _wp_sigfillset (sigset_t *set);
int _wp_sigaddset (sigset_t *set, int signo);
int _wp_sigdelset (sigset_t *set, int signo);
int _wp_sigismember (const sigset_t *set, int signo);
int _wp_sigprocmask (int how, const sigset_t *set, sigset_t *oset);
int _wp_sigpending (sigset_t *set);
int _wp_sigaction (int signo, const struct sigaction *act, struct sigaction *oact);

int _wp_sigsuspend (const sigset_t *sigmask);

int _wp_sigwait (const sigset_t *set, int *signop);

ssize_t _wp_readv (int filedes, const struct iovec *iov, int iovcnt);
ssize_t _wp_writev (int filedes, const struct iovec *iov, int iovcnt);

void *_wp_mmap (void *addr, size_t len, int prot, int flag, int filedes, off_t off);
int _wp_mprotect (void *addr, size_t len, int prot);
int _wp_msync (void *addr, size_t len, int flags);
int _wp_munmap (caddr_t addr, size_t len);

int _wp_pipe (int filedes[2]);

int _wp_mkfifo (const char *pathname, mode_t mode);

key_t _wp_ftok (const char *path, int id);

int _wp_msgget (key_t key, int flag);
int _wp_msgctl (int msqid, int cmd, struct msqid_ds *buf);
int _wp_msgsnd (int msqid, const void *ptr, size_t nbytes, int flag);
ssize_t _wp_msgrcv (int msqid, void *ptr, size_t nbytes, long type, int flag);

int _wp_semget (key_t key, int nsems, int flag);
#if 0
int _wp_semctl (int semid, int semnum, int cmd, union semun arg);
#endif
int _wp_semop (int semid, struct sembuf semoparray[], size_t nops);

int _wp_shmctl (int shmid, int cmd, struct shmid_ds *buf);
void *_wp_shmat (int shmid, const void *addr, int flag);
int _wp_shmdt (void *addr);

/* utilities */
void _wp_check_exit_status (int status);
ssize_t _wp_readn (int fd, void *ptr, size_t n);
ssize_t _wp_writen (int fd, void *ptr, size_t n);

/************************************
 * _wpfileio
 ***********************************/

#ifdef __USE_UNIX98
/* aton operate, lseek and read/write */
ssize_t _wp_pread (int filedes, void *buf, size_t nbytes, off_t offset);
ssize_t _wp_pwrite (int filedes, void *but, size_t nbytes, off_t offset);
#endif /* __USE_UNIX98 */


/***************************************
 * _wp file io
 **************************************/
int _wp_access (const char *pathname, int mode);
int _wp_chmod (const char *pathname, mode_t mode);
int _wp_chown (const char *pathname, uid_t owner, gid_t group);
int _wp_close (int filedes);
int _wp_creat (const char *pathname, mode_t mode);
int _wp_dup (int filedes);
int _wp_dup2 (int filedes, int filedes2);

int _wp_fchmod (int filedes, mode_t mode);
int _wp_fchown (int filedes, uid_t user, gid_t group);
int _wp_fcntl (int filedes, int cmd, int arg);
int _wp_fdatasync (int filedes);
int _wp_fstat (int filedes, struct stat *buf);
int _wp_fsync (int filedes);
int _wp_ftruncate (int filedes, off_t length);
int _wp_ioctl (int filedes, int request, void *arg);
off_t _wp_lseek (int filedes, off_t offset, int whence);
int _wp_lchown (const char *pathname, uid_t owenr, gid_t group);
int _wp_link (const char *exsitingpath, const char *newpath);
int _wp_lstat (const char *pathname, struct stat *buf);
int _wp_open (const char *pathname, int oflag, mode_t mode);
ssize_t _wp_read (int filedes, void *buf, size_t nbytes);
ssize_t _wp_readlink (const char *pathname, char *bug, size_t bufsize);
int _wp_stat (const char *pathname, struct stat *buf);
int _wp_symlink (const char *actualpath, const char *sympath);
int _wp_truncate (const char *pathname, off_t length);
int _wp_unlink (const char *pathname);
int _wp_utime (const char *pathname, const struct utimbuf *times);
ssize_t _wp_write (int filedes, const void *buf, size_t nbytes);

/**************************************
 * _wp io utilities
 *************************************/
int _wp_fd_create (const char *pathname, mode_t mode);
int _wp_fd_alloc (const char *pathname, mode_t mode, off_t offset);
int _wp_fd_append (int filedes, off_t offset);

void _wp_fd_set_flag (int fd, int flags);
void _wp_fd_clear_flag (int fd, int flags);
bool _wp_fd_is_flag_set (int fd, int flag);

typedef void (*_wp_dopath_func) (const char *path, void *data);
void _wp_dopath (char *path, _wp_dopath_func func, void *data);

/**************************************
 * _wp file utilities
 *************************************/
int _wp_chdir (const char *pathname);
int _wp_closedir (DIR *dp);
int _wp_fchdir (int filedes);

char *_wp_getcwd (char *bug, size_t size);
int _wp_mkdir (const char *pathname, mode_t mode);
DIR *_wp_opendir (const char *pathname);
struct dirent *_wp_readdir (DIR *dp);
int _wp_rmdir (const char *pathname);

ssize_t _wp_readv (int filedes, const struct iovec *iov, int iovcnt);
ssize_t _wp_writev (int filedes, const struct iovec *iov, int iovcnt);

/*************************************
 * _wp timer utilities
 ************************************/

typedef struct timeval WpTimer;

WpTimer *_wp_timer_new ();
void _wp_timer_free (WpTimer *t);
void _wp_timer_start (WpTimer *t);
double _wp_timer_elapse (WpTimer *t);


#endif /* _WPUNIX_H */
