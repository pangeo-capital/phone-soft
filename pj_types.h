#ifndef __PJ_CONTACT_SIP_Types_H
#define __PJ_CONTACT_SIP_Types_H

#include "pj_config.h"
#include <mem.h>

//------------------------------------------------------------------------------
/** Signed 8bit integer. */
typedef signed char	 pj_int8_t;

/** Unsigned 8bit integer. */
typedef unsigned char    pj_uint8_t;

/** Large signed integer. */
typedef long             pj_ssize_t;

/** Signed 16bit integer. */
typedef short		 pj_int16_t;

/** Unsigned 16bit integer. */
typedef unsigned short   pj_uint16_t;

/** Signed 32bit integer. */
typedef int		 pj_int32_t;

/** Unsigned 32bit integer. */
typedef unsigned int     pj_uint32_t;

typedef __int64          pj_int64_t;
typedef unsigned __int64 pj_uint64_t;

/** Boolean. */
typedef int	         pj_bool_t;

/** Large unsigned integer. */
typedef size_t	         pj_size_t;

/** Status code. */
typedef int		 pj_status_t;
//------------------------------------------------------------------------------
/** Some constants */
enum pj_constants_
{
    /** Status is OK. */
    PJ_SUCCESS=0,

    /** True value. */
    PJ_TRUE=1,

    /** False value. */
    PJ_FALSE=0
};
//------------------------------------------------------------------------------
/**
 * Representation of time value in this library.
 * This type can be used to represent either an interval or a specific time
 * or date.
 */
typedef struct pj_time_val
{
    /** The seconds part of the time. */
    long    sec;

    /** The miliseconds fraction of the time. */
    long    msec;

} pj_time_val;
//------------------------------------------------------------------------------
/**
 * This type is used as replacement to legacy C string, and used throughout
 * the library. By convention, the string is NOT null terminated.
 */
struct pj_str_t
{
    /** Buffer pointer, which is by convention NOT null terminated. */
    char       *ptr;

    /** The length of the string. */
    pj_ssize_t  slen;
};
//------------------------------------------------------------------------------
/**
 * This structure represents high resolution (64bit) time value. The time
 * values represent time in cycles, which is retrieved by calling
 * #pj_get_timestamp().
 */
typedef union pj_timestamp
{
    struct
    {
#if defined(PJ_IS_LITTLE_ENDIAN) && PJ_IS_LITTLE_ENDIAN!=0              //x86-64 - little endian - размещение многобайтовых слов в ѕјћя“» машины (а не в сети)
	pj_uint32_t lo;     /**< Low 32-bit value of the 64-bit value. */
	pj_uint32_t hi;     /**< high 32-bit value of the 64-bit value. */
#else
	pj_uint32_t hi;     /**< high 32-bit value of the 64-bit value. */
	pj_uint32_t lo;     /**< Low 32-bit value of the 64-bit value. */
#endif
    } u32;                  /**< The 64-bit value as two 32-bit values. */

#if PJ_HAS_INT64
    pj_uint64_t u64;        /**< The whole 64-bit value, where available. */
#endif
} pj_timestamp;
//-----------------------------------------------------------------------------
/**
 * Normalize the value in time value.
 * @param t     Time value to be normalized.
 */
PJ_DECL(void) pj_time_val_normalize(pj_time_val *t);
//-----------------------------------------------------------------------------
/**
 * Substract \a t2 from \a t1 and store the result in \a t1. Effectively
 * this macro will expand as (\a t1 -= \a t2).
 *
 * @param t1    The time value to subsctract.
 * @param t2    The time value to be substracted from \a t1.
 * @hideinitializer
 */
#define PJ_TIME_VAL_SUB(t1, t2)	    do {			    \
					(t1).sec -= (t2).sec;	    \
					(t1).msec -= (t2).msec;	    \
					pj_time_val_normalize(&(t1)); \
				    } while (0)
//-----------------------------------------------------------------------------
/**
 * Get the total time value in miliseconds. This is the same as
 * multiplying the second part with 1000 and then add the miliseconds
 * part to the result.
 *
 * @param t     The time value.
 * @return      Total time in miliseconds.
 * @hideinitializer
 */
#define PJ_TIME_VAL_MSEC(t)	((t).sec * 1000 + (t).msec)
//------------------------------------------------------------------------------
/**
 * This macro will check if \a t1 is equal to \a t2.
 *
 * @param t1    The first time value to compare.
 * @param t2    The second time value to compare.
 * @return      Non-zero if both time values are equal.
 * @hideinitializer
 */
#define PJ_TIME_VAL_EQ(t1, t2)	((t1).sec==(t2).sec && (t1).msec==(t2).msec)
//------------------------------------------------------------------------------
/**
 * This macro will check if \a t1 is greater than \a t2
 *
 * @param t1    The first time value to compare.
 * @param t2    The second time value to compare.
 * @return      Non-zero if t1 is greater than t2.
 * @hideinitializer
 */
#define PJ_TIME_VAL_GT(t1, t2)	((t1).sec>(t2).sec || \
                                ((t1).sec==(t2).sec && (t1).msec>(t2).msec))
//------------------------------------------------------------------------------
/**
 * This macro will check if \a t1 is greater than or equal to \a t2
 *
 * @param t1    The first time value to compare.
 * @param t2    The second time value to compare.
 * @return      Non-zero if t1 is greater than or equal to t2.
 * @hideinitializer
 */
#define PJ_TIME_VAL_GTE(t1, t2)	(PJ_TIME_VAL_GT(t1,t2) || \
                                 PJ_TIME_VAL_EQ(t1,t2))
//------------------------------------------------------------------------------
/**
 * This macro will check if \a t1 is less than \a t2
 *
 * @param t1    The first time value to compare.
 * @param t2    The second time value to compare.
 * @return      Non-zero if t1 is less than t2.
 * @hideinitializer
 */
#define PJ_TIME_VAL_LT(t1, t2)	(!(PJ_TIME_VAL_GTE(t1,t2)))
//-----------------------------------------------------------------------------
#endif //#ifndef __PJ_CONTACT_SIP_Types_H
