#pragma once
//==============================================================
// ͷ�ļ����������ﶨ��
//==============================================================
#if defined(_MSC_VER)
#define strcasecmp _stricmp
#endif

#pragma warning(disable:4996) //ȫ���ص�

#include "LOGCONF.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <ctype.h>

#include "def.h"
#include "token.h"
//#include "common.h"

extern LOG *gobal_logger;/* ��־���ָ�� */



