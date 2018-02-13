#pragma once
#include "LOGCONF.h"

//----------------------------------指定版本--------------------------------
#define VERINFO "v1.0.1"


//导出符号
#if (defined _WIN32)
#define DLL_EXPORT		__declspec(dllexport)
//#define DLL_EXPORT		extern "C __stdcall
#elif ( defined __linux__)
#define DLL_EXPORT __attribute__ ((visibility("default")))
#endif



//#if ( defined _WIN32 )
//#ifndef _WINDLL_FUNC
//#define _WINDLL_FUNC		_declspec(dllexport)
//#endif
//#elif ( defined __unix ) || ( defined _AIX ) || ( defined __linux__ ) || ( defined __hpux )
//#ifndef _WINDLL_FUNC
//#define _WINDLL_FUNC
//#endif
//#endif

//-----------------定义日期宏-----------------------
#define YEAR ((((__DATE__ [7] - '0') * 10 + (__DATE__ [8] - '0')) * 10 \
	+ (__DATE__ [9] - '0')) * 10 + (__DATE__ [10] - '0'))

#define MONTH (__DATE__ [2] == 'n' ? 0 \
	: __DATE__ [2] == 'b' ? 1 \
	: __DATE__ [2] == 'r' ? (__DATE__ [0] == 'M' ? 2 : 3) \
	: __DATE__ [2] == 'y' ? 4 \
	: __DATE__ [2] == 'n' ? 5 \
	: __DATE__ [2] == 'l' ? 6 \
	: __DATE__ [2] == 'g' ? 7 \
	: __DATE__ [2] == 'p' ? 8 \
	: __DATE__ [2] == 't' ? 9 \
	: __DATE__ [2] == 'v' ? 10 : 11)

#define DAY ((__DATE__ [4] == ' ' ? 0 : __DATE__ [4] - '0') * 10 \
	+ (__DATE__ [5] - '0'))

#define DATE_AS_INT (((YEAR - 2000) * 12 + MONTH) * 31 + DAY)

//日志风格
//#define LOG_STYLES_DEFAULT  ( LOG_STYLE_DATETIMEMS | LOG_STYLE_LOGLEVEL | LOG_STYLE_PID | LOG_STYLE_TID | LOG_STYLE_SOURCE | LOG_STYLE_FORMAT | LOG_STYLE_NEWLINE)
#define LOG_STYLES_DEFAULT  ( LOG_STYLE_DATETIMEMS | LOG_STYLE_LOGLEVEL | LOG_STYLE_SOURCE | LOG_STYLE_FORMAT | LOG_STYLE_NEWLINE)

//extern LOG *gobal_logger = NULL;/* 日志句柄指针 */
LOG *gobal_logger = NULL;/* 日志句柄指针 */