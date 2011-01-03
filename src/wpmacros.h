#ifndef _WPMACROS_H
#define _WPMACROS_H

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

#define wp_return_if_fail(expr) do {\
	if (expr) {} else \
	{\
		return;\
	}\
} while(0);

#define wp_return_val_if_fail(expr,val) do {\
	if (expr) {} else \
	{\
		return (val);\
	}\
} while(0);

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

#define WP_INT_SENT_MAX INT_MAX
#define WP_INT_SENT_MIN INT_MIN

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _WPMACROS_H */
