#pragma once
#include "lib.h"


//�ʷ����������ʼ��
void lex_LinkList_Init();
void lex_LinkList_destory();

void lex_list_merge_node();

//��ӡ�ʷ��������
void lex_LinkList_print();


//�õ��ʷ����������һ��
void get_next_line_lex_linkList(Node** linkList, Node** pHead_out, Node** pTail_out);