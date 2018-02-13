#include "scanner.h"
#include "util.h"
#include "lex_list.h"
#include "const.h"
#include "arg.h"

//1��ɨ��
void scanner_first()
{
	InfoLog(gobal_logger, __FILE__, __LINE__, "the 1st scanner start");

	Node* pList = gobal_lex_LinkList_head;//����ͷָ��
	Node* pHead = NULL;
	Node* pTail = NULL;
	int ret = 0;

	//����ͷָ��
	if (pList->line =-1)
	{
		pList = pList->next;
	}

	//ʶ���ÿһ��
	while (pList != NULL) {
		//ʶ�������
		get_next_line_lex_linkList(&pList, &pHead, &pTail);

		replace_const(&pHead);//�滻����

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

//�滻����
void replace_const(Node **linkList)
{
	Cnt cnt;
	Error error;
	int ret;
	Node* pList = *linkList;//����ͷָ��
	

	while (pList != NULL) {
		//ʶ�������
		if (pList->token.syn == TOKEN_DELIMITER_CNT)
		{
			ret = get_next_const(pList,&cnt,&error);

			if (lookup_cnt(cnt.name,&(cnt.value)))
			{
				ret = 0;
			}
			//------------------�滻����----------------
			//����1��token�ڵ㣬ɾ��2���ڵ� #KeyBlock_INIKey#
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

//2��ɨ��
void scanner_second()
{
	InfoLog(gobal_logger, __FILE__, __LINE__, "the 2nd scanner start");

	Node* pList = gobal_lex_LinkList_head;//����ͷָ��
	Node* pHead = NULL;
	Node* pTail = NULL;
	int ret = 0;

	//����ͷָ��
	if (pList->line = -1)
	{
		pList = pList->next;
	}

	//ʶ���ÿһ��
	while (pList != NULL) {
		//ʶ�������
		get_next_line_lex_linkList(&pList, &pHead, &pTail);

		replace_arg(&pHead);//�滻����

		pList = pList->next;
	}

	InfoLog(gobal_logger, __FILE__, __LINE__, "the 2nd scanner end");
}

//�滻����
void replace_arg(Node **linkList)
{
	Var var;
	Error error;
	int ret;
	Node* pList = *linkList;//����ͷָ��


	while (pList != NULL) {
		//ʶ�������
		if (pList->token.syn == TOKEN_DELIMITER_ARG)
		{
			ret = get_next_arg(pList, &var, &error);

			if (lookup_arg(var.name, var.value))
			{
				ret = 0;
			}
			//------------------�滻����----------------
			//����1��token�ڵ㣬ɾ��2���ڵ� #KeyBlock_INIKey#
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