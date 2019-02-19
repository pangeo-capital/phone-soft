#include "pj_os.h"
#include <Classes.hpp>

#define SECS_TO_FT_MULT 10000000

static LARGE_INTEGER base_time;

//----------------------------------------------------------------------------
PJ_DEF(pj_status_t) pj_gettimeofday(pj_time_val *tv)
{
#ifdef WINCE_TIME    //Windows CE/Windows Mobile platforms
    pj_timestamp tick;
    pj_uint64_t msec_elapsed;
#else
    SYSTEMTIME st;
    FILETIME ft;
    LARGE_INTEGER li;
#endif
    pj_status_t status;

    if (base_time.QuadPart == 0) {
	status = get_base_time();
	if (status != PJ_SUCCESS)
	    return status;
    }

#ifdef WINCE_TIME
    do {
	status = pj_get_timestamp(&tick);
	if (status != PJ_SUCCESS)
	    return status;

	if (tick.u64 - g_last_update.u64 >= g_update_period) {
	    pj_enter_critical_section();
	    if (tick.u64 - g_last_update.u64 >= g_update_period) {
		g_last_update.u64 = tick.u64;
		check_system_time(tick.u64 - g_start_tick.u64);
	    }
	    pj_leave_critical_section();
	} else {
	    break;
	}
    } while (1);

    msec_elapsed = pj_elapsed_msec64(&g_start_tick, &tick);

    tv->sec = (long)(g_start_time.QuadPart + msec_elapsed/1000);
    tv->msec = (long)(msec_elapsed % 1000);
#else
    /* Standard Win32 GetLocalTime */
    GetLocalTime(&st);
    SystemTimeToFileTime(&st, &ft);

    li.LowPart = ft.dwLowDateTime;
    li.HighPart = ft.dwHighDateTime;
    li.QuadPart /= SECS_TO_FT_MULT;
    li.QuadPart -= base_time.QuadPart;

    tv->sec = li.LowPart;
    tv->msec = st.wMilliseconds;
#endif	/* WINCE_TIME */

    return PJ_SUCCESS;
}
//------------------------------------------------------------------------------
// Find 1st Jan 1970 as a FILETIME
static pj_status_t get_base_time(void)
{
    SYSTEMTIME st;
    FILETIME ft;
    pj_status_t status = PJ_SUCCESS;

    memset(&st,0,sizeof(st));
    st.wYear=1970;
    st.wMonth=1;
    st.wDay=1;
    SystemTimeToFileTime(&st, &ft);

    base_time.LowPart = ft.dwLowDateTime;
    base_time.HighPart = ft.dwHighDateTime;
    base_time.QuadPart /= SECS_TO_FT_MULT;

#ifdef WINCE_TIME
    pj_enter_critical_section();
    status = init_start_time();
    pj_leave_critical_section();
#endif

    return status;
}
//------------------------------------------------------------------------------
/*
 * Use QueryPerformanceCounter and QueryPerformanceFrequency.
 * This should be the default implementation to be used on Windows.
 */
PJ_DEF(pj_status_t) pj_get_timestamp(pj_timestamp *ts)
{
    LARGE_INTEGER val;

    if (!QueryPerformanceCounter(&val))
	return PJ_RETURN_OS_ERROR(GetLastError());

    ts->u64 = val.QuadPart;
    return PJ_SUCCESS;
}
//------------------------------------------------------------------------------
PJ_DEF(pj_status_t) pj_get_timestamp_freq(pj_timestamp *freq)
{
    LARGE_INTEGER val;

    if (!QueryPerformanceFrequency(&val))
	return PJ_RETURN_OS_ERROR(GetLastError());

    freq->u64 = val.QuadPart;
    return PJ_SUCCESS;
}
//------------------------------------------------------------------------------
PJ_DEF(void) pj_time_val_normalize(pj_time_val *t)
{
    PJ_CHECK_STACK();

    if (t->msec >= 1000) {
	t->sec += (t->msec / 1000);
	t->msec = (t->msec % 1000);
    }
    else if (t->msec <= -1000) {
	do {
	    t->sec--;
	    t->msec += 1000;
        } while (t->msec <= -1000);
    }

    if (t->sec >= 1 && t->msec < 0) {
	t->sec--;
	t->msec += 1000;

    } else if (t->sec < 0 && t->msec > 0) {
	t->sec++;
	t->msec -= 1000;
    }
}
//------------------------------------------------------------------------------


