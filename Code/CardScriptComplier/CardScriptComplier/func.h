#pragma once
#include "lib.h"

//查找函数
int look_func(char* func_name);

//调用函数
int call_func(char* func_name, char argv[][512], int argn, char* out_result, Error* error);

//==============================内置函数===================================
static char* cnt_func_name[] = {
	"SUBSTR","STRLEN","BYTLEN","STRLEFT","STRRIGHT","STRPAD"
};
static int cnt_func_name_size = 6;

void func_substr(char* data, char *start_index, char* out_data);