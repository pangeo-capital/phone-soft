#ifndef __PJ_CONTACT_SIP_Sock_H
#define __PJ_CONTACT_SIP_Sock_H

#include "pj_types.h"
/*****************************************************************************
 *
 * SOCKET ADDRESS MANIPULATION.
 *
 *****************************************************************************
 */
/**
 * Convert 16-bit value from network byte order to host byte order.
 *
 * @param netshort  16-bit network value.
 * @return	    16-bit host value.
 */
PJ_DECL(pj_uint16_t) pj_ntohs(pj_uint16_t netshort);
//------------------------------------------------------------------------------
/**
 * Convert 32-bit value from network byte order to host byte order.
 *
 * @param netlong   32-bit network value.
 * @return	    32-bit host value.
 */
PJ_DECL(pj_uint32_t) pj_ntohl(pj_uint32_t netlong);
//------------------------------------------------------------------------------
/**
 * Convert 16-bit value from host byte order to network byte order.
 *
 * @param hostshort 16-bit host value.
 * @return	    16-bit network value.
 */
PJ_DECL(pj_uint16_t) pj_htons(pj_uint16_t hostshort);
//------------------------------------------------------------------------------
/**
 * Convert 32-bit value from host byte order to network byte order.
 *
 * @param hostlong  32-bit host value.
 * @return	    32-bit network value.
 */
PJ_DECL(pj_uint32_t) pj_htonl(pj_uint32_t hostlong);
//------------------------------------------------------------------------------
#endif //#ifndef __PJ_CONTACT_SIP_Sock_H

