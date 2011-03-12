#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdarg.h>
#include <syslog.h>
#include <errno.h>
#include <unistd.h>
#include <wpbase.h>

#define EXIT_STATUS_DEFAULT -1

static const char *error_name[] =
{
	"EMERGENCE",
	"ALERT",
	"CRITICAL",
	"ERROR",
	"WARNING",
	"NOTICE",
	"MESSAGE",
	"DEBUG",
};

static const char *wp_name = "WP";
static FILE *wp_error_of = NULL;
static bool wp_syslog_status = false;
static int wp_exit_level = LOG_CRIT;

static void error_do (FILE *output, bool errnoflag, int level, const char *fmt, va_list ap);

void wp_debug_full (FILE *of, const char *fmt, ...)
{
	va_list ap;
	va_start (ap, fmt);
	error_do (of, false, LOG_DEBUG, fmt, ap);
	va_end (ap);
}

void wp_message_full (FILE *of, const char *fmt, ...)
{
	va_list ap;

	va_start (ap, fmt);
	error_do (of, false, LOG_INFO, fmt, ap);
	va_end (ap);
}

void wp_warning_full (FILE *of, const char *fmt, ...)
{
	va_list ap;
	
	va_start (ap, fmt);
	error_do (of, false, LOG_WARNING, fmt, ap);
	va_end (ap);
}

void wp_error_full (FILE *of, const char *fmt, ...)
{
	va_list ap;

	va_start (ap, fmt);
	error_do (of, false, LOG_ERR, fmt, ap);
	va_end (ap);

	return;
}

void wp_critical_full (FILE *of, const char *fmt, ...)
{
	va_list ap;

	va_start (ap, fmt);
	error_do (of, false, LOG_CRIT, fmt, ap);
	va_end (ap);
}

void wp_sys_debug_full (FILE *of, const char *fmt, ...)
{
	va_list ap;
	va_start (ap, fmt);
	error_do (of, true, LOG_DEBUG, fmt, ap);
	va_end (ap);
}

void wp_sys_message_full (FILE *of, const char *fmt, ...)
{
	va_list ap;

	va_start (ap, fmt);
	error_do (of, true, LOG_INFO, fmt, ap);
	va_end (ap);
}

void wp_sys_warning_full (FILE *of, const char *fmt, ...)
{
	va_list ap;
	
	va_start (ap, fmt);
	error_do (of, true, LOG_WARNING, fmt, ap);
	va_end (ap);
}

void wp_sys_error_full (FILE *of, const char *fmt, ...)
{
	va_list ap;

	va_start (ap, fmt);
	error_do (of, true, LOG_ERR, fmt, ap);
	va_end (ap);

	return;
}

void wp_sys_critical_full (FILE *of, const char *fmt, ...)
{
	va_list ap;

	va_start (ap, fmt);
	error_do (of, true, LOG_CRIT, fmt, ap);
	va_end (ap);
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

void wp_set_name (const char *name)
{
	wp_name = name;
}

int wp_set_exit_level (int level)
{
	if (level < WP_LOG_EMERG)
	{
		level = WP_LOG_EMERG;
	}

	if (level > WP_LOG_MESSAGE)
	{
		level = WP_LOG_MESSAGE;
	}

	wp_exit_level = level;

	return level;
}

int wp_get_exit_level (void)
{
	return wp_exit_level;
}

static void error_do (FILE *output, bool errnoflag, int level, const char *fmt, va_list ap)
{
	int errno_save;
	int n;
	FILE *of;
	char buf[WP_BUF_SIZE + 1];

	errno_save = errno;
	of = output ? output : ((wp_error_of == NULL) ? stderr : wp_error_of);

	if (wp_syslog_status)
	{
		snprintf (buf, WP_BUF_SIZE, "<%s> ", error_name[level]);
	}
	else
	{
		snprintf (buf, WP_BUF_SIZE, "<%s-%s> ", wp_name ? wp_name : "LIBWP", error_name[level]);
	}
	n = strlen (buf);
	
	vsnprintf ((buf + n), (WP_BUF_SIZE - n), fmt, ap);

	if (errnoflag)
	{
		n = strlen (buf);
		snprintf ((buf + n), (WP_BUF_SIZE - n), ": %s", strerror (errno_save));
	}

	if (level <= wp_exit_level)
	{
		strncat (buf, " <will exit now>", WP_BUF_SIZE - strlen (buf));
	}

	if (wp_syslog_status) 
	{
		syslog (level, "%s", buf);
	}
	else 
	{
		if (buf[strlen(buf) - 1] != '\n')
		{
			strcat (buf, "\n");
		}
		fflush (stdout);
		fputs (buf, of);
		fflush (stderr);
	}

	if (level <= wp_exit_level)
	{
		exit (EXIT_STATUS_DEFAULT);
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
