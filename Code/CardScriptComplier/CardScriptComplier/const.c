#include "const.h"

void gobal_cnt_list_init()
{
	gobal_cnt_index = 0;
	gobal_cnt_list_add("KeyBlock_MaskKey", 2);//����Կ�洢��ʼ����
	gobal_cnt_list_add("KeyBlock_PSAMKey", 102);//PSAMĸ����Կ�洢��ʼ����
	gobal_cnt_list_add("KeyBlock_INIKey", 202);//ϴ��ĸ����Կ�洢��ʼ����
	gobal_cnt_list_add("KeyBlock_CITYKey", 40);//CPU��ͻ��� ������Կ

											   //---------------------------------
	gobal_cnt_list_add("KeyIndex_CCK", 0);//��Ƭ����
	gobal_cnt_list_add("KeyIndex_CMK", 1);//��Ƭά��
	gobal_cnt_list_add("KeyIndex_ACK", 2);//Ӧ������
	gobal_cnt_list_add("KeyIndex_AMK", 3);//Ӧ��ά��
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
		//��Сд������
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
