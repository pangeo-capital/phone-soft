#ifndef __PJ_CONTACT_SIP_Config_H
#define __PJ_CONTACT_SIP_Config_H

#define __x86_64
#define PJ_WIN32        1
#define PJ_HAS_INT64	1

#define TRACE_(expr)
//------------------------------------------------------------------------------
#ifndef PJ_OS_HAS_CHECK_STACK
#	define PJ_OS_HAS_CHECK_STACK		0
#endif
//------------------------------------------------------------------------------
#ifdef __cplusplus
# define PJ_INLINE_SPECIFIER	inline
#else
#  define PJ_INLINE_SPECIFIER	static __inline
#endif
//------------------------------------------------------------------------------
#if defined (PJ_M_I386) || defined(_i386_) || defined(i_386_) || \
	defined(_X86_) || defined(x86) || defined(__i386__) || \
	defined(__i386) || defined(_M_IX86) || defined(__I86__)
    /*
     * Generic i386 processor family, little-endian
     */
#   undef PJ_M_I386
#   define PJ_M_I386		1
#   define PJ_M_NAME		"i386"
#   define PJ_HAS_PENTIUM	1
#   define PJ_IS_LITTLE_ENDIAN	1
#   define PJ_IS_BIG_ENDIAN	0


#elif defined (PJ_M_X86_64) || defined(__amd64__) || defined(__amd64) || \
	defined(__x86_64__) || defined(__x86_64) || \
	defined(_M_X64) || defined(_M_AMD64)
    /*
     * AMD 64bit processor, little endian
     */
#   undef PJ_M_X86_64
#   define PJ_M_X86_64		1
#   define PJ_M_NAME		"x86_64"
#   define PJ_HAS_PENTIUM	1
#   define PJ_IS_LITTLE_ENDIAN	1
#   define PJ_IS_BIG_ENDIAN	0

#elif defined(PJ_M_IA64) || defined(__ia64__) || defined(_IA64) || \
	defined(__IA64__) || defined( 	_M_IA64)
    /*
     * Intel IA64 processor, default to little endian
     */
#   undef PJ_M_IA64
#   define PJ_M_IA64		1
#   define PJ_M_NAME		"ia64"
#   define PJ_HAS_PENTIUM	1
#   define PJ_IS_LITTLE_ENDIAN	1
#   define PJ_IS_BIG_ENDIAN	0
#endif
//------------------------------------------------------------------------------
#ifndef PJ_HAS_FLOATING_POINT
  #define PJ_HAS_FLOATING_POINT	    1
#endif
//------------------------------------------------------------------------------
/**
 * Specify the buffer length for storing any received RTCP SDES text
 * in a stream session. Usually RTCP contains only the mandatory SDES
 * field, i.e: CNAME.
 *
 * Default: 64 bytes.
 */
#ifndef PJMEDIA_RTCP_RX_SDES_BUF_LEN
#   define PJMEDIA_RTCP_RX_SDES_BUF_LEN		64
#endif
//------------------------------------------------------------------------------
/**
 * Specify whether RTCP statistics includes IP Delay Variation statistics.
 * IPDV is defined as network transit time difference of two consecutive
 * packets. The IPDV statistic can be useful to inspect clock skew existance
 * and level, e.g: when the IPDV mean values were stable in positive numbers,
 * then the remote clock (used in sending RTP packets) is faster than local
 * system clock. Ideally, the IPDV mean values are always equal to 0.
 *
 * Default: 0 (no).
 */
#ifndef PJMEDIA_RTCP_STAT_HAS_IPDV
#   define PJMEDIA_RTCP_STAT_HAS_IPDV		0
#endif
//------------------------------------------------------------------------------
/**
 * Specify whether RTCP statistics includes raw jitter statistics.
 * Raw jitter is defined as absolute value of network transit time
 * difference of two consecutive packets; refering to "difference D"
 * term in interarrival jitter calculation in RFC 3550 section 6.4.1.
 *
 * Default: 0 (no).
 */
#ifndef PJMEDIA_RTCP_STAT_HAS_RAW_JITTER
#   define PJMEDIA_RTCP_STAT_HAS_RAW_JITTER	0
#endif
//------------------------------------------------------------------------------
/**
 * Specify whether RTCP XR support should be built into PJMEDIA. Disabling
 * this feature will reduce footprint slightly. Note that even when this 
 * setting is enabled, RTCP XR processing will only be performed in stream 
 * if it is enabled on run-time on per stream basis. See  
 * PJMEDIA_STREAM_ENABLE_XR setting for more info.
 *
 * Default: 0 (no).
 */
#ifndef PJMEDIA_HAS_RTCP_XR
#   define PJMEDIA_HAS_RTCP_XR			0
#endif
//------------------------------------------------------------------------------
/**
 * @def PJ_DECL(type)
 * @param type The return type of the function.
 * Declare a function.
 */
#if defined(PJ_DLL)
#   if defined(PJ_EXPORTING)
#	de fine PJ_DECL(type)	    PJ_EXPORT_DECL_SPECIFIER type
#   else
#	de fine PJ_DECL(type)	    PJ_IMPORT_DECL_SPECIFIER type
#   endif
#elif !defined(PJ_DECL)
#   if defined(__cplusplus)
#	define PJ_DECL(type)	    type
#   else
#	define PJ_DECL(type)	    extern type
#   endif
#endif
//------------------------------------------------------------------------------
/**
 * @def PJ_DEF(type)
 * @param type The return type of the function.
 * Define a function.
 */
#if defined(PJ_DLL) && defined(PJ_EXPORTING)
#   define PJ_DEF(type)		    PJ_EXPORT_DEF_SPECIFIER type
#elif !defined(PJ_DEF)
#   define PJ_DEF(type)		    type
#endif
//------------------------------------------------------------------------------
/**
 * PJ_ERRNO_START is where PJLIB specific error values start.
 */
#define PJ_ERRNO_START		20000
//------------------------------------------------------------------------------
/**
 * PJ_ERRNO_SPACE_SIZE is the maximum number of errors in one of
 * the error/status range below.
 */
#define PJ_ERRNO_SPACE_SIZE	50000
//------------------------------------------------------------------------------
/**
 * @def PJ_INLINE(type)
 * @param type The return type of the function.
 * Expand the function as inline.
 */
#define PJ_INLINE(type)	 PJ_INLINE_SPECIFIER type
//------------------------------------------------------------------------------
/**
 * PJ_ERRNO_START_STATUS is where PJLIB specific status codes start.
 * Effectively the error in this class would be 70000 - 119000.
 */
#define PJ_ERRNO_START_STATUS	(PJ_ERRNO_START + PJ_ERRNO_SPACE_SIZE)
//------------------------------------------------------------------------------
/**
 * PJ_ERRNO_START_SYS converts platform specific error codes into
 * pj_status_t values.
 * Effectively the error in this class would be 120000 - 169000.
 */
#define PJ_ERRNO_START_SYS	(PJ_ERRNO_START_STATUS + PJ_ERRNO_SPACE_SIZE)
//------------------------------------------------------------------------------
/**
 * @hideinitializer
 * Fold a platform specific error into an pj_status_t code.
 *
 * @param e	The platform os error code.
 * @return	pj_status_t
 * @warning	Macro implementation; the syserr argument may be evaluated
 *		multiple times.
 */
#if PJ_NATIVE_ERR_POSITIVE
#   define PJ_STATUS_FROM_OS(e) (e == 0 ? PJ_SUCCESS : e + PJ_ERRNO_START_SYS)
#else
#   define PJ_STATUS_FROM_OS(e) (e == 0 ? PJ_SUCCESS : PJ_ERRNO_START_SYS - e)
#endif
//------------------------------------------------------------------------------
/**
 * @hideinitializer
 * Return platform os error code folded into pj_status_t code. This is
 * the macro that is used throughout the library for all PJLIB's functions
 * that returns error from operating system. Application may override
 * this macro to reduce size (e.g. by defining it to always return
 * #PJ_EUNKNOWN).
 *
 * Note:
 *  This macro MUST return non-zero value regardless whether zero is
 *  passed as the argument. The reason is to protect logic error when
 *  the operating system doesn't report error codes properly.
 *
 * @param os_code   Platform OS error code. This value may be evaluated
 *		    more than once.
 * @return	    The platform os error code folded into pj_status_t.
 */
#ifndef PJ_RETURN_OS_ERROR
#   define PJ_RETURN_OS_ERROR(os_code)   (os_code ?  PJ_STATUS_FROM_OS(os_code) : -1)
#endif
//-----------------------------------------------------------------------------
/**
 * @def PJ_UNUSED_ARG(arg)
 * @param arg   The argument name.
 * PJ_UNUSED_ARG prevents warning about unused argument in a function.
 */
#define PJ_UNUSED_ARG(arg)  (void)arg
//-----------------------------------------------------------------------------
/**
 * Tell RTCP to ignore the first N packets when calculating the
 * jitter statistics. From experimentation, the first few packets
 * (25 or so) have relatively big jitter, possibly because during
 * this time, the program is also busy setting up the signaling,
 * so they make the average jitter big.
 *
 * Default: 25.
 */
#ifndef PJMEDIA_RTCP_IGNORE_FIRST_PACKETS
#   define  PJMEDIA_RTCP_IGNORE_FIRST_PACKETS	25
#endif
//-----------------------------------------------------------------------------
/**
 * Specify the factor with wich RTCP RTT statistics should be normalized 
 * if exceptionally high. For e.g. mobile networks with potentially large
 * fluctuations, this might be unwanted.
 *
 * Use (0) to disable this feature.
 *
 * Default: 3.
 */
#ifndef PJMEDIA_RTCP_NORMALIZE_FACTOR
#   define PJMEDIA_RTCP_NORMALIZE_FACTOR	3
#endif
//------------------------------------------------------------------------------
/**
 * Declare maximum logging level/verbosity. Lower number indicates higher
 * importance, with the highest importance has level zero. The least
 * important level is five in this implementation, but this can be extended
 * by supplying the appropriate implementation.
 *
 * The level conventions:
 *  - 0: fatal error
 *  - 1: error
 *  - 2: warning
 *  - 3: info
 *  - 4: debug
 *  - 5: trace
 *  - 6: more detailed trace
 *
 * Default: 4
 */
#ifndef PJ_LOG_MAX_LEVEL
#  define PJ_LOG_MAX_LEVEL   5
#endif
//------------------------------------------------------------------------------
#endif //#ifndef __PJ_CONTACT_SIP_Config_H
