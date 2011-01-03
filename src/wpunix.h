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
#include <wpunix_rio.h>

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */


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

#ifdef DIASABLE_WP
#define wp_getpwuid getpwuid
#define wp_getpwanam getpwanam
#define wp_getpwent getpwent
#define wp_getspnam getspnam
#define wp_getspent getspent
#define wp_getgrgid getgrgid
#define wp_getgrnam getgrnam
#define wp_getgrent getgrent
#define wp_getgroups getgroups
#define wp_setgroups setgroups
#define wp_initgroups initgroups
#define wp_uname uname
#define wp_gethostname gethostname
#define wp_getrlimit getrlimit
#define wp_setrlimit setrlimit
#define wp_fork fork
#define wp_wait wait
#define wp_waitpid waitpid
#define wp_setuid setuid
#define wp_setgid setgid
#define wp_setreuid setreuid
#define wp_setregid setregid
#define wp_seteuid seteuid
#define wp_setegid setegid
#define wp_system system
#define wp_getlogin getlogin
#define wp_times times
#define wp_setpgid setpgid
#define wp_setsid setsid
#define wp_getsid getsid
#define wp_signal signal
#define wp_kill kill
#define wp_raise raise
#define wp_sigemptyset sigemptyset
#define wp_sigfillset sigfillset
#define wp_sigaddset sigaddset
#define wp_sigdelset sigdelset
#define wp_sigismember sigismember
#define wp_sigprocmask sigprocmask
#define wp_sigpending sigpending
#define wp_sigaction sigaction
#define wp_sigsuspend sigsuspend
#define wp_sigwait sigwait
#define wp_readv readv
#define wp_writev writev
#define wp_mmap mmap
#define wp_mprotect mprotect
#define wp_msync msync
#define wp_munmap munmap
#define wp_pipe pipe
#define wp_mkfifo mkfifo
#define wp_ftok ftok
#define wp_msgget msgget
#define wp_msgctl msgctl
#define wp_msgsnd msgsnd
#define wp_msgrcv msgrcv
#define wp_semget semget
#define wp_semop semop
#define wp_shmctl shmctl
#define wp_shmat shmat
#define wp_shmdt shmdt
#define wp_check_exit_status check_exit_status
#define wp_readn readn
#define wp_writen writen
#ifdef __USE_UNIX98
#define wp_pread pread
#define wp_pwrite pwrite
#endif /* __USE_UNIX98 */
#define wp_access access
#define wp_chmod chmod
#define wp_chown chown
#define wp_close close
#define wp_creat creat
#define wp_dup dup
#define wp_dup2 dup2
#define wp_fchmod fchmod
#define wp_fchown fchown
#define wp_fcntl fcntl
#define wp_fdatasync fdatasync
#define wp_fstat fstat
#define wp_fsync fsync
#define wp_ftruncate ftruncate
#define wp_ioctl ioctl
#define wp_lseek lseek
#define wp_lchown lchown
#define wp_link link
#define wp_lstat lstat
#define wp_open open
#define wp_read read
#define wp_readlink readlink
#define wp_stat stat
#define wp_symlink symlink
#define wp_truncate truncate
#define wp_unlink unlink
#define wp_utime utime
#define wp_write write
#define wp_chdir chdir
#define wp_closedir closedir
#define wp_fchdir fchdir
#define wp_getcwd getcwd
#define wp_mkdir mkdir
#define wp_opendir opendir
#define wp_readdir readdir
#define wp_rmdir rmdir
#define wp_readv readv
#define wp_writev writev
#else
#define wp_getpwuid _wp_getpwuid
#define wp_getpwanam _wp_getpwanam
#define wp_getpwent _wp_getpwent
#define wp_getspnam _wp_getspnam
#define wp_getspent _wp_getspent
#define wp_getgrgid _wp_getgrgid
#define wp_getgrnam _wp_getgrnam
#define wp_getgrent _wp_getgrent
#define wp_getgroups _wp_getgroups
#define wp_setgroups _wp_setgroups
#define wp_initgroups _wp_initgroups
#define wp_uname _wp_uname
#define wp_gethostname _wp_gethostname
#define wp_getrlimit _wp_getrlimit
#define wp_setrlimit _wp_setrlimit
#define wp_fork _wp_fork
#define wp_wait _wp_wait
#define wp_waitpid _wp_waitpid
#define wp_setuid _wp_setuid
#define wp_setgid _wp_setgid
#define wp_setreuid _wp_setreuid
#define wp_setregid _wp_setregid
#define wp_seteuid _wp_seteuid
#define wp_setegid _wp_setegid
#define wp_system _wp_system
#define wp_getlogin _wp_getlogin
#define wp_times _wp_times
#define wp_setpgid _wp_setpgid
#define wp_setsid _wp_setsid
#define wp_getsid _wp_getsid
#define wp_signal _wp_signal
#define wp_kill _wp_kill
#define wp_raise _wp_raise
#define wp_sigemptyset _wp_sigemptyset
#define wp_sigfillset _wp_sigfillset
#define wp_sigaddset _wp_sigaddset
#define wp_sigdelset _wp_sigdelset
#define wp_sigismember _wp_sigismember
#define wp_sigprocmask _wp_sigprocmask
#define wp_sigpending _wp_sigpending
#define wp_sigaction _wp_sigaction
#define wp_sigsuspend _wp_sigsuspend
#define wp_sigwait _wp_sigwait
#define wp_readv _wp_readv
#define wp_writev _wp_writev
#define wp_mmap _wp_mmap
#define wp_mprotect _wp_mprotect
#define wp_msync _wp_msync
#define wp_munmap _wp_munmap
#define wp_pipe _wp_pipe
#define wp_mkfifo _wp_mkfifo
#define wp_ftok _wp_ftok
#define wp_msgget _wp_msgget
#define wp_msgctl _wp_msgctl
#define wp_msgsnd _wp_msgsnd
#define wp_msgrcv _wp_msgrcv
#define wp_semget _wp_semget
#define wp_semop _wp_semop
#define wp_shmctl _wp_shmctl
#define wp_shmat _wp_shmat
#define wp_shmdt _wp_shmdt
#define wp_check_exit_status _wp_check_exit_status
#define wp_readn _wp_readn
#define wp_writen _wp_writen
#ifdef __USE_UNIX98
#define wp_pread _wp_pread
#define wp_pwrite _wp_pwrite
#endif /* __USE_UNIX98 */
#define wp_access _wp_access
#define wp_chmod _wp_chmod
#define wp_chown _wp_chown
#define wp_close _wp_close
#define wp_creat _wp_creat
#define wp_dup _wp_dup
#define wp_dup2 _wp_dup2
#define wp_fchmod _wp_fchmod
#define wp_fchown _wp_fchown
#define wp_fcntl _wp_fcntl
#define wp_fdatasync _wp_fdatasync
#define wp_fstat _wp_fstat
#define wp_fsync _wp_fsync
#define wp_ftruncate _wp_ftruncate
#define wp_ioctl _wp_ioctl
#define wp_lseek _wp_lseek
#define wp_lchown _wp_lchown
#define wp_link _wp_link
#define wp_lstat _wp_lstat
#define wp_open _wp_open
#define wp_read _wp_read
#define wp_readlink _wp_readlink
#define wp_stat _wp_stat
#define wp_symlink _wp_symlink
#define wp_truncate _wp_truncate
#define wp_unlink _wp_unlink
#define wp_utime _wp_utime
#define wp_write _wp_write
#define wp_chdir _wp_chdir
#define wp_closedir _wp_closedir
#define wp_fchdir _wp_fchdir
#define wp_getcwd _wp_getcwd
#define wp_mkdir _wp_mkdir
#define wp_opendir _wp_opendir
#define wp_readdir _wp_readdir
#define wp_rmdir _wp_rmdir
#define wp_readv _wp_readv
#define wp_writev _wp_writev
#endif /* DISABLE_WP */


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _WPUNIX_H */
