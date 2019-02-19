#include "rtcp.h"
#include "pj_config.h"
#include "pj_string.h"
#include "pj_assert.h"
#include "pj_os.h"
#include "pj_sock.h"
#include "pj_log.h"
#include "pj_errno.h"

#define THIS_FILE "rtcp.cpp"

#define RTCP_SR   200
#define RTCP_RR   201
#define RTCP_SDES 202
#define RTCP_BYE  203
#define RTCP_XR   207

enum {
    RTCP_SDES_NULL  = 0,
    RTCP_SDES_CNAME = 1,
    RTCP_SDES_NAME  = 2,
    RTCP_SDES_EMAIL = 3,
    RTCP_SDES_PHONE = 4,
    RTCP_SDES_LOC   = 5,
    RTCP_SDES_TOOL  = 6,
    RTCP_SDES_NOTE  = 7
};

#define RTP_SEQ_MOD	(1 << 16)
#define MAX_DROPOUT 	((pj_int16_t)3000)
#define MAX_MISORDER 	((pj_int16_t)100)
#define MIN_SEQUENTIAL  ((pj_int16_t)2)

//------------------------------------------------------------------------------
static void pjmedia_rtp_seq_restart(pjmedia_rtp_seq_session *seq_ctrl,
				    pj_uint16_t seq);
//------------------------------------------------------------------------------
/*
 * Initialize RTCP session setting.
 */
PJ_DEF(void) pjmedia_rtcp_session_setting_default(pjmedia_rtcp_session_setting *settings)
{
    pj_bzero(settings, sizeof(*settings));
}
//------------------------------------------------------------------------------
static void rtcp_init_seq(pjmedia_rtcp_session *sess)
{
    sess->received = 0;
    sess->exp_prior = 0;
    sess->rx_prior = 0;
    sess->transit = 0;
    sess->jitter = 0;
}
//------------------------------------------------------------------------------
/*
 * Initialize bidirectional RTCP statistics.
 *
 */
PJ_DEF(void) pjmedia_rtcp_init_stat(pjmedia_rtcp_stat *stat)
{
    pj_time_val now;

    pj_assert(stat);

    pj_bzero(stat, sizeof(pjmedia_rtcp_stat));

    pj_math_stat_init(&stat->rtt);
    pj_math_stat_init(&stat->rx.loss_period);
    pj_math_stat_init(&stat->rx.jitter);
    pj_math_stat_init(&stat->tx.loss_period);
    pj_math_stat_init(&stat->tx.jitter);

#if defined(PJMEDIA_RTCP_STAT_HAS_IPDV) && PJMEDIA_RTCP_STAT_HAS_IPDV!=0
    pj_math_stat_init(&stat->rx_ipdv);
#endif

#if defined(PJMEDIA_RTCP_STAT_HAS_RAW_JITTER) && PJMEDIA_RTCP_STAT_HAS_RAW_JITTER!=0
    pj_math_stat_init(&stat->rx_raw_jitter);
#endif

    pj_gettimeofday(&now);
    stat->start = now;
}
//------------------------------------------------------------------------------
/*
 * Initialize RTCP session.
 */
PJ_DEF(void) pjmedia_rtcp_init(pjmedia_rtcp_session *sess, 
			       char *name,
			       unsigned clock_rate,
			       unsigned samples_per_frame,
			       pj_uint32_t ssrc)
{
    pjmedia_rtcp_session_setting settings;

    pjmedia_rtcp_session_setting_default(&settings);
    settings.name = name;
    settings.clock_rate = clock_rate;
    settings.samples_per_frame = samples_per_frame;
    settings.ssrc = ssrc;

    pjmedia_rtcp_init2(sess, &settings);
}
//------------------------------------------------------------------------------
/*
 * Initialize RTCP session.
 */
PJ_DEF(void) pjmedia_rtcp_init2( pjmedia_rtcp_session *sess,
				 const pjmedia_rtcp_session_setting *settings)
{
    pjmedia_rtcp_sr_pkt *sr_pkt = &sess->rtcp_sr_pkt;
    pj_time_val now;

    /* Memset everything */
    pj_bzero(sess, sizeof(pjmedia_rtcp_session));

    /* Last RX timestamp in RTP packet */
    sess->rtp_last_ts = (unsigned)-1;

    /* Name */
    sess->name = settings->name ? settings->name : (char*)THIS_FILE;

    /* Set clock rate */
    sess->clock_rate = settings->clock_rate;
    sess->pkt_size = settings->samples_per_frame;

    /* Init common RTCP SR header */
    sr_pkt->common.version = 2;
    sr_pkt->common.count = 1;
    sr_pkt->common.pt = RTCP_SR;
    sr_pkt->common.length = pj_htons(12);
    sr_pkt->common.ssrc = pj_htonl(settings->ssrc);

    /* Copy to RTCP RR header */
    pj_memcpy(&sess->rtcp_rr_pkt.common, &sr_pkt->common, sizeof(pjmedia_rtcp_common));
    sess->rtcp_rr_pkt.common.pt = RTCP_RR;
    sess->rtcp_rr_pkt.common.length = pj_htons(7);

    /* Get time and timestamp base and frequency */
    pj_gettimeofday(&now);
    sess->tv_base = now;
    pj_get_timestamp(&sess->ts_base);
    pj_get_timestamp_freq(&sess->ts_freq);
    sess->rtp_ts_base = settings->rtp_ts_base;

    /* Initialize statistics states */
    pjmedia_rtcp_init_stat(&sess->stat);

    /* RR will be initialized on receipt of the first RTP packet. */
}
//------------------------------------------------------------------------------
/*
 * Get NTP time.
 */
PJ_DEF(pj_status_t) pjmedia_rtcp_get_ntp_time(const pjmedia_rtcp_session *sess,
					      pjmedia_rtcp_ntp_rec *ntp)
{
/* Seconds between 1900-01-01 to 1970-01-01 */
#define JAN_1970  (2208988800UL)
    pj_timestamp ts;
    pj_status_t status;

    status = pj_get_timestamp(&ts);

    /* Fill up the high 32bit part */
    ntp->hi = (pj_uint32_t)((ts.u64 - sess->ts_base.u64) / sess->ts_freq.u64)
	      + sess->tv_base.sec + JAN_1970;

    /* Calculate seconds fractions */
    ts.u64 = (ts.u64 - sess->ts_base.u64) % sess->ts_freq.u64;
    pj_assert(ts.u64 < sess->ts_freq.u64);
    ts.u64 = (ts.u64 << 32) / sess->ts_freq.u64;

    /* Fill up the low 32bit part */
    ntp->lo = ts.u32.lo;


#if (defined(PJ_WIN32) && PJ_WIN32!=0) || \
    (defined(PJ_WIN64) && PJ_WIN64!=0) || \
    (defined(PJ_WIN32_WINCE) && PJ_WIN32_WINCE!=0)

    /* On Win32, since we use QueryPerformanceCounter() as the backend
     * timestamp API, we need to protect against this bug:
     *   Performance counter value may unexpectedly leap forward
     *   http://support.microsoft.com/default.aspx?scid=KB;EN-US;Q274323
     */
    {
	/*
	 * Compare elapsed time reported by timestamp with actual elapsed
	 * time. If the difference is too excessive, then we use system
	 * time instead.
	 */

	/* MIN_DIFF needs to be large enough so that "normal" diff caused
	 * by system activity or context switch doesn't trigger the time
	 * correction.
	 */
	enum { MIN_DIFF = 400 };

	pj_time_val ts_time, elapsed, diff;

	pj_gettimeofday(&elapsed);

	ts_time.sec = ntp->hi - sess->tv_base.sec - JAN_1970;
	ts_time.msec = (long)(ntp->lo * 1000.0 / 0xFFFFFFFF);

	PJ_TIME_VAL_SUB(elapsed, sess->tv_base);

	if (PJ_TIME_VAL_LT(ts_time, elapsed)) {
	    diff = elapsed;
	    PJ_TIME_VAL_SUB(diff, ts_time);
	} else {
	    diff = ts_time;
	    PJ_TIME_VAL_SUB(diff, elapsed);
	}

	if (PJ_TIME_VAL_MSEC(diff) >= MIN_DIFF) {

	    TRACE_((sess->name, "RTCP NTP timestamp corrected by %d ms", PJ_TIME_VAL_MSEC(diff)));


	    ntp->hi = elapsed.sec + sess->tv_base.sec + JAN_1970;
	    ntp->lo = (elapsed.msec * 65536 / 1000) << 16;
	}

    }
#endif
    return status;
}
//------------------------------------------------------------------------------
PJ_DEF(void) pjmedia_rtcp_fini(pjmedia_rtcp_session *sess)
{
#if defined(PJMEDIA_HAS_RTCP_XR) && (PJMEDIA_HAS_RTCP_XR != 0)
    pjmedia_rtcp_xr_fini(&sess->xr_session);
#else
    /* Nothing to do. */
    PJ_UNUSED_ARG(sess);
#endif
}
//------------------------------------------------------------------------------
PJ_DEF(void) pjmedia_rtcp_rx_rtp( pjmedia_rtcp_session *sess,
				  unsigned seq,
				  unsigned rtp_ts,
				  unsigned payload)
{
   pjmedia_rtcp_rx_rtp2(sess, seq, rtp_ts, payload, PJ_FALSE);
}
//------------------------------------------------------------------------------
void pjmedia_rtp_seq_restart(pjmedia_rtp_seq_session *sess, pj_uint16_t seq)
{
    sess->base_seq = seq;
    sess->max_seq = seq;
    sess->bad_seq = RTP_SEQ_MOD + 1;
    sess->cycles = 0;
}
//------------------------------------------------------------------------------
void pjmedia_rtp_seq_init(pjmedia_rtp_seq_session *sess, pj_uint16_t seq)
{
    pjmedia_rtp_seq_restart(sess, seq);

    sess->max_seq = (pj_uint16_t) (seq - 1);
    sess->probation = MIN_SEQUENTIAL;
}
//------------------------------------------------------------------------------
void pjmedia_rtp_seq_update( pjmedia_rtp_seq_session *sess, 
			     pj_uint16_t seq,
			     pjmedia_rtp_status *seq_status)
{
    pj_uint16_t udelta = (pj_uint16_t) (seq - sess->max_seq);
    pjmedia_rtp_status st;
    
    /* Init status */
    st.status.value = 0;
    st.diff = 0;

    /*
     * Source is not valid until MIN_SEQUENTIAL packets with
     * sequential sequence numbers have been received.
     */
    if (sess->probation) {

	st.status.flag.probation = 1;
	
        if (seq == sess->max_seq+ 1) {
	    /* packet is in sequence */
	    st.diff = 1;
	    sess->probation--;
            sess->max_seq = seq;
            if (sess->probation == 0) {
		st.status.flag.probation = 0;
            }
	} else {

	    st.diff = 0;

	    st.status.flag.bad = 1;
	    if (seq == sess->max_seq)
		st.status.flag.dup = 1;
	    else
		st.status.flag.outorder = 1;

	    sess->probation = MIN_SEQUENTIAL - 1;
	    sess->max_seq = seq;
        }


    } else if (udelta == 0) {

	st.status.flag.dup = 1;

    } else if (udelta < MAX_DROPOUT) {
	/* in order, with permissible gap */
	if (seq < sess->max_seq) {
	    /* Sequence number wrapped - count another 64K cycle. */
	    sess->cycles += RTP_SEQ_MOD;
        }
        sess->max_seq = seq;

	st.diff = udelta;

    } else if (udelta <= (RTP_SEQ_MOD - MAX_MISORDER)) {
	/* the sequence number made a very large jump */
        if (seq == sess->bad_seq) {
	    /*
	     * Two sequential packets -- assume that the other side
	     * restarted without telling us so just re-sync
	     * (i.e., pretend this was the first packet).
	     */
	    pjmedia_rtp_seq_restart(sess, seq);
	    st.status.flag.restart = 1;
	    st.status.flag.probation = 1;
	    st.diff = 1;
	}
        else {
	    sess->bad_seq = (seq + 1) & (RTP_SEQ_MOD-1);
            st.status.flag.bad = 1;
	    st.status.flag.outorder = 1;
        }
    } else {
	/* old duplicate or reordered packet.
	 * Not necessarily bad packet (?)
	 */
	st.status.flag.outorder = 1;
    }
    

    if (seq_status) {
	seq_status->diff = st.diff;
	seq_status->status.value = st.status.value;
    }
}
//------------------------------------------------------------------------------
PJ_DEF(void) pjmedia_rtcp_rx_rtp2(pjmedia_rtcp_session *sess,
				  unsigned seq,
				  unsigned rtp_ts,
				  unsigned payload,
				  pj_bool_t discarded)
{
    pj_timestamp ts;
    pj_uint32_t arrival;
    pj_int32_t transit;
    pjmedia_rtp_status seq_st;

#if !defined(PJMEDIA_HAS_RTCP_XR) || (PJMEDIA_HAS_RTCP_XR == 0)
    PJ_UNUSED_ARG(discarded);
#endif

    if (sess->stat.rx.pkt == 0) {
	/* Init sequence for the first time. */
	pjmedia_rtp_seq_init(&sess->seq_ctrl, (pj_uint16_t)seq);
    }

    sess->stat.rx.pkt++;
    sess->stat.rx.bytes += payload;

    /* Process the RTP packet. */
    pjmedia_rtp_seq_update(&sess->seq_ctrl, (pj_uint16_t)seq, &seq_st);

    if (seq_st.status.flag.restart) {
	rtcp_init_seq(sess);
    }

    if (seq_st.status.flag.dup) {
	sess->stat.rx.dup++;
	TRACE_((sess->name, "Duplicate packet detected"));
    }

    if (seq_st.status.flag.outorder && !seq_st.status.flag.probation) {
	sess->stat.rx.reorder++;
	TRACE_((sess->name, "Out-of-order packet detected"));
    }

    if (seq_st.status.flag.bad) {
	sess->stat.rx.discard++;

#if defined(PJMEDIA_HAS_RTCP_XR) && (PJMEDIA_HAS_RTCP_XR != 0)
	pjmedia_rtcp_xr_rx_rtp(&sess->xr_session, seq,
			       -1,				 /* lost    */
			       (seq_st.status.flag.dup? 1:0),	 /* dup     */
			       (!seq_st.status.flag.dup? 1:-1),  /* discard */
			       -1,				 /* jitter  */
			       -1, 0);				 /* toh	    */
#endif

	TRACE_((sess->name, "Bad packet discarded"));
	return;
    }

    /* Only mark "good" packets */
    ++sess->received;

    /* Calculate loss periods. */
    if (seq_st.diff > 1) {
	unsigned count = seq_st.diff - 1;
	unsigned period;

	period = count * sess->pkt_size * 1000 / sess->clock_rate;
	period *= 1000;

	/* Update packet lost.
	 * The packet lost number will also be updated when we're sending
	 * outbound RTCP RR.
	 */
	sess->stat.rx.loss += (seq_st.diff - 1);
	TRACE_((sess->name, "%d packet(s) lost", seq_st.diff - 1));

	/* Update loss period stat */
	pj_math_stat_update(&sess->stat.rx.loss_period, period);
    }


    /*
     * Calculate jitter only when sequence is good (see RFC 3550 section A.8),
     * AND only when the timestamp is different than the last packet
     * (see RTP FAQ).
     */
    if (seq_st.diff == 1 && rtp_ts != sess->rtp_last_ts) {
	/* Get arrival time and convert timestamp to samples */
	pj_get_timestamp(&ts);
	ts.u64 = ts.u64 * sess->clock_rate / sess->ts_freq.u64;
	arrival = ts.u32.lo;

	transit = arrival - rtp_ts;

	/* Ignore the first N packets as they normally have bad jitter
	 * due to other threads working to establish the call
	 */
	if (sess->transit == 0 ||
	    sess->received < PJMEDIA_RTCP_IGNORE_FIRST_PACKETS)
	{
	    sess->transit = transit;
	    sess->stat.rx.jitter.min = (unsigned)-1;
	} else {
	    pj_int32_t d;
	    pj_uint32_t jitter;

	    d = transit - sess->transit;
	    if (d < 0)
		d = -d;

	    sess->jitter += d - ((sess->jitter + 8) >> 4);

	    /* Update jitter stat */
	    jitter = sess->jitter >> 4;

	    /* Convert jitter unit from samples to usec */
	    if (jitter < 4294)
		jitter = jitter * 1000000 / sess->clock_rate;
	    else {
		jitter = jitter * 1000 / sess->clock_rate;
		jitter *= 1000;
	    }
	    pj_math_stat_update(&sess->stat.rx.jitter, jitter);


#if defined(PJMEDIA_RTCP_STAT_HAS_RAW_JITTER) && PJMEDIA_RTCP_STAT_HAS_RAW_JITTER!=0
	    {
		pj_uint32_t raw_jitter;

		/* Convert raw jitter unit from samples to usec */
		if (d < 4294)
		    raw_jitter = d * 1000000 / sess->clock_rate;
		else {
		    raw_jitter = d * 1000 / sess->clock_rate;
		    raw_jitter *= 1000;
		}

		/* Update jitter stat */
		pj_math_stat_update(&sess->stat.rx_raw_jitter, raw_jitter);
	    }
#endif


#if defined(PJMEDIA_RTCP_STAT_HAS_IPDV) && PJMEDIA_RTCP_STAT_HAS_IPDV!=0
	    {
		pj_int32_t ipdv;

		ipdv = transit - sess->transit;
		/* Convert IPDV unit from samples to usec */
		if (ipdv > -2147 && ipdv < 2147)
		    ipdv = ipdv * 1000000 / (int)sess->clock_rate;
		else {
		    ipdv = ipdv * 1000 / (int)sess->clock_rate;
		    ipdv *= 1000;
		}

		/* Update jitter stat */
		pj_math_stat_update(&sess->stat.rx_ipdv, ipdv);
	    }
#endif

#if defined(PJMEDIA_HAS_RTCP_XR) && (PJMEDIA_HAS_RTCP_XR != 0)
	    pjmedia_rtcp_xr_rx_rtp(&sess->xr_session, seq,
				   0,			    /* lost    */
				   0,			    /* dup     */
				   discarded,		    /* discard */
				   (sess->jitter >> 4),	    /* jitter  */
				   -1, 0);		    /* toh     */
#endif

	    /* Update session transit */
	    sess->transit = transit;
	}
#if defined(PJMEDIA_HAS_RTCP_XR) && (PJMEDIA_HAS_RTCP_XR != 0)
    } else if (seq_st.diff > 1) {
	int i;

	/* Report RTCP XR about packet losses */
	for (i=seq_st.diff-1; i>0; --i) {
	    pjmedia_rtcp_xr_rx_rtp(&sess->xr_session, seq - i,
				   1,			    /* lost    */
				   0,			    /* dup     */
				   0,			    /* discard */
				   -1,			    /* jitter  */
				   -1, 0);		    /* toh     */
	}

	/* Report RTCP XR this packet */
	pjmedia_rtcp_xr_rx_rtp(&sess->xr_session, seq,
			       0,			    /* lost    */
			       0,			    /* dup     */
			       discarded,		    /* discard */
			       -1,			    /* jitter  */
			       -1, 0);			    /* toh     */
#endif
    }

    /* Update timestamp of last RX RTP packet */
    sess->rtp_last_ts = rtp_ts;
}
//------------------------------------------------------------------------------
PJ_DEF(void) pjmedia_rtcp_tx_rtp(pjmedia_rtcp_session *sess,
				 unsigned bytes_payload_size)
{
    /* Update statistics */
    sess->stat.tx.pkt++;
    sess->stat.tx.bytes += bytes_payload_size;
}
//------------------------------------------------------------------------------
static void parse_rtcp_report( pjmedia_rtcp_session *sess,
			       const void *pkt,
			       pj_size_t size)
{
    pjmedia_rtcp_common *common = (pjmedia_rtcp_common*) pkt;
    const pjmedia_rtcp_rr *rr = NULL;
    const pjmedia_rtcp_sr *sr = NULL;
    pj_uint32_t last_loss, jitter_samp, jitter;

    /* Parse RTCP */
    if (common->pt == RTCP_SR) {
	sr = (pjmedia_rtcp_sr*) (((char*)pkt) + sizeof(pjmedia_rtcp_common));
	if (common->count > 0 && size >= (sizeof(pjmedia_rtcp_sr_pkt))) {
	    rr = (pjmedia_rtcp_rr*)(((char*)pkt) + (sizeof(pjmedia_rtcp_common)
				    + sizeof(pjmedia_rtcp_sr)));
	}
    } else if (common->pt == RTCP_RR && common->count > 0) {
	rr = (pjmedia_rtcp_rr*)(((char*)pkt) + sizeof(pjmedia_rtcp_common));
#if defined(PJMEDIA_HAS_RTCP_XR) && (PJMEDIA_HAS_RTCP_XR != 0)
    } else if (common->pt == RTCP_XR) {
	if (sess->xr_enabled)
	    pjmedia_rtcp_xr_rx_rtcp_xr(&sess->xr_session, pkt, size);

	return;
#endif
    }


    if (sr) {
	/* Save LSR from NTP timestamp of RTCP packet */
	sess->rx_lsr = ((pj_ntohl(sr->ntp_sec) & 0x0000FFFF) << 16) | 
		       ((pj_ntohl(sr->ntp_frac) >> 16) & 0xFFFF);

	/* Calculate SR arrival time for DLSR */
	pj_get_timestamp(&sess->rx_lsr_time);

	TRACE_((sess->name, "Rx RTCP SR: ntp_ts=%p", 
		sess->rx_lsr,
		(pj_uint32_t)(sess->rx_lsr_time.u64*65536/sess->ts_freq.u64)));
    }


    /* Nothing more to do if there's no RR packet */
    if (rr == NULL)
	return;


    last_loss = sess->stat.tx.loss;

    /* Get packet loss */
    sess->stat.tx.loss = (rr->total_lost_2 << 16) +
			 (rr->total_lost_1 << 8) +
			  rr->total_lost_0;

    TRACE_((sess->name, "Rx RTCP RR: total_lost_2=%x, 1=%x, 0=%x, lost=%d", 
	    (int)rr->total_lost_2,
	    (int)rr->total_lost_1,
	    (int)rr->total_lost_0,
	    sess->stat.tx.loss));
    
    /* We can't calculate the exact loss period for TX, so just give the
     * best estimation.
     */
    if (sess->stat.tx.loss > last_loss) {
	unsigned period;

	/* Loss period in msec */
	period = (sess->stat.tx.loss - last_loss) * sess->pkt_size *
		 1000 / sess->clock_rate;

	/* Loss period in usec */
	period *= 1000;

	/* Update loss period stat */
	pj_math_stat_update(&sess->stat.tx.loss_period, period);
    }

    /* Get jitter value in usec */
    jitter_samp = pj_ntohl(rr->jitter);
    /* Calculate jitter in usec, avoiding overflows */
    if (jitter_samp <= 4294)
	jitter = jitter_samp * 1000000 / sess->clock_rate;
    else {
	jitter = jitter_samp * 1000 / sess->clock_rate;
	jitter *= 1000;
    }

    /* Update jitter statistics */
    pj_math_stat_update(&sess->stat.tx.jitter, jitter);

    /* Can only calculate if LSR and DLSR is present in RR */
    if (rr->lsr && rr->dlsr) {
	pj_uint32_t lsr, now, dlsr;
	pj_uint64_t eedelay;
	pjmedia_rtcp_ntp_rec ntp;

	/* LSR is the middle 32bit of NTP. It has 1/65536 second 
	 * resolution 
	 */
	lsr = pj_ntohl(rr->lsr);

	/* DLSR is delay since LSR, also in 1/65536 resolution */
	dlsr = pj_ntohl(rr->dlsr);

	/* Get current time, and convert to 1/65536 resolution */
	pjmedia_rtcp_get_ntp_time(sess, &ntp);
	now = ((ntp.hi & 0xFFFF) << 16) + (ntp.lo >> 16);

	/* End-to-end delay is (now-lsr-dlsr) */
	eedelay = now - lsr - dlsr;

	/* Convert end to end delay to usec (keeping the calculation in
         * 64bit space)::
	 *   sess->ee_delay = (eedelay * 1000) / 65536;
	 */
	if (eedelay < 4294) {
	    eedelay = (eedelay * 1000000) >> 16;
	} else {
	    eedelay = (eedelay * 1000) >> 16;
	    eedelay *= 1000;
	}

	TRACE_((sess->name, "Rx RTCP RR: lsr=%p, dlsr=%p (%d:%03dms), "
			   "now=%p, rtt=%p",
		lsr, dlsr, dlsr/65536, (dlsr%65536)*1000/65536,
		now, (pj_uint32_t)eedelay));
	
	/* Only save calculation if "now" is greater than lsr, or
	 * otherwise rtt will be invalid 
	 */
	if (now-dlsr >= lsr) {
	    unsigned rtt = (pj_uint32_t)eedelay;
	    
	    /* Check that eedelay value really makes sense. 
	     * We allow up to 30 seconds RTT!
	     */
	    if (eedelay > 30 * 1000 * 1000UL) {

		TRACE_((sess->name, "RTT not making any sense, ignored.."));
		goto end_rtt_calc;
	    }

#if defined(PJMEDIA_RTCP_NORMALIZE_FACTOR) && PJMEDIA_RTCP_NORMALIZE_FACTOR!=0
	    /* "Normalize" rtt value that is exceptionally high. For such
	     * values, "normalize" the rtt to be PJMEDIA_RTCP_NORMALIZE_FACTOR
	     * times the average value.
	     */
	    if (rtt > ((unsigned)sess->stat.rtt.mean *
		       PJMEDIA_RTCP_NORMALIZE_FACTOR) && sess->stat.rtt.n!=0)
	    {
		unsigned orig_rtt = rtt;
		rtt = sess->stat.rtt.mean * PJMEDIA_RTCP_NORMALIZE_FACTOR;
        	PJ_LOG(5,(sess->name, "RTT value %d usec is normalized to %d usec", orig_rtt, rtt));
	    }
#endif
	    TRACE_((sess->name, "RTCP RTT is set to %d usec", rtt));

	    /* Update RTT stat */
	    pj_math_stat_update(&sess->stat.rtt, rtt);

	} else {
	    PJ_LOG(5, (sess->name, "Internal RTCP NTP clock skew detected: "
				   "lsr=%p, now=%p, dlsr=%p (%d:%03dms), "
				   "diff=%d",
				   lsr, now, dlsr, dlsr/65536,
				   (dlsr%65536)*1000/65536,
				   dlsr-(now-lsr)));
	}
    }

end_rtt_calc:

    pj_gettimeofday(&sess->stat.tx.update);
    sess->stat.tx.update_cnt++;
}
//------------------------------------------------------------------------------
static void parse_rtcp_sdes(pjmedia_rtcp_session *sess,
			    const void *pkt,
			    pj_size_t size)
{
    pjmedia_rtcp_sdes *sdes = &sess->stat.peer_sdes;
    char *p, *p_end;
    char *b, *b_end;

    p = (char*)pkt + 8;
    p_end = (char*)pkt + size;

    pj_bzero(sdes, sizeof(*sdes));
    b = sess->stat.peer_sdes_buf_;
    b_end = b + sizeof(sess->stat.peer_sdes_buf_);

    while (p < p_end) {
	pj_uint8_t sdes_type, sdes_len;
	pj_str_t sdes_value = {NULL, 0};

	sdes_type = *p++;

	/* Check for end of SDES item list */
	if (sdes_type == RTCP_SDES_NULL || p == p_end)
	    break;

	sdes_len = *p++;

	/* Check for corrupted SDES packet */
	if (p + sdes_len > p_end)
	    break;

	/* Get SDES item */
	if (b + sdes_len < b_end) {
	    pj_memcpy(b, p, sdes_len);
	    sdes_value.ptr = b;
	    sdes_value.slen = sdes_len;
	    b += sdes_len;
	} else {
	    /* Insufficient SDES buffer */
	    PJ_LOG(5, (sess->name,
		    "Unsufficient buffer to save RTCP SDES type %d:%.*s",
		    sdes_type, sdes_len, p));
	    p += sdes_len;
	    continue;
	}

	switch (sdes_type) {
	case RTCP_SDES_CNAME:
	    sdes->cname = sdes_value;
	    break;
	case RTCP_SDES_NAME:
	    sdes->name = sdes_value;
	    break;
	case RTCP_SDES_EMAIL:
	    sdes->email = sdes_value;
	    break;
	case RTCP_SDES_PHONE:
	    sdes->phone = sdes_value;
	    break;
	case RTCP_SDES_LOC:
	    sdes->loc = sdes_value;
	    break;
	case RTCP_SDES_TOOL:
	    sdes->tool = sdes_value;
	    break;
	case RTCP_SDES_NOTE:
	    sdes->note = sdes_value;
	    break;
	default:
	    TRACE_((sess->name, "Received unknown RTCP SDES type %d:%.*s",
		    sdes_type, sdes_value.slen, sdes_value.ptr));
	    break;
	}

	p += sdes_len;
    }
}
//------------------------------------------------------------------------------
static void parse_rtcp_bye(pjmedia_rtcp_session *sess,
			   const void *pkt,
			   pj_size_t size)
{
    pj_str_t reason = {"-", 1};

    /* Check and get BYE reason */
    if (size > 8) {
	reason.slen = PJ_MIN(sizeof(sess->stat.peer_sdes_buf_),
                             *((pj_uint8_t*)pkt+8));
	pj_memcpy(sess->stat.peer_sdes_buf_, ((pj_uint8_t*)pkt+9),
		  reason.slen);
	reason.ptr = sess->stat.peer_sdes_buf_;
    }

    /* Just print RTCP BYE log */
    PJ_LOG(5, (sess->name, "Received RTCP BYE, reason: %.*s",
	       reason.slen, reason.ptr));
}
//------------------------------------------------------------------------------
PJ_DEF(void) pjmedia_rtcp_rx_rtcp( pjmedia_rtcp_session *sess,
				   const void *pkt,
				   pj_size_t size)
{
    pj_uint8_t *p, *p_end;
    p = (pj_uint8_t*)pkt;
    p_end = p + size;
    while (p < p_end) {
	pjmedia_rtcp_common *common = (pjmedia_rtcp_common*)p;
	unsigned len;
	len = (pj_ntohs((pj_uint16_t)common->length)+1) * 4;
	switch(common->pt) {
	case RTCP_SR:
	case RTCP_RR:
	case RTCP_XR:
	    parse_rtcp_report(sess, p, len);
	    break;
	case RTCP_SDES:
	    parse_rtcp_sdes(sess, p, len);
	    break;
	case RTCP_BYE:
	    parse_rtcp_bye(sess, p, len);
	    break;
	default:
	    /* Ignore unknown RTCP */
	    TRACE_((sess->name, "Received unknown RTCP packet type=%d",
		    common->pt));
	    break;
	}

	p += len;
    }  
}
//------------------------------------------------------------------------------
PJ_DEF(void) pjmedia_rtcp_build_rtcp(pjmedia_rtcp_session *sess, 
				     void **ret_p_pkt, int *len)
{
    pj_uint32_t expected, expected_interval, received_interval, lost_interval;
    pjmedia_rtcp_sr *sr;
    pjmedia_rtcp_rr *rr;
    pj_timestamp ts_now;
    pjmedia_rtcp_ntp_rec ntp;

    /* Get current NTP time. */
    pj_get_timestamp(&ts_now);
    pjmedia_rtcp_get_ntp_time(sess, &ntp);


    /* See if we have transmitted RTP packets since last time we
     * sent RTCP SR.
     */
    if (sess->stat.tx.pkt != pj_ntohl(sess->rtcp_sr_pkt.sr.sender_pcount)) {
	pj_time_val ts_time;
	pj_uint32_t rtp_ts;

	/* So we should send RTCP SR */
	*ret_p_pkt = (void*) &sess->rtcp_sr_pkt;
	*len = sizeof(pjmedia_rtcp_sr_pkt);
	rr = &sess->rtcp_sr_pkt.rr;
	sr = &sess->rtcp_sr_pkt.sr;

	/* Update packet count */
	sr->sender_pcount = pj_htonl(sess->stat.tx.pkt);

	/* Update octets count */
	sr->sender_bcount = pj_htonl(sess->stat.tx.bytes);

	/* Fill in NTP timestamp in SR. */
	sr->ntp_sec = pj_htonl(ntp.hi);
	sr->ntp_frac = pj_htonl(ntp.lo);

	/* Fill in RTP timestamp (corresponds to NTP timestamp) in SR. */
	ts_time.sec = ntp.hi - sess->tv_base.sec - JAN_1970;
	ts_time.msec = (long)(ntp.lo * 1000.0 / 0xFFFFFFFF);
	rtp_ts = sess->rtp_ts_base +
		 (pj_uint32_t)(sess->clock_rate*ts_time.sec) +
		 (pj_uint32_t)(sess->clock_rate*ts_time.msec/1000);
	sr->rtp_ts = pj_htonl(rtp_ts);

	TRACE_((sess->name, "TX RTCP SR: ntp_ts=%p", 
			   ((ntp.hi & 0xFFFF) << 16) + ((ntp.lo & 0xFFFF0000) 
				>> 16)));


    } else {
	/* We should send RTCP RR then */
	*ret_p_pkt = (void*) &sess->rtcp_rr_pkt;
	*len = sizeof(pjmedia_rtcp_rr_pkt);
	rr = &sess->rtcp_rr_pkt.rr;
	sr = NULL;
    }
    
    /* SSRC and last_seq */
    rr->ssrc = pj_htonl(sess->peer_ssrc);
    rr->last_seq = (sess->seq_ctrl.cycles & 0xFFFF0000L);
    /* Since this is an "+=" operation, make sure we update last_seq on
     * both RR and SR.
     */
    sess->rtcp_sr_pkt.rr.last_seq += sess->seq_ctrl.max_seq;
    sess->rtcp_rr_pkt.rr.last_seq += sess->seq_ctrl.max_seq;
    rr->last_seq = pj_htonl(rr->last_seq);


    /* Jitter */
    rr->jitter = pj_htonl(sess->jitter >> 4);
    
    
    /* Total lost. */
    expected = pj_ntohl(rr->last_seq) - sess->seq_ctrl.base_seq;

    /* This is bug: total lost already calculated on each incoming RTP!
    if (expected >= sess->received)
	sess->stat.rx.loss = expected - sess->received;
    else
	sess->stat.rx.loss = 0;
    */

    rr->total_lost_2 = (sess->stat.rx.loss >> 16) & 0xFF;
    rr->total_lost_1 = (sess->stat.rx.loss >> 8) & 0xFF;
    rr->total_lost_0 = (sess->stat.rx.loss & 0xFF);

    /* Fraction lost calculation */
    expected_interval = expected - sess->exp_prior;
    sess->exp_prior = expected;
    
    received_interval = sess->received - sess->rx_prior;
    sess->rx_prior = sess->received;
    
    if (expected_interval >= received_interval)
	lost_interval = expected_interval - received_interval;
    else
	lost_interval = 0;
    
    if (expected_interval==0 || lost_interval == 0) {
	rr->fract_lost = 0;
    } else {
	rr->fract_lost = (lost_interval << 8) / expected_interval;
    }
    
    if (sess->rx_lsr_time.u64 == 0 || sess->rx_lsr == 0) {
	rr->lsr = 0;
	rr->dlsr = 0;
    } else {
	pj_timestamp ts;
	pj_uint32_t lsr = sess->rx_lsr;
	pj_uint64_t lsr_time = sess->rx_lsr_time.u64;
	pj_uint32_t dlsr;
	
	/* Convert LSR time to 1/65536 seconds resolution */
	lsr_time = (lsr_time << 16) / sess->ts_freq.u64;

	/* Fill in LSR.
	   LSR is the middle 32bit of the last SR NTP time received.
	 */
	rr->lsr = pj_htonl(lsr);
	
	/* Fill in DLSR.
	   DLSR is Delay since Last SR, in 1/65536 seconds.
	 */
	ts.u64 = ts_now.u64;

	/* Convert interval to 1/65536 seconds value */
	ts.u64 = (ts.u64 << 16) / sess->ts_freq.u64;

	/* Get DLSR */
	dlsr = (pj_uint32_t)(ts.u64 - lsr_time);
	rr->dlsr = pj_htonl(dlsr);

	TRACE_((sess->name,"Tx RTCP RR: lsr=%p, lsr_time=%p, now=%p, dlsr=%p"
			   "(%ds:%03dms)",
			   lsr,
			   (pj_uint32_t)lsr_time,
			   (pj_uint32_t)ts.u64,
			   dlsr,
			   dlsr/65536,
			   (dlsr%65536)*1000/65536 ));
    }

    /* Update counter */
    pj_gettimeofday(&sess->stat.rx.update);
    sess->stat.rx.update_cnt++;
}
//------------------------------------------------------------------------------
PJ_DEF(pj_status_t) pjmedia_rtcp_build_rtcp_sdes(
					    pjmedia_rtcp_session *session,
					    void *buf,
					    pj_size_t *length,
					    const pjmedia_rtcp_sdes *sdes)
{
    pjmedia_rtcp_common *hdr;
    pj_uint8_t *p;
    pj_size_t len;

    PJ_ASSERT_RETURN(session && buf && length && sdes, PJ_EINVAL);

    /* Verify SDES item length */
    if (sdes->cname.slen > 255 || sdes->name.slen  > 255 ||
	sdes->email.slen > 255 || sdes->phone.slen > 255 ||
	sdes->loc.slen   > 255 || sdes->tool.slen  > 255 ||
	sdes->note.slen  > 255)
    {
	return PJ_EINVAL;
    }

    /* Verify buffer length */
    len = sizeof(*hdr);
    if (sdes->cname.slen) len += sdes->cname.slen + 2;
    if (sdes->name.slen)  len += sdes->name.slen  + 2;
    if (sdes->email.slen) len += sdes->email.slen + 2;
    if (sdes->phone.slen) len += sdes->phone.slen + 2;
    if (sdes->loc.slen)   len += sdes->loc.slen   + 2;
    if (sdes->tool.slen)  len += sdes->tool.slen  + 2;
    if (sdes->note.slen)  len += sdes->note.slen  + 2;
    len++; /* null termination */
    len = ((len+3)/4) * 4;
    if (len > *length)
	return PJ_ETOOSMALL;

    /* Build RTCP SDES header */
    hdr = (pjmedia_rtcp_common*)buf;
    pj_memcpy(hdr, &session->rtcp_sr_pkt.common,  sizeof(*hdr));
    hdr->pt = RTCP_SDES;
    hdr->length = pj_htons((pj_uint16_t)(len/4 - 1));

    /* Build RTCP SDES items */
    p = (pj_uint8_t*)hdr + sizeof(*hdr);
#define BUILD_SDES_ITEM(SDES_NAME, SDES_TYPE) \
    if (sdes->SDES_NAME.slen) { \
	*p++ = SDES_TYPE; \
	*p++ = (pj_uint8_t)sdes->SDES_NAME.slen; \
	pj_memcpy(p, sdes->SDES_NAME.ptr, sdes->SDES_NAME.slen); \
	p += sdes->SDES_NAME.slen; \
    }
    BUILD_SDES_ITEM(cname, RTCP_SDES_CNAME);
    BUILD_SDES_ITEM(name,  RTCP_SDES_NAME);
    BUILD_SDES_ITEM(email, RTCP_SDES_EMAIL);
    BUILD_SDES_ITEM(phone, RTCP_SDES_PHONE);
    BUILD_SDES_ITEM(loc,   RTCP_SDES_LOC);
    BUILD_SDES_ITEM(tool,  RTCP_SDES_TOOL);
    BUILD_SDES_ITEM(note,  RTCP_SDES_NOTE);
#undef BUILD_SDES_ITEM

    /* Null termination */
    *p++ = 0;

    /* Pad to 32bit */
    while ((p-(pj_uint8_t*)buf) % 4)
	*p++ = 0;

    /* Finally */
    pj_assert((int)len == p-(pj_uint8_t*)buf);
    *length = len;

    return PJ_SUCCESS;
}
//-----------------------------------------------------------------------------
PJ_DEF(pj_status_t) pjmedia_rtcp_build_rtcp_bye(pjmedia_rtcp_session *session,
						void *buf,
						pj_size_t *length,
						const pj_str_t *reason)
{
    pjmedia_rtcp_common *hdr;
    pj_uint8_t *p;
    pj_size_t len;

    PJ_ASSERT_RETURN(session && buf && length, PJ_EINVAL);

    /* Verify BYE reason length */
    if (reason && reason->slen > 255)
	return PJ_EINVAL;

    /* Verify buffer length */
    len = sizeof(*hdr);
    if (reason && reason->slen) len += reason->slen + 1;
    len = ((len+3)/4) * 4;
    if (len > *length)
	return PJ_ETOOSMALL;

    /* Build RTCP BYE header */
    hdr = (pjmedia_rtcp_common*)buf;
    pj_memcpy(hdr, &session->rtcp_sr_pkt.common,  sizeof(*hdr));
    hdr->pt = RTCP_BYE;
    hdr->length = pj_htons((pj_uint16_t)(len/4 - 1));

    /* Write RTCP BYE reason */
    p = (pj_uint8_t*)hdr + sizeof(*hdr);
    if (reason && reason->slen) {
	*p++ = (pj_uint8_t)reason->slen;
	pj_memcpy(p, reason->ptr, reason->slen);
	p += reason->slen;
    }

    /* Pad to 32bit */
    while ((p-(pj_uint8_t*)buf) % 4)
	*p++ = 0;

    pj_assert((int)len == p-(pj_uint8_t*)buf);
    *length = len;

    return PJ_SUCCESS;
}
//------------------------------------------------------------------------------
PJ_DEF(pj_status_t) pjmedia_rtcp_enable_xr( pjmedia_rtcp_session *sess, 
					    pj_bool_t enable)
{
#if defined(PJMEDIA_HAS_RTCP_XR) && (PJMEDIA_HAS_RTCP_XR != 0)

    /* Check if request won't change anything */
    if (!(enable ^ sess->xr_enabled))
	return PJ_SUCCESS;

    if (!enable) {
	sess->xr_enabled = PJ_FALSE;
	return PJ_SUCCESS;
    }

    pjmedia_rtcp_xr_init(&sess->xr_session, sess, 0, 1);
    sess->xr_enabled = PJ_TRUE;

    return PJ_SUCCESS;

#else

    PJ_UNUSED_ARG(sess);
    PJ_UNUSED_ARG(enable);
    return PJ_ENOTSUP;

#endif
}
//------------------------------------------------------------------------------

