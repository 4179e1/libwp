#ifndef _WPBASE_H
#define _WPBASE_H

#define WP_BUF_SIZE 1024

#include <stdio.h>
#include <stdbool.h>

/*****************
 * error
 ****************/

/* error process */
void wp_message (const char *fmt, ...);
void wp_warning (const char *fmt, ...);
void wp_error (const char *fmt, ...);
void wp_critical (const char *fmt, ...);

#define wp_func_warning() wp_warning ("%s() error\n", __func__)

/* error process for system call, check errno */
void wp_sys_message (const char *fmt, ...);
void wp_sys_warning (const char *fmt, ...);
void wp_sys_error (const char *fmt, ...);
void wp_sys_critical (const char *fmt, ...);

void wp_syslog_on (void);
void wp_syslog_off (void);
bool wp_syslog_is_on (void);

FILE *wp_set_output_file (FILE *new_of);
FILE *wp_get_output_file (void);

/************************************************
 * path
 ***********************************************/
int wp_get_path_size(void);
char *wp_path_alloc(int *sizep);

/***********************************************
 * openmax
 **********************************************/
long open_max (void);

#endif /* _WPBASE_H */
