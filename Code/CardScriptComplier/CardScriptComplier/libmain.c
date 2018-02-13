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

	//----------------���ԣ��ȶ������ļ�������Ҳ��������ļ�����ʹ��Ĭ�ϵ�
	gobal_logger = CreateLogHandleFromConfig("CardScriptComplier.conf", NULL);
	if (gobal_logger)
	{
		/*  �Բ�ͬ��־�ȼ�д����־  */
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

	/*  ������־����ļ���  */
	SetLogOutput(gobal_logger, LOG_OUTPUT_FILE, "CardScriptComplier.log", LOG_NO_OUTPUTFUNC);
	/*  ���õ�ǰ��־���˵ȼ�  */
	SetLogLevel(gobal_logger, LOG_LEVEL_INFO);
	/*  ���õ�ǰ����־��񷽰�  */
	SetLogStyles(gobal_logger, LOG_STYLES_DEFAULT, LOG_NO_STYLEFUNC);
	/*  ������־ת������  */
	SetLogRotateMode(gobal_logger, LOG_ROTATEMODE_PER_DAY);//ÿ��ת��

	WarnLog(gobal_logger, __FILE__, __LINE__, "config is loaded fail");


	/*  �Բ�ͬ��־�ȼ�д����־  */
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
/* ���캯��                                                             */
/************************************************************************/
void __attribute__((constructor)) x_init(void)
{

	char    buffer[64 + 1] = "";
	long    buflen = 64;

	//----------------���ԣ��ȶ������ļ�������Ҳ��������ļ�����ʹ��Ĭ�ϵ�
	gobal_logger = CreateLogHandleFromConfig("CardScriptComplier.conf", NULL);
	if (gobal_logger)
	{
		/*  �Բ�ͬ��־�ȼ�д����־  */
		DebugLog(gobal_logger, __FILE__, __LINE__, "dll is loaded,enter in x_init");

		return;
	}

	gobal_logger = CreateLogHandle();
	if (gobal_logger == NULL)
	{
		printf("create log handler fail.\n");
		return;
	}

	/*  ������־����ļ���  */
	SetLogOutput(gobal_logger, LOG_OUTPUT_FILE, "CardScriptComplier.log", LOG_NO_OUTPUTFUNC);
	/*  ���õ�ǰ��־���˵ȼ�  */
	SetLogLevel(gobal_logger, LOG_LEVEL_INFO);
	/*  ���õ�ǰ����־��񷽰�  */
	SetLogStyles(gobal_logger, LOG_STYLES_DEFAULT, LOG_NO_STYLEFUNC);
	/*  ������־ת������  */
	SetLogRotateMode(gobal_logger, LOG_ROTATEMODE_PER_DAY);//ÿ��ת��

	WarnLog(gobal_logger, __FILE__, __LINE__, "config is loaded fail");


	/*  �Բ�ͬ��־�ȼ�д����־  */
	DebugLog(gobal_logger, __FILE__, __LINE__, "dll is loaded,enter in x_init");
}

/************************************************************************/
/* ��������                                                             */
/************************************************************************/
void __attribute__((destructor))  x_fini(void)
{

	DebugLog(gobal_logger, __FILE__, __LINE__, "dll is unload,enter in x_fini");

	/*  ������־���  */
	DestroyLogHandle(gobal_logger);
}


#endif

/************************************************************************/
/* ��ȡ�汾                                                             */
/************************************************************************/
DLL_EXPORT int get_version(char* ver)
{
	//----------------�õ���ǰ����ʱ��-------------------
	char szComplieDate[256] = { 0 };
	sprintf(szComplieDate, "version: %s.%d%02d%02d", VERINFO, YEAR, MONTH + 1, DAY);
	strcpy(ver, "model: CardScriptComplier"); //��̬������
	strcat(ver, " | ");
	strcat(ver, szComplieDate); //��������

	return 0;
}



/************************************************************************/
/* ����ű�                                                             */
/************************************************************************/
DLL_EXPORT int csc(char* filename)
{
	return CardScriptComplier(filename);
}