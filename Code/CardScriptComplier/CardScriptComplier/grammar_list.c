#include "grammar_list.h"



//语法分析链表初始化
void gobal_grammar_LinkList_Init()
{
	Grammar* p = (Grammar*)malloc(sizeof(Grammar));
	if (p == NULL)
	{
		printf("malloc fail");
		return;
	}

	p->endflag = -1;
	p->node.line = -1;
	p->node.column = -1;
	p->node.token.syn = -1;
	strcpy(p->node.token.name, "");
	strcpy(p->node.token.token, "");
	p->node.token.sum = -1;
	p->node.pre = NULL;
	p->node.next = NULL;

	p->pre = NULL;
	p->next = NULL;

	gobal_grammar_LinkList_head = p;
	gobal_grammar_LinkList_tail = p;
	gobal_grammar_LinkList_cur = p;

	gobal_grammar_LinkList_size = 0;
}


void gobal_grammar_LinkList_destory()
{
	Grammar *p = gobal_grammar_LinkList_tail;
	Grammar *pTmp = NULL;

	while (p != NULL)
	{
		pTmp = p->pre;
		free(p);

		p = pTmp;
	}

	gobal_grammar_LinkList_head = NULL;
	gobal_grammar_LinkList_tail = NULL;
	gobal_grammar_LinkList_cur = NULL;
	gobal_grammar_LinkList_size = 0;
}

//语义分析链表 追加节点
void gobal_grammar_LinkList_add(Grammar* pGrammar, int is_end)
{
	char buf[1024] = { 0 };
	Grammar* p = NULL;

	//分配新的节点
	p = (Grammar*)malloc(sizeof(Grammar));
	if (p == NULL)
	{
		printf("malloc fail");
		return;
	}

	p->node.line = pGrammar->node.line;
	p->node.column = pGrammar->node.column;
	p->node.token.syn = pGrammar->node.token.syn;
	strcpy(p->node.token.name, pGrammar->node.token.name);
	get_token_str(p->node.token.syn, p->node.token.name);
	strcpy(p->node.token.token, pGrammar->node.token.token);
	p->node.token.sum = -1;
	p->node.pre = NULL;
	p->node.next = NULL;
	p->endflag = is_end;

	p->pre = gobal_grammar_LinkList_tail;
	p->next = NULL;

	gobal_grammar_LinkList_tail->next = p;
	gobal_grammar_LinkList_tail = p;
	gobal_grammar_LinkList_cur = p;
	gobal_grammar_LinkList_size++;

	if (gobal_grammar_LinkList_size > 21)
	{
		gobal_grammar_LinkList_size = gobal_grammar_LinkList_size;
	}

	sprintf(buf, "debug grammar (%s)\n", p->node.token.token);
	printf(buf);
}

//打印
void gobal_grammar_LinkList_print()
{
	Grammar *p = gobal_grammar_LinkList_head;
	char buf[1024] = {0};
	int i = 0;

	sprintf(buf, "-----------------grmammar list------------------");
	DebugLog(gobal_logger, __FILE__, __LINE__, buf);

	p = p->next;

	
	while (p != NULL)
	{
		/*if (i > 21)
		{
			p = p;
		}*/
		
		memset(buf,0,sizeof(buf));
		sprintf(buf, "ln %d col %d ,%s %s",p->node.line,p->node.column,p->node.token.name,p->node.token.token);
		DebugLog(gobal_logger, __FILE__, __LINE__, buf);

		p = p->next;
		i++;
	}


}