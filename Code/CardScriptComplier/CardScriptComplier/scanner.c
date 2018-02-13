#include "scanner.h"
#include "util.h"
#include "lex_list.h"
#include "const.h"
#include "arg.h"

//1趟扫描
void scanner_first()
{
	InfoLog(gobal_logger, __FILE__, __LINE__, "the 1st scanner start");

	Node* pList = gobal_lex_LinkList_head;//跳过头指针
	Node* pHead = NULL;
	Node* pTail = NULL;
	int ret = 0;

	//跳过头指针
	if (pList->line =-1)
	{
		pList = pList->next;
	}

	//识别出每一行
	while (pList != NULL) {
		//识别出单行
		get_next_line_lex_linkList(&pList, &pHead, &pTail);

		replace_const(&pHead);//替换常量

		pList = pList->next;
	}

	InfoLog(gobal_logger, __FILE__, __LINE__, "the 1st scanner end");
}

void del_next_one_node(Node **linkList)
{
	Node* pList = *linkList;
	Node* pDel = NULL;
	Node* pNext = NULL;

	pDel = pList->next;
	

	pNext = pList->next->next;
	pNext->pre = pList;
	pList->next = pNext;
	
	free(pDel);
}

//替换常量
void replace_const(Node **linkList)
{
	Cnt cnt;
	Error error;
	int ret;
	Node* pList = *linkList;//跳过头指针
	

	while (pList != NULL) {
		//识别出单行
		if (pList->token.syn == TOKEN_DELIMITER_CNT)
		{
			ret = get_next_const(pList,&cnt,&error);

			if (lookup_cnt(cnt.name,&(cnt.value)))
			{
				ret = 0;
			}
			//------------------替换常量----------------
			//更新1个token节点，删除2个节点 #KeyBlock_INIKey#
			pList->token.syn = TOKEN_KEYWORD_ID;
			strcpy(pList->token.name,"id");
			sprintf(pList->token.token, "%02X", cnt.value);
			pList->token.sum = cnt.value;

			del_next_one_node(&pList);
			del_next_one_node(&pList);

			ret = 0;
		}



		pList = pList->next;
	}
}

//2趟扫描
void scanner_second()
{
	InfoLog(gobal_logger, __FILE__, __LINE__, "the 2nd scanner start");

	Node* pList = gobal_lex_LinkList_head;//跳过头指针
	Node* pHead = NULL;
	Node* pTail = NULL;
	int ret = 0;

	//跳过头指针
	if (pList->line = -1)
	{
		pList = pList->next;
	}

	//识别出每一行
	while (pList != NULL) {
		//识别出单行
		get_next_line_lex_linkList(&pList, &pHead, &pTail);

		replace_arg(&pHead);//替换常量

		pList = pList->next;
	}

	InfoLog(gobal_logger, __FILE__, __LINE__, "the 2nd scanner end");
}

//替换参数
void replace_arg(Node **linkList)
{
	Var var;
	Error error;
	int ret;
	Node* pList = *linkList;//跳过头指针


	while (pList != NULL) {
		//识别出单行
		if (pList->token.syn == TOKEN_DELIMITER_ARG)
		{
			ret = get_next_arg(pList, &var, &error);

			if (lookup_arg(var.name, var.value))
			{
				ret = 0;
			}
			//------------------替换常量----------------
			//更新1个token节点，删除2个节点 #KeyBlock_INIKey#
			pList->token.syn = TOKEN_KEYWORD_ID;
			strcpy(pList->token.name, "id");
			strcpy(pList->token.token,var.value);
			pList->token.sum = 0;

			del_next_one_node(&pList);
			del_next_one_node(&pList);

			ret = 0;
		}



		pList = pList->next;
	}
}