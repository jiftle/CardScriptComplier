#pragma once
#include "lib.h"


//词法分析链表初始化
void lex_LinkList_Init();
void lex_LinkList_destory();

void lex_list_merge_node();

//打印词法分析结果
void lex_LinkList_print();


//得到词法分析结果下一行
void get_next_line_lex_linkList(Node** linkList, Node** pHead_out, Node** pTail_out);