#ifdef HAVE_CONFIG_H
#include <config.h>
#endif /* HAVE_CONFIG_H */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "wpstdc.h"
#include "wpbase.h"

int wp_fclose (FILE *fp)
{
	int n;
	if ((n = fclose (fp)) == EOF)
		wp_func_warning();
	return n;
}

FILE *wp_fdopen (int filedes, const char *type)
{
	FILE *file;
	if ((file = fdopen (filedes, type)) == NULL)
		wp_func_warning();
	return file;
}

int wp_fgetc (FILE *fp)
{
	int n;
	clearerr (fp);
	n = fgetc (fp);
	if (n == EOF && ferror (fp))
		wp_func_warning();
	return n;
}

char *wp_fgets (char *buf, int n, FILE *fp)
{
	char *str;
	if (((str = fgets (buf, n, fp)) == NULL) && ferror (fp))
		wp_func_warning();
	return str;
}

int wp_fputc (int c, FILE *fp)
{
	int n;
	if ((n = fputc (c, fp)) == EOF)
		wp_func_warning();
	return n;
}

int wp_fputs (const char *str, FILE *fp)
{
	int n;
	if ((n = fputs (str, fp)) == EOF)
		wp_func_warning();
	return n;
}

int wp_fflush (FILE *fp)
{
	int n;
	if ((n = fflush (fp)) == EOF)
		wp_func_warning();
	return n;
}

FILE *wp_fopen (const char *path, const char *type)
{
	FILE *file;
	if ((file = fopen (path, type)) == NULL)
		wp_warning ("%s(%s) error: %s", __func__, path, strerror (errno));
	return file;
}

size_t wp_fread (void *ptr, size_t size, size_t nobj, FILE *fp)
{
	size_t n;

	clearerr (fp);
	n = fread (ptr, size, nobj, fp);
	if (ferror (fp))
		wp_func_warning();
	return n;
}

FILE *wp_freopen (const char *pathname, const char *type, FILE *fp)
{
	FILE *file;
	if ((file = freopen (pathname, type, fp)) == NULL)
		wp_func_warning();
	return file;
}

int wp_getc (FILE *fp)
{
	int n;
	clearerr (fp);
	n = getc (fp);
	if (n == EOF && ferror(fp))
		wp_func_warning();
	return n;
}

int wp_getchar (void)
{
	int n;
	clearerr (stdin);
	n = getchar ();
	if (n == EOF && ferror (stdin))
		wp_func_warning();
	return n;
}

int wp_putc (int c, FILE *fp)
{
	int n;
	if ((n = putc (c, fp)) == EOF)
		wp_func_warning();
	return n;
}

int wp_putchar (int c)
{
	int n;
	if ((n = putchar (c)) == EOF)
		wp_func_warning();
	return n;
}

int wp_remove (const char *path)
{
	int n;
	if ((n = remove (path)) == -1)
		wp_func_warning();
	return n;
}

int wp_rename (const char *oldname, const char *newname)
{
	int n;
	if ((n = rename (oldname, newname)) == -1)
		wp_func_warning();
	return n;
}

int wp_setvbuf (FILE *fp, char *buf, int mode, size_t size)
{
	int n;
	if ((n = setvbuf (fp, buf, mode, size)) != 0)
		wp_func_warning();
	return n;
}

int wp_ungetc (int c, FILE *fp)
{
	int n;
	if ((n = ungetc (c, fp)) == EOF)
		wp_func_warning();
	return n;
}

size_t wp_fwrite (const void *ptr, size_t size, size_t nobj, FILE *fp)
{
	int n;
	clearerr (fp);
	n = fwrite (ptr, size, nobj, fp);
	if (ferror (fp))
		wp_func_warning();
	return n;
}

long wp_ftell (FILE *fp)
{
	long n;
	if ((n = ftell (fp)) == -1L)
		wp_func_warning();
	return n;
}

int wp_fseek (FILE *fp, long offset, int whence)
{
	int n;
	if ((n = fseek (fp, offset, whence)) != 0)
		wp_func_warning();
	return n;
}

off_t wp_ftello (FILE *fp)
{
	off_t n;
	if ((n = ftello (fp)) == -1)
		wp_func_warning();
	return n;
}

int wp_fseeko (FILE *fp, off_t offset, int whence)
{
	int n;
	if ((n = fseeko (fp, offset, whence)) !=0)
		wp_func_warning();
	return n;
}

int wp_fgetpos (FILE *fp, fpos_t *pos)
{
	int n;
	if ((n = fgetpos (fp, pos)) != 0)
		wp_func_warning();
	return n;
}

int wp_fsetpos (FILE *fp, fpos_t *pos)
{
	int n;
	if ((n = fsetpos (fp, pos)) != 0)
		wp_func_warning();
	return n;
}

int wp_vprintf (const char *fmt, va_list arg)
{
	int n;
	if ((n = wp_vprintf (fmt, arg)) < 0)
		wp_func_warning();
	return n;
}

int wp_vfprintf (FILE *fp, const char *fmt, va_list arg)
{
	int n;
	if ((n = vfprintf (fp, fmt, arg)) < 0)
		wp_func_warning();
	return n;
}

int wp_vsprintf (char *buf, const char *fmt, va_list arg)
{
	int n;
	if ((n = vsprintf (buf, fmt, arg)) < 0)
		wp_func_warning();
	return n;
}

int wp_vsnprintf (char *buf, size_t n, const char *fmt, va_list arg)
{
	int i;
	if ((i = vsnprintf (buf, n, fmt, arg)) < 0)
		wp_func_warning();
	return i;
}

int wp_vscanf (const char *format, va_list arg)
{
	int n;
	if ((n = vscanf (format, arg)) < 0)
		wp_func_warning();
	return n;
}

int wp_vfscanf (FILE *fp, const char *fmt, va_list arg)
{
	int n;
	if ((n = vfscanf (fp, fmt, arg)) < 0)
		wp_func_warning();
	return n;
}

int wp_vsscanf (const char *buf, const char *fmt, va_list arg)
{
	int n;
	if ((n = vsscanf (buf, fmt, arg)) < 0)
		wp_func_warning();
	return n;
}

FILE *wp_tmpfile (void)
{
	FILE *file;
	if ((file = tmpfile ()) == NULL)
		wp_func_warning();
	return file;
}

int wp_mkstemp (char *template)
{
	int n;
	if ((n = mkstemp (template)) == -1)
		wp_func_warning();
	return n;
}


FILE *wp_popen (const char *cmdstring, const char *type)
{
	FILE *fp;
	if ((fp = popen (cmdstring, type)) == NULL)
		wp_func_warning();
	return fp;
}

int wp_pclose (FILE *fp)
{
	int n;
	if ((n = pclose (fp)) == -1)
		wp_func_warning();
	return n;
}

time_t wp_time (time_t *calptr)
{
	time_t t;
	if ((t = time (calptr)) == -1)
		wp_func_warning();
	return t;
}

time_t wp_mktime (struct tm *tmptr)
{
	time_t t;
	if ((t = mktime (tmptr)) == -1)
		wp_func_warning();
	return t;
}

int wp_atexit (void (*func) (void))
{
	int n;
	if ((n = atexit (func)) != 0)
		wp_func_warning();
	return n;
}

void *wp_malloc (size_t size)
{
	void *ptr;
	if ((ptr = malloc (size)) == NULL)
		wp_func_warning();
	return ptr;
}

void *wp_calloc (size_t nobj, size_t size)
{
	void *ptr;
	if ((ptr = calloc (nobj, size)) == NULL)
		wp_func_warning();
	return ptr;
}

void *wp_realloc (void *ptr, size_t newsize)
{
	void *p;
	if ((p = realloc (ptr, newsize)) == NULL)
		wp_func_warning();
	return p;
}

int wp_posix_memalign (void **memptr, size_t alignment, size_t size)
{
	int n;
	if ((n = posix_memalign (memptr, alignment, size)) != 0)
		wp_posix_warning (n);
	return n;
}

char *wp_getenv (const char *name)
{
	char *str;
	if ((str = getenv (name)) == NULL)
		wp_func_warning();
	return str;
}

int wp_putenv (char *str)
{
	int n;
	if ((n = putenv (str)) != 0)
		wp_func_warning();
	return n;
}

int wp_setenv (const char *name, const char *value, int rewrite)
{
	int n;
	if ((n = setenv (name, value, rewrite)) != 0)
		wp_func_warning();
	return n;
}

int wp_unsetenv (const char *name)
{
	int n;
	if ((n = unsetenv (name)) != 0)
		wp_func_warning();
	return n;
}

int wp_clock_getres (clockid_t clock_id, struct timespec *res)
{
	int n;
	if ((n = clock_getres (clock_id, res)) == -1)
		wp_sys_func_warning ();
	return n;
}

int wp_clock_gettime (clockid_t clock_id, struct timespec *ts)
{
	int n;
	if ((n = clock_gettime (clock_id, ts)) == -1)
		wp_sys_func_warning ();
	return n;
}

int wp_clock_settime (clockid_t clock_id, struct timespec *ts)
{
	int n;
	if ((n = clock_settime (clock_id, ts)) == -1)
		wp_sys_func_warning ();
	return n;
}

void (*wp_signal (int signo, void (*func)(int)))(int)
{
	void (*f)(int) ;
	if ((f = signal (signo, func)) == SIG_ERR)
		wp_sys_func_warning();
	return f;
}

int wp_timer_create (clockid_t clockid, struct sigevent *evp, timer_t *timerid)
{
	int n;
	if ((n = timer_create (clockid, evp, timerid)) == -1)
		wp_sys_func_warning ();
	return n;
}

int wp_timer_settime (timer_t timerid, int flags, const struct itimerspec *value, struct itimerspec *ovalue)
{
	int n;
	if ((n = timer_settime (timerid, flags, value, ovalue)) == -1)
		wp_sys_func_warning ();
	return n;
}

int wp_timer_gettime (timer_t timerid, struct itimerspec *value)
{
	int n;
	if ((n = timer_gettime (timerid, value)) == -1)
		wp_sys_func_warning ();
	return n;
}

int wp_timer_getoverrun (timer_t timerid)
{
	int n;
	if ((n = timer_getoverrun (timerid)) == -1)
		wp_sys_func_warning ();
	return n;
}

int wp_timer_delete (timer_t timerid)
{
	int n;
	if ((n = timer_delete (timerid)) == -1)
		wp_sys_func_warning ();
	return n;
}
