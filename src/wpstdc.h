#include <stdio.h>
#include <unistd.h>
#include <stdarg.h>
#include <time.h>

#ifndef _WPSTDC_H
#define _WPSTDC_H

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

int _wp_fclose (FILE *fp);
FILE *_wp_fdopen (int filedes, const char *type);
int _wp_fgetc (FILE *fp);
char *_wp_fgets (char *buf, int n, FILE *fp);
int _wp_fputc (int c, FILE *fp);
int _wp_fputs (const char *str, FILE *fp);
int _wp_fflush (FILE *fp);
FILE *_wp_fopen (const char *pathname, const char *type);
size_t _wp_fread (void *ptr, size_t size, size_t nobj, FILE *fp);
FILE *_wp_freopen (const char *pathname, const char *type, FILE *fp);
int _wp_getc (FILE *fp);
int _wp_getchar (void);
int _wp_putc (int c, FILE *fp);
int _wp_putchar (int c);
int _wp_remove (const char *pathname);
int _wp_rename (const char *oldname, const char *newname);
int _wp_setvbuf (FILE *fp, char *buf, int mode, size_t size);
int _wp_ungetc (int c, FILE *fp);
size_t _wp_fwrite (const void *ptr, size_t size, size_t nobj, FILE *fp);

long _wp_ftell (FILE *fp);
int _wp_fseek (FILE *fp, long offset, int whence);
off_t _wp_ftello (FILE *fp);
int _wp_fseeko (FILE *fp, off_t offset, int whence);
int _wp_fgetpos (FILE *fp, fpos_t *pos);
int _wp_fsetpos (FILE *fp, fpos_t *pos);

int _wp_vprintf (const char *fmt, va_list arg);
int _wp_vfprintf (FILE *fp, const char *fmt, va_list arg);
int _wp_vsprintf (char *buf, const char *fmt, va_list arg);
int _wp_vsnprintf (char *buf, size_t n, const char *fmt, va_list arg);

int _wp_vscanf (const char *format, va_list arg);
int _wp_vfscanf (FILE *fp, const char *fmt, va_list arg);
int _wp_vsscanf (const char *buf, const char *fmt, va_list arg);

FILE *_wp_tmpfile (void);
int _wp_mkstemp (char *template);

FILE *_wp_popen (const char *cmdstring, const char *type);
int _wp_pclose (FILE *fp);

time_t _wp_time (time_t *calptr);
time_t _wp_mktime (struct tm *tmptr);

int _wp_atexit (void (*func) (void));

void *_wp_malloc (size_t size);
void *_wp_calloc (size_t nobj, size_t size);
void *_wp_realloc (void *ptr, size_t newsize);

char *_wp_getenv (const char *name);
int _wp_putenv (char *str);
int _wp_setenv (const char *name, const char *value, int rewrite);
int _wp_unsetenv (const char *name);


#ifdef DISABLE_WP
#define wp_fclose fclose
#define wp_fdopen fdopen
#define wp_fgetc fgetc
#define wp_fgets fgets
#define wp_fputc fputc
#define wp_fputs fputs
#define wp_fflush fflush
#define wp_fopen fopen
#define wp_fread fread
#define wp_freopen freopen
#define wp_getc getc
#define wp_getchar getchar
#define wp_putc putc
#define wp_putchar putchar
#define wp_remove remove
#define wp_rename rename
#define wp_setvbuf setvbuf
#define wp_ungetc ungetc
#define wp_fwrite fwrite
#define wp_ftell ftell
#define wp_fseek fseek
#define wp_ftello ftello
#define wp_fseeko fseeko
#define wp_fgetpos fgetpos
#define wp_fsetpos fsetpos
#define wp_vprintf vprintf
#define wp_vfprintf vfprintf
#define wp_vsprintf vsprintf
#define wp_vsnprintf vsnprintf
#define wp_vscanf vscanf
#define wp_vfscanf vfscanf
#define wp_vsscanf vsscanf
#define wp_tmpfile tmpfile
#define wp_mkstemp mkstemp
#define wp_popen popen
#define wp_pclose pclose
#define wp_time time
#define wp_mktime mktime
#define wp_atexit atexit
#define wp_malloc malloc
#define wp_calloc calloc
#define wp_realloc realloc
#define wp_getenv getenv
#define wp_putenv putenv
#define wp_setenv setenv
#define wp_unsetenv unsetenv
#else
#define wp_fclose _wp_fclose
#define wp_fdopen _wp_fdopen
#define wp_fgetc _wp_fgetc
#define wp_fgets _wp_fgets
#define wp_fputc _wp_fputc
#define wp_fputs _wp_fputs
#define wp_fflush _wp_fflush
#define wp_fopen _wp_fopen
#define wp_fread _wp_fread
#define wp_freopen _wp_freopen
#define wp_getc _wp_getc
#define wp_getchar _wp_getchar
#define wp_putc _wp_putc
#define wp_putchar _wp_putchar
#define wp_remove _wp_remove
#define wp_rename _wp_rename
#define wp_setvbuf _wp_setvbuf
#define wp_ungetc _wp_ungetc
#define wp_fwrite _wp_fwrite
#define wp_ftell _wp_ftell
#define wp_fseek _wp_fseek
#define wp_ftello _wp_ftello
#define wp_fseeko _wp_fseeko
#define wp_fgetpos _wp_fgetpos
#define wp_fsetpos _wp_fsetpos
#define wp_vprintf _wp_vprintf
#define wp_vfprintf _wp_vfprintf
#define wp_vsprintf _wp_vsprintf
#define wp_vsnprintf _wp_vsnprintf
#define wp_vscanf _wp_vscanf
#define wp_vfscanf _wp_vfscanf
#define wp_vsscanf _wp_vsscanf
#define wp_tmpfile _wp_tmpfile
#define wp_mkstemp _wp_mkstemp
#define wp_popen _wp_popen
#define wp_pclose _wp_pclose
#define wp_time _wp_time
#define wp_mktime _wp_mktime
#define wp_atexit _wp_atexit
#define wp_malloc _wp_malloc
#define wp_calloc _wp_calloc
#define wp_realloc _wp_realloc
#define wp_getenv _wp_getenv
#define wp_putenv _wp_putenv
#define wp_setenv _wp_setenv
#define wp_unsetenv _wp_unsetenv
#endif /* DISABLE_WP */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _WPSTDC_H */
