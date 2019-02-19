#ifndef __PJ_CONTACT_SIP_Os_H
#define __PJ_CONTACT_SIP_Os_H

#include "pj_config.h"
#include "pj_types.h"

//------------------------------------------------------------------------------

/**
 * Get current time of day in local representation.
 *
 * @param tv	Variable to store the result.
 *
 * @return zero if successfull.
 */
PJ_DECL(pj_status_t) pj_gettimeofday(pj_time_val *tv);

//------------------------------------------------------------------------------
static pj_status_t get_base_time(void);
//------------------------------------------------------------------------------
/**
 * Acquire high resolution timer value. The time value are stored
 * in cycles.
 *
 * @param ts	    High resolution timer value.
 * @return	    PJ_SUCCESS or the appropriate error code.
 *
 * @see pj_get_timestamp_freq().
 */
PJ_DECL(pj_status_t) pj_get_timestamp(pj_timestamp *ts);
//------------------------------------------------------------------------------
/**
 * Get high resolution timer frequency, in cycles per second.
 *
 * @param freq	    Timer frequency, in cycles per second.
 * @return	    PJ_SUCCESS or the appropriate error code.
 */
PJ_DECL(pj_status_t) pj_get_timestamp_freq(pj_timestamp *freq);
//------------------------------------------------------------------------------
/**
 * @def PJ_CHECK_STACK()
 * PJ_CHECK_STACK() macro is used to check the sanity of the stack.
 * The OS implementation may check that no stack overflow occurs, and
 * it also may collect statistic about stack usage.
 */
#if defined(PJ_OS_HAS_CHECK_STACK) && PJ_OS_HAS_CHECK_STACK!=0

#  define PJ_CHECK_STACK() pj_thread_check_stack(__FILE__, __LINE__)

/** @internal
 * The implementation of stack checking. 
 */
PJ_DECL(void) pj_thread_check_stack(const char *file, int line);

/** @internal
 * Get maximum stack usage statistic. 
 */
PJ_DECL(pj_uint32_t) pj_thread_get_stack_max_usage(pj_thread_t *thread);

/** @internal
 * Dump thread stack status. 
 */
PJ_DECL(pj_status_t) pj_thread_get_stack_info(pj_thread_t *thread,
					      const char **file,
					      int *line);
#else

#  define PJ_CHECK_STACK()
/** pj_thread_get_stack_max_usage() for the thread */
#  define pj_thread_get_stack_max_usage(thread)	    0
/** pj_thread_get_stack_info() for the thread */
#  define pj_thread_get_stack_info(thread,f,l)	    (*(f)="",*(l)=0)
#endif	/* PJ_OS_HAS_CHECK_STACK */
//-------------------------------------------------------------------------------
#endif //#ifndef __PJ_CONTACT_SIP_Os_H


