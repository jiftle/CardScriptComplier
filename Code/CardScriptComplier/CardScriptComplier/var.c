#include "var.h"


//初始化
void gobal_var_init()
{
	int i;
	gobal_var_index = 0;
	
	for (i =0;i<GOBAL_VAR_SIZE;i++)
	{
		//填表
		strcpy(gobal_var[i].name, "");
		strcpy(gobal_var[i].value, "");
	}
}

void gobal_var_add(char* name, char* value)
{
	int i;
	for (i = 0; i < GOBAL_VAR_SIZE; i++)
	{
		if (strcmp(name, gobal_var[i].name) == 0)
		{
			strcpy(gobal_var[i].name,name);
			strcpy(gobal_var[i].value,value);
			
			return;
		}
	}

	//填表
	strcpy(gobal_var[gobal_var_index].name, name);
	strcpy(gobal_var[gobal_var_index].value, value);
	gobal_var_index++;
}

//查变量表
int lookup_var(char* name, Var* var)
{
	int i;
	for (i = 0; i < GOBAL_VAR_SIZE; i++)
	{
		if (strcmp(name, gobal_var[i].name) == 0)
		{
			strcpy(var->name, gobal_var[i].name);
			strcpy(var->value, gobal_var[i].value);
			return 1;
		}
	}

	return 0;
}

//打印参数列表
void gobal_var_LinkList_print()
{
	int i;
	char buf[1024];

	sprintf(buf, "-----------------runtime var------------------");
	DebugLog(gobal_logger, __FILE__, __LINE__, buf);

	for (i = 0; i < gobal_var_index; i++)
	{
		sprintf(buf, "[%04X] {%s} = %s", i, gobal_var[i].name, gobal_var[i].value);
		DebugLog(gobal_logger, __FILE__, __LINE__, buf);
	}

}