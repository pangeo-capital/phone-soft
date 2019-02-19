#ifndef __PJ_CONTACT_SIP_Log_H
#define __PJ_CONTACT_SIP_Log_H

#include "pj_config.h"

#if PJ_LOG_MAX_LEVEL >= 1

#if 0
PJ_DEF_DATA(int) pj_log_max_level = PJ_LOG_MAX_LEVEL;
#else
static int pj_log_max_level = PJ_LOG_MAX_LEVEL;
#endif


#endif
//------------------------------------------------------------------------------
/**
 * Write log message.
 * This is the main macro used to write text to the logging backend.
 *
 * @param level	    The logging verbosity level. Lower number indicates higher
 *		    importance, with level zero indicates fatal error. Only
 *		    numeral argument is permitted (e.g. not variable).
 * @param arg	    Enclosed 'printf' like arguments, with the first
 *		    argument is the sender, the second argument is format
 *		    string and the following arguments are variable number of
 *		    arguments suitable for the format string.
 *
 * Sample:
 * \verbatim
   PJ_LOG(2, (__FILE__, "current value is %d", value));
   \endverbatim
 * @hideinitializer
 */
#define PJ_LOG(level,arg)	do { \
				    if (level <= pj_log_get_level()) \
					pj_log_wrapper_##level(arg); \
				} while (0)
//------------------------------------------------------------------------------
/**
 * Get current maximum log verbositylevel.
 *
 * @return	    Current log maximum level.
 */
#if 1
PJ_DECL(int) pj_log_get_level(void);
#else
PJ_DECL_DATA(int) pj_log_max_level;
#define pj_log_get_level()  pj_log_max_level
#endif
//------------------------------------------------------------------------------
/* **************************************************************************/
/*
 * Log functions implementation prototypes.
 * These functions are called by PJ_LOG macros according to verbosity
 * level specified when calling the macro. Applications should not normally
 * need to call these functions directly.
 */

/**
 * @def pj_log_wrapper_1(arg)
 * Internal function to write log with verbosity 1. Will evaluate to
 * empty expression if PJ_LOG_MAX_LEVEL is below 1.
 * @param arg       Log expression.
 */
#if PJ_LOG_MAX_LEVEL >= 1
    #define pj_log_wrapper_1(arg)	pj_log_1 arg
    /** Internal function. */
    PJ_DECL(void) pj_log_1(const char *src, const char *format, ...);
#else
    #define pj_log_wrapper_1(arg)
#endif

/**
 * @def pj_log_wrapper_2(arg)
 * Internal function to write log with verbosity 2. Will evaluate to
 * empty expression if PJ_LOG_MAX_LEVEL is below 2.
 * @param arg       Log expression.
 */
#if PJ_LOG_MAX_LEVEL >= 2
    #define pj_log_wrapper_2(arg)	pj_log_2 arg
    /** Internal function. */
    PJ_DECL(void) pj_log_2(const char *src, const char *format, ...);
#else
    #define pj_log_wrapper_2(arg)
#endif

/**
 * @def pj_log_wrapper_3(arg)
 * Internal function to write log with verbosity 3. Will evaluate to
 * empty expression if PJ_LOG_MAX_LEVEL is below 3.
 * @param arg       Log expression.
 */
#if PJ_LOG_MAX_LEVEL >= 3
    #define pj_log_wrapper_3(arg)	pj_log_3 arg
    /** Internal function. */
    PJ_DECL(void) pj_log_3(const char *src, const char *format, ...);
#else
    #define pj_log_wrapper_3(arg)
#endif

/**
 * @def pj_log_wrapper_4(arg)
 * Internal function to write log with verbosity 4. Will evaluate to
 * empty expression if PJ_LOG_MAX_LEVEL is below 4.
 * @param arg       Log expression.
 */
#if PJ_LOG_MAX_LEVEL >= 4
    #define pj_log_wrapper_4(arg)	pj_log_4 arg
    /** Internal function. */
    PJ_DECL(void) pj_log_4(const char *src, const char *format, ...);
#else
    #define pj_log_wrapper_4(arg)
#endif

/**
 * @def pj_log_wrapper_5(arg)
 * Internal function to write log with verbosity 5. Will evaluate to
 * empty expression if PJ_LOG_MAX_LEVEL is below 5.
 * @param arg       Log expression.
 */
#if PJ_LOG_MAX_LEVEL >= 5
    #define pj_log_wrapper_5(arg)	pj_log_5 arg
    /** Internal function. */
    PJ_DECL(void) pj_log_5(const char *src, const char *format, ...);
#else
    #define pj_log_wrapper_5(arg)
#endif

/**
 * @def pj_log_wrapper_6(arg)
 * Internal function to write log with verbosity 6. Will evaluate to
 * empty expression if PJ_LOG_MAX_LEVEL is below 6.
 * @param arg       Log expression.
 */
#if PJ_LOG_MAX_LEVEL >= 6
    #define pj_log_wrapper_6(arg)	pj_log_6 arg
    /** Internal function. */
    PJ_DECL(void) pj_log_6(const char *src, const char *format, ...);
#else
    #define pj_log_wrapper_6(arg)
#endif
//------------------------------------------------------------------------------
#endif  //#ifndef __PJ_CONTACT_SIP_Log_H
