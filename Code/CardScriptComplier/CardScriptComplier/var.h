#pragma once
#include "lib.h"

//初始化
void gobal_var_init();
void gobal_var_add(char* name, char* value);
//查变量表
int lookup_var(char* name, Var* var);
//打印参数列表
void gobal_var_LinkList_print();