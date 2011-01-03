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

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _WPMACROS_H */
