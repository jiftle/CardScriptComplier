#pragma once
#include "lib.h"



void gobal_arg_LinkList_init();
void gobal_arg_LinkList_add(char* name, char* value);
int gobal_arg_LinkList_get(char* name, char* value);
int lookup_arg(char* name, char* value);

//��ӡ�����б�
void gobal_arg_LinkList_print();