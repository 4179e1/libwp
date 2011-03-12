#ifndef _WPBASE_H
#define _WPBASE_H

#define WP_BUF_SIZE 1024

#include <stdio.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

/*****************
 * error
 ****************/

#if 0
/* from syslog.h */
#define	LOG_EMERG	0	/* system is unusable */
#define	LOG_ALERT	1	/* action must be taken immediately */
#define	LOG_CRIT	2	/* critical conditions */
#define	LOG_ERR		3	/* error conditions */
#define	LOG_WARNING	4	/* warning conditions */
#define	LOG_NOTICE	5	/* normal but significant condition */
#define	LOG_INFO	6	/* informational */
#define	LOG_DEBUG	7	/* debug-level messages */
#endif

#define WP_LOG_EMERG	0
#define WP_LOG_ALERT	1
#define WP_LOG_CRITICAL 2	/* wp_critical* */
#define WP_LOG_ERROR	3	/* wp_error* */
#define WP_LOG_WARNING	4	/* wp_warning* */
#define WP_LOG_NOTICE	5
#define WP_LOG_MESSAGE	6	/* wp_message* */
#define WP_LOG_DEBUG	7	/* wp_debug* */

/* error process */
#ifndef NDEBUG
void wp_debug_full (FILE *of, const char *fmt, ...);
#else
#define wp_debug_full(...) ((void)0)
#endif /* NDEBUG */
void wp_message_full (FILE *of, const char *fmt, ...);
void wp_warning_full (FILE *of, const char *fmt, ...);
void wp_error_full (FILE *of, const char *fmt, ...);
void wp_critical_full (FILE *of, const char *fmt, ...);

#define wp_debug(MSG, ...) 		wp_debug_full(NULL, (MSG), ##__VA_ARGS__)
#define wp_message(MSG, ...) 	wp_message_full(NULL, (MSG), ##__VA_ARGS__)
#define wp_warning(MSG, ...) 	wp_warning_full(NULL, (MSG), ##__VA_ARGS__)
#define wp_error(MSG, ...) 		wp_error_full(NULL, (MSG), ##__VA_ARGS__)
#define wp_critical(MSG, ...) 	wp_critical_full(NULL, (MSG), ##__VA_ARGS__)

#define wp_func_warning() wp_warning("%s() error", __func__)
#define wp_pthread_warning(N) wp_warning("%s() error: %s", __func__, strerror(N))

/* error process for system call, check errno */
#ifndef NDEBUG
void wp_sys_debug_full (FILE *of, const char *fmt, ...);
#else
#define wp_sys_debug_full(...) ((void)0)
#endif /* NDEBUG */
void wp_sys_message_full (FILE *of, const char *fmt, ...);
void wp_sys_warning_full (FILE *of, const char *fmt, ...);
void wp_sys_error_full (FILE *of, const char *fmt, ...);
void wp_sys_critical_full (FILE *of, const char *fmt, ...);

#define wp_sys_debug(MSG, ...)		wp_sys_debug_full(NULL, (MSG), ##__VA_ARGS__)
#define wp_sys_message(MSG, ...)	wp_sys_message_full(NULL, (MSG), ##__VA_ARGS__)
#define wp_sys_warning(MSG, ...)	wp_sys_warning_full(NULL, (MSG), ##__VA_ARGS__)
#define wp_sys_error(MSG, ...)		wp_sys_error_full(NULL, (MSG), ##__VA_ARGS__)
#define wp_sys_critical(MSG, ...)	wp_sys_critical_full(NULL, (MSG), ##__VA_ARGS__)

#define wp_sys_func_warning() wp_sys_warning("%s() error", __func__)

void wp_syslog_on (void);
void wp_syslog_off (void);
bool wp_syslog_is_on (void);

FILE *wp_set_output_file (FILE *new_of);
FILE *wp_get_output_file (void);

void wp_set_name (const char *name);

int wp_set_exit_level (int level);
int wp_get_exit_level (void);

/************************************************
 * path
 ***********************************************/
int wp_get_path_size(void);
char *wp_path_alloc(int *sizep);

/***********************************************
 * openmax
 **********************************************/
long open_max (void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _WPBASE_H */
