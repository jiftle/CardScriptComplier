#pragma once

#include "lib.h"
/*
* ���ã��ʷ�������
* ���ߣ�����
* ���ڣ�2017.5.17
*/

/************************************************/
//  �ʷ�������
//  	���ã�ʶ��������ĵ��ʷ���
//  	���룺�����ķ���Դ�����ַ���
//  	�������Ԫ��(syn,token��sum)���ɵ�����
//  	      syn �ֱ���
//  	      token ���ʷ���
//  	      sum ����
/************************************************/



//ɨ�赥��
void scaner_sigle_line(const char* pbuf, int lineno);

//��ӡ�Ǻ�
void print_token(int token_type, char* token_str, int token_sum, struct Line line, int cloumn_number);
