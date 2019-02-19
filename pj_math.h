#ifndef __PJ_CONTACT_SIP_Math_H
#define __PJ_CONTACT_SIP_Math_H

#include "pj_config.h"
#include "pj_string.h"
//-------------------------------------------------------------------------
/**
 * Mathematical macro
 */
#define	PJ_ABS(x)	((x) >  0 ? (x) : -(x))
#define	PJ_MAX(x, y)	((x) > (y)? (x) : (y))
#define	PJ_MIN(x, y)	((x) < (y)? (x) : (y))
//-------------------------------------------------------------------------
#if defined(PJ_HAS_FLOATING_POINT) && PJ_HAS_FLOATING_POINT != 0
    /*
     * The first choice for high precision math is to use double.
     */
typedef double pj_highprec_t;
#endif
//-------------------------------------------------------------------------
 /**
 * This structure describes statistics state.
 */
typedef struct pj_math_stat
{
    int		     n;		/* number of samples	*/
    int		     max;	/* maximum value	*/
    int		     min;	/* minimum value	*/
    int		     last;	/* last value		*/
    int		     mean;	/* mean			*/

    /* Private members */
#if PJ_HAS_FLOATING_POINT       // pj_config.h
    float	     fmean_;	/* mean(floating point) */
#else
    int		     mean_res_;	/* mean residu		*/
#endif
    pj_highprec_t    m2_;	/* variance * n		*/
} pj_math_stat;
//---------------------------------------------------------------------
/**
 * Initialize statistics state.
 *
 * @param stat	    Statistic state.
 */
PJ_INLINE(void) pj_math_stat_init(pj_math_stat *stat)
{
    pj_bzero(stat, sizeof(pj_math_stat));
}
//---------------------------------------------------------------------------
/**
 * Update statistics state as a new sample comes.
 *
 * @param stat	    Statistic state.
 * @param val	    The new sample data.
 */
PJ_INLINE(void) pj_math_stat_update(pj_math_stat *stat, int val)
{
#if PJ_HAS_FLOATING_POINT
    float	     delta;
#else
    int		     delta;
#endif

    stat->last = val;

    if (stat->n++) {
	if (stat->min > val)
	    stat->min = val;
	if (stat->max < val)
	    stat->max = val;
    } else {
	stat->min = stat->max = val;
    }

#if PJ_HAS_FLOATING_POINT
    delta = val - stat->fmean_;
    stat->fmean_ += delta/stat->n;

    /* Return mean value with 'rounding' */
    stat->mean = (int) (stat->fmean_ + 0.5);

    stat->m2_ += (int)(delta * (val-stat->fmean_));
#else
    delta = val - stat->mean;
    stat->mean += delta/stat->n;
    stat->mean_res_ += delta % stat->n;
    if (stat->mean_res_ >= stat->n) {
	++stat->mean;
	stat->mean_res_ -= stat->n;
    } else if (stat->mean_res_ <= -stat->n) {
	--stat->mean;
	stat->mean_res_ += stat->n;
    }

    stat->m2_ += delta * (val-stat->mean);
#endif
}
//------------------------------------------------------------------------------
#endif //__PJ_CONTACT_SIP_Math_H
