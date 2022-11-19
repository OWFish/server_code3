
#define DEBUG_LOGIC_TIME
#define DEBUG_LOG_INTERVAL 600000
#define DEBUG_LOG_MAX_TIME 500

#ifdef DEBUG_LOGIC_TIME
#define LOGTIME_BEGIN \
	static int __LOG_TIME_LOGS[100] = { 0 }; \
	int64_t __log_last_t, __log_curr_t;	\
	__log_curr_t = __log_last_t = _getTickCount(); \
	int64_t __log_tick_t; \
	int __log_diff_t; \
	int __log_idx = 0; \
	static int64_t __log_log_t = __log_curr_t + DEBUG_LOG_INTERVAL;

#define LOGTIME \
	__log_tick_t = _getTickCount(); \
	__log_diff_t = (int)(__log_tick_t - __log_last_t); \
	if (__log_idx >= 0 && __log_idx < 100 && __log_diff_t > __LOG_TIME_LOGS[__log_idx]) \
{ \
	__LOG_TIME_LOGS[__log_idx] = __log_diff_t; \
} \
	__log_last_t = __log_tick_t; \
	__log_idx ++;

#define SW_LOGTIME(__log_idx_) \
	__log_tick_t = _getTickCount(); \
	__log_diff_t = (int)(__log_tick_t - __log_last_t); \
	if (__log_idx_ >= 0 && __log_idx_ < 100 && __log_diff_t > __LOG_TIME_LOGS[__log_idx_]) \
{ \
	__LOG_TIME_LOGS[__log_idx_] = __log_diff_t; \
} \
	__log_idx = __log_idx_;

#define LOGTIME_END(__log_fun, __log_max_time) \
	if (__log_curr_t >= __log_log_t && __log_idx >= 0 && __log_idx < 100)	\
{	\
	bool __log_haslog = true;	\
	for (int i=0; i<__log_idx; i++)	\
{	\
	if (__LOG_TIME_LOGS[i] > __log_max_time)	\
{	\
	if (__log_haslog) {	\
	OutputMsg(rmError, "=============debug %s time:============", __log_fun);	\
	__log_haslog = false;	\
	}	\
	OutputMsg(rmError, "%d=%d", i, __LOG_TIME_LOGS[i]);	\
}	\
}	\
	memset(__LOG_TIME_LOGS, 0, sizeof(__LOG_TIME_LOGS));	\
	__log_log_t = __log_curr_t + DEBUG_LOG_INTERVAL;	\
}

#else
#define LOGTIME_BEGIN
#define LOGTIME
#define SW_LOGTIME(__log_idx_)
#define LOGTIME_END(__log_fun, __log_max_time)
#endif
