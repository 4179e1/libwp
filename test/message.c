#include <libwp.h>
#include <errno.h>

int main (int argc, char *argv[])
{
	errno = 0;
	wp_set_exit_level (WP_LOG_EMERG);

	fprintf (stderr, "ERRNO STDERR %d\n", errno);
	printf ("ERRNO %d\n", errno);
	fprintf (stderr, "ERRNO STDERR %d\n", errno);
	wp_debug ("debug");
	wp_message ("mssage");
	wp_warning ("warning");
	wp_error ("error");
	wp_critical ("critical");

	printf ("ERRNO %d\n", errno);
	fprintf (stderr, "ERRNO STDERR %d\n", errno);
	wp_debug_full (stdout, "debug");
	wp_message_full (stdout, "mssage");
	wp_warning_full (stdout, "warning");
	wp_error_full (stdout, "error");
	wp_critical_full (stdout, "critical");

	printf ("ERRNO %d\n", errno);
	fprintf (stderr, "ERRNO STDERR %d\n", errno);
	wp_sys_debug ("debug");
	wp_sys_message ("mssage");
	wp_sys_warning ("warning");
	wp_sys_error ("error");
	wp_sys_critical ("critical");

	printf ("ERRNO %d\n", errno);
	fprintf (stderr, "ERRNO STDERR %d\n", errno);
	wp_sys_debug_full (stdout, "stdout debug");
	wp_sys_message_full (stdout, "stdout mssage");
	wp_sys_warning_full (stdout, "stdout warning");
	wp_sys_error_full (stdout, "stdout error");
	wp_sys_critical_full (stdout, "stdout critical");

	return 0;
}
