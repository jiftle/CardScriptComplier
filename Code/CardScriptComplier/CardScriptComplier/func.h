#pragma once
#include "lib.h"

//���Һ���
int look_func(char* func_name);

//���ú���
int call_func(char* func_name, char argv[][512], int argn, char* out_result, Error* error);

//==============================���ú���===================================
static char* cnt_func_name[] = {
	"SUBSTR","STRLEN","BYTLEN","STRLEFT","STRRIGHT","STRPAD"
};
static int cnt_func_name_size = 6;

void func_substr(char* data, char *start_index, char* out_data);