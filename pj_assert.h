#ifndef __PJ_CONTACT_SIP_Assert_A_H
#define __PJ_CONTACT_SIP_Assert_A_H

#include <assert.h>

//------------------------------------------------------------------------------
#ifndef pj_assert
#   define pj_assert(expr)   assert(expr)
#endif
//------------------------------------------------------------------------------
/**
 * @hideinitializer
 * If #PJ_ENABLE_EXTRA_CHECK is declared and the value is non-zero, then
 * #PJ_ASSERT_RETURN macro will evaluate the expression in @a expr during
 * run-time. If the expression yields false, assertion will be triggered
 * and the current function will return with the specified return value.
 *
 * If #PJ_ENABLE_EXTRA_CHECK is not declared or is zero, then no run-time
 * checking will be performed. The macro simply evaluates to pj_assert(expr).
 */
#if defined(PJ_ENABLE_EXTRA_CHECK) && PJ_ENABLE_EXTRA_CHECK != 0
#   define PJ_ASSERT_RETURN(expr,retval)    \
	    do { \
		if (!(expr)) { pj_assert(expr); return retval; } \
	    } while (0)
#else
#   define PJ_ASSERT_RETURN(expr,retval)    pj_assert(expr)
#endif
//------------------------------------------------------------------------------
#endif //#ifndef __PJ_CONTACT_SIP_Assert_A_H

