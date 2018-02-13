#include "const.h"

void gobal_cnt_list_init()
{
	gobal_cnt_index = 0;
	gobal_cnt_list_add("KeyBlock_MaskKey", 2);//主密钥存储开始索引
	gobal_cnt_list_add("KeyBlock_PSAMKey", 102);//PSAM母卡密钥存储开始索引
	gobal_cnt_list_add("KeyBlock_INIKey", 202);//洗卡母卡密钥存储开始索引
	gobal_cnt_list_add("KeyBlock_CITYKey", 40);//CPU多客户版 二级密钥

											   //---------------------------------
	gobal_cnt_list_add("KeyIndex_CCK", 0);//卡片主控
	gobal_cnt_list_add("KeyIndex_CMK", 1);//卡片维护
	gobal_cnt_list_add("KeyIndex_ACK", 2);//应用主控
	gobal_cnt_list_add("KeyIndex_AMK", 3);//应用维护
}

void gobal_cnt_list_add(char* name, int value)
{
	strcpy(gobal_cnt_list[gobal_cnt_index].name, name);
	gobal_cnt_list[gobal_cnt_index].value = value;
	gobal_cnt_index++;
}

int gobal_cnt_list_get(char* name, int* value)
{
	int i;

	for (i = 0; i < gobal_cnt_index; i++)
	{
		//大小写不敏感
		if (strcasecmp(name, gobal_cnt_list[i].name) == 0) {
			*value = gobal_cnt_list[i].value;
			return 1;
		}
	}

	return 0;
}

int lookup_cnt(char* name, int* value)
{
	return gobal_cnt_list_get(name, value);
}

void gobal_cnt_list_print()
{
	int i;
	char buf[1024];

	sprintf(buf, "-----------------const------------------");
	//printf(buf);
	DebugLog(gobal_logger, __FILE__, __LINE__, buf);

	for (i = 0; i < gobal_cnt_index; i++)
	{
		sprintf(buf, "[%04X] $%s$ = %04X", i, gobal_cnt_list[i].name, gobal_cnt_list[i].value);
		//printf(buf);
		DebugLog(gobal_logger, __FILE__, __LINE__, buf);
	}

}
