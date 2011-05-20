#ifndef _WPSTDC_H
#define _WPSTDC_H

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif /* HAVE_CONFIG_H */

#include <stdio.h>
#include <unistd.h>
#include <stdarg.h>
#include <time.h>
#include <signal.h>

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

int wp_fclose (FILE *fp);
FILE *wp_fdopen (int filedes, const char *type);
int wp_fgetc (FILE *fp);
char *wp_fgets (char *buf, int n, FILE *fp);
int wp_fputc (int c, FILE *fp);
int wp_fputs (const char *str, FILE *fp);
int wp_fflush (FILE *fp);
FILE *wp_fopen (const char *pathname, const char *type);
size_t wp_fread (void *ptr, size_t size, size_t nobj, FILE *fp);
FILE *wp_freopen (const char *pathname, const char *type, FILE *fp);
int wp_getc (FILE *fp);
int wp_getchar (void);
int wp_putc (int c, FILE *fp);
int wp_putchar (int c);
int wp_remove (const char *pathname);
int wp_rename (const char *oldname, const char *newname);
int wp_setvbuf (FILE *fp, char *buf, int mode, size_t size);
int wp_ungetc (int c, FILE *fp);
size_t wp_fwrite (const void *ptr, size_t size, size_t nobj, FILE *fp);

long wp_ftell (FILE *fp);
int wp_fseek (FILE *fp, long offset, int whence);
off_t wp_ftello (FILE *fp);
int wp_fseeko (FILE *fp, off_t offset, int whence);
int wp_fgetpos (FILE *fp, fpos_t *pos);
int wp_fsetpos (FILE *fp, fpos_t *pos);

int wp_vprintf (const char *fmt, va_list arg);
int wp_vfprintf (FILE *fp, const char *fmt, va_list arg);
int wp_vsprintf (char *buf, const char *fmt, va_list arg);
int wp_vsnprintf (char *buf, size_t n, const char *fmt, va_list arg);

int wp_vscanf (const char *format, va_list arg);
int wp_vfscanf (FILE *fp, const char *fmt, va_list arg);
int wp_vsscanf (const char *buf, const char *fmt, va_list arg);

FILE *wp_tmpfile (void);
int wp_mkstemp (char *template);

FILE *wp_popen (const char *cmdstring, const char *type);
int wp_pclose (FILE *fp);

time_t wp_time (time_t *calptr);
time_t wp_mktime (struct tm *tmptr);

int wp_atexit (void (*func) (void));

void *wp_malloc (size_t size);
void *wp_calloc (size_t nobj, size_t size);
void *wp_realloc (void *ptr, size_t newsize);
int wp_posix_memalign (void **memptr, size_t alignment, size_t size);

char *wp_getenv (const char *name);
int wp_putenv (char *str);
int wp_setenv (const char *name, const char *value, int rewrite);
int wp_unsetenv (const char *name);

int wp_clock_getres (clockid_t clock_id, struct timespec *res);
int wp_clock_gettime (clockid_t clock_id, struct timespec *ts);
int wp_clock_settime (clockid_t clock_id, struct timespec *ts);

void (*wp_signal (int signo, void (*func)(int)))(int);

int wp_timer_create (clockid_t clockid, struct sigevent *evp, timer_t *timerid);
int wp_timer_settime (timer_t timerid, int flags, const struct itimerspec *value, struct itimerspec *ovalue);
int wp_timer_gettime (timer_t timerid, struct itimerspec *value);
int wp_timer_getoverrun (timer_t timerid);
int wp_timer_delete (timer_t timerid);

char *wp_asctime (const struct tm *tm);
char *wp_asctime_r (const struct tm *tm, char *buf);
char *wp_ctime (const time_t *timep);
char *wp_ctime_r (const time_t *timep, char *buf);
struct tm *wp_gmtime (const time_t *timep);
struct tm *wp_gmtime_r (const time_t *timep, struct tm *result);
struct tm *wp_localtime (const time_t *timep);
struct tm *wp_localtime_r (const time_t *timep, struct tm *result);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _WPSTDC_H */
