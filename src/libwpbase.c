#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdarg.h>
#include <syslog.h>
#include <errno.h>
#include <unistd.h>
#include "libwpbase.h"

#define EXIT_STATUS_DEFAULT -1

static bool wp_syslog_status = false;
static FILE *wp_error_of = NULL;

static void error_do (bool errnoflag, int level, const char *fmt, va_list ap);

void wp_message (const char *fmt, ...)
{
	va_list ap;

	va_start (ap, fmt);
	error_do (false, LOG_INFO, fmt, ap);
	va_end (ap);
}

void wp_warning (const char *fmt, ...)
{
	va_list ap;
	
	va_start (ap, fmt);
	error_do (false, LOG_WARNING, fmt, ap);
	va_end (ap);
}

void wp_error (const char *fmt, ...)
{
	va_list ap;

	va_start (ap, fmt);
	error_do (false, LOG_ERR, fmt, ap);
	va_end (ap);

	return;
}

void wp_critical (const char *fmt, ...)
{
	va_list ap;

	va_start (ap, fmt);
	error_do (false, LOG_ERR, fmt, ap);
	va_end (ap);
	
	exit (EXIT_STATUS_DEFAULT);
}

void wp_sys_message (const char *fmt, ...)
{
	va_list ap;

	va_start (ap, fmt);
	error_do (true, LOG_INFO, fmt, ap);
	va_end (ap);
}

void wp_sys_warning (const char *fmt, ...)
{
	va_list ap;
	
	va_start (ap, fmt);
	error_do (true, LOG_WARNING, fmt, ap);
	va_end (ap);
}

void wp_sys_error (const char *fmt, ...)
{
	va_list ap;

	va_start (ap, fmt);
	error_do (true, LOG_ERR, fmt, ap);
	va_end (ap);

	return;
}

void wp_sys_critical (const char *fmt, ...)
{
	va_list ap;

	va_start (ap, fmt);
	error_do (true, LOG_ERR, fmt, ap);
	va_end (ap);
	
	exit (EXIT_STATUS_DEFAULT);
}

void wp_syslog_on (void) 
{
	wp_syslog_status = true;
}

void wp_syslog_off (void)
{
	wp_syslog_status = false;
}

bool wp_syslog_is_on (void)
{
	return wp_syslog_status;
}

FILE *wp_set_output_file (FILE *new_of)
{
	wp_error_of = new_of;
	return wp_error_of;
}

FILE *wp_get_output_file (void)
{
	return wp_error_of;
}


static void error_do (bool errnoflag, int level, const char *fmt, va_list ap)
{
	int errno_save;
	int n;
	char buf[WP_BUF_SIZE];

	errno_save = errno;

	vsnprintf (buf, WP_BUF_SIZE, fmt, ap);

	n = strlen (buf);
	if (errnoflag)
		snprintf (buf + n, (WP_BUF_SIZE - n), ": %s", strerror (errno_save));
	strcat (buf, "\n");

	if (wp_syslog_status) 
	{
		syslog (level, buf);
	}
	else 
	{
		fflush (stdout);
		fputs (buf, ((wp_error_of == NULL) ? stderr : wp_error_of));
		fflush (stderr);
	}

	return;
}

/**************************************************************************
 * 								Open Max								  *
 *************************************************************************/
#ifdef OPEN_MAX
static long openmax = OPEN_MAX;
#else
static long openmax = 0;
#endif /* OPEN_MAX */

#define OPEN_MAX_GUESS 256

long open_max (void)
{
	if (openmax == 0)
	{
		errno = 0;
		if ((openmax = sysconf (_SC_OPEN_MAX)) < 0)
		{
			if (errno == 0)
				openmax = OPEN_MAX_GUESS;
			else
				wp_sys_warning ("sysconf error for _SC_OPEN_MAX");
		}

	}
	return (openmax);
}

/**************************************************************************
 * 								Path Max								  *
 *************************************************************************/
#ifdef PATH_MAX
static int pathmax = PATH_MAX;
#else
static int pathmax = 0;
#endif /* PATH_MAX */

#define SUSV3 200112L

#define PATH_MAX_GUESS	1024

static long posix_version = 0;

int wp_get_path_max(void)
{
	int size;
	if (posix_version == 0)
		posix_version = sysconf (_SC_VERSION);

	if (pathmax == 0)
	{
		errno = 0;
		if ((pathmax = pathconf ("/", _PC_PATH_MAX)) < 0)
		{
			if (errno == 0)
				pathmax = PATH_MAX_GUESS;
			else
				wp_sys_warning ("pathconf error for _PC_PATH_MAX");
		}
		else
		{
			pathmax++;
		}
	}

	if (posix_version < SUSV3)
		size = pathmax + 1;
	else 
		size = pathmax;

	return size;
}

char *wp_path_alloc (int *sizep)
{
	char *ptr;
	int size = wp_get_path_max();

	if ((ptr = malloc (size)) == NULL)
		wp_sys_critical ("malloc error for pathname");

	if (sizep != NULL)
		*sizep = size;

	return ptr;
}
