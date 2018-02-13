#include "arg.h"


//($iKeyDvsNum$)>{iKeyDvsNum}


void gobal_arg_LinkList_init()
{
	gobal_arg_LinkList_index = 0;
	gobal_arg_LinkList_add("iKeyDvsNum", "01");
	gobal_arg_LinkList_add("offset", "CA");
	gobal_arg_LinkList_add("proteIndex", "CA");
	gobal_arg_LinkList_add("asn", "030405060708090A");
	gobal_arg_LinkList_add("psn", "030405060708090A");
	gobal_arg_LinkList_add("makeCardID", "0102030405060708090A0B0C");
	gobal_arg_LinkList_add("appSN", "0102030405060708090A");
}

void gobal_arg_LinkList_add(char* name, char* value)
{
	strcpy(gobal_arg_LinkList[gobal_arg_LinkList_index].name, name);
	strcpy(gobal_arg_LinkList[gobal_arg_LinkList_index].value, value);
	gobal_arg_LinkList_index ++;
}

int lookup_arg(char* name, char* value)
{
	return gobal_arg_LinkList_get(name,value);
}

int gobal_arg_LinkList_get(char* name, char* value)
{
	int i;

	for ( i = 0; i < gobal_arg_LinkList_index; i++)
	{
		//大小写不敏感
		if (strcasecmp(name,gobal_arg_LinkList[i].name)==0) {
			strcpy(value, gobal_arg_LinkList[i].value);
			return 1;
		}
	}

	return 0;
}

//打印参数列表
void gobal_arg_LinkList_print()
{
	int i;
	char buf[1024];

	sprintf(buf, "-----------------args------------------");
	DebugLog(gobal_logger, __FILE__, __LINE__, buf);

	for (i = 0; i < gobal_arg_LinkList_index; i++)
	{
		sprintf(buf, "[%04X] $%s$ = %s",i, gobal_arg_LinkList[i].name, gobal_arg_LinkList[i].value);
		DebugLog(gobal_logger, __FILE__, __LINE__, buf);
	}

}
