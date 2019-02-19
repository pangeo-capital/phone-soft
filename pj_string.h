#ifndef __PJ_CONTACT_SIP_String_H
#define __PJ_CONTACT_SIP_String_H

#include "pj_types.h"
//------------------------------------------------------------------------------
PJ_INLINE(void) pj_bzero(void *dst, pj_size_t size)
{
memset(dst, 0, size);
}
//------------------------------------------------------------------------------
/**
 * Copy buffer.
 *
 * @param dst	    The destination buffer.
 * @param src	    The source buffer.
 * @param size	    The size to copy.
 *
 * @return the destination buffer.
 */
PJ_INLINE(void*) pj_memcpy(void *dst, const void *src, pj_size_t size)
{
    return memcpy(dst, src, size);
}
//------------------------------------------------------------------------------
#endif //__PJ_CONTACT_SIP_String_H

