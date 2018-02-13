#include "lex_list.h"


//词法分析链表初始化
void lex_LinkList_Init() {
	struct Node* pnode = (Node*)malloc(sizeof(struct Node));
	if (pnode == NULL) {
		printf("malloc fail.");
		return;
	}

	pnode->token.syn = -1;
	strcpy(pnode->token.token, "");
	strcpy(pnode->token.name, "");
	pnode->token.sum = -1;
	pnode->line = -1;
	pnode->column = -1;

	pnode->pre = NULL;
	pnode->next = NULL;

	gobal_lex_LinkList_head = pnode;
	gobal_lex_LinkList_tail = pnode;
}


void lex_LinkList_destory()
{
	Node *p = gobal_lex_LinkList_tail;
	Node *pTmp = NULL;

	while (p != NULL)
	{
		pTmp = p->pre;
		free(p);

		p = pTmp;
	}

	gobal_lex_LinkList_head = NULL;
	gobal_lex_LinkList_tail = NULL;
}

//打印词法分析结果链表
void lex_LinkList_print() {
	Node *p = gobal_lex_LinkList_head;
	FILE* file = NULL;
	char filename[] = {"tmp_lex.txt"};
	char bufdebug[1024] = { 0 };
	p = p->next;

	InfoLog(gobal_logger, __FILE__, __LINE__, "--------------token list-------------");


	//输出到文件
	//从文件中读取
	file = fopen(filename, "w+");
	if (!file)
	{
		ErrorLog(gobal_logger, __FILE__, __LINE__, "create file fail,filename: %s", filename);
		return;
	}

	while (p != NULL) {
		char buf[1024] = { 0 };
		sprintf(buf, "(%d,%s)\n", p->token.syn, p->token.token);

		//输出到控制台
		//printf(buf);

		sprintf(bufdebug, "ln:%d col:%d (%d,%s,%d) type:%s"
			, p->line, p->column, p->token.syn, p->token.token, p->token.sum, p->token.name);

		InfoLog(gobal_logger, __FILE__, __LINE__, bufdebug);

		fputs(buf, file);

		p = p->next;
	}

	fclose(file);

}

void lex_list_merge_node()
{
	InfoLog(gobal_logger, __FILE__, __LINE__, "the lex merge duplication node start");

	//合并重复的ID节点
	Node *pList = gobal_lex_LinkList_head;
	Node *pNext = NULL;
	Node *p = pList;

	pList = pList->next;

	while (p != NULL)
	{
		if (p->next == NULL)
		{
			break;;
		}
		pNext = p->next->next;

		if (p->token.syn == TOKEN_KEYWORD_ID && p->next->token.syn == TOKEN_KEYWORD_ID)
		{
			//id 合并
			strcat(p->token.token, " ");
			strcat(p->token.token, p->next->token.token);

			//删除节点
			free(p->next);
			pNext->pre = p;
			p->next = pNext;
		}
		else {
			p = p->next;
		}
	}

	InfoLog(gobal_logger, __FILE__, __LINE__, "the lex merge duplication node end");
}

//得到词法分析结果下一行
void get_next_line_lex_linkList(Node** linkList, Node** pHead_out, Node** pTail_out)
{
	Node* pList = *linkList;
	Node* pHead = NULL;
	Node* pTail = NULL;

	//识别出每一行
	pHead = pList;
	while (pList != NULL && pList->token.syn != TOKEN_KEYWORD_CRLF) {


		pList = pList->next;
	}
	pTail = pList;

	//返回
	*pHead_out = pHead;
	*pTail_out = pTail;

	*linkList = pList;
}