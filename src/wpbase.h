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

#define WP_LOG_CRITICAL 2
#define WP_LOG_ERROR	3
#define WP_LOG_WARNING	4
#define WP_LOG_MESSAGE	6
#define WP_LOG_DEBUG	7

/* error process */
#ifndef NDEBUG
void wp_debug (const char *fmt, ...);
#else
#define wp_debug(...) ((void)0)
#endif /* NDEBUG */
void wp_message (const char *fmt, ...);
void wp_warning (const char *fmt, ...);
void wp_error (const char *fmt, ...);
void wp_critical (const char *fmt, ...);

#define wp_func_warning() wp_warning("%s() error", __func__)
#define wp_pthread_warning(N) wp_warning("%s() error: %s", __func__, strerror(N))

/* error process for system call, check errno */
void wp_sys_debug (const char *fmt, ...);
void wp_sys_message (const char *fmt, ...);
void wp_sys_warning (const char *fmt, ...);
void wp_sys_error (const char *fmt, ...);
void wp_sys_critical (const char *fmt, ...);

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


/**
 * @brief Macro to calculate array's length.
 * @param array It MUST be a array, passing a pointer won't work as you expact.
 * @return Size of the array.
 */
#define WP_ARRAY_SIZE(array) (sizeof(array)/sizeof(array[0]))

#define WP_MAX(a, b) ((a > b) ? a : b)
#define WP_MIN(a, b) ((a < b) ? a : b)

#define WP_IS_ODD(n) ((n % 2) != 0)
#define WP_IS_EVEN(n) ((n % 2) == 0)

#define WP_INT_SENT_MAX 0x7fffffff
#define WP_INT_SENT_MIN 0x80000000

typedef bool (*wp_foreach_func_t) (void *elem, void *data);
typedef void (*wp_write_func_t) (const void *elem, FILE *file, void *data);
typedef int (*wp_compare_func_t) (const void *elem1, const void *elem2);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _WPBASE_H */
