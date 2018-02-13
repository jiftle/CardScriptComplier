#include <stdio.h>
#include "common.h"
#include "complier.h"

#if ( defined _WIN32 )

#define APIENTRY __stdcall

BOOL APIENTRY DllMain(HANDLE hModule
	, DWORD ul_reason_for_call
	, LPVOID lpReserved)
{
	char    buffer[64 + 1] = "";
	long    buflen = 64;

	//----------------策略，先读配置文件，如果找不到配置文件就行使用默认的
	gobal_logger = CreateLogHandleFromConfig("CardScriptComplier.conf", NULL);
	if (gobal_logger)
	{
		/*  以不同日志等级写行日志  */
		DebugLog(gobal_logger, __FILE__, __LINE__, "dll is loaded,enter in DllMain");

		switch (ul_reason_for_call)
		{
		case DLL_PROCESS_ATTACH:
			DebugLog(gobal_logger, __FILE__, __LINE__, "DLL_PROCESS_ATTACH");
			break;
		case DLL_THREAD_ATTACH:
			DebugLog(gobal_logger, __FILE__, __LINE__, "DLL_THREAD_ATTACH");
			break;
		case DLL_THREAD_DETACH:
			DebugLog(gobal_logger, __FILE__, __LINE__, "DLL_THREAD_DETACH");
			break;
		case DLL_PROCESS_DETACH:
			DebugLog(gobal_logger, __FILE__, __LINE__, "DLL_PROCESS_DETACH");
			break;
		}


		return TRUE;
	}

	gobal_logger = CreateLogHandle();
	if (gobal_logger == NULL)
	{
		printf("create log handler fail.\n");
		return TRUE;
	}

	/*  设置日志输出文件名  */
	SetLogOutput(gobal_logger, LOG_OUTPUT_FILE, "CardScriptComplier.log", LOG_NO_OUTPUTFUNC);
	/*  设置当前日志过滤等级  */
	SetLogLevel(gobal_logger, LOG_LEVEL_INFO);
	/*  设置当前行日志风格方案  */
	SetLogStyles(gobal_logger, LOG_STYLES_DEFAULT, LOG_NO_STYLEFUNC);
	/*  设置日志转储方案  */
	SetLogRotateMode(gobal_logger, LOG_ROTATEMODE_PER_DAY);//每天转储

	WarnLog(gobal_logger, __FILE__, __LINE__, "config is loaded fail");


	/*  以不同日志等级写行日志  */
	DebugLog(gobal_logger, __FILE__, __LINE__, "dll is loaded,enter in DllMain");

	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		DebugLog(gobal_logger, __FILE__, __LINE__, "DLL_PROCESS_ATTACH");
		break;
	case DLL_THREAD_ATTACH:
		DebugLog(gobal_logger, __FILE__, __LINE__, "DLL_THREAD_ATTACH");
		break;
	case DLL_THREAD_DETACH:
		DebugLog(gobal_logger, __FILE__, __LINE__, "DLL_THREAD_DETACH");
		break;
	case DLL_PROCESS_DETACH:
		DebugLog(gobal_logger, __FILE__, __LINE__, "DLL_PROCESS_DETACH");
		break;
	}


	return TRUE;
}

#elif ( defined __unix ) || ( defined _AIX ) || ( defined __linux__ ) || ( defined __hpux )

/************************************************************************/
/* 构造函数                                                             */
/************************************************************************/
void __attribute__((constructor)) x_init(void)
{

	char    buffer[64 + 1] = "";
	long    buflen = 64;

	//----------------策略，先读配置文件，如果找不到配置文件就行使用默认的
	gobal_logger = CreateLogHandleFromConfig("CardScriptComplier.conf", NULL);
	if (gobal_logger)
	{
		/*  以不同日志等级写行日志  */
		DebugLog(gobal_logger, __FILE__, __LINE__, "dll is loaded,enter in x_init");

		return;
	}

	gobal_logger = CreateLogHandle();
	if (gobal_logger == NULL)
	{
		printf("create log handler fail.\n");
		return;
	}

	/*  设置日志输出文件名  */
	SetLogOutput(gobal_logger, LOG_OUTPUT_FILE, "CardScriptComplier.log", LOG_NO_OUTPUTFUNC);
	/*  设置当前日志过滤等级  */
	SetLogLevel(gobal_logger, LOG_LEVEL_INFO);
	/*  设置当前行日志风格方案  */
	SetLogStyles(gobal_logger, LOG_STYLES_DEFAULT, LOG_NO_STYLEFUNC);
	/*  设置日志转储方案  */
	SetLogRotateMode(gobal_logger, LOG_ROTATEMODE_PER_DAY);//每天转储

	WarnLog(gobal_logger, __FILE__, __LINE__, "config is loaded fail");


	/*  以不同日志等级写行日志  */
	DebugLog(gobal_logger, __FILE__, __LINE__, "dll is loaded,enter in x_init");
}

/************************************************************************/
/* 析构函数                                                             */
/************************************************************************/
void __attribute__((destructor))  x_fini(void)
{

	DebugLog(gobal_logger, __FILE__, __LINE__, "dll is unload,enter in x_fini");

	/*  销毁日志句柄  */
	DestroyLogHandle(gobal_logger);
}


#endif

/************************************************************************/
/* 获取版本                                                             */
/************************************************************************/
DLL_EXPORT int get_version(char* ver)
{
	//----------------得到当前编译时间-------------------
	char szComplieDate[256] = { 0 };
	sprintf(szComplieDate, "version: %s.%d%02d%02d", VERINFO, YEAR, MONTH + 1, DAY);
	strcpy(ver, "model: CardScriptComplier"); //动态库名字
	strcat(ver, " | ");
	strcat(ver, szComplieDate); //编译日期

	return 0;
}



/************************************************************************/
/* 编译脚本                                                             */
/************************************************************************/
DLL_EXPORT int csc(char* filename)
{
	return CardScriptComplier(filename);
}