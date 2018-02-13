#include "func.h"
#include "util.h"

//���Һ���
int look_func(char* func_name)
{
	int i;

	for (i = 0; i < cnt_func_name_size; i++)
	{
		//��Сд������
		if (strcasecmp(func_name, cnt_func_name[i]) == 0) {
			return 1;
		}
	}

	return 0;
}

//���ú���
int call_func(char* func_name, char argv[][512],int argn, char* out_result, Error* error)
{
	//printf("%s\n", argv[0]);
	if (strcasecmp(func_name,"substr") == 0)
	{
		char data[1024] = {0};
		char start_index[4] = {0};

		strcpy(data, argv[0]);
		strcpy(start_index, argv[1]);
		
		func_substr(data, start_index, out_result);
	}
	else {
		//...
	}

	return 0;
}

//---------------------���ú���ʵ��-----------------------------------
void func_substr(char* data, char *start_index,char* out_data)
{
	int start;
	start = atoi(start_index);

	substring_2arg(data, start, out_data);
}
