#pragma once
#include "lib.h"

//语法分析链表初始化
void gobal_grammar_LinkList_Init();
void gobal_grammar_LinkList_destory();
//打印
void gobal_grammar_LinkList_print();

//语义分析链表 追加节点
void gobal_grammar_LinkList_add(Grammar* pGrammar, int is_end);