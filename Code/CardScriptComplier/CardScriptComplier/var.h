#pragma once
#include "lib.h"

//��ʼ��
void gobal_var_init();
void gobal_var_add(char* name, char* value);
//�������
int lookup_var(char* name, Var* var);
//��ӡ�����б�
void gobal_var_LinkList_print();